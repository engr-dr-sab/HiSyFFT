source clean.sh
./fft_ip_generator fft.conf
rm -rf source_hls
mkdir source_hls
mv functional_behavior_stage*.h ./source_hls
mv global_constants_stage*.h ./source_hls
mv setup_script.tcl ./source_hls
mv global_variables_stage*.h ./source_hls
mv pipeLinedFFT_WRAPPER* ./source_hls
mv stimulus.* ./source_hls
mv dtype.h ./source_hls	
mv global_constants.h ./source_hls
mv stimulus_top.cpp ./source_hls
mv hls_fixed_point_lib.h ./source_hls
mv hls_fixed_point_lib.cpp ./source_hls
mv fixed_point_arithmetic_constants.h ./source_hls
