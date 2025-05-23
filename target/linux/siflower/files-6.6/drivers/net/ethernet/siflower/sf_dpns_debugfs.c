#include <linux/debugfs.h>
#include "dpns.h"
#include "dma.h"

static const char * const sf21_dpns_mib_name[] = {
	"pkt_rcv_drop_port0",
	"pkt_rcv_drop_port1",
	"pkt_rcv_drop_port2",
	"pkt_rcv_drop_port3",
	"pkt_rcv_drop_port4",
	"pkt_rcv_drop_port5",
	"pkt_rcv_drop_port6",
	"pkt_rcv_drop_spl0",
	"pkt_rcv_drop_spl1",
	"pkt_rcv_drop_spl2",
	"pkt_rcv_drop_spl3",
	"pkt_rcv_drop_spl4",
	"pkt_rcv_drop_spl5",
	"pkt_rcv_drop_spl6",
	"pkt_rcv_trans_cnt0",
	"pkt_rcv_trans_cnt1",
	"pkt_rcv_trans_cnt2",
	"pkt_rcv_trans_cnt3",
	"pkt_rcv_trans_cnt4",
	"pkt_rcv_trans_cnt5",
	"pkt_rcv_trans_cnt6",
	"pkt_rcv_total0",
	"pkt_rcv_total1",
	"pkt_rcv_total2",
	"pkt_rcv_total3",
	"pkt_rcv_total4",
	"pkt_rcv_total5",
	"pkt_rcv_total6",
	"pkt_rcv",
	"udp",
	"tcp",
	"ipv4",
	"ipv6",
	"icmpv4",
	"icmpv6",
	"other_protocol",
	"ipv4_sip_eq_dip",
	"ipv4_icmp_frag",
	"ipv4_icmp_ping_too_big",
	"ipv4_udp_sp_eq_dp",
	"ipv4_tcp_flagchk_err",
	"ipv4_tcp_sq_eq_dp",
	"ipv4_tcp_frag_off1",
	"ipv4_tcp_syn_err",
	"ipv4_tcp_xmas",
	"ipv4_tcp_null",
	"ipv4_tcp_too_short",
	"ipv4_icmp4_redirect",
	"ipv4_icmp_smurf",
	"ipv6_sip_eq_dip",
	"ipv6_icmp_frag",
	"ipv6_icmp_ping_too_big",
	"ipv6_udp_sp_eq_dp",
	"ipv6_tcp_flagchk_err",
	"ipv6_tcp_sq_eq_dp",
	"ipv6_tcp_frag_off1",
	"ipv6_tcp_syn_err",
	"ipv6_tcp_xmas",
	"ipv6_tcp_null",
	"ipv6_tcp_too_short",
	"ipv6_icmp4_redirect",
	"ipv6_icmp_smurf",
	"ipv4in6_pls",
	"frame_ismc_pls",
	NULL,
	NULL,
	NULL,
	NULL,
	"arp_reply_err_fwd",
	"arp_req_err_fwd",
	"pkt_len_less_l2hd_err_fwd",
	"pkt_len_less_60B_err_fwd",
	"smac_is_mc_err_fwd",
	"smac_is_bc_err_fwd",
	"smac_eq_dmac_err_fwd",
	"smac_eq_zero_err_fwd",
	"dmac_eq_zero_err_fwd",
	"dribble_err_fwd",
	"runt_err_fwd",
	"giant_frame_err_fwd",
	"watchdog_err_fwd",
	"gmii_err_fwd",
	"dos_err_fwd",
	"ttl_err_fwd",
	"payload_chksum_err_fwd",
	"ip_version_err_fwd",
	"ip_hd_chksum_err_fwd",
	"crc_err_fwd",
	"pkt_len_err_fwd",
	"arp_reply_err_up",
	"arp_req_err_up",
	"pkt_len_less_l2hd_err_up",
	"pkt_len_less_60B_err_up",
	"smac_is_mc_err_up",
	"smac_is_bc_err_up",
	"smac_eq_dmac_err_up",
	"smac_eq_zero_err_up",
	"dmac_eq_zero_err_up",
	"dribble_err_up",
	"runt_err_up",
	"giant_frame_err_up",
	"watchdog_err_up",
	"gmii_err_up",
	"dos_err_up",
	"ttl_err_up",
	"payload_chksum_err_up",
	"ip_version_err_up",
	"ip_hd_chksum_err_up",
	"crc_err_up",
	"pkt_len_err_up",
	"arp_reply_err_drop",
	"arp_req_err_drop",
	"pkt_len_less_l2hd_err_drop",
	"pkt_len_less_60B_err_drop",
	"smac_is_mc_err_drop",
	"smac_is_bc_err_drop",
	"smac_eq_dmac_err_drop",
	"smac_eq_zero_err_drop",
	"dmac_eq_zero_err_drop",
	"dribble_err_drop",
	"runt_err_drop",
	"giant_frame_err_drop",
	"watchdog_err_drop",
	"gmii_err_drop",
	"dos_err_drop",
	"ttl_err_drop",
	"payload_chksum_err_drop",
	"ip_version_err_drop",
	"ip_hd_chksum_err_drop",
	"crc_err_drop",
	"pkt_len_err_drop",
	"ivlan_vid_input_mf",
	"ivlan_vid_pass_mf",
	"ivlan_vid_port_based_srch",
	"ivlan_vid_xlt_srch",
	"ivlan_vid_vfp_srch",
	"ivlan_vid_port_based_resp",
	"ivlan_vid_xlt_resp",
	"ivlan_vid_vfp_resp",
	"ivlan_vid_port_based_hit",
	"ivlan_vid_xlt_hit",
	"ivlan_vid_vfp_hit",
	"ivlan_vid_output_mf",
	"ivlan_vid_port_based_pass",
	"ivlan_vid_cp_drop",
	"ivlan_vid_cp_up",
	"ivlan_lkp_input_mf",
	"ivlan_lkp_pass_mf",
	"ivlan_lkp_srch",
	"ivlan_lkp_resp",
	"ivlan_lkp_hit",
	"ivlan_lkp_output_mf",
	"ivlan_lkp_cp_drop",
	"ivlan_lkp_cp_up",
	"l2_input_mf",
	"l2_pass_mf",
	"l2_flood_spl_srch_cnt",
	"l2_da_srch",
	"l2_sa_srch",
	"l2_flood_spl_resp_cnt",
	"l2_da_resp",
	"l2_sa_resp",
	"l2_flood_spl_cnt",
	"l2_da_hit",
	"l2_sa_hit",
	"l2_output_mf",
	"l2_cp_drop",
	"l2_cp_up",
	"l2_cp_fwd",
	"l2_cp_up_fwd",
	"nat_input_mf",
	"nat_pass_mf",
	"nat_srch",
	"nat_resp",
	"nat_hit",
	"nat_output_mf",
	"nat_v4_search",
	"nat_dnat",
	"nat_v4_hit",
	"nat_dnat_hit",
	"l3_input_mf",
	"l3_pass_mf",
	"l3_uc_srch",
	"l3_mcsg_srch",
	"l3_uc_resp",
	"l3_mcsg_resp",
	"l3_uc_hit",
	"l3_mcsg_hit",
	"l3_output_mf",
	"l3_v6_mf",
	"l3_mc",
	"l3_v6_srch",
	"l3_mc_srch",
	"l3_v6_hit",
	"l3_mc_hit",
	"iacl_input_mf",
	"iacl_pass_mf",
	"iacl_srch",
	"iacl_resp",
	"iacl_hit",
	"iacl_output_mf",
	"iacl_v6",
	"iacl_v6_srch",
	"iacl_v6_hit",
	"tmu_port0_phy_tran",
	"tmu_port1_phy_tran",
	"tmu_port2_phy_tran",
	"tmu_port3_phy_tran",
	"tmu_port4_phy_tran",
	"tmu_port5_phy_tran",
	"tmu_port6_phy_tran",
	"tmu_port7_phy_tran",
	"tmu_port8_phy_tran",
	"tmu_port9_phy_tran",
	"tmu_port10_phy_tran",
	"tmu_port11_phy_tran",
	"tmu_port12_phy_tran",
	"tmu_port13_phy_tran",
	"tmu_port14_phy_tran",
	"tmu_port15_phy_tran",
	"tmu_port16_phy_tran",
	"tmu_port17_phy_tran",
	"tmu_port18_phy_tran",
	"tmu_port19_phy_tran",
	"tmu_port20_phy_tran",
	"tmu_port21_phy_tran",
	"tmu_port22_phy_tran",
	"tmu_port23_phy_tran",
	"tmu_port24_phy_tran",
	"tmu_port25_phy_tran",
	"tmu_port26_phy_tran",
	"tmu_port0_phy_drop_rclm",
	"tmu_port1_phy_drop_rclm",
	"tmu_port2_phy_drop_rclm",
	"tmu_port3_phy_drop_rclm",
	"tmu_port4_phy_drop_rclm",
	"tmu_port5_phy_drop_rclm",
	"tmu_port6_phy_drop_rclm",
	"tmu_port7_phy_drop_rclm",
	"tmu_port8_phy_drop_rclm",
	"tmu_port9_phy_drop_rclm",
	"tmu_port10_phy_drop_rclm",
	"tmu_port11_phy_drop_rclm",
	"tmu_port12_phy_drop_rclm",
	"tmu_port13_phy_drop_rclm",
	"tmu_port14_phy_drop_rclm",
	"tmu_port15_phy_drop_rclm",
	"tmu_port16_phy_drop_rclm",
	"tmu_port17_phy_drop_rclm",
	"tmu_port18_phy_drop_rclm",
	"tmu_port19_phy_drop_rclm",
	"tmu_port20_phy_drop_rclm",
	"tmu_port21_phy_drop_rclm",
	"tmu_port22_phy_drop_rclm",
	"tmu_port23_phy_drop_rclm",
	"tmu_port24_phy_drop_rclm",
	"tmu_port25_phy_drop_rclm",
	"tmu_port26_phy_drop_rclm",
	"tmu_drop_bit_cnt",
	"nat_cp_drop_cnt",
	"nat_cp_up_cnt",
	"nat_fwd_cnt",
	"nat_cp_fwd_cnt",
	"l3_cp_up_fwd_cnt",
	"l3_cp_fwd_cnt",
	"l3_cp_up_cnt",
	"l3_drop_bit_cnt",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"arp_intf_input_mf",
	"arp_intf_pass_mf",
	"arp_intf_intf_srch",
	"arp_intf_arp_srch",
	"arp_intf_intf_resp",
	"arp_intf_arp_resp",
	"arp_intf_intf_hit",
	"arp_intf_arp_hit",
	"arp_intf_output_mf",
	"arp_intf_v6_mf",
	"arp_intf_mc",
	"arp_intf_v6_srch",
	"arp_intf_mc_srch",
	"arp_intf_v6_hit",
	"arp_intf_mc_hit",
	"evlan_lkp_input_mf",
	"evlan_lkp_pass_mf",
	"evlan_lkp_port_tpid_srch",
	"evlan_lkp_tag_mem_srch",
	"evlan_lkp_vlan_srch",
	"evlan_lkp_port_tpid_resp",
	"evlan_lkp_tag_mem_resp",
	"evlan_lkp_vlan_resp",
	"evlan_lkp_port_tpid_hit",
	"evlan_lkp_tag_mem_hit",
	"evlan_lkp_vlan_hit",
	"evlan_lkp_output_mf",
	"evlan_lkp_cp_drop",
	"evlan_lkp_cp_up",
	"evlan_lkp_cp_fwd",
	"evlan_act_input_mf",
	"evlan_act_pass_mf",
	"evlan_act_srch",
	"evlan_xlt_srch_cnt",
	"evlan_act_resp",
	"evlan_xlt_resp_hit",
	NULL,
	"evlan_xlt_hit_cnt",
	"evlan_act_output_mf",
	"evlan_act_cp_drop",
	"evlan_act_cp_cpu",
	"eacl_input_mf",
	"eacl_pass_mf",
	"eacl_srch",
	"eacl_resp",
	"eacl_hit",
	"eacl_output_mf",
	"eacl_v6",
	"eacl_v6_srch",
	"eacl_v6_hit",
	"md2port_0_data_sof",
	"md2port_0_data_eof",
	"md2port_1_data_sof",
	"md2port_1_data_eof",
	"md2port_2_data_sof",
	"md2port_2_data_eof",
	"md2port_3_data_sof",
	"md2port_3_data_eof",
	"md2port_4_data_sof",
	"md2port_4_data_eof",
	"md2port_5_data_sof",
	"md2port_5_data_eof",
	"md2port_6_data_sof",
	"md2port_6_data_eof",
	"pkt_separate_free_cnt",
	"pkt_whold_free_cnt",
	"se2md_result_cnt",
	"md2se_key_cnt",
	"mem2md_data_cnt",
	"md2mem_rd_cnt",
	"modify_drop_cnt",
	"mipp_cnt[0]",
	"mipp_cnt[1]",
	"ipv6_hdr_add",
	"ipv6_hdr_del",
	"otpid_replace",
	"itpid_replace",
	"ppp_hdr_add",
	"ppp_hdr_del",
	"avlan_replace",
	"avlan_add",
	"avlan_del",
	"ovlan_replace",
	"ovlan_add",
	"ovlan_del",
	"ivlan_replace",
	"ivlan_add",
	"ivlan_del",
};

