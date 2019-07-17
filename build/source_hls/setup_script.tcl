# File Name : setup_script.tcl
# This is an automatically generated file using HLS IP generator
# File creation time:17-7-2019 15:55:17
# Author Name : Shahzad Ahmad Butt
# Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
# PostDoctoral Researcher at Micro-electronics Group
# Department of Electronics and Telecommunications 
# Politecnico di Torino, Torino, Italy
# http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
#
set POWER_GATE true

if {[get_design] == ""} then {
        new_design pipeLinedFFT_WRAPPER
  } else {
                        close_design
                        new_design pipeLinedFFT_WRAPPER
 }
 set_attr auto_write_models "true" [get_design]
 define_sim_config -model_dir "./model" [get_design]
 ######################################################################################
 ##############Uncomment the directive below for testbench specs#######################
 ######################################################################################
 #define_sim_config -testbench_files "" [get_design]
 #define_sim_config -testbench_kind "self_checking" [get_design]
 #define_sim_config -makefile_name "Makefile.sim" [get_design]
 #define_sim_config -simulator_args "-top sc_main -Iinc -Itb" [get_design]
 #define_sim_config -success_msg "PASS: Simulation completed." [get_design]
 ######################################################################################
 ######################################################################################
 set_attr source_files [list ./source_hls/pipeLinedFFT_WRAPPER.cpp ./source_hls/hls_fixed_point_lib.cpp ] [get_design]
 set_attr header_files [list ./source_hls/fixed_point_arithmetic_constants.h./source_hls/dtype.h ./source_hls/global_constants.h ./source_hls/pipeLinedFFT_WRAPPER.h./source_hls/global_constants_stage1.h ./source_hls/global_constants_stage2.h ./source_hls/global_constants_stage3.h ./source_hls/global_constants_stage4.h ./source_hls/global_constants_stage5.h ./source_hls/global_constants_stage6.h ./source_hls/global_constants_stage7.h ./source_hls/global_constants_stage8.h ./source_hls/global_constants_stage9.h ./source_hls/global_constants_stage10.h ./source_hls/global_constants_stage11.h ./source_hls/global_variables_stage1.h ./source_hls/global_variables_stage2.h ./source_hls/global_variables_stage3.h ./source_hls/global_variables_stage4.h ./source_hls/global_variables_stage5.h ./source_hls/global_variables_stage6.h ./source_hls/global_variables_stage7.h ./source_hls/global_variables_stage8.h ./source_hls/global_variables_stage9.h ./source_hls/global_variables_stage10.h ./source_hls/global_variables_stage11.h ./source_hls/functional_behavior_stage1.h ./source_hls/functional_behavior_stage2.h ./source_hls/functional_behavior_stage3.h ./source_hls/functional_behavior_stage4.h ./source_hls/functional_behavior_stage5.h ./source_hls/functional_behavior_stage6.h ./source_hls/functional_behavior_stage7.h ./source_hls/functional_behavior_stage8.h ./source_hls/functional_behavior_stage9.h ./source_hls/functional_behavior_stage10.h ./source_hls/functional_behavior_stage11.h  ] [get_design] 
 set_attr compile_flags " -w" [get_design]
 ######################################################################################
 Uncomment this directive if you want to export memories during high level  synthesis
 # set_attr export_memories true [get_design]
 ######################################################################################
 set_attr top_module_path "pipeLinedFFT_WRAPPER" [get_design]
 set_attr build_flat "true" [get_design]
 set_attr default_export_memories "true" [get_design]
 define_clock -name clk -period 20000 -rise 0 -fall 10000
 set_attr tech_lib_names [list /tools/techlibs/umc/90nm_SP/fsd0a_a/2009Q2v2.0/GENERIC_CORE_1D0V/FrontEnd/synopsys/fsd0a_a_generic_core_ff1p1vm40c.lib /tools/techlibs/umc/90nm_SP/fsd0a_a/2009Q2v2.0/GENERIC_CORE_1D0V/FrontEnd/synopsys/fsd0a_a_generic_core_ss0p9v125c.lib /tools/techlibs/umc/90nm_SP/fsd0a_a/2009Q2v2.0/GENERIC_CORE_1D0V/FrontEnd/synopsys/fsd0a_a_generic_core_tt1v25c.lib] [get_design]
 set_attr low_power_clock_gating $POWER_GATE [get_design]
 build
 inline_calls -all
