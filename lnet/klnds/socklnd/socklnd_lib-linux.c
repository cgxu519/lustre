/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-
 * vim:expandtab:shiftwidth=8:tabstop=8:
 *
 * GPL HEADER START
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 only,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License version 2 for more details (a copy is included
 * in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; If not, see
 * http://www.sun.com/software/products/lustre/docs/GPLv2.pdf
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 *
 * GPL HEADER END
 */
/*
 * Copyright  2008 Sun Microsystems, Inc. All rights reserved
 * Use is subject to license terms.
 */
/*
 * This file is part of Lustre, http://www.lustre.org/
 * Lustre is a trademark of Sun Microsystems, Inc.
 */

#include "socklnd.h"

# if defined(CONFIG_SYSCTL) && !CFS_SYSFS_MODULE_PARM
static cfs_sysctl_table_t ksocknal_ctl_table[21];

cfs_sysctl_table_t ksocknal_top_ctl_table[] = {
        {
                .ctl_name = 200,
                .procname = "socknal",
                .data     = NULL,
                .maxlen   = 0,
                .mode     = 0555,
                .child    = ksocknal_ctl_table
        },
        { 0 }
};

int
ksocknal_lib_tunables_init ()
{
        int    i = 0;
        int    j = 1;

        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "timeout",
                .data     = ksocknal_tunables.ksnd_timeout,
                .maxlen   = sizeof (int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "credits",
                .data     = ksocknal_tunables.ksnd_credits,
                .maxlen   = sizeof (int),
                .mode     = 0444,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "peer_credits",
                .data     = ksocknal_tunables.ksnd_peercredits,
                .maxlen   = sizeof (int),
                .mode     = 0444,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "nconnds",
                .data     = ksocknal_tunables.ksnd_nconnds,
                .maxlen   = sizeof (int),
                .mode     = 0444,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "min_reconnectms",
                .data     = ksocknal_tunables.ksnd_min_reconnectms,
                .maxlen   = sizeof (int),
                .mode     = 0444,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "max_reconnectms",
                .data     = ksocknal_tunables.ksnd_max_reconnectms,
                .maxlen   = sizeof (int),
                .mode     = 0444,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "eager_ack",
                .data     = ksocknal_tunables.ksnd_eager_ack,
                .maxlen   = sizeof (int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "zero_copy",
                .data     = ksocknal_tunables.ksnd_zc_min_frag,
                .maxlen   = sizeof (int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "typed",
                .data     = ksocknal_tunables.ksnd_typed_conns,
                .maxlen   = sizeof (int),
                .mode     = 0444,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "min_bulk",
                .data     = ksocknal_tunables.ksnd_min_bulk,
                .maxlen   = sizeof (int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "rx_buffer_size",
                .data     = ksocknal_tunables.ksnd_rx_buffer_size,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "tx_buffer_size",
                .data     = ksocknal_tunables.ksnd_tx_buffer_size,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "nagle",
                .data     = ksocknal_tunables.ksnd_nagle,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
#ifdef CPU_AFFINITY
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "irq_affinity",
                .data     = ksocknal_tunables.ksnd_irq_affinity,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
#endif
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "keepalive_idle",
                .data     = ksocknal_tunables.ksnd_keepalive_idle,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "keepalive_count",
                .data     = ksocknal_tunables.ksnd_keepalive_count,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "keepalive_intvl",
                .data     = ksocknal_tunables.ksnd_keepalive_intvl,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
#ifdef SOCKNAL_BACKOFF
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "backoff_init",
                .data     = ksocknal_tunables.ksnd_backoff_init,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "backoff_max",
                .data     = ksocknal_tunables.ksnd_backoff_max,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
#endif
#if SOCKNAL_VERSION_DEBUG
        ksocknal_ctl_table[i++] = (cfs_sysctl_table_t) {
                .ctl_name = j++,
                .procname = "protocol",
                .data     = ksocknal_tunables.ksnd_protocol,
                .maxlen   = sizeof(int),
                .mode     = 0644,
                .proc_handler = &proc_dointvec
        };
#endif
        ksocknal_ctl_table[i++] =  (cfs_sysctl_table_t) { 0 };

        LASSERT (j == i);
        LASSERT (i <= sizeof(ksocknal_ctl_table)/sizeof(ksocknal_ctl_table[0]));

        ksocknal_tunables.ksnd_sysctl =
                cfs_register_sysctl_table(ksocknal_top_ctl_table, 0);

        if (ksocknal_tunables.ksnd_sysctl == NULL)
                CWARN("Can't setup /proc tunables\n");

        return 0;
}

void
ksocknal_lib_tunables_fini ()
{
        if (ksocknal_tunables.ksnd_sysctl != NULL)
                cfs_unregister_sysctl_table(ksocknal_tunables.ksnd_sysctl);
}
#else
int
ksocknal_lib_tunables_init ()
{
        return 0;
}

void
ksocknal_lib_tunables_fini ()
{
}
#endif /* # if CONFIG_SYSCTL && !CFS_SYSFS_MODULE_PARM */

void
ksocknal_lib_bind_irq (unsigned int irq)
{
#if (defined(CONFIG_SMP) && defined(CPU_AFFINITY))
        int              bind;
        int              cpu;
        char             cmdline[64];
        ksock_irqinfo_t *info;
        char            *argv[] = {"/bin/sh",
                                   "-c",
                                   cmdline,
                                   NULL};
        char            *envp[] = {"HOME=/",
                                   "PATH=/sbin:/bin:/usr/sbin:/usr/bin",
                                   NULL};

        LASSERT (irq < NR_IRQS);
        if (irq == 0)              /* software NIC or affinity disabled */
                return;

        info = &ksocknal_data.ksnd_irqinfo[irq];

        write_lock_bh (&ksocknal_data.ksnd_global_lock);

        LASSERT (info->ksni_valid);
        bind = !info->ksni_bound;
        info->ksni_bound = 1;

        write_unlock_bh (&ksocknal_data.ksnd_global_lock);

        if (!bind)                              /* bound already */
                return;

        cpu = ksocknal_irqsched2cpu(info->ksni_sched);
        snprintf (cmdline, sizeof (cmdline),
                  "echo %d > /proc/irq/%u/smp_affinity", 1 << cpu, irq);

        LCONSOLE_INFO("Binding irq %u to CPU %d with cmd: %s\n",
                      irq, cpu, cmdline);

        /* FIXME: Find a better method of setting IRQ affinity...
         */

        USERMODEHELPER(argv[0], argv, envp);
#endif
}

int
ksocknal_lib_get_conn_addrs (ksock_conn_t *conn)
{
        int rc = libcfs_sock_getaddr(conn->ksnc_sock, 1,
                                     &conn->ksnc_ipaddr,
                                     &conn->ksnc_port);

        /* Didn't need the {get,put}connsock dance to deref ksnc_sock... */
        LASSERT (!conn->ksnc_closing);

        if (rc != 0) {
                CERROR ("Error %d getting sock peer IP\n", rc);
                return rc;
        }

        rc = libcfs_sock_getaddr(conn->ksnc_sock, 0,
                                 &conn->ksnc_myipaddr, NULL);
        if (rc != 0) {
                CERROR ("Error %d getting sock local IP\n", rc);
                return rc;
        }

        return 0;
}

unsigned int
ksocknal_lib_sock_irq (struct socket *sock)
{
        int                irq = 0;
#ifdef CPU_AFFINITY
        struct dst_entry  *dst;

        if (!*ksocknal_tunables.ksnd_irq_affinity)
                return 0;

        dst = sk_dst_get (sock->sk);
        if (dst != NULL) {
                if (dst->dev != NULL) {
                        irq = dst->dev->irq;
                        if (irq >= NR_IRQS) {
                                CERROR ("Unexpected IRQ %x\n", irq);
                                irq = 0;
                        }
                }
                dst_release (dst);
        }

#endif
        return irq;
}

int
ksocknal_lib_zc_capable(struct socket *sock)
{
        int  caps = sock->sk->sk_route_caps;

        /* ZC if the socket supports scatter/gather and doesn't need software
         * checksums */
        return ((caps & NETIF_F_SG) != 0 &&
                (caps & (NETIF_F_IP_CSUM | NETIF_F_NO_CSUM | NETIF_F_HW_CSUM)) != 0);
}

int
ksocknal_lib_send_iov (ksock_conn_t *conn, ksock_tx_t *tx)
{
        struct socket *sock = conn->ksnc_sock;
        int            nob;
        int            rc;

        if (*ksocknal_tunables.ksnd_enable_csum        && /* checksum enabled */
            conn->ksnc_proto == &ksocknal_protocol_v2x && /* V2.x connection  */
            tx->tx_nob == tx->tx_resid                 && /* frist sending    */
            tx->tx_msg.ksm_csum == 0)                     /* not checksummed  */
                ksocknal_lib_csum_tx(tx);

        /* NB we can't trust socket ops to either consume our iovs
         * or leave them alone. */

        {
#if SOCKNAL_SINGLE_FRAG_TX
                struct iovec    scratch;
                struct iovec   *scratchiov = &scratch;
                unsigned int    niov = 1;
#else
                struct iovec   *scratchiov = conn->ksnc_tx_scratch_iov;
                unsigned int    niov = tx->tx_niov;
#endif
                struct msghdr msg = {
                        .msg_name       = NULL,
                        .msg_namelen    = 0,
                        .msg_iov        = scratchiov,
                        .msg_iovlen     = niov,
                        .msg_control    = NULL,
                        .msg_controllen = 0,
                        .msg_flags      = MSG_DONTWAIT
                };
                mm_segment_t oldmm = get_fs();
                int  i;

                for (nob = i = 0; i < niov; i++) {
                        scratchiov[i] = tx->tx_iov[i];
                        nob += scratchiov[i].iov_len;
                }

                if (!list_empty(&conn->ksnc_tx_queue) ||
                    nob < tx->tx_resid)
                        msg.msg_flags |= MSG_MORE;

                set_fs (KERNEL_DS);
                rc = sock_sendmsg(sock, &msg, nob);
                set_fs (oldmm);
        }
        return rc;
}

int
ksocknal_lib_send_kiov (ksock_conn_t *conn, ksock_tx_t *tx)
{
        struct socket *sock = conn->ksnc_sock;
        lnet_kiov_t    *kiov = tx->tx_kiov;
        int            rc;
        int            nob;

        /* NB we can't trust socket ops to either consume our iovs
         * or leave them alone. */

        if (kiov->kiov_len >= *ksocknal_tunables.ksnd_zc_min_frag &&
            tx->tx_msg.ksm_zc_req_cookie != 0) {
                /* Zero copy is enabled */
                struct sock   *sk = sock->sk;
                struct page   *page = kiov->kiov_page;
                int            offset = kiov->kiov_offset;
                int            fragsize = kiov->kiov_len;
                int            msgflg = MSG_DONTWAIT;

                CDEBUG(D_NET, "page %p + offset %x for %d\n",
                               page, offset, kiov->kiov_len);

                if (!list_empty(&conn->ksnc_tx_queue) ||
                    fragsize < tx->tx_resid)
                        msgflg |= MSG_MORE;

                if (sk->sk_prot->sendpage != NULL) {
                        rc = sk->sk_prot->sendpage(sk, page,
                                                   offset, fragsize, msgflg);
                } else {
                        rc = tcp_sendpage(sock, page, offset, fragsize, msgflg);
                }
        } else {
#if SOCKNAL_SINGLE_FRAG_TX || !SOCKNAL_RISK_KMAP_DEADLOCK
                struct iovec  scratch;
                struct iovec *scratchiov = &scratch;
                unsigned int  niov = 1;
#else
#ifdef CONFIG_HIGHMEM
#warning "XXX risk of kmap deadlock on multiple frags..."
#endif
                struct iovec *scratchiov = conn->ksnc_tx_scratch_iov;
                unsigned int  niov = tx->tx_nkiov;
#endif
                struct msghdr msg = {
                        .msg_name       = NULL,
                        .msg_namelen    = 0,
                        .msg_iov        = scratchiov,
                        .msg_iovlen     = niov,
                        .msg_control    = NULL,
                        .msg_controllen = 0,
                        .msg_flags      = MSG_DONTWAIT
                };
                mm_segment_t  oldmm = get_fs();
                int           i;

                for (nob = i = 0; i < niov; i++) {
                        scratchiov[i].iov_base = kmap(kiov[i].kiov_page) +
                                                 kiov[i].kiov_offset;
                        nob += scratchiov[i].iov_len = kiov[i].kiov_len;
                }

                if (!list_empty(&conn->ksnc_tx_queue) ||
                    nob < tx->tx_resid)
                        msg.msg_flags |= MSG_MORE;

                set_fs (KERNEL_DS);
                rc = sock_sendmsg(sock, &msg, nob);
                set_fs (oldmm);

                for (i = 0; i < niov; i++)
                        kunmap(kiov[i].kiov_page);
        }
        return rc;
}

void
ksocknal_lib_eager_ack (ksock_conn_t *conn)
{
        int            opt = 1;
        mm_segment_t   oldmm = get_fs();
        struct socket *sock = conn->ksnc_sock;

        /* Remind the socket to ACK eagerly.  If I don't, the socket might
         * think I'm about to send something it could piggy-back the ACK
         * on, introducing delay in completing zero-copy sends in my
         * peer. */

        set_fs(KERNEL_DS);
        sock->ops->setsockopt (sock, SOL_TCP, TCP_QUICKACK,
                               (char *)&opt, sizeof (opt));
        set_fs(oldmm);
}

int
ksocknal_lib_recv_iov (ksock_conn_t *conn)
{
#if SOCKNAL_SINGLE_FRAG_RX
        struct iovec  scratch;
        struct iovec *scratchiov = &scratch;
        unsigned int  niov = 1;
#else
        struct iovec *scratchiov = conn->ksnc_rx_scratch_iov;
        unsigned int  niov = conn->ksnc_rx_niov;
#endif
        struct iovec *iov = conn->ksnc_rx_iov;
        struct msghdr msg = {
                .msg_name       = NULL,
                .msg_namelen    = 0,
                .msg_iov        = scratchiov,
                .msg_iovlen     = niov,
                .msg_control    = NULL,
                .msg_controllen = 0,
                .msg_flags      = 0
        };
        mm_segment_t oldmm = get_fs();
        int          nob;
        int          i;
        int          rc;
        int          fragnob;
        int          sum;
        __u32        saved_csum;

        /* NB we can't trust socket ops to either consume our iovs
         * or leave them alone. */
        LASSERT (niov > 0);

        for (nob = i = 0; i < niov; i++) {
                scratchiov[i] = iov[i];
                nob += scratchiov[i].iov_len;
        }
        LASSERT (nob <= conn->ksnc_rx_nob_wanted);

        set_fs (KERNEL_DS);
        rc = sock_recvmsg (conn->ksnc_sock, &msg, nob, MSG_DONTWAIT);
        /* NB this is just a boolean..........................^ */
        set_fs (oldmm);

        saved_csum = 0;
        if (conn->ksnc_proto == &ksocknal_protocol_v2x) {
                saved_csum = conn->ksnc_msg.ksm_csum;
                conn->ksnc_msg.ksm_csum = 0;
        }

        if (saved_csum != 0) {
                /* accumulate checksum */
                for (i = 0, sum = rc; sum > 0; i++, sum -= fragnob) {
                        LASSERT (i < niov);

                        fragnob = iov[i].iov_len;
                        if (fragnob > sum)
                                fragnob = sum;

                        conn->ksnc_rx_csum = ksocknal_csum(conn->ksnc_rx_csum,
                                                           iov[i].iov_base, fragnob);
                }
                conn->ksnc_msg.ksm_csum = saved_csum;
        }

        return rc;
}

int
ksocknal_lib_recv_kiov (ksock_conn_t *conn)
{
#if SOCKNAL_SINGLE_FRAG_RX || !SOCKNAL_RISK_KMAP_DEADLOCK
        struct iovec  scratch;
        struct iovec *scratchiov = &scratch;
        unsigned int  niov = 1;
#else
#ifdef CONFIG_HIGHMEM
#warning "XXX risk of kmap deadlock on multiple frags..."
#endif
        struct iovec *scratchiov = conn->ksnc_rx_scratch_iov;
        unsigned int  niov = conn->ksnc_rx_nkiov;
#endif
        lnet_kiov_t   *kiov = conn->ksnc_rx_kiov;
        struct msghdr msg = {
                .msg_name       = NULL,
                .msg_namelen    = 0,
                .msg_iov        = scratchiov,
                .msg_iovlen     = niov,
                .msg_control    = NULL,
                .msg_controllen = 0,
                .msg_flags      = 0
        };
        mm_segment_t oldmm = get_fs();
        int          nob;
        int          i;
        int          rc;
        void        *base;
        int          sum;
        int          fragnob;

        /* NB we can't trust socket ops to either consume our iovs
         * or leave them alone. */
        for (nob = i = 0; i < niov; i++) {
                scratchiov[i].iov_base = kmap(kiov[i].kiov_page) + kiov[i].kiov_offset;
                nob += scratchiov[i].iov_len = kiov[i].kiov_len;
        }
        LASSERT (nob <= conn->ksnc_rx_nob_wanted);

        set_fs (KERNEL_DS);
        rc = sock_recvmsg (conn->ksnc_sock, &msg, nob, MSG_DONTWAIT);
        /* NB this is just a boolean.......................^ */
        set_fs (oldmm);

        if (conn->ksnc_msg.ksm_csum != 0) {
                for (i = 0, sum = rc; sum > 0; i++, sum -= fragnob) {
                        LASSERT (i < niov);

                        /* Dang! have to kmap again because I have nowhere to stash the
                         * mapped address.  But by doing it while the page is still
                         * mapped, the kernel just bumps the map count and returns me
                         * the address it stashed. */
                        base = kmap(kiov[i].kiov_page) + kiov[i].kiov_offset;
                        fragnob = kiov[i].kiov_len;
                        if (fragnob > sum)
                                fragnob = sum;

                        conn->ksnc_rx_csum = ksocknal_csum(conn->ksnc_rx_csum,
                                                           base, fragnob);

                        kunmap(kiov[i].kiov_page);
                }
        }
        for (i = 0; i < niov; i++)
                kunmap(kiov[i].kiov_page);

        return (rc);
}

void
ksocknal_lib_csum_tx(ksock_tx_t *tx)
{
        int          i;
        __u32        csum;
        void        *base;

        LASSERT(tx->tx_iov[0].iov_base == (void *)&tx->tx_msg);
        LASSERT(tx->tx_conn != NULL);
        LASSERT(tx->tx_conn->ksnc_proto == &ksocknal_protocol_v2x);

        tx->tx_msg.ksm_csum = 0;

        csum = ksocknal_csum(~0, (void *)tx->tx_iov[0].iov_base,
                             tx->tx_iov[0].iov_len);

        if (tx->tx_kiov != NULL) {
                for (i = 0; i < tx->tx_nkiov; i++) {
                        base = kmap(tx->tx_kiov[i].kiov_page) +
                               tx->tx_kiov[i].kiov_offset;

                        csum = ksocknal_csum(csum, base, tx->tx_kiov[i].kiov_len);

                        kunmap(tx->tx_kiov[i].kiov_page);
                }
        } else {
                for (i = 1; i < tx->tx_niov; i++)
                        csum = ksocknal_csum(csum, tx->tx_iov[i].iov_base,
                                             tx->tx_iov[i].iov_len);
        }

        if (*ksocknal_tunables.ksnd_inject_csum_error) {
                csum++;
                *ksocknal_tunables.ksnd_inject_csum_error = 0;
        }

        tx->tx_msg.ksm_csum = csum;
}

int
ksocknal_lib_get_conn_tunables (ksock_conn_t *conn, int *txmem, int *rxmem, int *nagle)
{
        mm_segment_t   oldmm = get_fs ();
        struct socket *sock = conn->ksnc_sock;
        int            len;
        int            rc;

        rc = ksocknal_connsock_addref(conn);
        if (rc != 0) {
                LASSERT (conn->ksnc_closing);
                *txmem = *rxmem = *nagle = 0;
                return (-ESHUTDOWN);
        }

        rc = libcfs_sock_getbuf(sock, txmem, rxmem);
        if (rc == 0) {
                len = sizeof(*nagle);
                set_fs(KERNEL_DS);
                rc = sock->ops->getsockopt(sock, SOL_TCP, TCP_NODELAY,
                                           (char *)nagle, &len);
                set_fs(oldmm);
        }

        ksocknal_connsock_decref(conn);

        if (rc == 0)
                *nagle = !*nagle;
        else
                *txmem = *rxmem = *nagle = 0;

        return (rc);
}

int
ksocknal_lib_setup_sock (struct socket *sock)
{
        mm_segment_t    oldmm = get_fs ();
        int             rc;
        int             option;
        int             keep_idle;
        int             keep_intvl;
        int             keep_count;
        int             do_keepalive;
        struct linger   linger;

        sock->sk->sk_allocation = GFP_NOFS;

        /* Ensure this socket aborts active sends immediately when we close
         * it. */

        linger.l_onoff = 0;
        linger.l_linger = 0;

        set_fs (KERNEL_DS);
        rc = sock_setsockopt (sock, SOL_SOCKET, SO_LINGER,
                              (char *)&linger, sizeof (linger));
        set_fs (oldmm);
        if (rc != 0) {
                CERROR ("Can't set SO_LINGER: %d\n", rc);
                return (rc);
        }

        option = -1;
        set_fs (KERNEL_DS);
        rc = sock->ops->setsockopt (sock, SOL_TCP, TCP_LINGER2,
                                    (char *)&option, sizeof (option));
        set_fs (oldmm);
        if (rc != 0) {
                CERROR ("Can't set SO_LINGER2: %d\n", rc);
                return (rc);
        }

        if (!*ksocknal_tunables.ksnd_nagle) {
                option = 1;

                set_fs (KERNEL_DS);
                rc = sock->ops->setsockopt (sock, SOL_TCP, TCP_NODELAY,
                                            (char *)&option, sizeof (option));
                set_fs (oldmm);
                if (rc != 0) {
                        CERROR ("Can't disable nagle: %d\n", rc);
                        return (rc);
                }
        }

        rc = libcfs_sock_setbuf(sock,
                                *ksocknal_tunables.ksnd_tx_buffer_size,
                                *ksocknal_tunables.ksnd_rx_buffer_size);
        if (rc != 0) {
                CERROR ("Can't set buffer tx %d, rx %d buffers: %d\n",
                        *ksocknal_tunables.ksnd_tx_buffer_size,
                        *ksocknal_tunables.ksnd_rx_buffer_size, rc);
                return (rc);
        }

/* TCP_BACKOFF_* sockopt tunables unsupported in stock kernels */
#ifdef SOCKNAL_BACKOFF
        if (*ksocknal_tunables.ksnd_backoff_init > 0) {
                option = *ksocknal_tunables.ksnd_backoff_init;
#ifdef SOCKNAL_BACKOFF_MS
                option *= 1000;
#endif

                set_fs (KERNEL_DS);
                rc = sock->ops->setsockopt (sock, SOL_TCP, TCP_BACKOFF_INIT,
                                            (char *)&option, sizeof (option));
                set_fs (oldmm);
                if (rc != 0) {
                        CERROR ("Can't set initial tcp backoff %d: %d\n",
                                option, rc);
                        return (rc);
                }
        }

        if (*ksocknal_tunables.ksnd_backoff_max > 0) {
                option = *ksocknal_tunables.ksnd_backoff_max;
#ifdef SOCKNAL_BACKOFF_MS
                option *= 1000;
#endif

                set_fs (KERNEL_DS);
                rc = sock->ops->setsockopt (sock, SOL_TCP, TCP_BACKOFF_MAX,
                                            (char *)&option, sizeof (option));
                set_fs (oldmm);
                if (rc != 0) {
                        CERROR ("Can't set maximum tcp backoff %d: %d\n",
                                option, rc);
                        return (rc);
                }
        }
#endif

        /* snapshot tunables */
        keep_idle  = *ksocknal_tunables.ksnd_keepalive_idle;
        keep_count = *ksocknal_tunables.ksnd_keepalive_count;
        keep_intvl = *ksocknal_tunables.ksnd_keepalive_intvl;

        do_keepalive = (keep_idle > 0 && keep_count > 0 && keep_intvl > 0);

        option = (do_keepalive ? 1 : 0);
        set_fs (KERNEL_DS);
        rc = sock_setsockopt (sock, SOL_SOCKET, SO_KEEPALIVE,
                              (char *)&option, sizeof (option));
        set_fs (oldmm);
        if (rc != 0) {
                CERROR ("Can't set SO_KEEPALIVE: %d\n", rc);
                return (rc);
        }

        if (!do_keepalive)
                return (0);

        set_fs (KERNEL_DS);
        rc = sock->ops->setsockopt (sock, SOL_TCP, TCP_KEEPIDLE,
                                    (char *)&keep_idle, sizeof (keep_idle));
        set_fs (oldmm);
        if (rc != 0) {
                CERROR ("Can't set TCP_KEEPIDLE: %d\n", rc);
                return (rc);
        }

        set_fs (KERNEL_DS);
        rc = sock->ops->setsockopt (sock, SOL_TCP, TCP_KEEPINTVL,
                                    (char *)&keep_intvl, sizeof (keep_intvl));
        set_fs (oldmm);
        if (rc != 0) {
                CERROR ("Can't set TCP_KEEPINTVL: %d\n", rc);
                return (rc);
        }

        set_fs (KERNEL_DS);
        rc = sock->ops->setsockopt (sock, SOL_TCP, TCP_KEEPCNT,
                                    (char *)&keep_count, sizeof (keep_count));
        set_fs (oldmm);
        if (rc != 0) {
                CERROR ("Can't set TCP_KEEPCNT: %d\n", rc);
                return (rc);
        }

        return (0);
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,5,0))
struct tcp_opt *sock2tcp_opt(struct sock *sk)
{
        return &(sk->tp_pinfo.af_tcp);
}
#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,10))
#define sock2tcp_opt(sk) tcp_sk(sk)
#else
struct tcp_opt *sock2tcp_opt(struct sock *sk)
{
        struct tcp_sock *s = (struct tcp_sock *)sk;
        return &s->tcp;
}
#endif

void
ksocknal_lib_push_conn (ksock_conn_t *conn)
{
        struct sock    *sk;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,11))
        struct tcp_opt *tp;
#else
        struct tcp_sock *tp;
#endif
        int             nonagle;
        int             val = 1;
        int             rc;
        mm_segment_t    oldmm;

        rc = ksocknal_connsock_addref(conn);
        if (rc != 0)                            /* being shut down */
                return;

        sk = conn->ksnc_sock->sk;
        tp = sock2tcp_opt(sk);

        lock_sock (sk);
        nonagle = tp->nonagle;
        tp->nonagle = 1;
        release_sock (sk);

        oldmm = get_fs ();
        set_fs (KERNEL_DS);

        rc = sk->sk_prot->setsockopt (sk, SOL_TCP, TCP_NODELAY,
                                      (char *)&val, sizeof (val));
        LASSERT (rc == 0);

        set_fs (oldmm);

        lock_sock (sk);
        tp->nonagle = nonagle;
        release_sock (sk);

        ksocknal_connsock_decref(conn);
}

extern void ksocknal_read_callback (ksock_conn_t *conn);
extern void ksocknal_write_callback (ksock_conn_t *conn);
/*
 * socket call back in Linux
 */
static void
ksocknal_data_ready (struct sock *sk, int n)
{
        ksock_conn_t  *conn;
        ENTRY;

        /* interleave correctly with closing sockets... */
        LASSERT(!in_irq());
        read_lock (&ksocknal_data.ksnd_global_lock);

        conn = sk->sk_user_data;
        if (conn == NULL) {             /* raced with ksocknal_terminate_conn */
                LASSERT (sk->sk_data_ready != &ksocknal_data_ready);
                sk->sk_data_ready (sk, n);
        } else
                ksocknal_read_callback(conn);

        read_unlock (&ksocknal_data.ksnd_global_lock);

        EXIT;
}

static void
ksocknal_write_space (struct sock *sk)
{
        ksock_conn_t  *conn;
        int            wspace;
        int            min_wpace;

        /* interleave correctly with closing sockets... */
        LASSERT(!in_irq());
        read_lock (&ksocknal_data.ksnd_global_lock);

        conn = sk->sk_user_data;
        wspace = SOCKNAL_WSPACE(sk);
        min_wpace = SOCKNAL_MIN_WSPACE(sk);

        CDEBUG(D_NET, "sk %p wspace %d low water %d conn %p%s%s%s\n",
               sk, wspace, min_wpace, conn,
               (conn == NULL) ? "" : (conn->ksnc_tx_ready ?
                                      " ready" : " blocked"),
               (conn == NULL) ? "" : (conn->ksnc_tx_scheduled ?
                                      " scheduled" : " idle"),
               (conn == NULL) ? "" : (list_empty (&conn->ksnc_tx_queue) ?
                                      " empty" : " queued"));

        if (conn == NULL) {             /* raced with ksocknal_terminate_conn */
                LASSERT (sk->sk_write_space != &ksocknal_write_space);
                sk->sk_write_space (sk);

                read_unlock (&ksocknal_data.ksnd_global_lock);
                return;
        }

        if (wspace >= min_wpace) {              /* got enough space */
                ksocknal_write_callback(conn);

                /* Clear SOCK_NOSPACE _after_ ksocknal_write_callback so the
                 * ENOMEM check in ksocknal_transmit is race-free (think about
                 * it). */

                clear_bit (SOCK_NOSPACE, &sk->sk_socket->flags);
        }

        read_unlock (&ksocknal_data.ksnd_global_lock);
}

void
ksocknal_lib_save_callback(struct socket *sock, ksock_conn_t *conn)
{
        conn->ksnc_saved_data_ready = sock->sk->sk_data_ready;
        conn->ksnc_saved_write_space = sock->sk->sk_write_space;
}

void
ksocknal_lib_set_callback(struct socket *sock,  ksock_conn_t *conn)
{
        sock->sk->sk_user_data = conn;
        sock->sk->sk_data_ready = ksocknal_data_ready;
        sock->sk->sk_write_space = ksocknal_write_space;
        return;
}

void
ksocknal_lib_reset_callback(struct socket *sock, ksock_conn_t *conn)
{
        /* Remove conn's network callbacks.
         * NB I _have_ to restore the callback, rather than storing a noop,
         * since the socket could survive past this module being unloaded!! */
        sock->sk->sk_data_ready = conn->ksnc_saved_data_ready;
        sock->sk->sk_write_space = conn->ksnc_saved_write_space;

        /* A callback could be in progress already; they hold a read lock
         * on ksnd_global_lock (to serialise with me) and NOOP if
         * sk_user_data is NULL. */
        sock->sk->sk_user_data = NULL;

        return ;
}
