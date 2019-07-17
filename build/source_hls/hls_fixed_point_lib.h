/* File Name : hls_fixed_point_lib.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef LS_FIXED_POINT_LIB_H_
#define LS_FIXED_POINT_LIB_H_




#define ADD_SYSTEMC_SIMULATION_SUPPORT_FUCNTIONS



#include "fixed_point_arithmetic_constants.h"




#include "dtype.h"


extern int round(int input ,  unsigned int in_frac_len ,unsigned int out_frac_len, unsigned int rmod);
extern int ovManager(int input , unsigned int input_len , unsigned int out_len ,unsigned int ov_mode );
extern int add(int in1, int  in2, unsigned int in1_len,unsigned int in2_len,unsigned int out_len,unsigned int in1_frac_len,unsigned int in2_frac_len,unsigned int out_frac_len,unsigned int rmod,unsigned int ov_mode,int default_mode);
extern int mul(int in1, int  in2, unsigned int in1_len,unsigned int in2_len,unsigned int out_len,unsigned int in1_frac_len,unsigned int in2_frac_len,unsigned int out_frac_len,unsigned int rmod,unsigned int ov_mode,int default_mode);
extern void butterfly(dtype_f temp1_real, dtype_f temp1_imag , dtype_f temp2_real , dtype_f twiddle_imag,dtype_f twiddle_real, dtype_f temp2_imag , dtype_f *temp_out_sum_real, dtype_f *temp_out_sum_imag, dtype_f *bout_real, dtype_f *bout_imag, int pINPUT_SAMPLE_BIT_WIDTH , int pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,int pTWIDDLE_FACTORS_BIT_WIDTH, int pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,  int pTRUNCATE_MODE , int pSATURATION_MODE, int default_mode);



#ifdef ADD_SYSTEMC_SIMULATION_SUPPORT_FUCNTIONS

extern int toQ(double number,unsigned int num_len,unsigned int frac_len);
extern double toFloat(int number,unsigned int num_len,unsigned int frac_len);
#endif


#endif /* LS_FIXED_POINT_LIB_H_ */ 
