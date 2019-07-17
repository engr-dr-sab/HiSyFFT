/*
 * FFT_IP_GENERATOR.h
 *
 *  Created on: Oct 5, 2012 : 4:33:00 PM
 *  Project : FFT IP/S-Fucntion generator
 *      Author: Shahzad Ahmad Butt
 */
#include <stdio.h>
#include <time.h>
#include "support_functions.h"
int main(int argc, char const *argv[])
{
    /* This code will generate and FFT IP with pipelined architecture
	*  The generated code can be integerated with simulink for simulation
	* and can also be synthesized using high level synthesis tool
	* that supports synthesis from C/C++/systemC 
	*/

	// open and read the file that defines the configuration of the FFT IP
	 FILE* file;
	 FILE *fptr;
	 int i;
	 int ctos_model;
	 int fft_len;
	 int fft_threads;
	 int fft_input_sample_resolution;
	 int fft_input_sample_fractional_part_len;
	 int fft_input_sample_integer_part_len;
	 int fft_output_sample_resolution;
	 int fft_output_sample_fractional_part_len;
	 int fft_output_sample_inetger_part_len;
	 int total_butterfly_stages;
	 int circular_buffers;
	 int twiddle_factors_bit_width;
	 int twiddle_factors_fraction_width;
	 char tempFileName[100];
	 file=fopen ("fft.conf","r");
	
    
	fscanf(file, "%d", &i);  
	/*printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");*/
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("This Program Will Generate a SytemC model For FFT with Streaming Arcitecture\n");
	printf("The configuration file \"fft.conf\" define I/O and architecture details.....\n\n");
	printf("The FFT is generated with a length of : %d\n",i);
	//line1
	fft_len=i;
	
	fscanf(file, "%d", &i);  
	printf("Input samples have resolution of :   %d Bits\n",i);
	//line2
	fft_input_sample_resolution=i;

	fscanf(file, "%d", &i);  
	printf("Input sample fractional part, bit width :   %d Bits\n",i);
	fft_input_sample_fractional_part_len=i;
	fft_input_sample_integer_part_len=fft_input_sample_resolution-i;
	printf("Input sample Integer part,  bit width :   %d Bits\n",fft_input_sample_integer_part_len);

	fscanf(file, "%d", &i);  
	printf("Output samples have resolution of :   %d Bits\n",i);
	fft_output_sample_resolution=i;

	fscanf(file, "%d", &i);  
	printf("Output sample fractional part, bit width :   %d Bits\n",i);
	fft_output_sample_fractional_part_len=i;
	fft_output_sample_inetger_part_len=fft_output_sample_resolution-i;
	printf("Output sample integer part, bit width :   %d Bits\n",fft_output_sample_inetger_part_len);

	fscanf(file, "%d", &i);
	fft_threads=i;
	if(i==1)
	printf("FFT with SINGLE THREADED architecture is generated......\n");
	else
	printf("FFT with MULTIPLE THREADED architecture is generated......\n");


	fscanf(file, "%d", &i);
	circular_buffers=i;
	if(i==1)
	printf("FFT with Circular Buffer architecture is generated......\n");
	else
	printf("FFT with  Shift Register architecture is generated......\n");

	fscanf(file, "%d", &i);
	ctos_model=i;

	fscanf(file, "%d", &i);
	twiddle_factors_bit_width=i;

	fscanf(file, "%d", &i);
	twiddle_factors_fraction_width=i;

	/*printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");*/
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	total_butterfly_stages=mf_log2(fft_len);
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a header file that 
	* will define the integer data type to be used for defining fixed
	* point data types.
	*/
//	fclose(fptr);
    fptr = fopen("dtype.h","w");
    printAuthor(fptr,"dtype","h");
    printFileGaurd_start(fptr,"dtype","h");
    print_BODY_dtype_dot_h(fptr);
	printFileGaurd_end(fptr,"dtype","h");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a header file that 
	* will define the constant that are global to all the design
	*/
	fclose(fptr);
    fptr = fopen("global_constants.h","w");
    printAuthor(fptr,"global_constants","h");
    printFileGaurd_start(fptr,"global_constants","h");
    print_BODY_global_constants_dot_h(fptr,fft_len,fft_input_sample_resolution,fft_output_sample_resolution,fft_threads,circular_buffers,ctos_model,fft_input_sample_fractional_part_len,fft_input_sample_integer_part_len,fft_output_sample_fractional_part_len,fft_output_sample_inetger_part_len);
	printFileGaurd_end(fptr,"global_constants","h");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of header files that 
	* will define the global variables for pipeline stage of FFT
	*/
	for (i = 1; i <= total_butterfly_stages; i++)
	{
		/* code */
		sprintf(tempFileName,"global_variables_stage%d.h",i);
		fclose(fptr);
		fptr = fopen(tempFileName,"w");
		sprintf(tempFileName,"global_variables_stage%d",i); 
		printAuthor(fptr,tempFileName,"h");
		printFileGaurd_start(fptr,tempFileName,"h");
		print_BODY_global_variables_stageN_dot_h(fptr,i,fft_len);
		printFileGaurd_end(fptr,tempFileName,"h");

	}
    
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of header files that 
	* will define the global constants for every butterfly stage , these con-
	* tants are seperated from the rest of the constants in global file in 
	* order to ease up the design of S-functions
	*/
	for (i = 1; i <= total_butterfly_stages; i++)
	{
		/* code */
		sprintf(tempFileName,"global_constants_stage%d.h",i); 
		fclose(fptr);
		fptr = fopen(tempFileName,"w");
		sprintf(tempFileName,"global_constants_stage%d",i); 
		printAuthor(fptr,tempFileName,"h");
		printFileGaurd_start(fptr,tempFileName,"h");
		print_BODY_global_constants_stageN_dot_h(fptr,i,fft_len);
		printFileGaurd_end(fptr,tempFileName,"h");

	}
    
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	


	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of header files that 
	* will define the different butterfly stages of the FFT
	*/
	for (i = 1; i <= total_butterfly_stages; i++)
	{
		/* code */
		sprintf(tempFileName,"functional_behavior_stage%d.h",i);
		fclose(fptr);
		fptr = fopen(tempFileName,"w");
		sprintf(tempFileName,"functional_behavior_stage%d",i); 
		printAuthor(fptr,tempFileName,"h");
		printFileGaurd_start(fptr,tempFileName,"h");
		print_BODY_functional_behavior_stageN_dot_h(fptr,i,fft_len,fft_output_sample_resolution);
		printFileGaurd_end(fptr,tempFileName,"h");

	}
    
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of header files that 
	* will define SystemC header to and hardware interfaces.
	*/
	fclose(fptr);
	fptr = fopen("pipeLinedFFT_WRAPPER.h","w");
    printAuthor(fptr,"pipeLinedFFT_WRAPPER","h");
    printFileGaurd_start(fptr,"pipeLinedFFT_WRAPPER","h");
    print_BODY_fftPipelined_wrapper_dot_h(fptr,total_butterfly_stages,fft_len,fft_input_sample_resolution,fft_output_sample_resolution);
	printFileGaurd_end(fptr,"pipeLinedFFT_WRAPPER","h");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////		



	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of SystemC wrapper
	* that will stitch together all the code from different files that describe
	* functional behavior of FFT stages and also it will act as encapsulating wra
	* wrapper that defines interfaces between all the stages.
	*/
	fclose(fptr);
	fptr = fopen("pipeLinedFFT_WRAPPER.cpp","w");
    printAuthor(fptr,"pipeLinedFFT_WRAPPER","cpp");
    //printFileGaurd_start(fptr,"pipeLinedFFT_WRAPPER","h");
    print_BODY_fftPipelined_wrapper_dot_cpp(fptr,total_butterfly_stages,fft_len,twiddle_factors_bit_width,twiddle_factors_fraction_width,fft_output_sample_resolution);

	//printFileGaurd_end(fptr,"pipeLinedFFT_WRAPPER","h");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of SystemC wrapper
	* that will stitch together all the code from different files that describe
	* functional behavior of FFT stages and also it will act as encapsulating wra
	* wrapper that defines interfaces between all the stages.
	*/
	fclose(fptr);
	fptr = fopen("stimulus.h","w");
    printAuthor(fptr,"stimulus","h");
    printFileGaurd_start(fptr,"stimulus","h");
    print_BODY_stimulus_dot_h(fptr);
	printFileGaurd_end(fptr,"stimulus","h");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	


	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of SystemC wrapper
	* that will stitch together all the code from different files that describe
	* functional behavior of FFT stages and also it will act as encapsulating wra
	* wrapper that defines interfaces between all the stages.
	*/
	fclose(fptr);
	fptr = fopen("stimulus.cpp","w");
    printAuthor(fptr,"stimulus","cpp");
    //printFileGaurd_start(fptr,"stimulus","cpp");
    print_BODY_stimulus_dot_cpp(fptr,fft_len,4);
	//printFileGaurd_end(fptr,"stimulus","cpp");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of SystemC wrapper
	* that will stitch together all the code from different files that describe
	* functional behavior of FFT stages and also it will act as encapsulating wra
	* wrapper that defines interfaces between all the stages.
	*/
	fclose(fptr);
	fptr = fopen("stimulus_top.cpp","w");
    printAuthor(fptr,"stimulus_top","cpp");
    //printFileGaurd_start(fptr,"stimulus_top","cpp");
    print_BODY_stimulus_top_dot_cpp(fptr,fft_len,fft_input_sample_resolution,fft_output_sample_resolution);
	//printFileGaurd_end(fptr,"stimulus_top","cpp");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of SystemC wrapper
	* that will stitch together all the code from different files that describe
	* functional behavior of FFT stages and also it will act as encapsulating wra
	* wrapper that defines interfaces between all the stages.
	*/
	fclose(fptr);
	fptr = fopen("setup_script.tcl","w");
    printAuthor(fptr,"setup_script","tcl");
    //printFileGaurd_start(fptr,"stimulus_top","cpp");
    print_BODY_setup_script_dot_tcl(fptr,fft_len,total_butterfly_stages);
	//printFileGaurd_end(fptr,"stimulus_top","cpp");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	

	//void print_BODY_stimulus_top_dot_cpp(FILE *fptr, int fft_len, int input_sample_bit_width, int output_sample_bitwidth)

	/*void print_BODY_stimulus_dot_cpp(FILE *fptr, int fft_len, int no_of_sim_frame)*/

	//print_BODY_stimulus_dot_h(FILE *fptr)

	//void print_BODY_fftPipelined_wrapper_dot_cpp(FILE *fptr,int total_stages,int fft_len,int input_bit_width);

	//fprintf(fptr, "\n\n#ifndef DTYPE_H_\n");
	// fprintf(fptr, "#define DTYPE_H_\n");
	// The vody of the file goes here and after.
	// fprintf(fptr, "\n\n#endif //File Gaurd End here DTYPE_H_\n");

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of SystemC wrapper
	* that will stitch together all the code from different files that describe
	* functional behavior of FFT stages and also it will act as encapsulating wra
	* wrapper that defines interfaces between all the stages.
	*/
	fclose(fptr);
	fptr = fopen("fixed_point_arithmetic_constants.h","w");
    printAuthor(fptr,"fixed_point_arithmetic_constants","h");
    printFileGaurd_start(fptr,"fixed_point_arithmetic_constants","h");
    print_BODY_fixed_point_arithmetic_constants_dot_h(fptr,fft_len,total_butterfly_stages);
	printFileGaurd_end(fptr,"fixed_point_arithmetic_constants","h");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	


	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of SystemC wrapper
	* that will stitch together all the code from different files that describe
	* functional behavior of FFT stages and also it will act as encapsulating wra
	* wrapper that defines interfaces between all the stages.
	*/
	fclose(fptr);
	fptr = fopen("hls_fixed_point_lib.h","w");
    printAuthor(fptr,"hls_fixed_point_lib","h");
    printFileGaurd_start(fptr,"hls_fixed_point_lib","h");
    print_BODY_hls_fixed_point_lib_dot_h(fptr,fft_len,total_butterfly_stages);
	printFileGaurd_end(fptr,"hls_fixed_point_lib","h");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	
	/* 
	* The following block of the code will generat a set of SystemC wrapper
	* that will stitch together all the code from different files that describe
	* functional behavior of FFT stages and also it will act as encapsulating wra
	* wrapper that defines interfaces between all the stages.
	*/
	fclose(fptr);
	fptr = fopen("hls_fixed_point_lib.cpp","w");
    printAuthor(fptr,"hls_fixed_point_lib","cpp");
    //printFileGaurd_start(fptr,"hls_fixed_point_lib","h");
    print_BODY_hls_fixed_point_lib_dot_cpp(fptr,fft_len,total_butterfly_stages);
	//printFileGaurd_end(fptr,"stimulus_top","cpp");
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////	





    fclose(fptr); 
	fclose(file);
	return 0;
}









