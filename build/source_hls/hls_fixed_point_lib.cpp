/* File Name : hls_fixed_point_lib.cpp
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/



#include "dtype.h"
#include "hls_fixed_point_lib.h"


//@@2_function_number:fft_support_functions
// Generic round function  
int round(int input ,  unsigned int in_frac_len ,unsigned int out_frac_len, unsigned int rmod)
{
    unsigned int no_of_bits_truncated;
	int output =input;
	
	if( in_frac_len > out_frac_len)
	{
	    no_of_bits_truncated = in_frac_len - out_frac_len;
		if(rmod==TRUNCATE_MODE)
			 output = output >> no_of_bits_truncated;
		else if(rmod==ROUND_MODE)
		output = (((output & (1<<(no_of_bits_truncated-1))) != 0) && (((output & ((1<<(no_of_bits_truncated-1))-1)) != 0) || (output > 0))) + (output >> no_of_bits_truncated);
		else if(rmod==CEIL_MODE)
		output = ((output & (((1<<(no_of_bits_truncated))-1))) != 0) + (output >> no_of_bits_truncated);
    }
	else if( out_frac_len > in_frac_len)
	{
	    output = output << (out_frac_len - in_frac_len);
	}
	return output;
}

int ovManager(int input , unsigned int input_len , unsigned int out_len ,unsigned int ov_mode )
{
	int output = input;
	int testDig;
	/*if(input_len >= out_len)
	{*/
		if(ov_mode == SATURATION_MODE)
		{
			if( output > (((1<<(out_len-1))-1)) )
			output = ((1<<(out_len-1))-1);
			else if (output < (-1*(1<<(out_len-1))))
			{
				output = (-1*(1<<(out_len-1))) ;
			}
		}
		else if(ov_mode == WRAP_MODE)
		{
		   // Check for msb and extended it in case of wrapping
		   if( ((output>>(out_len-1)) & 1)==1 ) // Extract the sign bit 
		   output = output | ((((1<<(32-out_len-1))-1)<<1)|1)<<out_len;  //(( (1<<(32-input_len))-1)<<(input_len)) ;  //sign extend the number     // ((1<<out_len) - 1);
		   else
		   output = output & ((1 << input_len)-1);
		}
	/*}\n	else
	{
			return output; 
	}*/
		testDig  = output;
	output = (output &  (( ((1<<(out_len-1)) -1) << 1)|1)); ///-------c---cc--
	if( ((output>>(out_len-1)) & 1)==1 ) // Extract the sign bit 
		    output = output | ((((1<<(32-out_len-1))-1)<<1)|1)<<out_len; // (( (1<<(32-input_len))-1)<<(input_len));sign extend the number     // ((1<<out_len) - 1);
		   else
		    output = output & (((1 << (out_len-1))-1)<<1)|1;
	/*if(testDig!=output)
		printf("The ouput mismatch.......
");*/
	return output;

}

