/* File Name : global_variables_stage9.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef LOBAL_VARIABLES_STAGE9_H_
#define LOBAL_VARIABLES_STAGE9_H_

	//Global Schedule control variabels for stage:9
	int GLOBAL_OUTER_ITERATION_COUNTER_s9;
	///////////////////////////////////////////////////////////////////////
	/// Stage-1 variables
	dtype_f shift_register_s9_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s9];
	dtype_f shift_register_s9_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s9];
	dtype_int i_s9,j_s9;
	dtype_f input_s9[FFT_LEN];
	#ifdef USE_CIRCULAR_BUFFERS
	int RD_PTR_s9;
	#endif
	///////////////////////////////////////////////////////////////////////
	#ifdef HLS_MODEL
	//////////////////////CLASS STATIC MEMBERS////////////////////////////////////////
	static const dtype_f twiddle_table_s9[FFT_LEN>>9];
	static const dtype_f twiddle_table_imag_s9[FFT_LEN>>9];
	//////////////////////////////////////////////////////////////
	#else
	///////////////////////////////////////////////////////////////////////////////////
	dtype_f twiddle_table_s9[FFT_LEN>>9];
	dtype_f twiddle_table_imag_s9[FFT_LEN>>9];
	#endif


#endif /* LOBAL_VARIABLES_STAGE9_H_ */ 
