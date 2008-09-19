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
 *
 * lnet/include/lnet/socklnd.h
 *
 * #defines shared between socknal implementation and utilities
 */
#ifndef __LNET_LNET_SOCKLND_H__
#define __LNET_LNET_SOCKLND_H__

#include <lnet/types.h>
#include <lnet/lib-types.h>

#define SOCKLND_CONN_NONE     (-1)
#define SOCKLND_CONN_ANY        0
#define SOCKLND_CONN_CONTROL    1
#define SOCKLND_CONN_BULK_IN    2
#define SOCKLND_CONN_BULK_OUT   3
#define SOCKLND_CONN_NTYPES     4

typedef struct {
        __u32                   kshm_magic;     /* magic number of socklnd message */
        __u32                   kshm_version;   /* version of socklnd message */
        lnet_nid_t              kshm_src_nid;   /* sender's nid */
        lnet_nid_t              kshm_dst_nid;   /* destination nid */
        lnet_pid_t              kshm_src_pid;   /* sender's pid */
        lnet_pid_t              kshm_dst_pid;   /* destination pid */
        __u64                   kshm_src_incarnation; /* sender's incarnation */
        __u64                   kshm_dst_incarnation; /* destination's incarnation */
        __u32                   kshm_ctype;     /* connection type */
        __u32                   kshm_nips;      /* # IP addrs */
        __u32                   kshm_ips[0];    /* IP addrs */
} WIRE_ATTR ksock_hello_msg_t;

typedef struct {
        lnet_hdr_t              ksnm_hdr;       /* lnet hdr */
        char                    ksnm_payload[0];/* lnet payload */
} WIRE_ATTR ksock_lnet_msg_t;

typedef struct {
        __u32                   ksm_type;       /* type of socklnd message */
        __u32                   ksm_csum;       /* checksum if != 0 */
        __u64                   ksm_zc_req_cookie; /* ack required if != 0 */
        __u64                   ksm_zc_ack_cookie; /* ack if != 0 */
        union {
                ksock_lnet_msg_t lnetmsg;       /* lnet message, it's empty if it's NOOP */
        } WIRE_ATTR ksm_u;
} WIRE_ATTR ksock_msg_t;

#define KSOCK_MSG_NOOP          0xc0            /* ksm_u empty */ 
#define KSOCK_MSG_LNET          0xc1            /* lnet msg */

/* We need to know this number to parse hello msg from ksocklnd in
 * other LND (usocklnd, for example) */ 
#define KSOCK_PROTO_V2          2

#endif