int add(int in1, int  in2, unsigned int in1_len,unsigned int in2_len,unsigned int out_len,unsigned int in1_frac_len,unsigned int in2_frac_len,unsigned int out_frac_len,unsigned int rmod,unsigned int ov_mode,int default_mode)
{
    int add,output;
	int in1_temp,in2_temp;
	unsigned int new_frac_len;
	unsigned int new_int_len;
	unsigned int new_len;
	unsigned int max_frac_len;
	unsigned int add_fraction_len,add_integer_len,add_len,no_of_bits_truncated,add_len_after_round;
    ////////////////////////////////////////////////////////////////////////
	// If it is a default mode then 
	if(default_mode==1)
	{

		new_len = in1_len > in2_len ? in1_len : in2_len;
		new_int_len = ((in1_len - in1_frac_len) > (in2_len - in2_frac_len)) ? (in1_len - in1_frac_len):(in1_len - in2_frac_len);
		new_frac_len = new_len - new_int_len;
		max_frac_len = in1_frac_len > in2_frac_len ? in1_frac_len : in2_frac_len;
	    if(in1_frac_len > in2_frac_len)
		 {
			 in1_temp = in1;
			 in2_temp = in2 << (in1_frac_len- in2_frac_len);		 
			 
		 }
		 else if(in1_frac_len < in2_frac_len)
		 {
			 in1_temp = in1 <<(in2_frac_len - in1_frac_len);		
			 in2_temp = in2;
			 
		 }
		 else
		 {
		   in1_temp = in1;
		   in2_temp = in2;
		 }	 
	   output =  in1_temp+in2_temp;
	   output =  output >> (max_frac_len - new_frac_len);
	   if( ((output>>(new_len-1)) & 1)==1 ) // Mask to find the MSB ...IE the sign bit
		   output = output | (( (1<<(32-new_len+1))-1)<<new_len) ; // Sign extens the ouput // ((1<<new_len) - 1);
	   else
		   output = output & ((1 << new_len)-1);
	 return output;
	}
	////////////////////////////////////////////////////////////////////////
	else
	{
		/// check what is the rounding mode and then round the number
		 add_fraction_len = (in1_frac_len > in1_frac_len ? in1_frac_len:in2_frac_len);
		 add_integer_len = ((in1_len - in1_frac_len) > (in2_len - in2_frac_len)) ? (in1_len - in1_frac_len):(in1_len - in2_frac_len);
		 add_len = add_fraction_len + add_integer_len;
		 add_len_after_round = 	out_frac_len + add_integer_len;
		 // Align the Binary Points
		 no_of_bits_truncated = add_fraction_len - out_frac_len;
		 if(in1_frac_len > in2_frac_len)
		 {
			 in1_temp = in1;
			 in2_temp = in2 << (in1_frac_len- in2_frac_len);		  
		 }
		 else if(in1_frac_len < in2_frac_len)
		 {
			 in1_temp = in1 <<(in2_frac_len - in1_frac_len);		
			 in2_temp = in2; 
		 }
		 else
		 {
		   in1_temp = in1;
		   in2_temp = in2;
		 }
		 /// Perfoerm Addition after the binary points are aligned 
		 add =  in1_temp + in2_temp;
		 add = round( add,add_fraction_len,out_frac_len,rmod);
		 add = ovManager(add,add_len_after_round,out_len,ov_mode);
		return add;
	}
	
}

