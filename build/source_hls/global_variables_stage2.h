/* File Name : global_variables_stage2.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef LOBAL_VARIABLES_STAGE2_H_
#define LOBAL_VARIABLES_STAGE2_H_

	//Global Schedule control variabels for stage:2
	int GLOBAL_OUTER_ITERATION_COUNTER_s2;
	///////////////////////////////////////////////////////////////////////
	/// Stage-1 variables
	dtype_f shift_register_s2_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s2];
	dtype_f shift_register_s2_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s2];
	dtype_int i_s2,j_s2;
	dtype_f input_s2[FFT_LEN];
	#ifdef USE_CIRCULAR_BUFFERS
	int RD_PTR_s2;
	#endif
	///////////////////////////////////////////////////////////////////////
	#ifdef HLS_MODEL
	//////////////////////CLASS STATIC MEMBERS////////////////////////////////////////
	static const dtype_f twiddle_table_s2[FFT_LEN>>2];
	static const dtype_f twiddle_table_imag_s2[FFT_LEN>>2];
	//////////////////////////////////////////////////////////////
	#else
	///////////////////////////////////////////////////////////////////////////////////
	dtype_f twiddle_table_s2[FFT_LEN>>2];
	dtype_f twiddle_table_imag_s2[FFT_LEN>>2];
	#endif


#endif /* LOBAL_VARIABLES_STAGE2_H_ */ 
