/* File Name : global_variables_stage4.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef LOBAL_VARIABLES_STAGE4_H_
#define LOBAL_VARIABLES_STAGE4_H_

	//Global Schedule control variabels for stage:4
	int GLOBAL_OUTER_ITERATION_COUNTER_s4;
	///////////////////////////////////////////////////////////////////////
	/// Stage-1 variables
	dtype_f shift_register_s4_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s4];
	dtype_f shift_register_s4_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s4];
	dtype_int i_s4,j_s4;
	dtype_f input_s4[FFT_LEN];
	#ifdef USE_CIRCULAR_BUFFERS
	int RD_PTR_s4;
	#endif
	///////////////////////////////////////////////////////////////////////
	#ifdef HLS_MODEL
	//////////////////////CLASS STATIC MEMBERS////////////////////////////////////////
	static const dtype_f twiddle_table_s4[FFT_LEN>>4];
	static const dtype_f twiddle_table_imag_s4[FFT_LEN>>4];
	//////////////////////////////////////////////////////////////
	#else
	///////////////////////////////////////////////////////////////////////////////////
	dtype_f twiddle_table_s4[FFT_LEN>>4];
	dtype_f twiddle_table_imag_s4[FFT_LEN>>4];
	#endif


#endif /* LOBAL_VARIABLES_STAGE4_H_ */ 
