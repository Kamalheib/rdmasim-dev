// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020-2021 Kamal Heib <kamalheib1@gmail.com>
 */

#ifndef _RDMASIM_H
#define _RDMASIM_H

#define RDMASIM_MAX_PORT 1
#define RDMASIM_MAX_PKEY 1
#define RDMASIM_MAX_PD 0xFFFF
#define RDMASIM_MAX_AH 0xFFFF

#define RDMASIM_MAX_QP 0xFFFFFF
#define RDMASIM_MAX_QP_WR 0xFFFF
#define RDMASIM_MAX_MR 0xFFFFFF
#define RDMASIM_MAX_CQ 0xFFFFFF
#define RDMASIM_MAX_CQE 0xFFFF

#define RDMASIM_MAX_SEND_SGE 16
#define RDMASIM_MAX_RECV_SGE 16
#define RDMASIM_MAX_SGE_RD 16

#define RDMASIM_VENDOR_ID 0xFFFFFF
#define RDMASIM_NODE_DESC "Software RDMA suimlator"

struct rdmasim_device {
	struct ib_device ibdev;
	struct net_device *netdev;
};

#endif
