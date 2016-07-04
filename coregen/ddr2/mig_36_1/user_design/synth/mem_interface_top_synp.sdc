# Synplicity, Inc. constraint file
# Written on Mon Jun 27 15:50:39 2005

define_global_attribute          syn_global_buffers {2}
define_attribute          {v:work.mig_36_1_parameters_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1} syn_hier {hard}
define_attribute          {v:work.mig_36_1_cal_ctl} syn_hier {hard}
define_attribute          {v:work.mig_36_1_cal_top} syn_hier {hard}
define_attribute          {v:work.mig_36_1_clk_dcm} syn_hier {hard}
define_attribute          {v:work.mig_36_1_controller_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_controller_iobs_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_data_path_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_data_path_iobs_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_data_read_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_data_read_controller_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_data_write_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_dqs_delay_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_fifo_0_wr_en_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_fifo_1_wr_en_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_infrastructure} syn_hier {hard}
define_attribute          {v:work.mig_36_1_infrastructure_iobs_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_infrastructure_top} syn_hier {hard}
define_attribute          {v:work.mig_36_1_iobs_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_ram8d_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_rd_gray_cntr} syn_hier {hard}
define_attribute          {v:work.mig_36_1_s3_dm_iob} syn_hier {hard}
define_attribute          {v:work.mig_36_1_s3_dq_iob} syn_hier {hard}
define_attribute          {v:work.mig_36_1_s3_dqs_iob} syn_hier {hard}
define_attribute          {v:work.mig_36_1_tap_dly} syn_hier {hard}
define_attribute          {v:work.mig_36_1_top_0} syn_hier {hard}
define_attribute          {v:work.mig_36_1_wr_gray_cntr} syn_hier {hard}


# clock Constraints

define_clock -disable -name {clk_dcm0} -period 6.667 -clockgroup default_clkgroup_2
define_clock          -name {infrastructure_top0.lvds_clk_input} -period 6.667 -clockgroup default_clkgroup_3
define_clock -disable -name {DCM_INST1} -period 6.667 -clockgroup default_clkgroup_4


