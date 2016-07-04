# The package naming convention is <core_name>_xmdf
package provide mig_36_1_xmdf 1.0

# This includes some utilities that support common XMDF operations 
package require utilities_xmdf

# Define a namespace for this package. The name of the name space
# is <core_name>_xmdf
namespace eval ::mig_36_1_xmdf {
# Use this to define any statics
}

# Function called by client to rebuild the params and port arrays
# Optional when the use context does not require the param or ports
# arrays to be available.
proc ::mig_36_1_xmdf::xmdfInit { instance } {
	# Variable containing name of library into which module is compiled
	# Recommendation: <module_name>
	# Required
	utilities_xmdf::xmdfSetData $instance Module Attributes Name mig_36_1
}
# ::mig_36_1_xmdf::xmdfInit

# Function called by client to fill in all the xmdf* data variables
# based on the current settings of the parameters
proc ::mig_36_1_xmdf::xmdfApplyParams { instance } {

set fcount 0
	# Array containing libraries that are assumed to exist
	# Examples include unisim and xilinxcorelib
	# Optional
	# In this example, we assume that the unisim library will
	# be magically
	# available to the simulation and synthesis tool
	utilities_xmdf::xmdfSetData $instance FileSet $fcount type logical_library
	utilities_xmdf::xmdfSetData $instance FileSet $fcount logical_library unisim
	incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_cal_ctl.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_cal_top.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_clk_dcm.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_controller_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_controller_iobs_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_data_path_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_data_path_iobs_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_data_read_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_data_read_controller_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_data_write_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_dqs_delay_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_fifo_0_wr_en_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_fifo_1_wr_en_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_infrastructure.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_infrastructure_iobs_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_infrastructure_top.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_iobs_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_parameters_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_ram8d_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_rd_gray_cntr.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_s3_dm_iob.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_s3_dq_iob.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_s3_dqs_iob.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_tap_dly.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_top_0.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/rtl/mig_36_1_wr_gray_cntr.vhd
utilities_xmdf::xmdfSetData $instance FileSet $fcount type vhdl
incr fcount

utilities_xmdf::xmdfSetData $instance FileSet $fcount relative_path mig_36_1/user_design/par/mig_36_1.ucf
utilities_xmdf::xmdfSetData $instance FileSet $fcount type ucf 
utilities_xmdf::xmdfSetData $instance FileSet $fcount associated_module mig_36_1
incr fcount

}

# ::gen_comp_name_xmdf::xmdfApplyParams
