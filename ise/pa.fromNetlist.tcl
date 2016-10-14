
# PlanAhead Launch Script for Post-Synthesis floorplanning, created by Project Navigator

create_project -name main -dir "D:/ise/planAhead_run_4" -part xc3sd3400afg676-5
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "D:/ise/mian.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {D:/ise} }
add_files [list {D:/ise/mb.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {D:/ise/mb_clock_generator_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {D:/ise/mb_dlmb_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {D:/ise/mb_ilmb_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {D:/ise/mb_microblaze_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {D:/ise/mb_mpmc_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {D:/ise/mb_pci_arbiter_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {D:/ise/mb_xps_ll_temac_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {D:/ise/mb_xps_ll_temac_1_wrapper.ncf}] -fileset [get_property constrset [current_run]]
set_property target_constrs_file "main.ucf" [current_fileset -constrset]
add_files [list {main.ucf}] -fileset [get_property constrset [current_run]]
link_design
