/* File Name : global_variables_stage1.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef LOBAL_VARIABLES_STAGE1_H_
#define LOBAL_VARIABLES_STAGE1_H_

	//Global Schedule control variabels for stage:1
	int GLOBAL_OUTER_ITERATION_COUNTER_s1;
#ifdef HLS_MODEL
	sc_signal<int> GLOBAL_INNER_ITERATION_COUNTER_s1;
#else 
	int GLOBAL_INNER_ITERATION_COUNTER_s1;
#endif 
	///////////////////////////////////////////////////////////////////////
	/// Stage-1 variables
	dtype_f shift_register_s1_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s1];
	dtype_f shift_register_s1_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s1];
	dtype_int i_s1,j_s1;
	dtype_f input_s1[FFT_LEN];
	#ifdef USE_CIRCULAR_BUFFERS
	int RD_PTR_s1;
	#endif
	///////////////////////////////////////////////////////////////////////
	#ifdef HLS_MODEL
	//////////////////////CLASS STATIC MEMBERS////////////////////////////////////////
	static const dtype_f twiddle_table_s1[FFT_LEN>>1];
	static const dtype_f twiddle_table_imag_s1[FFT_LEN>>1];
	//////////////////////////////////////////////////////////////
	#else
	///////////////////////////////////////////////////////////////////////////////////
	dtype_f twiddle_table_s1[FFT_LEN>>1];
	dtype_f twiddle_table_imag_s1[FFT_LEN>>1];
	#endif


#endif /* LOBAL_VARIABLES_STAGE1_H_ */ 
