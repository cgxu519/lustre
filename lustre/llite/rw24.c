/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-
 * vim:expandtab:shiftwidth=8:tabstop=8:
 *
 * Lustre Lite I/O page cache for the 2.4 kernel version
 *
 *  Copyright (c) 2001-2003 Cluster File Systems, Inc.
 *
 *   This file is part of Lustre, http://www.lustre.org.
 *
 *   Lustre is free software; you can redistribute it and/or
 *   modify it under the terms of version 2 of the GNU General Public
 *   License as published by the Free Software Foundation.
 *
 *   Lustre is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Lustre; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/string.h>
#include <linux/stat.h>
#include <linux/errno.h>
#include <linux/smp_lock.h>
#include <linux/unistd.h>
#include <linux/version.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#include <linux/fs.h>
#include <linux/iobuf.h>
#include <linux/stat.h>
#include <asm/uaccess.h>
#include <asm/segment.h>
#include <linux/mm.h>
#include <linux/pagemap.h>
#include <linux/smp_lock.h>

#define DEBUG_SUBSYSTEM S_LLITE

#include <linux/lustre_mds.h>
#include <linux/lustre_lite.h>
#include "llite_internal.h"
#include <linux/lustre_compat25.h>

/* called as the osc engine completes an rpc that included our ocp.  
 * the ocp itself holds a reference to the page and will drop it when
 * the page is removed from the page cache.  our job is simply to
 * transfer rc into the page and unlock it */
void ll_complete_writepage_24(struct obd_client_page *ocp, int rc)
{
        struct page *page = ocp->ocp_page;

        LASSERT(page->private == (unsigned long)ocp);
        LASSERT(PageLocked(page));

        if (rc != 0) {
                CERROR("writeback error on page %p index %ld: %d\n", page,
                       page->index, rc);
                SetPageError(page);
        }
        ocp->ocp_flags &= ~OCP_IO_READY;
        unlock_page(page);
        page_cache_release(page);
}

static int ll_writepage_24(struct page *page)
{
        struct obd_client_page *ocp;
        ENTRY;

        LASSERT(!PageDirty(page));
        LASSERT(PageLocked(page));
        LASSERT(page->private != 0);

        ocp = (struct obd_client_page *)page->private;
        ocp->ocp_flags |= OCP_IO_READY;
        page_cache_get(page);

        /* sadly, not all callers who writepage eventually call sync_page
         * (ahem, kswapd) so we need to raise this page's priority 
         * immediately */
        RETURN(ll_sync_page(page));
}

static int ll_direct_IO_24(int rw, struct inode *inode, struct kiobuf *iobuf,
                           unsigned long blocknr, int blocksize)
{
        struct ll_inode_info *lli = ll_i2info(inode);
        struct lov_stripe_md *lsm = lli->lli_smd;
        struct brw_page *pga;
        struct ptlrpc_request_set *set;
        struct obdo oa;
        int length, i, flags, rc = 0;
        loff_t offset;
        ENTRY;

        if (!lsm || !lsm->lsm_object_id)
                RETURN(-EBADF);

        /* FIXME: io smaller than PAGE_SIZE is broken on ia64 */
        if ((iobuf->offset & (PAGE_SIZE - 1)) ||
            (iobuf->length & (PAGE_SIZE - 1)))
                RETURN(-EINVAL);

        set = ptlrpc_prep_set();
        if (set == NULL)
                RETURN(-ENOMEM);

        OBD_ALLOC(pga, sizeof(*pga) * iobuf->nr_pages);
        if (!pga) {
                ptlrpc_set_destroy(set);
                RETURN(-ENOMEM);
        }

        flags = (rw == WRITE ? OBD_BRW_CREATE : 0) /* | OBD_BRW_DIRECTIO */;
        offset = ((obd_off)blocknr << inode->i_blkbits);
        length = iobuf->length;

        for (i = 0, length = iobuf->length; length > 0;
             length -= pga[i].count, offset += pga[i].count, i++) { /*i last!*/
                pga[i].pg = iobuf->maplist[i];
                pga[i].off = offset;
                /* To the end of the page, or the length, whatever is less */
                pga[i].count = min_t(int, PAGE_SIZE - (offset & ~PAGE_MASK),
                                     length);
                pga[i].flag = flags;
                if (rw == READ) {
                        //POISON(kmap(iobuf->maplist[i]), 0xc5, PAGE_SIZE);
                        //kunmap(iobuf->maplist[i]);
                }
        }

        oa.o_id = lsm->lsm_object_id;
        oa.o_valid = OBD_MD_FLID;
        obdo_from_inode(&oa, inode, OBD_MD_FLTYPE | OBD_MD_FLATIME |
                                    OBD_MD_FLMTIME | OBD_MD_FLCTIME);

        if (rw == WRITE)
                lprocfs_counter_add(ll_i2sbi(inode)->ll_stats,
                                    LPROC_LL_DIRECT_WRITE, iobuf->length);
        else
                lprocfs_counter_add(ll_i2sbi(inode)->ll_stats,
                                    LPROC_LL_DIRECT_READ, iobuf->length);
        rc = obd_brw_async(rw == WRITE ? OBD_BRW_WRITE : OBD_BRW_READ,
                           ll_i2obdexp(inode), &oa, lsm, iobuf->nr_pages, pga,
                           set, NULL);
        if (rc) {
                CDEBUG(rc == -ENOSPC ? D_INODE : D_ERROR,
                       "error from obd_brw_async: rc = %d\n", rc);
        } else {
                rc = ptlrpc_set_wait(set);
                if (rc)
                        CERROR("error from callback: rc = %d\n", rc);
        }
        ptlrpc_set_destroy(set);
        if (rc == 0)
                rc = iobuf->length;

        OBD_FREE(pga, sizeof(*pga) * iobuf->nr_pages);
        RETURN(rc);
}

struct address_space_operations ll_aops = {
        readpage: ll_readpage,
        direct_IO: ll_direct_IO_24,
        writepage: ll_writepage_24,
/* we shouldn't use this until we have a better story about sync_page
 * and writepage completion racing.  also, until we differentiate between 
 * writepage and syncpage it seems of little value to raise the priority
 * twice*/
//        sync_page: ll_sync_page,
        prepare_write: ll_prepare_write,
        commit_write: ll_commit_write,
        removepage: ll_removepage,
        bmap: NULL
};
