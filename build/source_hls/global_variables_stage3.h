/* File Name : global_variables_stage3.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef LOBAL_VARIABLES_STAGE3_H_
#define LOBAL_VARIABLES_STAGE3_H_

	//Global Schedule control variabels for stage:3
	int GLOBAL_OUTER_ITERATION_COUNTER_s3;
	///////////////////////////////////////////////////////////////////////
	/// Stage-1 variables
	dtype_f shift_register_s3_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s3];
	dtype_f shift_register_s3_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s3];
	dtype_int i_s3,j_s3;
	dtype_f input_s3[FFT_LEN];
	#ifdef USE_CIRCULAR_BUFFERS
	int RD_PTR_s3;
	#endif
	///////////////////////////////////////////////////////////////////////
	#ifdef HLS_MODEL
	//////////////////////CLASS STATIC MEMBERS////////////////////////////////////////
	static const dtype_f twiddle_table_s3[FFT_LEN>>3];
	static const dtype_f twiddle_table_imag_s3[FFT_LEN>>3];
	//////////////////////////////////////////////////////////////
	#else
	///////////////////////////////////////////////////////////////////////////////////
	dtype_f twiddle_table_s3[FFT_LEN>>3];
	dtype_f twiddle_table_imag_s3[FFT_LEN>>3];
	#endif


#endif /* LOBAL_VARIABLES_STAGE3_H_ */ 
