project new test.xise

project set "Device Family" "Spartan-3A DSP"

project set "Device" "xc3sd3400a"

project set "Package" "fg676"

project set "Speed Grade" "-5"

project set "Synthesis Tool" "XST (VHDL/Verilog)"

project set "Simulator" "Modelsim-SE Mixed"

xfile add "../rtl/mig_36_1_parameters_0.vhd"
xfile add "../rtl/mig_36_1.vhd"
xfile add "../rtl/mig_36_1_cal_ctl.vhd"
xfile add "../rtl/mig_36_1_cal_top.vhd"
xfile add "../rtl/mig_36_1_clk_dcm.vhd"
xfile add "../rtl/mig_36_1_controller_0.vhd"
xfile add "../rtl/mig_36_1_controller_iobs_0.vhd"
xfile add "../rtl/mig_36_1_data_path_0.vhd"
xfile add "../rtl/mig_36_1_data_path_iobs_0.vhd"
xfile add "../rtl/mig_36_1_data_read_0.vhd"
xfile add "../rtl/mig_36_1_data_read_controller_0.vhd"
xfile add "../rtl/mig_36_1_data_write_0.vhd"
xfile add "../rtl/mig_36_1_dqs_delay_0.vhd"
xfile add "../rtl/mig_36_1_fifo_0_wr_en_0.vhd"
xfile add "../rtl/mig_36_1_fifo_1_wr_en_0.vhd"
xfile add "../rtl/mig_36_1_infrastructure.vhd"
xfile add "../rtl/mig_36_1_infrastructure_iobs_0.vhd"
xfile add "../rtl/mig_36_1_infrastructure_top.vhd"
xfile add "../rtl/mig_36_1_iobs_0.vhd"
xfile add "../rtl/mig_36_1_ram8d_0.vhd"
xfile add "../rtl/mig_36_1_rd_gray_cntr.vhd"
xfile add "../rtl/mig_36_1_s3_dm_iob.vhd"
xfile add "../rtl/mig_36_1_s3_dq_iob.vhd"
xfile add "../rtl/mig_36_1_s3_dqs_iob.vhd"
xfile add "../rtl/mig_36_1_tap_dly.vhd"
xfile add "../rtl/mig_36_1_top_0.vhd"
xfile add "../rtl/mig_36_1_wr_gray_cntr.vhd"

xfile add "mig_36_1.ucf"

