/* File Name : global_constants_stage8.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef LOBAL_CONSTANTS_STAGE8_H_
#define LOBAL_CONSTANTS_STAGE8_H_

	///////////////////////////////////////////////////////
	/// Constants for Stage Number-8
	#define STAGE_NUMBER_s8 8
	#define STAGE_NUMBER_TO_POWER_2_s8 256
	#define GLOBAL_INNER_ITERATION_COUNTER_MASK_s8 31
	#define GLOBAL_OUTER_ITERATION_COUNTER_MASK_s8 511
	#define GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s8 128
	#define GLOBAL_INNER_ITERATION_COUNTER_BUFFER_LIMIT_s8 8
	#define GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s8 16
	#define RD_PTR_MASK_s8 7
	///////////////////////////////////////////////////////
// The constants that will be used for masking 
// These constact will be used to mask a counter
 //for stage1 to get the inner iteration counts for different stages 
#define INNER_ITERATION_COUNTER_MASK_s8 15
	///////////////////////////////////////////////////////


#endif /* LOBAL_CONSTANTS_STAGE8_H_ */ 