static int
sf_dpns_mib_show(struct seq_file *m, void *private)
{
	struct dpns_priv *priv = m->private;
	u64 bytes;
	u32 count;
	int i;
	seq_printf(m, "General MIBs:\n");
	for (i = 0; i < ARRAY_SIZE(sf21_dpns_mib_name); i++) {
		if (!sf21_dpns_mib_name[i])
			continue;
		count = dpns_r32(priv, NPU_MIB(i));
		seq_printf(m, "name:%-30s packets:%11u\n",
			   sf21_dpns_mib_name[i], count);
	}
	seq_printf(m, "Port MIBs:\n");
	for (i = 0; i < DPNS_MAX_PORT; i++) {
		count = dpns_r32(priv, NPU_MIB_PKT_RCV_PORT(i));
		bytes = dpns_r32(priv, NPU_MIB_NCI_RD_DATA2) |
			(u64)dpns_r32(priv, NPU_MIB_NCI_RD_DATA3) << 32;
		seq_printf(m,
			   "name:pkt_rcv_port%-18u packets:%11u bytes:%20llu\n",
			   i, count, bytes);
	}
	return 0;
}

static int sf_dpns_mib_open(struct inode *inode, struct file *file)
{
	return single_open_size(file, sf_dpns_mib_show, inode->i_private,
				56 * (ARRAY_SIZE(sf21_dpns_mib_name) + 1) +
					83 * (DPNS_MAX_PORT + 1));
}

static const struct file_operations sf_dpns_mib_fops = {
	.owner		= THIS_MODULE,
	.open		= sf_dpns_mib_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

void sf_dpns_debugfs_init(struct dpns_priv *priv)
{
	priv->debugfs = debugfs_create_dir(dev_name(priv->dev), NULL);
	debugfs_create_file("mib", S_IRUSR, priv->debugfs, priv, &sf_dpns_mib_fops);
}