project set "FSM Encoding Algorithm" "Auto" -process "Synthesize - XST"
project set "Safe Implementation" "No" -process "Synthesize - XST"
project set "FSM Style" "LUT" -process "Synthesize - XST"
project set "RAM Extraction" "True" -process "Synthesize - XST"
project set "RAM Style" "Auto" -process "Synthesize - XST"
project set "ROM Extraction" "True" -process "Synthesize - XST"
project set "ROM Style" "Auto" -process "Synthesize - XST"
project set "Mux Extraction" "Yes" -process "Synthesize - XST"
project set "Mux Style" "Auto" -process "Synthesize - XST"
project set "Decoder Extraction" "True" -process "Synthesize - XST"
project set "Priority Encoder Extraction" "Yes" -process "Synthesize - XST"
project set "Shift Register Extraction" "True" -process "Synthesize - XST"
project set "Logical Shifter Extraction" "True" -process "Synthesize - XST"
project set "XOR Collapsing" "True" -process "Synthesize - XST"
project set "Resource Sharing" "True" -process "Synthesize - XST"
project set "Asynchronous To Synchronous" "False" -process "Synthesize - XST"
project set "Register Balancing" "No" -process "Synthesize - XST"
project set "Add I/O Buffers" "True" -process "Synthesize - XST"
project set "Max Fanout" "500" -process "Synthesize - XST"
project set "Number of Clock Buffers" "8" -process "Synthesize - XST"
project set "Register Duplication" "True" -process "Synthesize - XST"
project set "Slice Packing" "True" -process "Synthesize - XST"
project set "Optimize Instantiated Primitives" "False" -process "Synthesize - XST"
project set "Use Clock Enable" "Yes" -process "Synthesize - XST"
project set "Use Synchronous Set" "Yes" -process "Synthesize - XST"
project set "Use Synchronous Reset" "Yes" -process "Synthesize - XST"
project set "Pack I/O Registers into IOBs" "Auto" -process "Synthesize - XST"
project set "Equivalent Register Removal" "True" -process "Synthesize - XST"
project set "Optimization Goal" "Speed" -process "Synthesize - XST"
project set "Optimization Effort" "Normal" -process "Synthesize - XST"
project set "Library Search Order" "../synth/mig_36_1.lso" -process "Synthesize - XST"
project set "Keep Hierarchy" "Soft" -process "Synthesize - XST"
project set "Netlist Hierarchy" "As Optimized" -process "Synthesize - XST"
project set "Generate RTL Schematic" "Yes" -process "Synthesize - XST"
project set "Global Optimization Goal" "AllClockNets" -process "Synthesize - XST"
project set "Read Cores" "True" -process "Synthesize - XST"
project set "Write Timing Constraints" "False" -process "Synthesize - XST"
project set "Cross Clock Analysis" "False" -process "Synthesize - XST"
project set "Hierarchy Separator" "/" -process "Synthesize - XST"
project set "Bus Delimiter" "<>" -process "Synthesize - XST"
project set "Case" "Maintain" -process "Synthesize - XST"
project set "Slice Utilization Ratio" "100" -process "Synthesize - XST"
project set "BRAM Utilization Ratio" "100" -process "Synthesize - XST"
project set "Verilog 2001" "True" -process "Synthesize - XST"
project set "Automatic BRAM Packing" "False" -process "Synthesize - XST"

project set "Optimization Strategy (Cover Mode)" "Speed" -process Map
project set "Pack I/O Registers/Latches into IOBs" "Off" -process Map

project set "Place & Route Effort Level (Overall)" "Standard" -process "Place & Route"
project set "Starting Placer Cost Table (1-100)" "1" -process "Place & Route"

project set "Number of Paths in Error/Verbose Report" "100" -process "Generate Post-Map Static Timing"

project set "Enable Debugging of Serial Mode BitStream" "False" -process "Generate Programming File"
project set "Create Binary Configuration File" "False" -process "Generate Programming File"
project set "Enable Cyclic Redundancy Checking (CRC)" "True" -process "Generate Programming File"
project set "Configuration Rate" "6" -process "Generate Programming File"
project set "Configuration Pin Program" "Pull Up" -process "Generate Programming File"
project set "Configuration Pin Done" "Pull Up" -process "Generate Programming File"
project set "JTAG Pin TCK" "Pull Up" -process "Generate Programming File"
project set "JTAG Pin TDI" "Pull Up" -process "Generate Programming File"
project set "JTAG Pin TDO" "Pull Up" -process "Generate Programming File"
project set "JTAG Pin TMS" "Pull Up" -process "Generate Programming File"
project set "Unused IOB Pins" "Float" -process "Generate Programming File"
project set "UserID Code (8 Digit Hexadecimal)" "0xFFFFFFFF" -process "Generate Programming File"
project set "FPGA Start-Up Clock" "CCLK" -process "Generate Programming File"
project set "Done (Output Events)" "Default (4)" -process "Generate Programming File"
project set "Enable Outputs (Output Events)" "Default (5)" -process "Generate Programming File"
project set "Release Write Enable (Output Events)" "Default (6)" -process "Generate Programming File"
project set "Wait for DLL Lock (Output Events)" "Default (NoWait)" -process "Generate Programming File"
project set "Enable Internal Done Pipe" "False" -process "Generate Programming File"
project set "Drive Done Pin High" "False" -process "Generate Programming File"
project set "Security" "Enable Readback and Reconfiguration" -process "Generate Programming File"

project close

