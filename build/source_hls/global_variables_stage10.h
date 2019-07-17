/* File Name : global_variables_stage10.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef LOBAL_VARIABLES_STAGE10_H_
#define LOBAL_VARIABLES_STAGE10_H_

	//Global Schedule control variabels for stage:10
	int GLOBAL_OUTER_ITERATION_COUNTER_s10;
	///////////////////////////////////////////////////////////////////////
	/// Stage-1 variables
	dtype_f shift_register_s10_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s10];
	dtype_f shift_register_s10_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s10];
	dtype_int i_s10,j_s10;
	dtype_f input_s10[FFT_LEN];
	#ifdef USE_CIRCULAR_BUFFERS
	int RD_PTR_s10;
	#endif
	///////////////////////////////////////////////////////////////////////
	#ifdef HLS_MODEL
	//////////////////////CLASS STATIC MEMBERS////////////////////////////////////////
	static const dtype_f twiddle_table_s10[FFT_LEN>>10];
	static const dtype_f twiddle_table_imag_s10[FFT_LEN>>10];
	//////////////////////////////////////////////////////////////
	#else
	///////////////////////////////////////////////////////////////////////////////////
	dtype_f twiddle_table_s10[FFT_LEN>>10];
	dtype_f twiddle_table_imag_s10[FFT_LEN>>10];
	#endif


#endif /* LOBAL_VARIABLES_STAGE10_H_ */ 
