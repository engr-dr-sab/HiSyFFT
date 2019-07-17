#ifndef FIXED_POINT_LIB_H_
#define FIXED_POINT_LIB_H_
//shazfunc_number1
/*---------------------------------Function-------------------------------------------------
* Name:"toQ":This function will convert a double number  to a fixed point integer 
* representation.
* The output number can be maximum of 32 bits.
*--------------------------------- Arguments------------------------------------------------
* #1 : number	: It is a double number that will be converted to fixed point
* #2 : num_len  : Total number of bits that will be used to store the fixed-point number
# #3 : frac_len : This defines total nuber of bits used to store the fractional part.
*-------------------------------------------------------------------------------------------
*/
int toQ(double number,unsigned int num_len,unsigned int frac_len);
// {
// 	  int repMax,repMin,fixed;
// 	  double temp;
// 	  repMax = (1<<(num_len-1))-1;
// 	  repMin = -(1<<(num_len-1));
// 	  temp =  number * (1<<frac_len);
// 	  fixed  =  (int)(temp);
// 	  if(fixed > repMax)
// 		  fixed = repMax;
// 	  else if(fixed < repMin)
// 		  fixed = repMin;
// 	  return fixed;

// }
//shazfunc_number2
/*---------------------------------Function--------------------------------------------------------
* Name:"toFloat":This function will convert a fixed point integer number  to a  
* floating point number.
* The input number can be maximum of 32 bits.
*--------------------------------- Arguments-------------------------------------------------------
* #1 : number	: It is a fixed point number that will be converted to double
* #2 : num_len  : Total number of bits that will be used to store the fixed-point number
# #3 : frac_len : This defines total nuber of bits used to store the fractional part.
*--------------------------------------------------------------------------------------------------
*/
double toFloat(int number,unsigned int num_len,unsigned int frac_len);
// {
// 	unsigned int steps;
// 	double resolution,output;
// 	steps = 1<<(frac_len);
// 	resolution  = ((double)1)/((double)steps);
// 	output = resolution * number;
// 	return output;
// }

#endif 
/* End of *FIXED_POINT_LIB_H_*/