int mul(int in1, int  in2, unsigned int in1_len,unsigned int in2_len,unsigned int out_len,unsigned int in1_frac_len,unsigned int in2_frac_len,unsigned int out_frac_len,unsigned int rmod,unsigned int ov_mode,int default_mode)
{
    ///                                                                                                                                                  
    int prd,output,sat_flag;
	int in1_temp,in2_temp;
	unsigned int prd_fraction_len,prd_integer_len,prd_len,no_of_bits_truncated,prd_len_after_round;
//	unsigned int new_frac_len;
//	unsigned int new_int_len;
	unsigned int new_len;
	unsigned int max_int_len;
	unsigned int max_frac_len;
	////////////////////////////////////////////////////////////////////////
	// If it is a default mode then 
	if(default_mode==1)
	{
		
		
		max_int_len = ((in1_len - in1_frac_len) > (in2_len - in2_frac_len)) ? (in1_len - in1_frac_len):(in1_len - in2_frac_len);
		max_frac_len = in1_frac_len > in2_frac_len ? in1_frac_len : in2_frac_len;
		new_len = 2*max_frac_len + 2*max_int_len;
	    if(in1_frac_len > in2_frac_len)
		 {
			 in1_temp = in1;
			 in2_temp = in2 << (in1_frac_len- in2_frac_len);		 
			 
		 }
		 else if(in1_frac_len < in2_frac_len)
		 {
			 in1_temp = in1 <<(in2_frac_len - in1_frac_len);		
			 in2_temp = in2;
			 
		 }
		 else
		 {
		   in1_temp = in1;
		   in2_temp = in2;
		 }	
	  output=  in1_temp*in2_temp;

	   if( ((output>>(new_len-1)) & 1)==1 )
		   output = output | (( (1<<(32-new_len+1))-1)<<new_len) ;      // ((1<<out_len) - 1);
	   else
		   output = output & ((1 << new_len)-1);

	   	   return output;
	}
	////////////////////////////////////////////////////////////////////////
	else
	{
		prd = in1*in2;
		/// check what is the rounding mode and then round the number
		prd_fraction_len = in1_frac_len +  in2_frac_len;
		prd_integer_len = (in1_len - in1_frac_len) + (in2_len - in2_frac_len);
		prd_len = in1_len + in2_len;
		no_of_bits_truncated = prd_fraction_len - out_frac_len;
		sat_flag = prd_len - (out_len);
		prd_len_after_round = out_frac_len + prd_integer_len;
		
		prd = round(prd,prd_fraction_len,out_frac_len,rmod);
		// if( no_of_bits_truncated > 0)
		// {
			// if(rmod==TRUNCATE_MODE)
				 // prd = prd >> no_of_bits_truncated;
			// else if(rmod==ROUND_MODE)
			// prd = (((prd & (1<<(no_of_bits_truncated-1))) != 0) && (((prd & ((1<<(no_of_bits_truncated-1))-1)) != 0) || (prd > 0))) + (prd >> no_of_bits_truncated);
			// else if(rmod==CEIL_MODE)
			// prd = ((prd & (((1<<(no_of_bits_truncated))-1))) != 0) + (prd >> no_of_bits_truncated);
		// }
		prd = ovManager(prd,prd_len_after_round,out_len,ov_mode);
		
		return prd;
	}
}
	void butterfly(dtype_f temp1_real, dtype_f temp1_imag , dtype_f temp2_real , dtype_f twiddle_imag,dtype_f twiddle_real, dtype_f temp2_imag , dtype_f *temp_out_sum_real, dtype_f *temp_out_sum_imag, dtype_f *bout_real, dtype_f *bout_imag, int pINPUT_SAMPLE_BIT_WIDTH , int pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,int pTWIDDLE_FACTORS_BIT_WIDTH, int pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,  int pTRUNCATE_MODE , int pSATURATION_MODE, int default_mode)
{
	dtype_f bout_imag_part1,bout_real_part1;
	dtype_f bout_imag_part2,bout_real_part2;

	dtype_f temp_out_diff_real;
	dtype_f temp_out_diff_imag;
	//dtype_f temp_out_diff_real,temp_out_sum_imag,temp_out_diff_imag
	*temp_out_sum_real=add(temp1_real,temp2_real,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
	//temp_out_sum_imag =temp1_imag+temp2_imag;
	*temp_out_sum_imag=add(temp1_imag,temp2_imag,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
	//temp_out_diff_real=(temp1_real-temp2_real);
	temp_out_diff_real=add(temp1_real,-temp2_real,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
	temp_out_diff_imag=(temp1_imag-temp2_imag); 
	temp_out_diff_imag=add(temp1_imag,-temp2_imag,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
	//bout_real=(temp_out_diff_real*twiddle_real+temp_out_diff_imag*twiddle_imag);
	//bout_real_part1 = temp_out_diff_real*twiddle_real;
	bout_real_part1=mul(temp_out_diff_real,twiddle_real,pINPUT_SAMPLE_BIT_WIDTH,pTWIDDLE_FACTORS_BIT_WIDTH,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
	//bout_real_part2 = temp_out_diff_imag*twiddle_imag;
	bout_real_part2=mul(temp_out_diff_imag,twiddle_imag,pINPUT_SAMPLE_BIT_WIDTH,pTWIDDLE_FACTORS_BIT_WIDTH,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
	//bout_real = bout_real_part1+bout_real_part2;
	*bout_real=add(bout_real_part1,-bout_real_part2,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
	//bout_imag=(temp_out_diff_imag*twiddle_real-temp_out_diff_real*twiddle_imag);
	//bout_imag_part1=temp_out_diff_imag*twiddle_reala;
	bout_imag_part1=mul(temp_out_diff_imag,twiddle_real,pINPUT_SAMPLE_BIT_WIDTH,pINPUT_SAMPLE_BIT_WIDTH,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
	//bout_imag_part2=temp_out_diff_real*twiddle_imag;
	bout_imag_part2=mul(temp_out_diff_real,twiddle_imag,pINPUT_SAMPLE_BIT_WIDTH,pTWIDDLE_FACTORS_BIT_WIDTH,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
	//bout_imag=bout_imag_part1+bout_imag_part2;
	*bout_imag=add(bout_imag_part1,bout_imag_part2,(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),(pINPUT_SAMPLE_BIT_WIDTH+pTWIDDLE_FACTORS_BIT_WIDTH),pINPUT_SAMPLE_BIT_WIDTH,(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),(pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH+pTWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH),pINPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,pTRUNCATE_MODE,pSATURATION_MODE,default_mode);
}
#ifdef ADD_SYSTEMC_SIMULATION_SUPPORT_FUCNTIONS
int toQ(double number,unsigned int num_len,unsigned int frac_len)
{
	  int repMax,repMin,fixed;
	  double temp;
	  
	  repMax = (1<<(num_len-1))-1;
	  repMin = -(1<<(num_len-1));
	  temp =  number * (1<<frac_len);
	  fixed  =  (int)(temp);
	  if(fixed > repMax)
		  fixed = repMax;
	  else if(fixed < repMin)
		  fixed = repMin;

	  return fixed;

}
double toFloat(int number,unsigned int num_len,unsigned int frac_len)
{
	unsigned int steps;
	double resolution,output;
	steps = 1<<(frac_len);
	resolution  = ((double)1)/((double)steps);
	output = resolution * number;
	return output;
}
#endif
