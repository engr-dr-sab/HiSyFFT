/* File Name : global_constants_stage7.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef LOBAL_CONSTANTS_STAGE7_H_
#define LOBAL_CONSTANTS_STAGE7_H_

	///////////////////////////////////////////////////////
	/// Constants for Stage Number-7
	#define STAGE_NUMBER_s7 7
	#define STAGE_NUMBER_TO_POWER_2_s7 128
	#define GLOBAL_INNER_ITERATION_COUNTER_MASK_s7 63
	#define GLOBAL_OUTER_ITERATION_COUNTER_MASK_s7 255
	#define GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s7 64
	#define GLOBAL_INNER_ITERATION_COUNTER_BUFFER_LIMIT_s7 16
	#define GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s7 32
	#define RD_PTR_MASK_s7 15
	///////////////////////////////////////////////////////
// The constants that will be used for masking 
// These constact will be used to mask a counter
 //for stage1 to get the inner iteration counts for different stages 
#define INNER_ITERATION_COUNTER_MASK_s7 31
	///////////////////////////////////////////////////////


#endif /* LOBAL_CONSTANTS_STAGE7_H_ */ 
