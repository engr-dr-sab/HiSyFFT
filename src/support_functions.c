#include "support_functions.h"
#include <math.h>
#include <string.h>
int mf_log2(int x)
{
	double temp = (double)x;
	temp =log2(temp);
	return (int)temp;
	//return (int)(log((float)x)/log((float)2));

}
int power2(int x) 
{
	int prd=1;
	int i;
	for (i = 0; i < x; i++)
	{
		/* code */
		prd=prd*2;
	}
	return prd;
}

//as

void print_BODY_hls_fixed_point_lib_dot_h(FILE *fptr,int fft_len,int total_stages)
{
	fprintf(fptr,"\n\n\n#define ADD_SYSTEMC_SIMULATION_SUPPORT_FUCNTIONS\n\n");
	fprintf(fptr, "\n\n#include \"fixed_point_arithmetic_constants.h\"\n\n\n");
	fprintf(fptr, "\n\n#include \"dtype.h\"\n\n\n");
	fprintf(fptr,"extern int round(int input ,  unsigned int in_frac_len ,unsigned int out_frac_len, unsigned int rmod);\n");
	fprintf(fptr,"extern int ovManager(int input , unsigned int input_len , unsigned int out_len ,unsigned int ov_mode );\n");
	fprintf(fptr,"extern int add(int in1, int  in2, unsigned int in1_len,unsigned int in2_len,unsigned int out_len,unsigned int in1_frac_len,unsigned int in2_frac_len,unsigned int out_frac_len,unsigned int rmod,unsigned int ov_mode,int default_mode);\n");
	fprintf(fptr,"extern int mul(int in1, int  in2, unsigned int in1_len,unsigned int in2_len,unsigned int out_len,unsigned int in1_frac_len,unsigned int in2_frac_len,unsigned int out_frac_len,unsigned int rmod,unsigned int ov_mode,int default_mode);\n");
	fprintf(fptr,"extern void butterfly(dtype_f temp1_real, dtype_f temp1_imag , dtype_f temp2_real , dtype_f twiddle_imag,dtype_f twiddle_real, dtype_f temp2_imag , dtype_f *temp_out_sum_real, dtype_f *temp_out_sum_imag, dtype_f *bout_real, dtype_f *bout_imag, int pINPUT_SAMPLE_BIT_WIDTH , int pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,int pTWIDDLE_FACTORS_BIT_WIDTH, int pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,  int pTRUNCATE_MODE , int pSATURATION_MODE, int default_mode);\n");

	fprintf(fptr,"\n\n\n#ifdef ADD_SYSTEMC_SIMULATION_SUPPORT_FUCNTIONS\n\n");
	fprintf(fptr,"extern int toQ(double number,unsigned int num_len,unsigned int frac_len);\n");
	
	fprintf(fptr,"extern double toFloat(int number,unsigned int num_len,unsigned int frac_len);\n");
	
	fprintf(fptr,"#endif\n");
}
void print_BODY_hls_fixed_point_lib_dot_cpp(FILE *fptr,int fft_len,int total_stages)
{
	fprintf(fptr, "\n\n\n#include \"dtype.h\"\n");
	fprintf(fptr, "#include \"hls_fixed_point_lib.h\"\n\n\n");
	fprintf(fptr,"//@@2_function_number:fft_support_functions\n");
	fprintf(fptr,"// Generic round function  \n");
	fprintf(fptr,"int round(int input ,  unsigned int in_frac_len ,unsigned int out_frac_len, unsigned int rmod)\n");
	fprintf(fptr,"{\n");
	fprintf(fptr,"    unsigned int no_of_bits_truncated;\n");
	fprintf(fptr,"	int output =input;\n");
	fprintf(fptr,"	\n");
	fprintf(fptr,"	if( in_frac_len > out_frac_len)\n");
	fprintf(fptr,"	{\n");
	fprintf(fptr,"	    no_of_bits_truncated = in_frac_len - out_frac_len;\n");
	fprintf(fptr,"		if(rmod==TRUNCATE_MODE)\n");
	fprintf(fptr,"			 output = output >> no_of_bits_truncated;\n");
	fprintf(fptr,"		else if(rmod==ROUND_MODE)\n");
	fprintf(fptr,"		output = (((output & (1<<(no_of_bits_truncated-1))) != 0) && (((output & ((1<<(no_of_bits_truncated-1))-1)) != 0) || (output > 0))) + (output >> no_of_bits_truncated);\n");
	fprintf(fptr,"		else if(rmod==CEIL_MODE)\n");
	fprintf(fptr,"		output = ((output & (((1<<(no_of_bits_truncated))-1))) != 0) + (output >> no_of_bits_truncated);\n");
	fprintf(fptr,"    }\n");
	fprintf(fptr,"	else if( out_frac_len > in_frac_len)\n");
	fprintf(fptr,"	{\n");
	fprintf(fptr,"	    output = output << (out_frac_len - in_frac_len);\n");
	fprintf(fptr,"	}\n");
	fprintf(fptr,"	return output;\n");
	fprintf(fptr,"}\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"int ovManager(int input , unsigned int input_len , unsigned int out_len ,unsigned int ov_mode )\n");
	fprintf(fptr,"{\n");
	fprintf(fptr,"	int output = input;\n");
	fprintf(fptr,"	int testDig;\n");
	fprintf(fptr,"	/*if(input_len >= out_len)\n");
	fprintf(fptr,"	{*/\n");
	fprintf(fptr,"		if(ov_mode == SATURATION_MODE)\n");
	fprintf(fptr,"		{\n");
	fprintf(fptr,"			if( output > (((1<<(out_len-1))-1)) )\n");
	fprintf(fptr,"			output = ((1<<(out_len-1))-1);\n");
	fprintf(fptr,"			else if (output < (-1*(1<<(out_len-1))))\n");
	fprintf(fptr,"			{\n");
	fprintf(fptr,"				output = (-1*(1<<(out_len-1))) ;\n");
	fprintf(fptr,"			}\n");
	fprintf(fptr,"		}\n");
	fprintf(fptr,"		else if(ov_mode == WRAP_MODE)\n");
	fprintf(fptr,"		{\n");
	fprintf(fptr,"		   // Check for msb and extended it in case of wrapping\n");
	fprintf(fptr,"		   if( ((output>>(out_len-1)) & 1)==1 ) // Extract the sign bit \n");
	fprintf(fptr,"		   output = output | ((((1<<(32-out_len-1))-1)<<1)|1)<<out_len;  //(( (1<<(32-input_len))-1)<<(input_len)) ;  //sign extend the number     // ((1<<out_len) - 1);\n");
	fprintf(fptr,"		   else\n");
	fprintf(fptr,"		   output = output & ((1 << input_len)-1);\n");
	fprintf(fptr,"		}\n");
	fprintf(fptr,"	/*}\\n");
	fprintf(fptr,"	else\n");
	fprintf(fptr,"	{\n");
	fprintf(fptr,"			return output; \n");
	fprintf(fptr,"	}*/\n");
	fprintf(fptr,"		testDig  = output;\n");
	fprintf(fptr,"	output = (output &  (( ((1<<(out_len-1)) -1) << 1)|1)); ///-------c---cc--\n");
	fprintf(fptr,"	if( ((output>>(out_len-1)) & 1)==1 ) // Extract the sign bit \n");
	fprintf(fptr,"		    output = output | ((((1<<(32-out_len-1))-1)<<1)|1)<<out_len; // (( (1<<(32-input_len))-1)<<(input_len));sign extend the number     // ((1<<out_len) - 1);\n");
	fprintf(fptr,"		   else\n");
	fprintf(fptr,"		    output = output & (((1 << (out_len-1))-1)<<1)|1;\n");
	fprintf(fptr,"	/*if(testDig!=output)\n");
	fprintf(fptr,"		printf(\"The ouput mismatch.......\n\");*/\n");
	fprintf(fptr,"	return output;\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"}\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"int add(int in1, int  in2, unsigned int in1_len,unsigned int in2_len,unsigned int out_len,unsigned int in1_frac_len,unsigned int in2_frac_len,unsigned int out_frac_len,unsigned int rmod,unsigned int ov_mode,int default_mode)\n");
	fprintf(fptr,"{\n");
	fprintf(fptr,"    int add,output;\n");
	fprintf(fptr,"	int in1_temp,in2_temp;\n");
	fprintf(fptr,"	unsigned int new_frac_len;\n");
	fprintf(fptr,"	unsigned int new_int_len;\n");
	fprintf(fptr,"	unsigned int new_len;\n");
	fprintf(fptr,"	unsigned int max_frac_len;\n");
	fprintf(fptr,"	unsigned int add_fraction_len,add_integer_len,add_len,no_of_bits_truncated,add_len_after_round;\n");
	fprintf(fptr,"    ////////////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	// If it is a default mode then \n");
	fprintf(fptr,"	if(default_mode==1)\n");
	fprintf(fptr,"	{\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"		new_len = in1_len > in2_len ? in1_len : in2_len;\n");
	fprintf(fptr,"		new_int_len = ((in1_len - in1_frac_len) > (in2_len - in2_frac_len)) ? (in1_len - in1_frac_len):(in1_len - in2_frac_len);\n");
	fprintf(fptr,"		new_frac_len = new_len - new_int_len;\n");
	fprintf(fptr,"		max_frac_len = in1_frac_len > in2_frac_len ? in1_frac_len : in2_frac_len;\n");
	fprintf(fptr,"	    if(in1_frac_len > in2_frac_len)\n");
	fprintf(fptr,"		 {\n");
	fprintf(fptr,"			 in1_temp = in1;\n");
	fprintf(fptr,"			 in2_temp = in2 << (in1_frac_len- in2_frac_len);		 \n");
	fprintf(fptr,"			 \n");
	fprintf(fptr,"		 }\n");
	fprintf(fptr,"		 else if(in1_frac_len < in2_frac_len)\n");
	fprintf(fptr,"		 {\n");
	fprintf(fptr,"			 in1_temp = in1 <<(in2_frac_len - in1_frac_len);		\n");
	fprintf(fptr,"			 in2_temp = in2;\n");
	fprintf(fptr,"			 \n");
	fprintf(fptr,"		 }\n");
	fprintf(fptr,"		 else\n");
	fprintf(fptr,"		 {\n");
	fprintf(fptr,"		   in1_temp = in1;\n");
	fprintf(fptr,"		   in2_temp = in2;\n");
	fprintf(fptr,"		 }	 \n");
	fprintf(fptr,"	   output =  in1_temp+in2_temp;\n");
	fprintf(fptr,"	   output =  output >> (max_frac_len - new_frac_len);\n");
	fprintf(fptr,"	   if( ((output>>(new_len-1)) & 1)==1 ) // Mask to find the MSB ...IE the sign bit\n");
	fprintf(fptr,"		   output = output | (( (1<<(32-new_len+1))-1)<<new_len) ; // Sign extens the ouput // ((1<<new_len) - 1);\n");
	fprintf(fptr,"	   else\n");
	fprintf(fptr,"		   output = output & ((1 << new_len)-1);\n");
	fprintf(fptr,"	 return output;\n");
	fprintf(fptr,"	}\n");
	fprintf(fptr,"	////////////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	else\n");
	fprintf(fptr,"	{\n");
	fprintf(fptr,"		/// check what is the rounding mode and then round the number\n");
	fprintf(fptr,"		 add_fraction_len = (in1_frac_len > in1_frac_len ? in1_frac_len:in2_frac_len);\n");
	fprintf(fptr,"		 add_integer_len = ((in1_len - in1_frac_len) > (in2_len - in2_frac_len)) ? (in1_len - in1_frac_len):(in1_len - in2_frac_len);\n");
	fprintf(fptr,"		 add_len = add_fraction_len + add_integer_len;\n");
	fprintf(fptr,"		 add_len_after_round = 	out_frac_len + add_integer_len;\n");
	fprintf(fptr,"		 // Align the Binary Points\n");
	fprintf(fptr,"		 no_of_bits_truncated = add_fraction_len - out_frac_len;\n");
	fprintf(fptr,"		 if(in1_frac_len > in2_frac_len)\n");
	fprintf(fptr,"		 {\n");
	fprintf(fptr,"			 in1_temp = in1;\n");
	fprintf(fptr,"			 in2_temp = in2 << (in1_frac_len- in2_frac_len);		  \n");
	fprintf(fptr,"		 }\n");
	fprintf(fptr,"		 else if(in1_frac_len < in2_frac_len)\n");
	fprintf(fptr,"		 {\n");
	fprintf(fptr,"			 in1_temp = in1 <<(in2_frac_len - in1_frac_len);		\n");
	fprintf(fptr,"			 in2_temp = in2; \n");
	fprintf(fptr,"		 }\n");
	fprintf(fptr,"		 else\n");
	fprintf(fptr,"		 {\n");
	fprintf(fptr,"		   in1_temp = in1;\n");
	fprintf(fptr,"		   in2_temp = in2;\n");
	fprintf(fptr,"		 }\n");
	fprintf(fptr,"		 /// Perfoerm Addition after the binary points are aligned \n");
	fprintf(fptr,"		 add =  in1_temp + in2_temp;\n");
	fprintf(fptr,"		 add = round( add,add_fraction_len,out_frac_len,rmod);\n");
	fprintf(fptr,"		 add = ovManager(add,add_len_after_round,out_len,ov_mode);\n");
	fprintf(fptr,"		return add;\n");
	fprintf(fptr,"	}\n");
	fprintf(fptr,"	\n");
	fprintf(fptr,"}\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"int mul(int in1, int  in2, unsigned int in1_len,unsigned int in2_len,unsigned int out_len,unsigned int in1_frac_len,unsigned int in2_frac_len,unsigned int out_frac_len,unsigned int rmod,unsigned int ov_mode,int default_mode)\n");
	fprintf(fptr,"{\n");
	fprintf(fptr,"    ///                                                                                                                                                  \n");
	fprintf(fptr,"    int prd,output,sat_flag;\n");
	fprintf(fptr,"	int in1_temp,in2_temp;\n");
	fprintf(fptr,"	unsigned int prd_fraction_len,prd_integer_len,prd_len,no_of_bits_truncated,prd_len_after_round;\n");
	fprintf(fptr,"//	unsigned int new_frac_len;\n");
	fprintf(fptr,"//	unsigned int new_int_len;\n");
	fprintf(fptr,"	unsigned int new_len;\n");
	fprintf(fptr,"	unsigned int max_int_len;\n");
	fprintf(fptr,"	unsigned int max_frac_len;\n");
	fprintf(fptr,"	////////////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	// If it is a default mode then \n");
	fprintf(fptr,"	if(default_mode==1)\n");
	fprintf(fptr,"	{\n");
	fprintf(fptr,"		\n");
	fprintf(fptr,"		\n");
	fprintf(fptr,"		max_int_len = ((in1_len - in1_frac_len) > (in2_len - in2_frac_len)) ? (in1_len - in1_frac_len):(in1_len - in2_frac_len);\n");
	fprintf(fptr,"		max_frac_len = in1_frac_len > in2_frac_len ? in1_frac_len : in2_frac_len;\n");
	fprintf(fptr,"		new_len = 2*max_frac_len + 2*max_int_len;\n");
	fprintf(fptr,"	    if(in1_frac_len > in2_frac_len)\n");
	fprintf(fptr,"		 {\n");
	fprintf(fptr,"			 in1_temp = in1;\n");
	fprintf(fptr,"			 in2_temp = in2 << (in1_frac_len- in2_frac_len);		 \n");
	fprintf(fptr,"			 \n");
	fprintf(fptr,"		 }\n");
	fprintf(fptr,"		 else if(in1_frac_len < in2_frac_len)\n");
	fprintf(fptr,"		 {\n");
	fprintf(fptr,"			 in1_temp = in1 <<(in2_frac_len - in1_frac_len);		\n");
	fprintf(fptr,"			 in2_temp = in2;\n");
	fprintf(fptr,"			 \n");
	fprintf(fptr,"		 }\n");
	fprintf(fptr,"		 else\n");
	fprintf(fptr,"		 {\n");
	fprintf(fptr,"		   in1_temp = in1;\n");
	fprintf(fptr,"		   in2_temp = in2;\n");
	fprintf(fptr,"		 }	\n");
	fprintf(fptr,"	  output=  in1_temp*in2_temp;\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"	   if( ((output>>(new_len-1)) & 1)==1 )\n");
	fprintf(fptr,"		   output = output | (( (1<<(32-new_len+1))-1)<<new_len) ;      // ((1<<out_len) - 1);\n");
	fprintf(fptr,"	   else\n");
	fprintf(fptr,"		   output = output & ((1 << new_len)-1);\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"	   	   return output;\n");
	fprintf(fptr,"	}\n");
	fprintf(fptr,"	////////////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	else\n");
	fprintf(fptr,"	{\n");
	fprintf(fptr,"		prd = in1*in2;\n");
	fprintf(fptr,"		/// check what is the rounding mode and then round the number\n");
	fprintf(fptr,"		prd_fraction_len = in1_frac_len +  in2_frac_len;\n");
	fprintf(fptr,"		prd_integer_len = (in1_len - in1_frac_len) + (in2_len - in2_frac_len);\n");
	fprintf(fptr,"		prd_len = in1_len + in2_len;\n");
	fprintf(fptr,"		no_of_bits_truncated = prd_fraction_len - out_frac_len;\n");
	fprintf(fptr,"		sat_flag = prd_len - (out_len);\n");
	fprintf(fptr,"		prd_len_after_round = out_frac_len + prd_integer_len;\n");
	fprintf(fptr,"		\n");
	fprintf(fptr,"		prd = round(prd,prd_fraction_len,out_frac_len,rmod);\n");
	fprintf(fptr,"		// if( no_of_bits_truncated > 0)\n");
	fprintf(fptr,"		// {\n");
	fprintf(fptr,"			// if(rmod==TRUNCATE_MODE)\n");
	fprintf(fptr,"				 // prd = prd >> no_of_bits_truncated;\n");
	fprintf(fptr,"			// else if(rmod==ROUND_MODE)\n");
	fprintf(fptr,"			// prd = (((prd & (1<<(no_of_bits_truncated-1))) != 0) && (((prd & ((1<<(no_of_bits_truncated-1))-1)) != 0) || (prd > 0))) + (prd >> no_of_bits_truncated);\n");
	fprintf(fptr,"			// else if(rmod==CEIL_MODE)\n");
	fprintf(fptr,"			// prd = ((prd & (((1<<(no_of_bits_truncated))-1))) != 0) + (prd >> no_of_bits_truncated);\n");
	fprintf(fptr,"		// }\n");
	fprintf(fptr,"		prd = ovManager(prd,prd_len_after_round,out_len,ov_mode);\n");
	fprintf(fptr,"		\n");
	fprintf(fptr,"		return prd;\n");
	fprintf(fptr,"	}\n");
	fprintf(fptr,"}\n");

fprintf(fptr,"	void butterfly(dtype_f temp1_real, dtype_f temp1_imag , dtype_f temp2_real , dtype_f twiddle_imag,dtype_f twiddle_real, dtype_f temp2_imag , dtype_f *temp_out_sum_real, dtype_f *temp_out_sum_imag, dtype_f *bout_real, dtype_f *bout_imag, int pINPUT_SAMPLE_BIT_WIDTH , int pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,int pTWIDDLE_FACTORS_BIT_WIDTH, int pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,  int pTRUNCATE_MODE , int pSATURATION_MODE, int default_mode)\n");
fprintf(fptr,"{\n");
fprintf(fptr,"	dtype_f bout_imag_part1,bout_real_part1;\n");
fprintf(fptr,"	dtype_f bout_imag_part2,bout_real_part2;\n");
fprintf(fptr,"\n");	
fprintf(fptr,"	dtype_f temp_out_diff_real;\n");
fprintf(fptr,"	dtype_f temp_out_diff_imag;\n");
fprintf(fptr,"	//dtype_f temp_out_diff_real,temp_out_sum_imag,temp_out_diff_imag\n");
fprintf(fptr,"	*temp_out_sum_real=add(temp1_real,temp2_real,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"	//temp_out_sum_imag =temp1_imag+temp2_imag;\n");
fprintf(fptr,"	*temp_out_sum_imag=add(temp1_imag,temp2_imag,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"	//temp_out_diff_real=(temp1_real-temp2_real);\n");
fprintf(fptr,"	temp_out_diff_real=add(temp1_real,-temp2_real,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"	temp_out_diff_imag=(temp1_imag-temp2_imag); \n");
fprintf(fptr,"	temp_out_diff_imag=add(temp1_imag,-temp2_imag,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"	//bout_real=(temp_out_diff_real*twiddle_real+temp_out_diff_imag*twiddle_imag);\n");
fprintf(fptr,"	//bout_real_part1 = temp_out_diff_real*twiddle_real;\n");
fprintf(fptr,"	bout_real_part1=mul(temp_out_diff_real,twiddle_real,pINPUT_SAMPLE_BIT_WIDTH,pTWIDDLE_FACTORS_BIT_WIDTH,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"	//bout_real_part2 = temp_out_diff_imag*twiddle_imag;\n");
fprintf(fptr,"	bout_real_part2=mul(temp_out_diff_imag,twiddle_imag,pINPUT_SAMPLE_BIT_WIDTH,pTWIDDLE_FACTORS_BIT_WIDTH,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"	//bout_real = bout_real_part1+bout_real_part2;\n");
fprintf(fptr,"	*bout_real=add(bout_real_part1,-bout_real_part2,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"	//bout_imag=(temp_out_diff_imag*twiddle_real-temp_out_diff_real*twiddle_imag);\n");
fprintf(fptr,"	//bout_imag_part1=temp_out_diff_imag*twiddle_reala;\n");
fprintf(fptr,"	bout_imag_part1=mul(temp_out_diff_imag,twiddle_real,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"	//bout_imag_part2=temp_out_diff_real*twiddle_imag;\n");
fprintf(fptr,"	bout_imag_part2=mul(temp_out_diff_real,twiddle_imag,pINPUT_SAMPLE_BIT_WIDTH,pTWIDDLE_FACTORS_BIT_WIDTH,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"	//bout_imag=bout_imag_part1+bout_imag_part2;\n");
fprintf(fptr,"	*bout_imag=add(bout_imag_part1,bout_imag_part2,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);\n");
fprintf(fptr,"}\n");



	fprintf(fptr,"#ifdef ADD_SYSTEMC_SIMULATION_SUPPORT_FUCNTIONS\n");
	fprintf(fptr,"int toQ(double number,unsigned int num_len,unsigned int frac_len)\n");
	fprintf(fptr,"{\n");
	fprintf(fptr,"	  int repMax,repMin,fixed;\n");
	fprintf(fptr,"	  double temp;\n");
	fprintf(fptr,"	  \n");
	fprintf(fptr,"	  repMax = (1<<(num_len-1))-1;\n");
	fprintf(fptr,"	  repMin = -(1<<(num_len-1));\n");
	fprintf(fptr,"	  temp =  number * (1<<frac_len);\n");
	fprintf(fptr,"	  fixed  =  (int)(temp);\n");
	fprintf(fptr,"	  if(fixed > repMax)\n");
	fprintf(fptr,"		  fixed = repMax;\n");
	fprintf(fptr,"	  else if(fixed < repMin)\n");
	fprintf(fptr,"		  fixed = repMin;\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"	  return fixed;\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"}\n");
	fprintf(fptr,"double toFloat(int number,unsigned int num_len,unsigned int frac_len)\n");
	fprintf(fptr,"{\n");
	fprintf(fptr,"	unsigned int steps;\n");
	fprintf(fptr,"	double resolution,output;\n");
	fprintf(fptr,"	steps = 1<<(frac_len);\n");
	fprintf(fptr,"	resolution  = ((double)1)/((double)steps);\n");
	fprintf(fptr,"	output = resolution * number;\n");
	fprintf(fptr,"	return output;\n");
	fprintf(fptr,"}\n");
	fprintf(fptr,"#endif\n");
}



void print_BODY_fixed_point_arithmetic_constants_dot_h(FILE *fptr,int fft_len,int total_stages)
{
fprintf(fptr,"#define TRUNCATE_MODE 0\n");
fprintf(fptr,"#define ROUND_MODE 1\n");
fprintf(fptr,"#define CEIL_MODE 2\n");
fprintf(fptr,"#define WRAP_MODE 3\n");
fprintf(fptr,"#define SATURATION_MODE 4\n");
}

void createTwiddleTable(FILE *fptr,int fft_len,int stage_number,int twiddle_factor_bit_width,int twiddle_table_fraction_width)
{
	//FILE *fptr;
int i;
double re,im;
int real,imag;
int k;

double PI = ((double)22/(double)7);

  for(i=0;i<(fft_len>>stage_number);i++)
  {
	  k=i<<(stage_number-1);
	  re = cos((2*PI*k)/fft_len);
	  im = -sin((2*PI*k)/fft_len);
	  real = toQ(re,twiddle_factor_bit_width,twiddle_table_fraction_width);
	  imag = toQ(im,twiddle_factor_bit_width,twiddle_table_fraction_width);
	  //fprintf(fptr," %d + (%di);",(signed short)ccin[loo].real,(signed short)ccin[loo].imag);
	  if(i==0)
	  {
		  if((fft_len>>stage_number)==1)
		   fprintf(fptr,"{ %d",real);
		  else
		   fprintf(fptr,"{ %d,",real);


	  }
	  else 
		  {
			  if(i==((fft_len>>stage_number)-1))
			  fprintf(fptr," %d };\n",real);
			  else
				  fprintf(fptr,"%d,",real);
	     }

	  if((i%20==0 && i!=0))
		   fprintf(fptr,"\n");
	  if((i==0 && (fft_len>>stage_number)==1 ))
		  fprintf(fptr,"};\n");

  }
}
void createTwiddleTable_image(FILE *fptr,int fft_len,int stage_number,int twiddle_factor_bit_width,int twiddle_table_fraction_width)
{
	//FILE *fptr;
int i;
double re,im;
int real,imag;
int k;

double PI = ((double)22/(double)7);

  for(i=0;i<(fft_len>>stage_number);i++)
  {
	  k=i<<(stage_number-1);
	  re = cos((2*PI*k)/fft_len);
	  im = -sin((2*PI*k)/fft_len);
	  real = toQ(re,twiddle_factor_bit_width,twiddle_table_fraction_width);
	  imag = toQ(im,twiddle_factor_bit_width,twiddle_table_fraction_width);
	  //fprintf(fptr," %d + (%di);",(signed short)ccin[loo].real,(signed short)ccin[loo].imag);
	  if(i==0)
	  {
		  if((fft_len>>stage_number)==1)
		   fprintf(fptr,"{ %d",imag);
		  else
		   fprintf(fptr,"{ %d,",imag);


	  }
	  else 
		  {
			  if(i==((fft_len>>stage_number)-1))
			  fprintf(fptr," %d };\n",imag);
			  else
				  fprintf(fptr,"%d,",imag);
	     }

	  if((i%20==0 & i!=0))
		   fprintf(fptr,"\n");
	  if((i==0 && (fft_len>>stage_number)==1 ))
		  fprintf(fptr,"};\n");

  }
}

void print_BODY_setup_script_dot_tcl(FILE *fptr,int fft_len,int total_stages)
{
	int i;
		fprintf(fptr,"set POWER_GATE true\n");
		fprintf(fptr,"\n");
		fprintf(fptr,"if {[get_design] == \"\"} then {\n");
		fprintf(fptr,"        new_design pipeLinedFFT_WRAPPER\n");
		fprintf(fptr,"  } else {\n");
		fprintf(fptr,"                        close_design\n");
		fprintf(fptr,"                        new_design pipeLinedFFT_WRAPPER\n");
		fprintf(fptr," }\n");
		fprintf(fptr," set_attr auto_write_models \"true\" [get_design]\n");
		
		fprintf(fptr," define_sim_config -model_dir \"./model\" [get_design]\n");
		fprintf(fptr," ######################################################################################\n");
		fprintf(fptr," ##############Uncomment the directive below for testbench specs#######################\n");
		fprintf(fptr," ######################################################################################\n");
		fprintf(fptr," #define_sim_config -testbench_files \"\" [get_design]\n");
		fprintf(fptr," #define_sim_config -testbench_kind \"self_checking\" [get_design]\n");
		fprintf(fptr," #define_sim_config -makefile_name \"Makefile.sim\" [get_design]\n");
		fprintf(fptr," #define_sim_config -simulator_args \"-top sc_main -Iinc -Itb\" [get_design]\n");
		fprintf(fptr," #define_sim_config -success_msg \"PASS: Simulation completed.\" [get_design]\n");
		fprintf(fptr," ######################################################################################\n");
		fprintf(fptr," ######################################################################################\n");
		fprintf(fptr," set_attr source_files [list ./source_hls/pipeLinedFFT_WRAPPER.cpp ./source_hls/hls_fixed_point_lib.cpp ] [get_design]\n");
		fprintf(fptr," set_attr header_files [list ./source_hls/fixed_point_arithmetic_constants.h./source_hls/dtype.h ./source_hls/global_constants.h ./source_hls/pipeLinedFFT_WRAPPER.h");

		//fprintf(fptr,"./source_hls/global_constants_stage%d.h ",i);
		for ( i = 1; i <= total_stages; i++)
		{
			fprintf(fptr,"./source_hls/global_constants_stage%d.h ",i);
		}

		for ( i = 1; i <= total_stages; i++)
		{
			fprintf(fptr,"./source_hls/global_variables_stage%d.h ",i);
		}
		for ( i = 1; i <= total_stages; i++)
		{
			fprintf(fptr,"./source_hls/functional_behavior_stage%d.h ",i);
		}


		fprintf(fptr," ] [get_design] \n",i);


		//fprintf(fptr,"rce/pipeLinedFFT_WRAPPER.h source/stage1_functional_behavior.h source/stage2_functional_behavior.h source/stage3_functional_behavior.h source/pipeLinedFFT_WRAPPER.h] [get_design]\n");
		fprintf(fptr," set_attr compile_flags \" -w\" [get_design]\n");
		fprintf(fptr," ######################################################################################\n");
		fprintf(fptr," Uncomment this directive if you want to export memories during high level  synthesis\n");
		fprintf(fptr," # set_attr export_memories true [get_design]\n");
		fprintf(fptr," ######################################################################################\n");
		fprintf(fptr," set_attr top_module_path \"pipeLinedFFT_WRAPPER\" [get_design]\n");
		fprintf(fptr," set_attr build_flat \"true\" [get_design]\n");
		fprintf(fptr," set_attr default_export_memories \"true\" [get_design]\n");
		fprintf(fptr," define_clock -name clk -period 20000 -rise 0 -fall 10000\n");
		fprintf(fptr," set_attr tech_lib_names [list /tools/techlibs/umc/90nm_SP/fsd0a_a/2009Q2v2.0/GENERIC_CORE_1D0V/FrontEnd/synopsys/fsd0a_a_generic_core_ff1p1vm40c.lib /tools/techlibs/umc/90nm_SP/fsd0a_a/2009Q2v2.0/GENERIC_CORE_1D0V/FrontEnd/synopsys/fsd0a_a_generic_core_ss0p9v125c.lib /tools/techlibs/umc/90nm_SP/fsd0a_a/2009Q2v2.0/GENERIC_CORE_1D0V/FrontEnd/synopsys/fsd0a_a_generic_core_tt1v25c.lib] [get_design]\n");
		fprintf(fptr," set_attr low_power_clock_gating $POWER_GATE [get_design]\n");
		fprintf(fptr," build\n");
		fprintf(fptr," inline_calls -all\n");

}


void print_BODY_stimulus_top_dot_cpp(FILE *fptr, int fft_len, int input_sample_bit_width, int output_sample_bitwidth)
{
	fprintf(fptr,"\n");
	fprintf(fptr,"#include \"systemc.h\"\n");
	fprintf(fptr,"#include \"stimulus.h\"\n");
	fprintf(fptr,"#include \"pipeLinedFFT_WRAPPER.h\"\n");
	fprintf(fptr,"int sc_main(int argc, char *argv [])\n");
	fprintf(fptr,"{\n");
	fprintf(fptr,"	// Declare Signals for to connect processor and stimulus generator\n");
	fprintf(fptr,"	//////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	sc_clock clk;\n");
	fprintf(fptr,"	sc_signal < bool > reset;\n");
	fprintf(fptr,"	sc_signal < bool > start;\n");
	fprintf(fptr,"	sc_signal < bool > done;\n");
	fprintf(fptr,"	sc_signal < sc_int <%d> > sample_input_real;\n",input_sample_bit_width);
	fprintf(fptr,"	sc_signal < sc_int <%d> > sample_input_imag;\n",input_sample_bit_width);
	fprintf(fptr,"	sc_signal <sc_int <%d> > sample_output_real;\n",output_sample_bitwidth);
	fprintf(fptr,"	sc_signal <sc_int <%d> > sample_output_imag;\n",output_sample_bitwidth);
	fprintf(fptr,"	sc_signal <bool> ready;\n");
	fprintf(fptr,"	sc_signal <bool> done_sim ; // this signal will be asserted true when simulation finishes\n");
	fprintf(fptr,"	//////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"	// Create a VCD file for signal tracing\n");
	fprintf(fptr,"	//////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	sc_trace_file *wf= sc_create_vcd_trace_file(\"pipeLineFFT.vcd\");\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"	// trace signals to file\n");
	fprintf(fptr,"	/////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	sc_trace(wf,clk,\"clk\");\n");
	fprintf(fptr,"	sc_trace(wf,reset,\"reset\");\n");
	fprintf(fptr,"	sc_trace(wf,done,\"done\");\n");
	fprintf(fptr,"	sc_trace(wf,sample_input_real,\"sample_input_real\");\n");
	fprintf(fptr,"	sc_trace(wf,sample_input_imag,\"sample_input_imag\");\n");
	fprintf(fptr,"	sc_trace(wf,ready,\"ready\");\n");
	fprintf(fptr,"	sc_trace(wf,start,\"start\");\n");
	fprintf(fptr,"	sc_trace(wf,sample_output_imag,\"sample_output_imag\");\n");
	fprintf(fptr,"	sc_trace(wf,sample_output_real,\"sample_output_real\");\n");
	fprintf(fptr,"	// Instantiate a pipelined FFT processor for Simulation\n");
	fprintf(fptr,"	/////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	pipeLinedFFT_WRAPPER pipeFFTInstance(\"pipeFFTInstanceName\");\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"	// Wire the FFT processor\n");
	fprintf(fptr,"	/////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	pipeFFTInstance.clk(clk.signal());\n");
	fprintf(fptr,"	pipeFFTInstance.reset(reset);\n");
	fprintf(fptr,"	pipeFFTInstance.start(start);\n");
	fprintf(fptr,"	pipeFFTInstance.done(done);\n");
	fprintf(fptr,"	pipeFFTInstance.sample_input_real(sample_input_real);\n");
	fprintf(fptr,"	pipeFFTInstance.sample_input_imag(sample_input_imag);\n");
	fprintf(fptr,"	//pipeFFTInstance.clk(clk.signal());\n");
	fprintf(fptr,"	pipeFFTInstance.sample_output_real(sample_output_real);\n");
	fprintf(fptr,"	pipeFFTInstance.sample_output_imag(sample_output_imag);\n");
	fprintf(fptr,"	pipeFFTInstance.ready(ready);\n");
	fprintf(fptr,"    // Instantiate a stimulus generator for FFT processor\n");
	fprintf(fptr,"	/////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	stimulus stimGeneratorInstance(\"stimGeneratorInstanceName\");\n");
	fprintf(fptr,"	// Wire stimulus generator to FFT processor\n");
	fprintf(fptr,"	//////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"	stimGeneratorInstance.clk(clk.signal());\n");
	fprintf(fptr,"	stimGeneratorInstance.reset(reset);\n");
	fprintf(fptr,"	stimGeneratorInstance.start(start);\n");
	fprintf(fptr,"	stimGeneratorInstance.done(done);\n");
	fprintf(fptr,"	stimGeneratorInstance.sample_input_real(sample_input_real);\n");
	fprintf(fptr,"	stimGeneratorInstance.sample_input_imag(sample_input_imag);\n");
	fprintf(fptr,"	stimGeneratorInstance.sample_output_imag(sample_output_imag);\n");
	fprintf(fptr,"	stimGeneratorInstance.sample_output_real(sample_output_real);\n");
	fprintf(fptr,"	stimGeneratorInstance.ready(ready);\n");
	fprintf(fptr,"	stimGeneratorInstance.done_sim(done_sim);\n");
	fprintf(fptr,"    // Start simulation and wait until it is finished\n");
	fprintf(fptr,"	sc_start();\n");
	fprintf(fptr,"	while(done_sim.read()==false) wait();\n");
	fprintf(fptr,"	// stop signal tracing\n");
	fprintf(fptr,"	sc_close_vcd_trace_file(wf);\n");
	fprintf(fptr,"	wait();\n");
	fprintf(fptr,"	// stop simulation and return\n");
	fprintf(fptr,"	sc_stop();\n");
	fprintf(fptr,"	return 0;\n");
	fprintf(fptr,"}\n");
	fprintf(fptr,"\n");
}
//as

//as
void print_BODY_stimulus_dot_cpp(FILE *fptr, int fft_len, int no_of_sim_frame)
{
	

fprintf(fptr,"#include \"stimulus.h\"\n");
fprintf(fptr,"#include <stdio.h>\n");
fprintf(fptr,"#include <math.h>\n");
fprintf(fptr,"void stimulus::genSim(void)\n");
fprintf(fptr,"{\n");
fprintf(fptr,"	int i,real,imag;\n");
fprintf(fptr,"	float real_in,imag_in,pi,angle;\nfloat f0=0.2;\n");
fprintf(fptr,"	wait();\n");
fprintf(fptr,"	reset.write(true);\n");
fprintf(fptr,"	wait();\n");
fprintf(fptr,"	reset.write(false);\n");
fprintf(fptr,"	wait();\n");
fprintf(fptr,"	while(ready.read()==false)\n\twait();\n");
fprintf(fptr,"	start.write(true);\n");
fprintf(fptr,"	GEN_SIM:\n");
fprintf(fptr,"	for(i=0;i<(%d*%d);i++)\n",fft_len,no_of_sim_frame);
fprintf(fptr,"	{\n");

fprintf(fptr,"		pi = (float)22/(float)7;\n");
fprintf(fptr,"		angle = 2*pi*f0*(i%%(FFT_LEN>>1));\n");
fprintf(fptr,"		imag_in =0;//sin(angle);\n");
fprintf(fptr,"		real_in =(i%%FFT_LEN)+1; //cos(angle);\n");
fprintf(fptr,"		imag=toQ(imag_in,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH);\n");
fprintf(fptr,"		real=toQ(real_in,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH);\n");

// fprintf(fptr,"		real_in = sin((float)(2*(22/7)*(i%%(FFT_LEN>1))/2)*(1<<8);\n");
// fprintf(fptr,"		imag_in = sin((float)(2*(22/7)*(i%%(FFT_LEN>1))/2)*(1<<8);\n");

fprintf(fptr,"		sample_input_real.write(real);\n");
fprintf(fptr,"		sample_input_imag.write(imag);\n");
//fprintf(fptr,"		//printf (\"The Stimulus to Mic:%%d\\n\",(int)sample_input_real.read());\n");
//fprintf(fptr,"		//printf (\"The Stimulus to Mic:%%d\\n\",(int)sample_input_imag.read());\n");
fprintf(fptr,"		wait();\n");
fprintf(fptr,"	}\n");
fprintf(fptr,"}\n");
fprintf(fptr,"\n");
fprintf(fptr,"void stimulus::check_outputs(void)\n");
fprintf(fptr,"{\n");
fprintf(fptr,"	int temp_real,temp_imag;   \n");
fprintf(fptr,"   	int count=0;\n");
fprintf(fptr,"   	done_sim.write(false);\n");
fprintf(fptr,"   	wait();\n");
fprintf(fptr,"   	while(start.read()==false) wait();\n");
fprintf(fptr,"   	while(count < (%d*%d))\n",fft_len,no_of_sim_frame);
fprintf(fptr,"   	{\n");
fprintf(fptr,"\n\n\n#ifdef ADD_SYSTEMC_SIMULATION_SUPPORT_FUCNTIONS\n\n");
fprintf(fptr,"temp_real= (int)sample_output_real.read();  	\n");
fprintf(fptr,"temp_imag= (int)sample_output_imag.read();   	\n");
fprintf(fptr,"if(temp_imag < 0)  	\n");
fprintf(fptr,"   		printf (\"The output sample no %%d------------ : ( %%f - %%fi )\\n\",count,toFloat(temp_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH),-toFloat(temp_imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH));\n");
fprintf(fptr,"else  	\n");
fprintf(fptr,"   		printf (\"The output sample no %%d------------ : ( %%f + %%fi )\\n\",count,toFloat(temp_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH),toFloat(temp_imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH));\n");
//fprintf(fptr,"   		printf (\"The output sample no %%d------------ : %%f\\n\",count,toFloat(temp_imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH));\n");

fprintf(fptr,"#else\n");
fprintf(fptr,"if(temp_imag < 0)  	\n");
fprintf(fptr,"   		printf (\"The output sample  no %%d------------ : ( %%d - %%di )\\n\",count,(int)sample_output_real.read()),(int)sample_output_imag.read());\n");
fprintf(fptr,"else  	\n");
fprintf(fptr,"   		printf (\"The output sample  no %%d------------ : ( %%d + %%di )\\n\",count,(int)sample_output_real.read()),(int)sample_output_imag.read());\n");
//fprintf(fptr,"   		printf (\"The output sample  no %%d------------ : %%d\\n\",count,(int)sample_output_imag.read());\n");
fprintf(fptr,"#endif\n");
fprintf(fptr,"		count++;\n");
fprintf(fptr,"		wait();\n");
fprintf(fptr,"   	}\n");
fprintf(fptr,"    done_sim.write(true);\n	sc_stop();\n");

fprintf(fptr,"	wait();\n");
fprintf(fptr,"	wait(10);\n");
fprintf(fptr,"	while(1) wait();\n");
fprintf(fptr,"}\n");
fprintf(fptr,"\n");
}
//as

void print_BODY_stimulus_dot_h(FILE *fptr)
{
	fprintf(fptr,"#include \"global_constants.h\"\n");
	fprintf(fptr,"#include \"systemc.h\"\n");
	fprintf(fptr,"#include \"hls_fixed_point_lib.h\"\n");
	
	fprintf(fptr,"SC_MODULE(stimulus)\n");
	fprintf(fptr,"{\n");
	fprintf(fptr,"   sc_in < sc_int <OUTPUT_INTERFACE_WIDTH> > sample_output_real;\n");
	fprintf(fptr,"   sc_in < sc_int <OUTPUT_INTERFACE_WIDTH> > sample_output_imag;\n");
	fprintf(fptr,"   sc_in < bool > clk;\n");
	fprintf(fptr,"   sc_in < bool > done;\n");
	fprintf(fptr,"   sc_out < bool> reset;\n");
	fprintf(fptr,"   sc_out < bool> start;\n");
	fprintf(fptr,"   sc_out <bool> done_sim;\n");
	//fprintf(fptr,"   sc_out < sc_int < INTERFACE_WIDTH> > sample_input;\n");
	fprintf(fptr,"   sc_out < sc_int < INTERFACE_WIDTH > > sample_input_real;\n");
	fprintf(fptr,"   sc_out < sc_int < INTERFACE_WIDTH > > sample_input_imag;\n");
	fprintf(fptr,"   sc_in < bool > ready;\n");
	fprintf(fptr,"   void check_outputs(void);\n");
	fprintf(fptr,"   void genSim(void);\n");
	fprintf(fptr,"   SC_CTOR(stimulus)\n");
	fprintf(fptr,"   {\n");
	fprintf(fptr,"		SC_CTHREAD(genSim,clk.pos());\n");
	fprintf(fptr,"		dont_initialize();\n");
	fprintf(fptr,"		SC_CTHREAD(check_outputs,clk.pos());\n");
	fprintf(fptr,"		dont_initialize();\n");
	fprintf(fptr,"   };\n");
	fprintf(fptr,"};\n");
}

void print_BODY_fftPipelined_wrapper_dot_cpp(FILE *fptr,int total_stages,int fft_len,int twiddle_factors_bit_width,int twiddle_factors_fraction_width, int output_bit_width)
{
	int i,j,k;
	



	fprintf(fptr,"#include \"global_constants.h\"\n");
	fprintf(fptr,"#include \"pipeLinedFFT_WRAPPER.h\"\n");
	fprintf(fptr,"#ifdef __CTOS__\n");
	fprintf(fptr,"SC_MODULE_EXPORT (pipeLinedFFT_WRAPPER);\n");
	fprintf(fptr,"#endif\n");

	fprintf(fptr,"///////////////INCLUDE STAGES.CPP START//////////////////\n");

	

	fprintf(fptr,"#include \"systemc.h\"\n");

	fprintf(fptr,"///#include \"hw_sw_interface.h\"\n");

	fprintf(fptr,"//#include \"pipeLinedFFT_WRAPPER.h\"\n");

	fprintf(fptr,"#include \"dtype.h\"\n");

	fprintf(fptr,"#ifndef HLS_MODEL\n");


	fprintf(fptr,"#include \"stdio.h\"\n");
	fprintf(fptr,"#endif\n");

	fprintf(fptr,"#define TIMED_MODEL\n");

	fprintf(fptr,"///////////////INCLUDE STAGES.CPP END//////////////////\n");

	fprintf(fptr,"pipeLinedFFT_WRAPPER::pipeLinedFFT_WRAPPER(sc_module_name name)\n");

	fprintf(fptr,"	:sc_module(name),\n");

	fprintf(fptr,"		clk(\"clk\"),\n");

	fprintf(fptr,"		reset(\"reset\"),\n");
	fprintf(fptr,"		ready(\"ready\"),\n");
	fprintf(fptr,"		start(\"start\"),\n");
	fprintf(fptr,"		done(\"done\"),\n");

	fprintf(fptr,"		sample_input_real(\"sample_input_real\"),\n");
	fprintf(fptr,"		sample_input_imag(\"sample_input_imag\"),\n");

	fprintf(fptr,"		sample_output_real(\"sample_output_real\"),\n");
	fprintf(fptr,"		sample_output_imag(\"sample_output_imag\")\n");

	fprintf(fptr,"{\n");

	fprintf(fptr,"	//SC_CTHREAD(step, clk.pos());\n");
	fprintf(fptr,"#ifdef SINGLE_THREAD_WRAPPER\n");
	fprintf(fptr,"	SC_CTHREAD(single_thread_wrapper,clk.pos());\n");
	fprintf(fptr,"	reset_signal_is(reset,true);\n");
	fprintf(fptr,"	#else\n");

	for (i = 1; i <=total_stages; i++)
	{
		/* code */
		fprintf(fptr,"	SC_CTHREAD(stage%d_exec_WRAPPER, clk.pos());",i);

		fprintf(fptr,"	reset_signal_is(reset, true);\n");

		fprintf(fptr,"\n");
	}
	
	

	// fprintf(fptr,"	SC_CTHREAD(stage2_exec_WRAPPER, clk.pos());\n");

	// fprintf(fptr,"	reset_signal_is(reset, true);\n");

	// fprintf(fptr,"\n");

	// fprintf(fptr,"	SC_CTHREAD(stage3_exec_WRAPPER, clk.pos());\n");

	// fprintf(fptr,"	reset_signal_is(reset, true);  \n");

	fprintf(fptr,"	SC_CTHREAD(assign_outputs,clk.pos());\n");

	fprintf(fptr,"	reset_signal_is(reset,true);\n");
	fprintf(fptr,"	#endif\n");

	fprintf(fptr,"	\n");

	fprintf(fptr,"	#ifdef LOG_FILE\n");

	fprintf(fptr,"	SC_CTHREAD(logThread,clk.pos());\n");

	fprintf(fptr,"	reset_signal_is(reset,true);\n");

	fprintf(fptr,"\n");

	fprintf(fptr,"	logFile=fopen(\"Data_log.lg\",\"w\");\n");

	fprintf(fptr,"	fclose(logFile);\n");

	fprintf(fptr,"\n");

	fprintf(fptr,"	#endif\n");

	fprintf(fptr,"\n");

	fprintf(fptr,"}\n");

	

	fprintf(fptr,"#ifdef SINGLE_THREAD_WRAPPER\n");
	fprintf(fptr,"void pipeLinedFFT_WRAPPER::single_thread_wrapper(void)\n");
	fprintf(fptr,"{\n");
	//fprintf(fptr,"// int ");
	//for (i = 1; i <=total_stages; i++)
	//{
	//	//fprintf(fptr,"	int in,out1,out2,out3;\n");
	//	fprintf(fptr,",out%d",i);
	//}
	//fprintf(fptr,";\n",i);

	fprintf(fptr,"\tstruct mcomplex in",i);
	for (i = 1; i <=total_stages; i++)
	{
		//fprintf(fptr,"	int in,out1,out2,out3;\n");
		fprintf(fptr,",out%d",i);
	}
	fprintf(fptr,";\n",i);

	fprintf(fptr,"\tstruct mcomplex ind",i);
	for (i = 1; i <=total_stages; i++)
	{
		//fprintf(fptr,"	int in,out1,out2,out3;\n");
		fprintf(fptr,",out%dd",i);
	}
	fprintf(fptr,";\n",i);
	fprintf(fptr,"sc_int < %d > trans_real;\n",output_bit_width);
	fprintf(fptr,"sc_int < %d > trans_imag;\n",output_bit_width);

	

	fprintf(fptr,"	int count;\n");
	//fprintf(fptr,"	sample_output.write(0);\n");
	fprintf(fptr,"	sample_output_real.write(0);\n");
	fprintf(fptr,"	sample_output_imag.write(0);\n");
	fprintf(fptr,"	done.write(0);\n");
	fprintf(fptr,"	init_all();\n");
	fprintf(fptr,"	wait();\n");
	fprintf(fptr,"	ready.write(true);\n");
	fprintf(fptr,"	wait();\n");
	fprintf(fptr,"	while(start.read()==false) wait();\n");
	fprintf(fptr,"	while(1)\n");
	fprintf(fptr,"	{\n");
	fprintf(fptr,"	done.write(false);\n");
	fprintf(fptr,"	trans_real=(int)sample_input_real.read();//in.real=count;\n");
	fprintf(fptr,"	trans_imag=(int)sample_input_imag.read();//in.imag=count;\n");
	fprintf(fptr,"	in.real=trans_real;\n");
	fprintf(fptr,"	in.imag=trans_imag;\n");
	for (i = 1; i <=total_stages; i++)
	{
		if(i==1)
			{
				fprintf(fptr,"	functional_behavior_stage%d(in,&out%dd);\n",i,i);
				fprintf(fptr,"	trans_real=out1d.real;\n");
				fprintf(fptr,"	trans_imag=out1d.imag;;\n");
				fprintf(fptr,"	out1.real = trans_real;\n");
				fprintf(fptr,"	out1.imag = trans_imag;\n");
			}

		else
			{
					
				
				if(i!=total_stages)
				{
				fprintf(fptr,"	functional_behavior_stage%d(out%d,&out%dd);\n",i,(i-1),i);
				fprintf(fptr,"	trans_real=out%dd.real;\n",i);
				fprintf(fptr,"	trans_imag=out%dd.imag;;\n",i);
				fprintf(fptr,"	out%d.real = trans_real;\n",i);
				fprintf(fptr,"	out%d.imag = trans_imag;\n",i);
				}
				else
				{

					fprintf(fptr,"	functional_behavior_stage%d(out%d,&out%d);\n",i,(i-1),i);
				}

			}
		fprintf(fptr,"	wait();\n");
			

	}
	/*fprintf(fptr,"	out2 = stage2_functional_behavior(out1);\n");
	fprintf(fptr,"	out3 = stage3_functional_behavior(out2);\n");*/
	fprintf(fptr,"    //count++;\n");
	fprintf(fptr,"	sample_output_real.write(out%d.real);\n",total_stages);
	fprintf(fptr,"	sample_output_imag.write(out%d.imag);\n",total_stages);
	fprintf(fptr,"	#ifdef CREATE_LOG\n");
	for (i = 1; i <=total_stages; i++)
	{
	fprintf(fptr,"		log_var(\"stage%d_out_real.lg\",out%d.real);\n",i,i);
	fprintf(fptr,"		log_var(\"stage%d_out_imag.lg\",out%d.imag);\n",i,i);
	fprintf(fptr,"		log_varf(\"stage%d_out_real.lgf\",toFloat(out%d.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i,i);
	fprintf(fptr,"		log_varf(\"stage%d_out_imag.lgf\",toFloat(out%d.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i,i);
	}

	for (i = 1; i <=total_stages; i++)
	{
		if(i==1)
		{
			fprintf(fptr,"		log_var(\"stage%d_in_real.lg\",in.real);\n",i);
			fprintf(fptr,"		log_var(\"stage%d_in_imag.lg\",in.imag);\n",i);
			fprintf(fptr,"		log_varf(\"stage%d_in_real.lgf\",toFloat(in.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i);
			fprintf(fptr,"		log_varf(\"stage%d_in_imag.lgf\",toFloat(in.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i);
		}
		else
		{
			fprintf(fptr,"		log_var(\"stage%d_in_real.lg\",out%d.real);\n",i,(i-1));
			fprintf(fptr,"		log_var(\"stage%d_in_imag.lg\",out%d.imag);\n",i,(i-1));
			fprintf(fptr,"		log_varf(\"stage%d_in_real.lgf\",toFloat(out%d.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i,i-1);
			fprintf(fptr,"		log_varf(\"stage%d_in_imag.lgf\",toFloat(out%d.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i,i-1);

		}
	}



	//fprintf(fptr,"		log_var("stage2_out.lg",out2);\n");
	//fprintf(fptr,"		log_var("stage3_out.lg",out3);\n");
	fprintf(fptr,"	#endif\n");
	fprintf(fptr,"	done.write(true);\n");
	fprintf(fptr,"	wait();\n");
	fprintf(fptr,"	}\n");
	fprintf(fptr,"\n");
	fprintf(fptr,"}\n");
	fprintf(fptr,"#endif\n");




	fprintf(fptr,"#ifdef CREATE_LOG\n");

	fprintf(fptr,"void pipeLinedFFT_WRAPPER::log_var(char *file_name,int variable)\n");

	fprintf(fptr,"{\n");

	fprintf(fptr," FILE *fptr;\n");

	fprintf(fptr," fptr = fopen(file_name,\"a\");\n");

	fprintf(fptr," fprintf(fptr,\"%%d\\n\",variable);\n");

	fprintf(fptr," fclose(fptr);\n");

	fprintf(fptr,"}\n");

	fprintf(fptr,"void pipeLinedFFT_WRAPPER::log_varf(char *file_name,double variable)\n");

	fprintf(fptr,"{\n");

	fprintf(fptr," FILE *fptr;\n");

	fprintf(fptr," fptr = fopen(file_name,\"a\");\n");

	fprintf(fptr," fprintf(fptr,\"%%f\\n\",variable);\n");

	fprintf(fptr," fclose(fptr);\n");

	fprintf(fptr,"}\n");

	

	fprintf(fptr,"#endif\n");

	fprintf(fptr,"#ifdef LOG_FILE\n");

	fprintf(fptr,"void pipeLinedFFT_WRAPPER::logThread(void)\n");

	fprintf(fptr,"{\n");
fprintf(fptr,"	FILE *logFile_real,*logFile_imag;");

	fprintf(fptr,"	while(start.read()==false) wait();\n");

	fprintf(fptr,"	while(1)\n");

	fprintf(fptr,"	{\n");

	fprintf(fptr,"		\n");

	fprintf(fptr,"	logFile_real=fopen(\"Data_log_real.lg\",\"a\");\n");
	fprintf(fptr,"	logFile_imag=fopen(\"Data_log_imag.lg\",\"a\");\n");

	fprintf(fptr,"	fprintf(logFile_real,\"%%d\\n\",(int)sample_output_real.read());\n");
	fprintf(fptr,"	fprintf(logFile_imag,\"%%d\\n\",(int)sample_output_imag.read());\n");

	fprintf(fptr,"	fclose(logFile_real);\n");
	fprintf(fptr,"	fclose(logFile_imag);\n");

	fprintf(fptr,"	wait();\n");

	fprintf(fptr,"	}\n");

	fprintf(fptr,"}\n");

	fprintf(fptr,"#endif\n");

	fprintf(fptr,"\n");

	fprintf(fptr,"//Define all thread wrappers for pipeline stages\n");
	// Print thread wrappers for stage-1
    ///////////////////////////////////////////////////////////////////////////////
	fprintf(fptr,"void pipeLinedFFT_WRAPPER::stage1_exec_WRAPPER(void)\n");

	fprintf(fptr,"{\n");

	fprintf(fptr,"	//int input_sample;\n");

	fprintf(fptr,"	//int output_calculated;\n");

	fprintf(fptr,"	struct mcomplex input_sample;\n");

	fprintf(fptr,"	struct mcomplex output_calculated;\n");

	fprintf(fptr,"	int count;\n");

	fprintf(fptr,"	ready.write(false);\n");
	fprintf(fptr,"	done.write(false);\n");
	fprintf(fptr,"	count=0;\n");

	fprintf(fptr,"	wait(); \n");

	fprintf(fptr,"	init_stage1();\n");

	fprintf(fptr,"	wait();\n");

	fprintf(fptr,"	ready.write(true);\n");
	fprintf(fptr,"	wait();\n");
	fprintf(fptr,"	while(start.read()==false) wait();\n");
	fprintf(fptr,"	hshake[STAGE_NUMBER_s1].write(true);\n");
	fprintf(fptr,"	while(1)\n");

	fprintf(fptr,"	{\n");

	fprintf(fptr,"	input_sample.real =(int)sample_input_real.read();//count\n");
	fprintf(fptr,"	input_sample.imag =(int)sample_input_imag.read();//count\n");

	fprintf(fptr,"	functional_behavior_stage1(input_sample,&output_calculated);\n");

	fprintf(fptr,"	stageInterface_real[STAGE_NUMBER_s1].write(output_calculated.real);\n");
	fprintf(fptr,"	stageInterface_imag[STAGE_NUMBER_s1].write(output_calculated.imag);\n");
	fprintf(fptr,"	if(count==FFT_LEN)\n");
	fprintf(fptr,"	{\n"); 
	fprintf(fptr,"	count=0;\n");
	fprintf(fptr,"	done.write(true);\n");
	fprintf(fptr,"	}\n");
	fprintf(fptr,"	else\n");
	fprintf(fptr,"	{\n");
	fprintf(fptr,"	count++;\n");
	fprintf(fptr,"	done.write(false);\n");
	fprintf(fptr,"	}\n");
	
	fprintf(fptr,"	//count++;\n");

	fprintf(fptr,"	#ifdef CREATE_LOG\n");
	fprintf(fptr,"	int temp_real = (int)stageInterface_real[STAGE_NUMBER_s1].read();\n");
	fprintf(fptr,"	int temp_imag = (int)stageInterface_imag[STAGE_NUMBER_s1].read();\n");

	fprintf(fptr,"		log_var(\"stage1_out_real.lg\",output_calculated.real);\n");
	fprintf(fptr,"		log_var(\"stage1_out_imag.lg\",output_calculated.imag);\n");

	fprintf(fptr,"		log_var(\"stage1_in_imag.lg\",input_sample.imag);\n");
	fprintf(fptr,"		log_var(\"stage1_in_real.lg\",input_sample.real);\n");
	//fprintf(fptr,"		log_varf(\"stage%d_in_imag.lgf\",toFloat(out%d.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i,i-1);

	fprintf(fptr,"		log_varf(\"stage1_out_real.lgf\",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n");
	fprintf(fptr,"		log_varf(\"stage1_out_imag.lgf\",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n");

	fprintf(fptr,"		log_varf(\"stage1_in_imag.lgf\",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n");
	fprintf(fptr,"		log_varf(\"stage1_in_real.lgf\",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n");
	//fprintf(fptr,"		log_varf(\"stage1_in_real.lg\",input_sample.real);\n");


	fprintf(fptr,"	#endif\n");

	fprintf(fptr,"	#ifdef HLS_MODEL\n");

	fprintf(fptr,"	wait();\n");

	fprintf(fptr,"	#endif\n");

	fprintf(fptr,"	}\n");

	fprintf(fptr,"}\n");
	////////////////////////Print wrapper for stage-1 ends here////////////////

	////////////////////////Print thread wrapers for stage 2 to N-1////////////
	for (i = 2; i < total_stages; i++)
	{
			/* code */
		fprintf(fptr,"void pipeLinedFFT_WRAPPER::stage%d_exec_WRAPPER(void)\n",i);

		fprintf(fptr,"{\n");

		//fprintf(fptr,"	//int input_sample;\n");
		fprintf(fptr,"	struct mcomplex input_sample;\n");

		fprintf(fptr,"	struct mcomplex output_calculated;\n");

		fprintf(fptr,"	//int count=0;\n");

		fprintf(fptr,"	hshake[STAGE_NUMBER_s%d].write(false);\n",i);

		fprintf(fptr,"\t wait();\n");
		fprintf(fptr,"	init_stage%d();\n",i);
		fprintf(fptr,"\t wait();\n");
		fprintf(fptr,"	while(hshake[STAGE_NUMBER_s%d].read()==false) wait();\n",i-1);

		fprintf(fptr,"	hshake[STAGE_NUMBER_s%d].write(true);\n",i);

		fprintf(fptr,"	while(1)\n");

		fprintf(fptr,"	{\n");

		fprintf(fptr,"		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s%d-1].read();\n",i);
		fprintf(fptr,"		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s%d-1].read();\n",i);

		fprintf(fptr,"		functional_behavior_stage%d(input_sample,&output_calculated);\n",i);
		//fprintf(fptr,"		output_calculated.imag = functional_behavior_stage%d(input_sample);\n",i);

		fprintf(fptr,"		//count++;\n");

		fprintf(fptr,"		stageInterface_real[STAGE_NUMBER_s%d].write(output_calculated.real);\n",i);
		fprintf(fptr,"		stageInterface_imag[STAGE_NUMBER_s%d].write(output_calculated.imag);\n",i);

		fprintf(fptr,"		#ifdef CREATE_LOG\n");

		fprintf(fptr,"		log_var(\"stage%d_out_real.lg\",output_calculated.real);\n",i);
		fprintf(fptr,"		log_var(\"stage%d_out_imag.lg\",output_calculated.imag);\n",i);

		fprintf(fptr,"		log_var(\"stage%d_in_real.lg\",input_sample.real);\n",i);
		fprintf(fptr,"		log_var(\"stage%d_in_imag.lg\",input_sample.imag);\n",i);

		fprintf(fptr,"		log_varf(\"stage%d_in_real.lgf\",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i);
		fprintf(fptr,"		log_varf(\"stage%d_in_imag.lgf\",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i);

		fprintf(fptr,"		log_varf(\"stage%d_out_real.lgf\",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i);
		fprintf(fptr,"		log_varf(\"stage%d_out_imag.lgf\",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));\n",i);
		//fprintf(fptr,"		log_varf(\"stage1_in_real.lg\",input_sample.real);\n");


		fprintf(fptr,"		#endif\n");

		fprintf(fptr,"	#ifdef HLS_MODEL\n");

		fprintf(fptr,"	wait();\n");

		fprintf(fptr,"	#endif\n");

		fprintf(fptr,"	}\n");

		fprintf(fptr,"}\n");
	}
	////////////////////////Print thread wrapers for stage 2 to N-1 ends here/

	////////////////////////Print thread wraper for stage N /////////////////
	fprintf(fptr,"void pipeLinedFFT_WRAPPER::stage%d_exec_WRAPPER(void)\n",total_stages);

	fprintf(fptr,"{\n");

	fprintf(fptr,"	struct mcomplex input_sample;\n");

	fprintf(fptr,"	struct mcomplex output_calculated;\n");

	

	fprintf(fptr,"	//int count=1;\n");

	fprintf(fptr,"	hshake[STAGE_NUMBER_s%d].write(false);\n",total_stages);
	fprintf(fptr,"	wait();\n");
	fprintf(fptr,"	init_stage%d();\n",total_stages);
	fprintf(fptr,"	wait();\n");
	//if(fft_len==4)
	//fprintf(fptr,"	while(ready.read()==false) wait();\n",total_stages);
	//else
	fprintf(fptr,"	while(hshake[STAGE_NUMBER_s%d-1].read()==false) wait();\n",total_stages);
	


	fprintf(fptr,"	hshake[STAGE_NUMBER_s%d].write(true);\n",total_stages);
	//fprintf(fptr,"\t wait();\n");

	fprintf(fptr,"	while(1)\n");

	fprintf(fptr,"	{\n");

	fprintf(fptr,"		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s%d-1].read();\n",total_stages);
	fprintf(fptr,"		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s%d-1].read();\n",total_stages);

	fprintf(fptr,"		functional_behavior_stage%d(input_sample,&output_calculated);\n",total_stages);

	fprintf(fptr,"		//count++;\n");

	fprintf(fptr,"		stageInterface_real[STAGE_NUMBER_s%d].write(output_calculated.real);\n",total_stages);
	fprintf(fptr,"		stageInterface_imag[STAGE_NUMBER_s%d].write(output_calculated.imag);\n",total_stages);

	fprintf(fptr,"		#ifdef CREATE_LOG\n");

	fprintf(fptr,"		log_var(\"stage%d_out_real.lg\",output_calculated.real);\n",total_stages);
	fprintf(fptr,"		log_var(\"stage%d_out_imag.lg\",output_calculated.imag);\n",total_stages);

	fprintf(fptr,"		log_var(\"stage%d_in_real.lg\",input_sample.real);\n",total_stages);
	fprintf(fptr,"		log_var(\"stage%d_in_imag.lg\",input_sample.imag);\n",total_stages);

	fprintf(fptr,"		#endif\n");

	fprintf(fptr,"	#ifdef HLS_MODEL\n");

	fprintf(fptr,"	wait();\n");

	fprintf(fptr,"	#endif\n");

	fprintf(fptr,"	}\n");

	fprintf(fptr,"}\n");

	fprintf(fptr,"\n");
	////////////////////////Print thread wraper for stage N ends here//////

	fprintf(fptr,"/// IO interface\n");

	fprintf(fptr,"void pipeLinedFFT_WRAPPER::assign_outputs (void)\n");

	fprintf(fptr,"{\n");

	fprintf(fptr,"	sample_output_real.write(0);\n");
	fprintf(fptr,"	sample_output_imag.write(0);\n");
	fprintf(fptr,"	wait();\n");

	fprintf(fptr,"	while(ready.read()==false) wait();\n");

	fprintf(fptr,"	while(1)\n");

	fprintf(fptr,"	{\n");

	fprintf(fptr,"		sample_output_real.write((int)stageInterface_real[FFT_LEN_LOG2].read());\n");
	fprintf(fptr,"		sample_output_imag.write((int)stageInterface_imag[FFT_LEN_LOG2].read());\n");

	fprintf(fptr,"		wait();\n");

	fprintf(fptr,"	}\n");

	fprintf(fptr,"}\n");

	fprintf(fptr,"void pipeLinedFFT_WRAPPER::assign_inputs (void)\n");

	fprintf(fptr,"{\n");

	fprintf(fptr,"\n");

	fprintf(fptr,"	int temp1_real=(int)sample_input_real.read();\n");
	fprintf(fptr,"	int temp1_imag=(int)sample_input_imag.read();\n");

	fprintf(fptr,"	stageInterface_real[0].write(sample_input_real.read());\n");
	fprintf(fptr,"	stageInterface_real[0].write(sample_input_real.read());\n");

	fprintf(fptr,"	int temp2_real = (int)stageInterface_real[0].read();\n");
	fprintf(fptr,"	int temp2_imag = (int)stageInterface_imag[0].read();\n");

	fprintf(fptr,"}\n");

	fprintf(fptr,"\n");

	fprintf(fptr,"/// STAGES.CPP\n");

	fprintf(fptr,"////////////////STAGES.CPP START/////////////////////////\n");

	fprintf(fptr,"#ifdef	HLS_MODEL\n");

	fprintf(fptr,"void pipeLinedFFT_WRAPPER::init_all(void)\n");

	fprintf(fptr,"#else\n");

	fprintf(fptr,"void init_all(void)\n");

	fprintf(fptr,"#endif\n");

	fprintf(fptr,"{\n");
	for ( i = 1 ;i <= total_stages;i++)
	{
		/* code */
		fprintf(fptr,"	init_stage%d();\n",i);
	}

	//fprintf(fptr,"	init_stage1();\n");

	//fprintf(fptr,"	init_stage2();\n");

	//fprintf(fptr,"	init_stage3();\n");

	fprintf(fptr,"}\n");

	//////////////////Generate code for initialization behabior of all stages //////
	for ( i = 1;i <= total_stages;i++)
	{

		fprintf(fptr,"/////////////////////////////////////////////////////////////////////////\n");

		fprintf(fptr,"//////////// Stage-%d Initialization ....",i);

		fprintf(fptr,"////////////\n");

		fprintf(fptr,"#ifdef	HLS_MODEL\n");

		fprintf(fptr,"void pipeLinedFFT_WRAPPER::init_stage%d(void)\n",i);

		fprintf(fptr,"#else\n");

		fprintf(fptr,"void init_stage%d(void)\n",i);

		fprintf(fptr,"#endif\n");

		fprintf(fptr,"{\n");

		fprintf(fptr,"	int i;\n");
		

		
		fprintf(fptr,"	#ifdef CREATE_LOG\n");
		fprintf(fptr,"	FILE *tptr_real;\n");
		fprintf(fptr,"	FILE *tptr_imag;\n");
		fprintf(fptr,"	tptr_real=fopen(\"stage%d_out_real.lg\",\"w\");\n",i);
		fprintf(fptr,"	tptr_imag=fopen(\"stage%d_out_imag.lg\",\"w\");\n",i);
		fprintf(fptr,"	fclose(tptr_real);\n",i);
		fprintf(fptr,"	fclose(tptr_imag);\n",i);
		fprintf(fptr,"	tptr_real=fopen(\"stage%d_out_real.lgf\",\"w\");\n",i);
		fprintf(fptr,"	tptr_imag=fopen(\"stage%d_out_imag.lgf\",\"w\");\n",i);
		fprintf(fptr,"	fclose(tptr_real);\n",i);
		fprintf(fptr,"	fclose(tptr_imag);\n",i);
		fprintf(fptr,"	tptr_real=fopen(\"stage%d_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g\",\"w\");\n",i);
		fprintf(fptr,"	tptr_imag=fopen(\"stage%d_in_imag.lg\",\"w\");\n",i);
		fprintf(fptr,"	fclose(tptr_real);\n",i);
		fprintf(fptr,"	fclose(tptr_imag);\n",i);
		fprintf(fptr,"	tptr_real=fopen(\"stage%d_in_real.lgf\",\"w\");\n",i);
		fprintf(fptr,"	tptr_imag=fopen(\"stage%d_in_imag.lgf\",\"w\");\n",i);
		fprintf(fptr,"	fclose(tptr_real);\n",i);
		fprintf(fptr,"	fclose(tptr_imag);\n",i);
		fprintf(fptr,"	#endif\n");

		fprintf(fptr,"	 GLOBAL_OUTER_ITERATION_COUNTER_s%d=0;\n",i);
		if(i==total_stages)
		fprintf(fptr,"	 GLOBAL_INNER_ITERATION_COUNTER_s1=0;\n",i);

		fprintf(fptr,"	 #ifdef USE_CIRCULAR_BUFFERS\n\n");

		fprintf(fptr,"	 RD_PTR_s%d=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d) &RD_PTR_MASK_s%d )-1;\n",i,i,i);

		fprintf(fptr,"	 #endif\n");
		fprintf(fptr,"\t INIT_STAGE%d:;\n",i);

	/*	fprintf(fptr,"	for(i=0;i<FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d;i++)\n",i);

		fprintf(fptr,"	{\n");

		fprintf(fptr,"		shift_register_s%d_real[i]=0;\n",i);
		fprintf(fptr,"		shift_register_s%d_imag[i]=0;\n",i);

		fprintf(fptr,"	}\n");*/

		fprintf(fptr,"}\n"); 

		fprintf(fptr,"// END:init_stage%d",i);
	}
	//////////////////Finished Generating code for initialization of all stages /////



	// fprintf(fptr,"/////////////////////////////////////////////////////////////////////////\n");

	// fprintf(fptr,"#ifdef	HLS_MODEL\n");

	// fprintf(fptr,"void pipeLinedFFT_WRAPPER::init_stage2(void)\n");

	// fprintf(fptr,"#else\n");

	// fprintf(fptr,"void init_stage2(void)\n");

	// fprintf(fptr,"#endif\n");

	// fprintf(fptr,"{\n");

	// fprintf(fptr,"	int i;\n");

	// fprintf(fptr,"	GLOBAL_OUTER_ITERATION_COUNTER_s2=0;\n");

	// fprintf(fptr,"	GLOBAL_INNER_ITERATION_COUNTER_s2=0;\n");

	// fprintf(fptr,"	#ifdef USE_CIRCULAR_BUFFERS\n");

	// fprintf(fptr,"	RD_PTR_s2=(FFT_LEN/STAGE_NUMBER_TO_POWER_2_s2)-1;\n");

	// fprintf(fptr,"	#endif\n");

	// fprintf(fptr,"	for(i=0;i<FFT_LEN/STAGE_NUMBER_TO_POWER_2_s2;i++)\n");

	// fprintf(fptr,"	{\n");

	// fprintf(fptr,"		shift_register_s2[i]=0;\n");

	// fprintf(fptr,"	}\n");

	// fprintf(fptr,"\n");

	// fprintf(fptr,"}\n");

	// fprintf(fptr,"// END:init_stage1\n");

	// fprintf(fptr,"////////////////////////////////////////////////////////////////////////////////////////\n");

	// fprintf(fptr,"\n");

	// fprintf(fptr,"/////////////////////////////////////////////////////////////////////////\n");

	// fprintf(fptr,"#ifdef	HLS_MODEL\n");

	// fprintf(fptr,"void pipeLinedFFT_WRAPPER::init_stage3(void)\n");

	// fprintf(fptr,"#else\n");

	// fprintf(fptr,"void init_stage3(void)\n");

	// fprintf(fptr,"#endif\n");

	// fprintf(fptr,"{\n");

	// fprintf(fptr,"	int i;\n");

	// fprintf(fptr,"	GLOBAL_OUTER_ITERATION_COUNTER_s3=0;\n");

	// fprintf(fptr,"	GLOBAL_INNER_ITERATION_COUNTER_s3=0;\n");

	// fprintf(fptr,"	#ifdef USE_CIRCULAR_BUFFERS\n");

	// fprintf(fptr,"	RD_PTR_s3=(FFT_LEN/STAGE_NUMBER_TO_POWER_2_s3)-1;\n");

	// fprintf(fptr,"	#endif\n");

	// fprintf(fptr,"	for(i=0;i<FFT_LEN/STAGE_NUMBER_TO_POWER_2_s3;i++)\n");

	// fprintf(fptr,"	{\n");

	// fprintf(fptr,"		shift_register_s3[i]=0;\n");

	// fprintf(fptr,"	}\n");

	// fprintf(fptr,"}\n");

	// fprintf(fptr,"// END:init_stage3\n");

	// fprintf(fptr,"\n");

	fprintf(fptr,"////////////////STAGES.CPP END/////////////////////////\n");

	fprintf(fptr,"//////////////////////STATIC_CONSTANTS.H START///////////////\n");

			fprintf(fptr,"#ifdef HLS_MODEL\n");
			for (j = 1; j <=total_stages ; j++)
			{
				fprintf(fptr,"  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s%d[FFT_LEN>>%d] =",j,j); 
				//createTwiddleTable(fptr,fft_len,j,16);
				createTwiddleTable(fptr,fft_len,j,twiddle_factors_bit_width,twiddle_factors_fraction_width);
			}
			fprintf(fptr,"#else\n");
			for (j = 1; j <=total_stages ; j++)
			{
				fprintf(fptr,"  const dtype_f twiddle_table_s%d[FFT_LEN>>%d] =",j,j); 
				createTwiddleTable(fptr,fft_len,j,twiddle_factors_bit_width,twiddle_factors_fraction_width);
			}
			fprintf(fptr,"#endif\n");
			///// Print imaginary twiddle table
			fprintf(fptr,"#ifdef HLS_MODEL\n");
			for (j = 1; j <=total_stages ; j++)
			{
				fprintf(fptr,"  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s%d[FFT_LEN>>%d] =",j,j); 
				//createTwiddleTable(fptr,fft_len,j,16);
				createTwiddleTable_image(fptr,fft_len,j,twiddle_factors_bit_width,twiddle_factors_fraction_width);
			}
			fprintf(fptr,"#else\n");
			for (j = 1; j <=total_stages ; j++)
			{
				fprintf(fptr,"  const dtype_f twiddle_table_imag_s%d[FFT_LEN>>%d] =",j,j); 
				createTwiddleTable_image(fptr,fft_len,j,twiddle_factors_bit_width,twiddle_factors_fraction_width);
			}
			fprintf(fptr,"#endif\n");


			//void createTwiddleTable_image(FILE *fptr,int fft_len,int stage_number,int twiddle_factor_bit_width,int twiddle_table_fraction_width);

	// }
	/////////////// The Twiddle table generation finished /////////////////////

	fprintf(fptr,"//////////////////////Inlcude code that defines functional behavior of butterfly stages start///////////////\n");

	for(i=1;i<=total_stages;i++)
	{
	fprintf(fptr,"#include \"functional_behavior_stage%d.h\"\n",i);
	}
	//fprintf(fptr,"#include \"functional_behavior_stage2.h\"\n");

	//fprintf(fptr,"#include \"functional_behavior_stage3.h\"\n");

}

void print_BODY_fftPipelined_wrapper_dot_h(FILE *fptr,int stage,int fft_len,int input_bit_width, int output_bit_width)
{
	int i;
	fprintf(fptr,"#include \"global_constants.h\"\n");
	fprintf(fptr,"#ifndef HLS_MODEL\n#include <stdio.h>\n#endif\n");
	fprintf(fptr,"#include \"systemc.h\"\n");

	fprintf(fptr,"#include \"dtype.h\"\n");
	fprintf(fptr,"#include \"hls_fixed_point_lib.h\"\n");


	

	for(i=1;i<=stage;i++)
	{
		fprintf(fptr,"#include \"global_constants_stage%d.h\"\n",i);
	}

	fprintf(fptr,"class pipeLinedFFT_WRAPPER:public sc_module\n");

	fprintf(fptr,"{\n");

	fprintf(fptr,"	/* public data and function members */\n");

	fprintf(fptr,"	public:\n");

	fprintf(fptr,"		pipeLinedFFT_WRAPPER(sc_module_name name); // constructor\n");

	fprintf(fptr,"		SC_HAS_PROCESS(pipeLinedFFT_WRAPPER); //\n");

	fprintf(fptr,"		#ifdef LOG_FILE \n");

	fprintf(fptr,"		FILE * logFile;\n");

	//fprintf(fptr,"		static int logInt;\n");

	//fprintf(fptr,"		static double logDouble;\n");

	fprintf(fptr,"		void logThread();\n");

	fprintf(fptr,"		#endif\n");
	fprintf(fptr, "//Stitch together all the global variables from different pipeline stages as class members\n");
	for(i=1;i<=stage;i++)
	{
		fprintf(fptr,"		#include \"global_variables_stage%d.h\"\n",i);
	}

	fprintf(fptr,"		//define interface signals\n");
	// This is comment: Need to be adddressed in future. For proper bit-width definition of Interface
	//fprintf(fptr,"		sc_signal < sc_int < INTERFACE_WIDTH > > stageInterface[FFT_LEN_LOG2+1];\n");
	//fprintf(fptr,"		sc_signal < sc_int < 32 > > stageInterface_real[FFT_LEN_LOG2+1];\n");
	//fprintf(fptr,"		sc_signal < sc_int < 32 > > stageInterface_imag[FFT_LEN_LOG2+1];\n");


	fprintf(fptr,"		sc_signal < sc_int < %d > > stageInterface_real[FFT_LEN_LOG2+1];\n",output_bit_width);
	fprintf(fptr,"		sc_signal < sc_int < %d > > stageInterface_imag[FFT_LEN_LOG2+1];\n",output_bit_width);

	fprintf(fptr, "		//Define all the signal that will be used for synchronization between the stages\n");
	fprintf(fptr, "		//All these signals will be internal to overall FFT.\n");

	fprintf(fptr,"		sc_signal < bool > hshake[FFT_LEN_LOG2+1];\n");

	fprintf(fptr,"		/////////////////////////////////////////////////////////////////////\n");

	fprintf(fptr,"		// Inputs\n");

	fprintf(fptr,"		/////////////////////////////////////////////////////////////////////\n");

	fprintf(fptr,"		sc_in<bool> clk;\n");

	fprintf(fptr,"		sc_in< bool > reset;\n");
	fprintf(fptr,"		sc_in< bool > start;\n");
	fprintf(fptr,"		sc_out< bool > done;\n");

	fprintf(fptr,"		sc_in< sc_int <INTERFACE_WIDTH> > sample_input_real;\n");
	fprintf(fptr,"		sc_in< sc_int <INTERFACE_WIDTH> > sample_input_imag;\n");

	fprintf(fptr,"		/////////////////////////////////////////////////////////////////////\n");

	fprintf(fptr,"		// Outputs\n");

	fprintf(fptr,"		/////////////////////////////////////////////////////////////////////\n");

	fprintf(fptr,"		sc_out< bool > ready;\n");

	fprintf(fptr,"		sc_out< sc_int <OUTPUT_INTERFACE_WIDTH> > sample_output_real;\n");
	fprintf(fptr,"		sc_out< sc_int <OUTPUT_INTERFACE_WIDTH> > sample_output_imag;\n");

	fprintf(fptr,"		/////////////////////////////////////\n");

	for (i = 1; i <= stage; i++)
	{
		/* code */
	fprintf(fptr,"		/// Stage-%d\n",i);
	fprintf(fptr,"		void init_stage%d(void);\n",i);

	//fprintf(fptr,"		void stage%d_exec(void);\n",i);
	}



	fprintf(fptr,"		/////////////////////////////////////\n");

	fprintf(fptr,"		#ifdef CREATE_LOG\n");

	fprintf(fptr,"		void log_var(char *file_name,int variable);\n");
	fprintf(fptr,"      void log_varf(char *file_name,double variable);\n");


	fprintf(fptr,"		#endif\n");

	fprintf(fptr,"		void init_all(void);\n");

	//fprintf(fptr,"		void step();\n");

	fprintf(fptr,"		// output assigning process\n");

	fprintf(fptr,"		void assign_outputs(void);\n");

	fprintf(fptr,"		// input assigning process\n");

	fprintf(fptr,"		void assign_inputs(void);\n");

	fprintf(fptr,"		// Possible Functional Behaviour of PipeLined Stages that allows to achieve higher level of concurrency...\n");

	// fprintf(fptr,"		void streaming_interface(void);\n");
	for ( i = 1; i <= stage; i++)
	{
		/* code */


	fprintf(fptr,"		void functional_behavior_stage%d(struct mcomplex sample_input_stage%d,struct mcomplex *output_ret);\n",i,i);
	}

	fprintf(fptr,"		// constructor\n");

	fprintf(fptr,"		// Declare all the thread wrapper for pipeline stages\n");

	fprintf(fptr,"		// These thread wrappers will allow us to define level of concurrency.\n");

	for ( i = 1; i <= stage; i++)
	{
		fprintf(fptr,"		void stage%d_exec_WRAPPER(void);\n",i);
	}

	//fprintf(fptr,"		void stage2_exec_WRAPPER(void);\n");

	//fprintf(fptr,"		void stage3_exec_WRAPPER(void);\n");
	fprintf(fptr,"#ifdef SINGLE_THREAD_WRAPPER\n");
	fprintf(fptr,"\tvoid single_thread_wrapper(void);\n");
    fprintf(fptr,"#endif\n");
	fprintf(fptr,"};\n");
}

void print_BODY_functional_behavior_stageN_dot_h(FILE *fptr,int stage,int fft_len,int output_bit_width)
{
	fprintf(fptr,"#ifdef HLS_MODEL\n");
	fprintf(fptr,"void pipeLinedFFT_WRAPPER::functional_behavior_stage%d(struct mcomplex sample_input_stage%d,struct mcomplex *output_ret )\n",stage,stage);
	fprintf(fptr,"#else\n");
	fprintf(fptr,"void functional_behavior_stage%d(struct mcomplex sample_input_stage%d,struct mcomplex *output_ret)\n",stage,stage);
	fprintf(fptr,"#endif\n");
	fprintf(fptr,"{\n");
	fprintf(fptr,"\tint i;\n");
	fprintf(fptr,"\dtype_f mem_reg1,mem_reg2,mem_reg3,mem_reg4;\n");
	//fprintf(fptr,"\tint output_ret;\n");
	fprintf(fptr,"\t//if(GLOBAL_OUTER_ITERATION_COUNTER_s%d <  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s%d )\n",stage,stage);
	fprintf(fptr,"\t//{\n");
	fprintf(fptr,"\t#ifdef USE_CIRCULAR_BUFFERS\n");
	fprintf(fptr,"\t\t///////////////////////////////Behavior with circular Buffers $START//////////////////////////////////\n");
	fprintf(fptr,"\t\t//Read the input stream for processing and stream out previously calculated values\n");

	fprintf(fptr,"\t\tmem_reg1=shift_register_s%d_real[RD_PTR_s%d];\n",stage,stage);
	fprintf(fptr,"\t\tmem_reg2=shift_register_s%d_imag[RD_PTR_s%d];\n",stage,stage);

	fprintf(fptr,"\t\tL_readInputStreamWriteLastCalculateOuput_s%d:\n",stage);
	fprintf(fptr,"\t\tif((GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d) < GLOBAL_INNER_ITERATION_COUNTER_BUFFER_LIMIT_s%d )\n",stage,stage);
	fprintf(fptr,"\t\t{\n");
	fprintf(fptr,"\t\t\t// Read a sample, buffer it and write a sample output for next stage\n");
	fprintf(fptr,"\t\t\t// Write last element from the buffer to output signal\n");
	fprintf(fptr,"\t\t\toutput_ret->real=mem_reg1;\n");
	fprintf(fptr,"\t\t\toutput_ret->imag=mem_reg2;\n");
	fprintf(fptr,"\t\t\tmem_reg3=sample_input_stage%d.real;\n",stage);
	fprintf(fptr,"\t\t\tmem_reg4=sample_input_stage%d.imag;\n",stage);
	fprintf(fptr,"\t\t\t    //mmmRD_PTR_s%d=((RD_PTR_s%d+1)&RD_PTR_MASK_s%d);\n",stage,stage,stage);
	fprintf(fptr,"\t\t\t    //mmmGLOBAL_INNER_ITERATION_COUNTER_s%d=(GLOBAL_INNER_ITERATION_COUNTER_s%d+1)&GLOBAL_INNER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage);
	//fprintf(fptr,"\t\t\treturn output_ret;\n");
	fprintf(fptr,"\t\t\t#ifdef TIMED_MODEL22\n");
	fprintf(fptr,"\t\t\twait();\n");
	fprintf(fptr,"\t\t\t#endif\n");
	fprintf(fptr,"\t\t} else { \n");
	fprintf(fptr,"\t\t\///////////////////////////////Behavior with circular Buffers $END////////////////////////////////// \n");
	fprintf(fptr,"\t\t#else\n");

	fprintf(fptr,"		mem_reg1= shift_register_s%d_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d -1];\n",stage,stage);
	fprintf(fptr,"		mem_reg2= shift_register_s%d_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d -1];\n",stage,stage);


	fprintf(fptr,"		if(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d < GLOBAL_INNER_ITERATION_COUNTER_BUFFER_LIMIT_s%d )\n",stage,stage,stage);
	fprintf(fptr,"		{\n");
	fprintf(fptr,"			// Read a sample, buffer it and write a sample output for next stage\n");
	fprintf(fptr,"			// Write last element from the buffer to output signal\n");
	//fprintf(fptr,"			output_ret->real= shift_register_s%d_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d -1];\n",stage,stage);
	//fprintf(fptr,"			output_ret->imag= shift_register_s%d_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d -1];\n",stage,stage);
	fprintf(fptr,"			output_ret->real= mem_reg1;\n");
	fprintf(fptr,"			output_ret->imag= mem_reg2;\n");
	fprintf(fptr,"			int temp_real =shift_register_s%d_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d -1];// stageInterface[STAGE_NUMBER_s%d].read();\n",stage,stage,stage);
	fprintf(fptr,"			int temp_imag =shift_register_s%d_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d -1];// stageInterface[STAGE_NUMBER_s%d].read();\n",stage,stage,stage);
	fprintf(fptr,"			L_shiftInputSampleInBuffer_s%d:\n",stage);
	fprintf(fptr,"			for(i=FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d-1;i>0;i--)\n",stage);
	fprintf(fptr,"			{\n");
	fprintf(fptr,"				shift_register_s%d_real[i]= %d &  shift_register_s%d_real[i-1];\n",stage,((1<<output_bit_width)-1),stage);
	fprintf(fptr,"				shift_register_s%d_imag[i]= %d &  shift_register_s%d_imag[i-1];\n",stage,((1<<output_bit_width)-1),stage);
	fprintf(fptr,"				// read the input sample and store in the buffer\n");
	fprintf(fptr,"			}\n");
	/*fprintf(fptr,"			shift_register_s%d_real[0]=sample_input_stage%d.real;\n",stage,stage);
	fprintf(fptr,"			shift_register_s%d_imag[0]=sample_input_stage%d.imag;\n",stage,stage);*/
	fprintf(fptr,"			mem_reg3=sample_input_stage%d.real;\n",stage);
	fprintf(fptr,"			mem_reg4=sample_input_stage%d.imag;\n",stage);
	fprintf(fptr,"			//GLOBAL_INNER_ITERATION_COUNTER_s%d=(GLOBAL_INNER_ITERATION_COUNTER_s%d+1)&GLOBAL_INNER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage);
	//fprintf(fptr,"			return output_ret;\n");
	fprintf(fptr,"			#ifdef TIMED_MODEL22\n");
	fprintf(fptr,"			wait();\n");
	fprintf(fptr,"			#endif\n");
	fprintf(fptr,"		} else {\n");
	fprintf(fptr,"		#endif\n");
	fprintf(fptr,"		 // calculate the outputs for current frame store half of them\n");
	fprintf(fptr,"		 // and, calculate and stream out half of the outputs for butterflies\n");
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	fprintf(fptr,"		#ifdef USE_CIRCULAR_BUFFERS\n");
	fprintf(fptr,"		L_execSingleButterflyPerIteration_s%d:\n",stage);
	fprintf(fptr,"		//else( GLOBAL_INNER_ITERATION_COUNTER_s%d <= (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d + FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d -1) )\n",stage,stage,stage);
	fprintf(fptr,"		//{\n");
	fprintf(fptr,"			// read the input and process to execute butterflies\n");
	fprintf(fptr,"			dtype_f temp1_real,temp2_real;\n");
	fprintf(fptr,"			dtype_f temp1_imag,temp2_imag;\n");

	fprintf(fptr,"			dtype_f bout_imag,bout_real;\n");

	fprintf(fptr,"			dtype_f bout_imag_part1,bout_real_part1;\n");
	fprintf(fptr,"			dtype_f bout_imag_part2,bout_real_part2;\n");

	fprintf(fptr,"			dtype_f twiddle_imag,twiddle_real;\n");
	fprintf(fptr,"			dtype_f temp_out_sum_real,temp_out_diff_real;\n");
	fprintf(fptr,"			dtype_f temp_out_sum_imag,temp_out_diff_imag;\n");
	fprintf(fptr,"			// Read Twiddle table enteries and input samples to be processes in temporary variables.\n");
	fprintf(fptr,"			j_s%d = GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d - FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d;\n",stage,stage,stage);
	fprintf(fptr,"			twiddle_real=twiddle_table_s%d[(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d) & ((FFT_LEN>>%d)-1)];\n",stage,stage,stage);
	fprintf(fptr,"			twiddle_imag=twiddle_table_imag_s%d[(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d) & ((FFT_LEN>>%d)-1)];\n",stage,stage,stage);

	//fprintf(fptr,"			twiddle_imag=twiddle_table_imag_s%d[(GLOBAL_INNER_ITERATION_COUNTER_s%d + (FFT_LEN>>(2+%d))) %% (FFT_LEN>>%d)];\n",stage,stage,(stage-1),stage);

	fprintf(fptr,"			temp1_real = mem_reg1; //last value from buffer\n");
	fprintf(fptr,"			temp1_imag = mem_reg2; //last value from buffer\n");
	fprintf(fptr,"			temp2_real = sample_input_stage%d.real;\n",stage);
	fprintf(fptr,"			temp2_imag = sample_input_stage%d.imag;\n",stage);
	fprintf(fptr,"			// execute butterfly\n");

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// Butter Fle generation.........
	fprintf(fptr,"			butterfly( temp1_real,  temp1_imag ,  temp2_real ,  twiddle_imag, twiddle_real,  temp2_imag ,  &temp_out_sum_real,  &temp_out_sum_imag,  &bout_real, &bout_imag, INPUT_SAMPLE_BIT_WIDTH , INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE ,SATURATION_MODE,0);\n");

	/*fprintf(fptr,"			//temp_out_sum_real =temp1_real+temp2_real;\n");
	fprintf(fptr,"			temp_out_sum_real=add(temp1_real,temp2_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");



	fprintf(fptr,"			//temp_out_sum_imag =temp1_imag+temp2_imag;\n");
	fprintf(fptr,"			temp_out_sum_imag=add(temp1_imag,temp2_imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");


	fprintf(fptr,"			//temp_out_diff_real=(temp1_real-temp2_real);\n");
	fprintf(fptr,"			temp_out_diff_real=add(temp1_real,-temp2_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");

	fprintf(fptr,"			//temp_out_diff_imag=(temp1_imag-temp2_imag);\n");
	fprintf(fptr,"			temp_out_diff_imag=add(temp1_imag,-temp2_imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");

	fprintf(fptr,"			//bout_real=(temp_out_diff_real*twiddle_real+temp_out_diff_imag*twiddle_imag);\n");
	fprintf(fptr,"			//bout_real_part1 = temp_out_diff_real*twiddle_real;\n");
	fprintf(fptr,"			bout_real_part1=mul(temp_out_diff_real,twiddle_real,INPUT_SAMPLE_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),TRUNCATE_MODE,SATURATION_MODE,0);\n");
	fprintf(fptr,"			//bout_real_part2 = temp_out_diff_imag*twiddle_imag;\n");
	fprintf(fptr,"			bout_real_part2=mul(temp_out_diff_imag,twiddle_imag,INPUT_SAMPLE_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),TRUNCATE_MODE,SATURATION_MODE,0);\n");

	fprintf(fptr,"			//bout_real = bout_real_part1+bout_real_part2;\n");
	fprintf(fptr,"			bout_real=add(bout_real_part1,-bout_real_part2,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");

	fprintf(fptr,"			//bout_imag=(temp_out_diff_imag*twiddle_real-temp_out_diff_real*twiddle_imag);\n");
	fprintf(fptr,"			//bout_imag_part1=temp_out_diff_imag*twiddle_real;\n");
	fprintf(fptr,"			bout_imag_part1=mul(temp_out_diff_imag,twiddle_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),TRUNCATE_MODE,SATURATION_MODE,0);\n");

	fprintf(fptr,"			//bout_imag_part2=temp_out_diff_real*twiddle_imag;\n");
	fprintf(fptr,"			bout_imag_part2=mul(temp_out_diff_real,twiddle_imag,INPUT_SAMPLE_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),TRUNCATE_MODE,SATURATION_MODE,0);\n");
	fprintf(fptr,"			//bout_imag=bout_imag_part1+bout_imag_part2;\n");
	fprintf(fptr,"			bout_imag=add(bout_imag_part1,bout_imag_part2,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");
*/

	//fprintf(fptr,"			temp_out_diff=(temp1-temp2)*twiddle_table_s%d[GLOBAL_INNER_ITERATION_COUNTER_s%d %% (FFT_LEN>>%d)];\n",stage,stage,stage);
	fprintf(fptr,"			// Stream out the sum output\n");
	fprintf(fptr,"			// Stream out the calculated value\n");
	//fprintf(fptr,"			output_ret=temp_out_sum;\n");
	fprintf(fptr,"			// store the difference sample in buffer and shift the buffer\n");
	fprintf(fptr,"			// Store the calculated out sample it will be streamed out in next phase\n");
	fprintf(fptr,"			mem_reg3=bout_real;\n");
	fprintf(fptr,"			mem_reg4=bout_imag;\n");
	
	fprintf(fptr,"			//if(GLOBAL_OUTER_ITERATION_COUNTER_s%d >=  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s%d )\n",stage,stage);
	fprintf(fptr,"				//GLOBAL_OUTER_ITERATION_COUNTER_s%d=0;\n",stage);
	 
	//fprintf(fptr,"			return output_ret;\n");
	fprintf(fptr,"			output_ret->real=temp_out_sum_real;\n");
	fprintf(fptr,"			output_ret->imag=temp_out_sum_imag;\n");
	
	fprintf(fptr,"			#ifdef TIMED_MODEL22\n");
	fprintf(fptr,"			wait();\n");
	fprintf(fptr,"			#endif\n");
	fprintf(fptr,"		 }\n");
	fprintf(fptr,"		 shift_register_s%d_real[RD_PTR_s%d]=mem_reg3;\n",stage,stage);
	fprintf(fptr,"		 shift_register_s%d_imag[RD_PTR_s%d]=mem_reg4;\n",stage,stage);
    fprintf(fptr,"			RD_PTR_s%d=((RD_PTR_s%d+1)&RD_PTR_MASK_s%d);\n",stage,stage,stage);
	fprintf(fptr,"			//GLOBAL_INNER_ITERATION_COUNTER_s%d=(GLOBAL_INNER_ITERATION_COUNTER_s%d+1)&GLOBAL_INNER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage);
	fprintf(fptr,"			if((GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d) == (GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s%d))\n",stage,stage);
	fprintf(fptr,"			{\n");
	fprintf(fptr,"			//	GLOBAL_INNER_ITERATION_COUNTER_s%d=0;\n",stage);
	fprintf(fptr,"			//	GLOBAL_OUTER_ITERATION_COUNTER_s%d=(GLOBAL_OUTER_ITERATION_COUNTER_s%d + 1) %%  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s%d;\n",stage,stage,stage);
	fprintf(fptr,"				if(GLOBAL_OUTER_ITERATION_COUNTER_s%d==( GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s%d-1))\n",stage,stage);
	fprintf(fptr,"				GLOBAL_OUTER_ITERATION_COUNTER_s%d=0;\n",stage);
	fprintf(fptr,"				else\n");
	fprintf(fptr,"				GLOBAL_OUTER_ITERATION_COUNTER_s%d=(GLOBAL_OUTER_ITERATION_COUNTER_s%d + 1)&GLOBAL_OUTER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage);
	fprintf(fptr,"			}\n");

	if(stage==mf_log2(fft_len))
	{
		fprintf(fptr,"			GLOBAL_INNER_ITERATION_COUNTER_s1=(GLOBAL_INNER_ITERATION_COUNTER_s1+1)&GLOBAL_INNER_ITERATION_COUNTER_MASK_s1;\n");
		fprintf(fptr,"			if(GLOBAL_INNER_ITERATION_COUNTER_s1 > (GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s1 -1))\n");
		fprintf(fptr,"			{\n");
		fprintf(fptr,"			   GLOBAL_INNER_ITERATION_COUNTER_s1=0;\n");
		fprintf(fptr,"			}\n");
	}
    fprintf(fptr,"	//}\n");
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	fprintf(fptr,"		#else\n");
	fprintf(fptr,"		// else( GLOBAL_INNER_ITERATION_COUNTER_s%d  <= (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d + FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d -1) )\n",stage,stage,stage);
	fprintf(fptr,"		//{\n");
	fprintf(fptr,"			// read the input and process to execute butterflies\n");
	fprintf(fptr,"			dtype_f temp1_real,temp2_real;\n");
	fprintf(fptr,"			dtype_f temp1_imag,temp2_imag;\n");
	fprintf(fptr,"			dtype_f bout_imag,bout_real;\n");

	fprintf(fptr,"			dtype_f bout_imag_part1,bout_real_part1;\n");
	fprintf(fptr,"			dtype_f bout_imag_part2,bout_real_part2;\n");

	fprintf(fptr,"			dtype_f twiddle_imag,twiddle_real;\n");
	fprintf(fptr,"			dtype_f temp_out_sum_imag,temp_out_diff_imag;\n");
	fprintf(fptr,"			dtype_f temp_out_sum_real,temp_out_diff_real;\n");
	fprintf(fptr,"			j_s%d = (GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d) - FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d;\n",stage,stage,stage);

	fprintf(fptr,"			twiddle_real=twiddle_table_s%d[(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d) %% (FFT_LEN>>%d)];\n",stage,stage,stage);
	fprintf(fptr,"			twiddle_imag=twiddle_table_imag_s%d[(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d) %% (FFT_LEN>>%d)];\n",stage,stage,stage);

	//fprintf(fptr,"			twiddle_imag=twiddle_table_s%d[(GLOBAL_INNER_ITERATION_COUNTER_s%d + (FFT_LEN>>(2+%d))) %% (FFT_LEN>>%d)];\n",stage,stage,(stage-1),stage);


	fprintf(fptr,"		//	temp1_real = shift_register_s%d_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d-1]; //last value from buffer\n",stage,stage);
	fprintf(fptr,"		//	temp1_imag = shift_register_s%d_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d-1]; //last value from buffer\n",stage,stage);
	fprintf(fptr,"			temp1_real = mem_reg1; //last value from buffer\n");
	fprintf(fptr,"			temp1_imag = mem_reg2; //last value from buffer\n");
	fprintf(fptr,"			temp2_real = sample_input_stage%d.real;\n",stage);
	fprintf(fptr,"			temp2_imag = sample_input_stage%d.imag;\n",stage);
	fprintf(fptr,"			// execute butterfly\n");
	fprintf(fptr,"			butterfly( temp1_real,  temp1_imag ,  temp2_real ,  twiddle_imag, twiddle_real,  temp2_imag ,  &temp_out_sum_real,  &temp_out_sum_imag,  &bout_real, &bout_imag, INPUT_SAMPLE_BIT_WIDTH , INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE ,SATURATION_MODE,0);\n");

	//fprintf(fptr,"			temp_out_sum =temp1+temp2;\n");
	// Butterfly calculations....
	//fprintf(fptr,"			butterfly( temp1_real,  temp1_imag ,  temp2_real ,  twiddle_imag, twiddle_real,  temp2_imag ,  &temp_out_sum_real,  &temp_out_sum_imag,  &bout_real, &bout_imag, INPUT_SAMPLE_BIT_WIDTH , INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE ,SATURATION_MODE,0);\n");
	////////////////////////////////////////////////
	//fprintf(fptr,"			//temp_out_sum_real =temp1_real+temp2_real;\n");
	//fprintf(fptr,"			temp_out_sum_real=add(temp1_real,temp2_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");





	//fprintf(fptr,"			//temp_out_sum_imag =temp1_imag+temp2_imag;\n");
	//fprintf(fptr,"			temp_out_sum_imag=add(temp1_imag,temp2_imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");

	////fprintf(fptr,"			temp_out_diff=(temp1-temp2)*twiddle_table_s%d[GLOBAL_INNER_ITERATION_COUNTER_s%d %% (FFT_LEN>>%d)];\n",stage,stage,stage); 
	//fprintf(fptr,"			//temp_out_diff_real=(temp1_real-temp2_real);\n");
	//fprintf(fptr,"			temp_out_diff_real=add(temp1_real,-temp2_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");
	//fprintf(fptr,"			temp_out_diff_imag=(temp1_imag-temp2_imag);\n");
	//fprintf(fptr,"			temp_out_diff_imag=add(temp1_imag,-temp2_imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");
	////fprintf(fptr,"			bout_real=(temp_out_diff_real*twiddle_real+temp_out_diff_imag*twiddle_imag);\n");
	//fprintf(fptr,"			//bout_real=(temp_out_diff_real*twiddle_real+temp_out_diff_imag*twiddle_imag);\n");
	//fprintf(fptr,"			//bout_real_part1 = temp_out_diff_real*twiddle_real;\n");
	//fprintf(fptr,"			bout_real_part1=mul(temp_out_diff_real,twiddle_real,INPUT_SAMPLE_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),TRUNCATE_MODE,SATURATION_MODE,0);\n");
	//fprintf(fptr,"			//bout_real_part2 = temp_out_diff_imag*twiddle_imag;\n");
	//fprintf(fptr,"			bout_real_part2=mul(temp_out_diff_imag,twiddle_imag,INPUT_SAMPLE_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),TRUNCATE_MODE,SATURATION_MODE,0);\n");

	//fprintf(fptr,"			//bout_real = bout_real_part1+bout_real_part2;\n");
	//fprintf(fptr,"			bout_real=add(bout_real_part1,-bout_real_part2,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");

	//fprintf(fptr,"			//bout_imag=(temp_out_diff_imag*twiddle_real-temp_out_diff_real*twiddle_imag);\n");
	//fprintf(fptr,"			//bout_imag_part1=temp_out_diff_imag*twiddle_real;\n");
	//fprintf(fptr,"			bout_imag_part1=mul(temp_out_diff_imag,twiddle_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_BIT_WIDTH,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),TRUNCATE_MODE,SATURATION_MODE,0);\n");

	//fprintf(fptr,"			//bout_imag_part2=temp_out_diff_real*twiddle_imag;\n");
	//fprintf(fptr,"			bout_imag_part2=mul(temp_out_diff_real,twiddle_imag,INPUT_SAMPLE_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),TRUNCATE_MODE,SATURATION_MODE,0);\n");
	//fprintf(fptr,"			//bout_imag=bout_imag_part1+bout_imag_part2;\n");
	//fprintf(fptr,"			bout_imag=add(bout_imag_part1,bout_imag_part2,(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),(INPUT_SAMPLE_BIT_WIDTH+TWIDDLE_FACTORS_BIT_WIDTH),INPUT_SAMPLE_BIT_WIDTH,(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),(INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE,SATURATION_MODE,0);\n");


	//fprintf(fptr,"			// Stream out the sum output\n");
	//fprintf(fptr,"			// Stream out the calculated value\n");
	//fprintf(fptr,"			output_ret=temp_out_sum;\n");
	fprintf(fptr,"			output_ret->real=temp_out_sum_real;\n");
	fprintf(fptr,"			output_ret->imag=temp_out_sum_imag;\n");
	fprintf(fptr,"			// store the difference sample in buffer and shift the buffer\n");
	fprintf(fptr,"			L_storeOutputsInShiftRegister_s%d:\n",stage);
	fprintf(fptr,"			for(i=FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d-1;i>0;i--)\n",stage);
	fprintf(fptr,"			{\n");
	fprintf(fptr,"				shift_register_s%d_real[i]= %d & shift_register_s%d_real[i-1];\n",stage,((1<<output_bit_width)-1),stage);
	fprintf(fptr,"				shift_register_s%d_imag[i]= %d & shift_register_s%d_imag[i-1];\n",stage,((1<<output_bit_width)-1),stage);

	fprintf(fptr,"			}\n");
	fprintf(fptr,"			// Store the calculated out sample it will be streamed out in next phase\n");
	fprintf(fptr,"			//shift_register_s%d_real[0]=bout_real;\n",stage);
	fprintf(fptr,"			//shift_register_s%d_imag[0]=bout_imag;\n",stage);
	fprintf(fptr,"			mem_reg3=bout_real;\n",stage);
	fprintf(fptr,"			mem_reg4=bout_imag;\n",stage);

	/*fprintf(fptr,"			GLOBAL_INNER_ITERATION_COUNTER_s%d=(GLOBAL_INNER_ITERATION_COUNTER_s%d+1) & GLOBAL_INNER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage);
	fprintf(fptr,"			if(GLOBAL_INNER_ITERATION_COUNTER_s%d > (GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s%d -1))\n",stage,stage);
	fprintf(fptr,"			{\n");
	fprintf(fptr,"				GLOBAL_INNER_ITERATION_COUNTER_s%d=0;\n",stage);
	fprintf(fptr,"				GLOBAL_OUTER_ITERATION_COUNTER_s%d=((GLOBAL_OUTER_ITERATION_COUNTER_s%d + 1) %%  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s%d)& GLOBAL_OUTER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage,stage);

	fprintf(fptr,"				//GLOBAL_OUTER_ITERATION_COUNTER_s%d=(GLOBAL_OUTER_ITERATION_COUNTER_s%d + 1)&GLOBAL_OUTER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage);
	fprintf(fptr,"			}\n");*/

	fprintf(fptr,"			//if(GLOBAL_OUTER_ITERATION_COUNTER_s%d >=  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s%d )\n",stage,stage);
	fprintf(fptr,"				//GLOBAL_OUTER_ITERATION_COUNTER_s%d=0;\n",stage);
	//fprintf(fptr,"			return output_ret;\n");

	fprintf(fptr,"			#ifdef TIMED_MODEL22\n");
	fprintf(fptr,"			wait();\n");
	fprintf(fptr,"			#endif\n");
	fprintf(fptr,"		}\n");
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	fprintf(fptr,"		shift_register_s%d_real[0]=mem_reg3;\n",stage);
	fprintf(fptr,"		shift_register_s%d_imag[0]=mem_reg4;\n",stage);

	fprintf(fptr,"			//GLOBAL_INNER_ITERATION_COUNTER_s1 INNER_ITERATION_COUNTER_MASK_s%d =(GLOBAL_INNER_ITERATION_COUNTER_s%d+1) & GLOBAL_INNER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage);
	fprintf(fptr,"			if((GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s%d) == (GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s%d))\n",stage,stage);
	fprintf(fptr,"			{\n");
	fprintf(fptr,"			//	GLOBAL_INNER_ITERATION_COUNTER_s%d=0;\n",stage);
	fprintf(fptr,"				//GLOBAL_OUTER_ITERATION_COUNTER_s%d=((GLOBAL_OUTER_ITERATION_COUNTER_s%d + 1) %%  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s%d)&GLOBAL_OUTER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage,stage);
	fprintf(fptr,"				if(GLOBAL_OUTER_ITERATION_COUNTER_s%d== GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s%d)\n",stage,stage);
	fprintf(fptr,"				GLOBAL_OUTER_ITERATION_COUNTER_s%d=0;\n",stage);
	fprintf(fptr,"				else\n");
	fprintf(fptr,"				GLOBAL_OUTER_ITERATION_COUNTER_s%d=(GLOBAL_OUTER_ITERATION_COUNTER_s%d + 1)&GLOBAL_OUTER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage);

	fprintf(fptr,"				//GLOBAL_OUTER_ITERATION_COUNTER_s%d=(GLOBAL_OUTER_ITERATION_COUNTER_s%d + 1)&GLOBAL_OUTER_ITERATION_COUNTER_MASK_s%d;\n",stage,stage,stage);
	fprintf(fptr,"			}\n");
	if(stage==mf_log2(fft_len))
	{
		fprintf(fptr,"			GLOBAL_INNER_ITERATION_COUNTER_s1=(GLOBAL_INNER_ITERATION_COUNTER_s1+1)&GLOBAL_INNER_ITERATION_COUNTER_MASK_s1;\n");
		fprintf(fptr,"			if(GLOBAL_INNER_ITERATION_COUNTER_s1 > (GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s1 -1))\n");
		fprintf(fptr,"			{\n");
		fprintf(fptr,"			   GLOBAL_INNER_ITERATION_COUNTER_s1=0;\n");
		fprintf(fptr,"			}\n");
	}
	fprintf(fptr,"	//}\n");
	fprintf(fptr,"		 #endif\n");
	fprintf(fptr,"	//}\n");
	fprintf(fptr,"}\n");
	/*fprintf(fptr,"}\n");	*/		 
}

void print_BODY_global_constants_stageN_dot_h(FILE *fptr,int stage,int fft_len)
{
	int temp,counter_gen_mask;
	int logfft_len;
	temp = (1<< (mf_log2(fft_len) +2 - stage ))-1;
	logfft_len = mf_log2(fft_len);
	counter_gen_mask = (1<<(logfft_len - stage + 1))-1;
	fprintf(fptr,"\t///////////////////////////////////////////////////////\n"); 
	fprintf(fptr,"\t/// Constants for Stage Number-%d\n",stage); 
	fprintf(fptr,"\t#define STAGE_NUMBER_s%d %d\n",stage,stage);
	fprintf(fptr,"\t#define STAGE_NUMBER_TO_POWER_2_s%d %d\n",stage,power2(stage));
	fprintf(fptr,"\t#define GLOBAL_INNER_ITERATION_COUNTER_MASK_s%d %d\n",stage,temp);

	temp = (1<< (stage+1))-1;
	fprintf(fptr,"\t#define GLOBAL_OUTER_ITERATION_COUNTER_MASK_s%d %d\n",stage,temp);
	

	// Print global outer iteration counter limit: That defines how many time an atomic
	// Butterfly unit should iterate to execute one computaion of a column in signal flow
	// graph. Actually in R2SDF every column has a symmetric set of butterflies that are 
	// executed number of times= powerOf2(stage_number-1) , where first stage on left is
	// indexed as "1"
	temp = power2(stage-1);
	fprintf(fptr,"\t#define GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s%d %d\n",stage,temp);
	// Define limits in the inner counter , that controls how much buffer is done in the first
	// phase before starting the butteflies and and then keeps track on number of butterflies
	// that will be executed per each iteration of the outer iteration counter.

	temp = fft_len/(power2(stage));
	fprintf(fptr,"\t#define GLOBAL_INNER_ITERATION_COUNTER_BUFFER_LIMIT_s%d %d\n",stage,temp);
	fprintf(fptr,"\t#define GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s%d %d\n",stage,2*temp);
	// Read pointer mask will converts a simple buffer to a circular buffer
	fprintf(fptr,"\t#define RD_PTR_MASK_s%d %d\n",stage,temp-1);

	fprintf(fptr,"\t///////////////////////////////////////////////////////\n"); 
	fprintf(fptr,"// The constants that will be used for masking \n");
	fprintf(fptr,"// These constact will be used to mask a counter\n //for stage1 to get the inner iteration counts for different stages \n");
	fprintf(fptr,"#define INNER_ITERATION_COUNTER_MASK_s%d %d\n",stage,counter_gen_mask);
	

	fprintf(fptr,"\t///////////////////////////////////////////////////////\n"); 
}
void print_BODY_global_variables_stageN_dot_h(FILE *fptr,int stage,int fft_len)
{
	fprintf(fptr,"\t//Global Schedule control variabels for stage:%d\n",stage);  
	fprintf(fptr,"\tint GLOBAL_OUTER_ITERATION_COUNTER_s%d;\n",stage);
	if(stage==1)
	{
		fprintf(fptr,"#ifdef HLS_MODEL\n");
		fprintf(fptr,"\tsc_signal<int> GLOBAL_INNER_ITERATION_COUNTER_s%d;\n",stage);
		fprintf(fptr,"#else \n");
		fprintf(fptr,"\tint GLOBAL_INNER_ITERATION_COUNTER_s%d;\n",stage);
		fprintf(fptr,"#endif \n");
	}

	fprintf(fptr,"\t///////////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"\t/// Stage-1 variables\n");
	fprintf(fptr,"\tdtype_f shift_register_s%d_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d];\n",stage,stage);
	fprintf(fptr,"\tdtype_f shift_register_s%d_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s%d];\n",stage,stage);
	fprintf(fptr,"\tdtype_int i_s%d,j_s%d;\n",stage,stage);
	fprintf(fptr,"\tdtype_f input_s%d[FFT_LEN];\n",stage);
	fprintf(fptr,"\t#ifdef USE_CIRCULAR_BUFFERS\n");
	fprintf(fptr,"\tint RD_PTR_s%d;\n",stage);
	fprintf(fptr,"\t#endif\n");
	fprintf(fptr,"\t///////////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"\t#ifdef HLS_MODEL\n");
	fprintf(fptr,"\t//////////////////////CLASS STATIC MEMBERS////////////////////////////////////////\n");
	fprintf(fptr,"\tstatic const dtype_f twiddle_table_s%d[FFT_LEN>>%d];\n",stage,stage);
	fprintf(fptr,"\tstatic const dtype_f twiddle_table_imag_s%d[FFT_LEN>>%d];\n",stage,stage);
	fprintf(fptr,"\t//////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"\t#else\n");
	fprintf(fptr,"\t///////////////////////////////////////////////////////////////////////////////////\n");
	fprintf(fptr,"\tdtype_f twiddle_table_s%d[FFT_LEN>>%d];\n",stage,stage);
	fprintf(fptr,"\tdtype_f twiddle_table_imag_s%d[FFT_LEN>>%d];\n",stage,stage);
	fprintf(fptr,"\t#endif\n");

}

void print_BODY_global_constants_dot_h(FILE *fptr,int fft_len,int in_sample_width,int output_sample_width,int fft_threads,int circular_buffers,int ctos_model, int pfft_input_sample_fractional_part_len, int pfft_input_sample_integer_part_len, int pfft_output_sample_fractional_part_len, int pfft_output_sample_inetger_part_len)
{
	
	

	fprintf(fptr,"#define FFT_LEN %d\n",fft_len);
	fprintf(fptr,"#define FFT_LEN_LOG2 %d\n",mf_log2(fft_len));
	fprintf(fptr,"#define INTERFACE_WIDTH %d\n",in_sample_width);
	fprintf(fptr,"#define OUTPUT_INTERFACE_WIDTH %d\n",output_sample_width);
	fprintf(fptr,"#define HLS_MODEL\n");
	
	if(ctos_model!=1)
	{ 
		fprintf(fptr,"#define LOG_FILE\n");
		fprintf(fptr,"#define CREATE_LOG\n");
	}
	else
	{ 
	fprintf(fptr,"//#define LOG_FILE\n");
	fprintf(fptr,"//#define CREATE_LOG\n");
	}
	if(fft_threads==1)
	{
	fprintf(fptr,"#define SINGLE_THREAD_WRAPPER\n");
	}
	else
	{
		fprintf(fptr,"//#define SINGLE_THREAD_WRAPPER\n");
	}
	
	if(circular_buffers==1)
	{
	fprintf(fptr,"#define USE_CIRCULAR_BUFFERS\n");
	}
	else
	{
	fprintf(fptr,"//#define USE_CIRCULAR_BUFFERS\n");
	}

	

	fprintf(fptr,"#define INPUT_SAMPLE_BIT_WIDTH %d\n",in_sample_width);
	fprintf(fptr,"#define INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH %d\n",pfft_input_sample_integer_part_len);
	fprintf(fptr,"#define INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH %d\n",pfft_input_sample_fractional_part_len);

	fprintf(fptr,"#define OUTPUT_SAMPLE_BIT_WIDTH %d\n",output_sample_width);
	fprintf(fptr,"#define OUTPUT_SAMPLE_INTEGER_PART_BIT_WIDTH %d\n",pfft_output_sample_inetger_part_len);
	fprintf(fptr,"#define OUTPUT_SAMPLE_FRACTION_PART_BIT_WIDTH %d\n",pfft_output_sample_fractional_part_len);

	fprintf(fptr,"#define TWIDDLE_FACTORS_BIT_WIDTH 8\n");
	fprintf(fptr,"#define TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH 7\n");
	fprintf(fptr,"#define TWIDDLE_FACTORS_INTEGER_PART_BIT_WIDTH 1\n");

}

void print_BODY_dtype_dot_h(FILE *fptr)
{
	fprintf(fptr,"typedef int dtype_f;\n" );
	fprintf(fptr,"typedef int dtype_int;\n" );
	fprintf(fptr,"	struct mcomplex {");
	fprintf(fptr,"	 dtype_int real;");
	fprintf(fptr,"	 dtype_int imag;");
	fprintf(fptr,"};");
	
}
void printAuthor(FILE *fptr,char* file_name,char *file_ext)
{
	// This function will print the details of the author
	// to the given input file...
	time_t t = time(NULL);
    struct tm tm = *localtime(&t); // Get current time and the date
    if(strcmp(file_ext,"tcl")!=0)
    {
	fprintf(fptr, "/* File Name : %s.%s\n",file_name,file_ext);
	fprintf(fptr,"* This is an automatically generated file using HLS IP generator\n");
	fprintf(fptr,"* File creation time:%d-%d-%d %d:%d:%d\n", tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fprintf(fptr,"* Author Name : Shahzad Ahmad Butt\n");
	fprintf(fptr,"* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com\n");
	fprintf(fptr,"* PostDoctoral Researcher at Micro-electronics Group\n");
	fprintf(fptr,"* Department of Electronics and Telecommunications \n");
	fprintf(fptr,"* Politecnico di Torino, Torino, Italy\n");
	fprintf(fptr,"* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt\n");
	fprintf(fptr,"*/\n");
	}
	else
	{
		fprintf(fptr, "# File Name : %s.%s\n",file_name,file_ext);
		fprintf(fptr,"# This is an automatically generated file using HLS IP generator\n");
		fprintf(fptr,"# File creation time:%d-%d-%d %d:%d:%d\n", tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(fptr,"# Author Name : Shahzad Ahmad Butt\n");
		fprintf(fptr,"# Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com\n");
		fprintf(fptr,"# PostDoctoral Researcher at Micro-electronics Group\n");
		fprintf(fptr,"# Department of Electronics and Telecommunications \n");
		fprintf(fptr,"# Politecnico di Torino, Torino, Italy\n");
		fprintf(fptr,"# http://polimage.polito.it/wsn/people/shahzad-ahmad-butt\n");
		fprintf(fptr,"#\n");

	}
	
}

void printFileGaurd_start(FILE *fptr, char *file_name,char *file_ext)
{
	char *file_upCase;
    file_upCase=covertToUpper(file_name);
	fprintf(fptr, "\n\n#ifndef %s_H_\n",file_upCase);
	fprintf(fptr, "#define %s_H_\n\n",file_upCase);
}

void printFileGaurd_end(FILE *fptr, char *file_name,char *file_ext)
{
   char *file_upCase;
   file_upCase=covertToUpper(file_name);
   fprintf(fptr, "\n\n#endif /* %s_H_ */ \n",file_upCase);
}

// This function will convert a string to upper case letters
char *covertToUpper(char *str)
{
    char *newstr, *p;
    p = newstr =strdup(str);
    while(*p++=toupper(*p));

    return newstr;
}












