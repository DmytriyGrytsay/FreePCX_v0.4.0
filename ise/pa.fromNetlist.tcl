
# PlanAhead Launch Script for Post-Synthesis floorplanning, created by Project Navigator

create_project -name main -dir "/home/kruger/FreePCX_v0.4.0/ise/planAhead_run_3" -part xc3sd3400afg676-5
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "/home/kruger/FreePCX_v0.4.0/ise/mian.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {/home/kruger/FreePCX_v0.4.0/ise} }
add_files [list {/home/kruger/FreePCX_v0.4.0/ise/mb_mpmc_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {/home/kruger/FreePCX_v0.4.0/ise/mb_xps_ll_temac_1_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {/home/kruger/FreePCX_v0.4.0/ise/mb_ilmb_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {/home/kruger/FreePCX_v0.4.0/ise/mb_pci_arbiter_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {/home/kruger/FreePCX_v0.4.0/ise/mb_microblaze_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {/home/kruger/FreePCX_v0.4.0/ise/mb_clock_generator_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {/home/kruger/FreePCX_v0.4.0/ise/mb_dlmb_wrapper.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {/home/kruger/FreePCX_v0.4.0/ise/mb.ncf}] -fileset [get_property constrset [current_run]]
add_files [list {/home/kruger/FreePCX_v0.4.0/ise/mb_xps_ll_temac_0_wrapper.ncf}] -fileset [get_property constrset [current_run]]
set_property target_constrs_file "main.ucf" [current_fileset -constrset]
add_files [list {main.ucf}] -fileset [get_property constrset [current_run]]
link_design
