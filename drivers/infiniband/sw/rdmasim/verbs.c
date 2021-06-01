// SPDX-License-Identifier: GPL-2.0
/*
 * Software RDMA simulator driver
 * Copyright (C) 2020-2021 Kamal Heib <kamalheib1@gmail.com>
 */

#include <rdma/ib_verbs.h>
#include <linux/types.h>

#include "rdmasim.h"

int rdmasim_query_device(struct ib_device *device,
			 struct ib_device_attr *device_attr,
			 struct ib_udata *udata)
{
	memset(device_attr, 0, sizeof(*device_attr));
	device_attr->device_cap_flags = IB_DEVICE_ALLOW_USER_UNREG |
					IB_DEVICE_MEM_MGT_EXTENSIONS;

	device_attr->sys_image_guid = device->node_guid;
	device_attr->max_mr_size = ULONG_MAX;
	device_attr->page_size_cap = 0;
	device_attr->vendor_id = RDMASIM_VENDOR_ID;
	device_attr->vendor_part_id = 0;
	device_attr->hw_ver = 0;
	device_attr->max_qp = RDMASIM_MAX_QP;
	device_attr->max_qp_wr = RDMASIM_MAX_QP_WR;
	device_attr->max_send_sge = RDMASIM_MAX_SEND_SGE;
	device_attr->max_recv_sge = RDMASIM_MAX_RECV_SGE;
	device_attr->max_sge_rd = RDMASIM_MAX_SGE_RD;
	device_attr->max_cq = RDMASIM_MAX_CQ;
	device_attr->max_cqe = RDMASIM_MAX_CQE;
	device_attr->max_mr = RDMASIM_MAX_MR;
	device_attr->max_pd = RDMASIM_MAX_PD;
	device_attr->max_qp_rd_atom = 64;
	device_attr->max_ee_rd_atom = 0;
	device_attr->max_res_rd_atom = 64;
	device_attr->max_qp_init_rd_atom = 64;
	device_attr->max_ee_init_rd_atom = 64;
	device_attr->atomic_cap = 0;
	device_attr->masked_atomic_cap = 0;
	device_attr->max_ee = 0;
	device_attr->max_rdd = 0;
	device_attr->max_mw = 0;
	device_attr->max_raw_ipv6_qp = 0;
	device_attr->max_raw_ethy_qp = 0;
	device_attr->max_mcast_grp = 0;
	device_attr->max_mcast_qp_attach = 0;
	device_attr->max_ah = RDMASIM_MAX_AH;
	device_attr->max_srq = 0;
	device_attr->max_srq_wr = 0;
	device_attr->max_srq_sge = 0;
	device_attr->max_fast_reg_page_list_len = 4;
	device_attr->max_pkeys = RDMASIM_MAX_PKEY;
	device_attr->local_ca_ack_delay = 16;
	device_attr->sig_prot_cap = 0;
	device_attr->sig_guard_cap = 0;
	device_attr->timestamp_mask = 0;
	device_attr->hca_core_clock = 0;
	return 0;
}

int rdmasim_get_port_immutable(struct ib_device *device, u32 port_num,
			       struct ib_port_immutable *immutable)
{
	return 0;
}

int rdmasim_query_port(struct ib_device *device, u32 port_num,
		       struct ib_port_attr *port_attr)
{
	return 0;
}

void rdmasim_dealloc_driver(struct ib_device *dev)
{
}

int rdmasim_alloc_pd(struct ib_pd *pd, struct ib_udata *udata)
{
	struct rdmasim_device *rdev = to_rdmasim_dev(pd->device);

	if (atomic_add_unless(&rdev->num_pd, 1, RDMASIM_MAX_PD))
		return -ENOMEM;

	return 0;
}

int rdmasim_dealloc_pd(struct ib_pd *pd, struct ib_udata *udata)
{
	struct rdmasim_device *rdev = to_rdmasim_dev(pd->device);

	atomic_dec(&rdev->num_pd);
	return 0;
}
