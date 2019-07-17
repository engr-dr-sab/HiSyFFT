/* File Name : functional_behavior_stage7.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef UNCTIONAL_BEHAVIOR_STAGE7_H_
#define UNCTIONAL_BEHAVIOR_STAGE7_H_

#ifdef HLS_MODEL
void pipeLinedFFT_WRAPPER::functional_behavior_stage7(struct mcomplex sample_input_stage7,struct mcomplex *output_ret )
#else
void functional_behavior_stage7(struct mcomplex sample_input_stage7,struct mcomplex *output_ret)
#endif
{
	int i;
dtype_f mem_reg1,mem_reg2,mem_reg3,mem_reg4;
	//if(GLOBAL_OUTER_ITERATION_COUNTER_s7 <  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s7 )
	//{
	#ifdef USE_CIRCULAR_BUFFERS
		///////////////////////////////Behavior with circular Buffers $START//////////////////////////////////
		//Read the input stream for processing and stream out previously calculated values
		mem_reg1=shift_register_s7_real[RD_PTR_s7];
		mem_reg2=shift_register_s7_imag[RD_PTR_s7];
		L_readInputStreamWriteLastCalculateOuput_s7:
		if((GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7) < GLOBAL_INNER_ITERATION_COUNTER_BUFFER_LIMIT_s7 )
		{
			// Read a sample, buffer it and write a sample output for next stage
			// Write last element from the buffer to output signal
			output_ret->real=mem_reg1;
			output_ret->imag=mem_reg2;
			mem_reg3=sample_input_stage7.real;
			mem_reg4=sample_input_stage7.imag;
			    //mmmRD_PTR_s7=((RD_PTR_s7+1)&RD_PTR_MASK_s7);
			    //mmmGLOBAL_INNER_ITERATION_COUNTER_s7=(GLOBAL_INNER_ITERATION_COUNTER_s7+1)&GLOBAL_INNER_ITERATION_COUNTER_MASK_s7;
			#ifdef TIMED_MODEL22
			wait();
			#endif
		} else { 
		///////////////////////////////Behavior with circular Buffers $END////////////////////////////////// 
		#else
		mem_reg1= shift_register_s7_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7 -1];
		mem_reg2= shift_register_s7_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7 -1];
		if(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7 < GLOBAL_INNER_ITERATION_COUNTER_BUFFER_LIMIT_s7 )
		{
			// Read a sample, buffer it and write a sample output for next stage
			// Write last element from the buffer to output signal
			output_ret->real= mem_reg1;
			output_ret->imag= mem_reg2;
			int temp_real =shift_register_s7_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7 -1];// stageInterface[STAGE_NUMBER_s7].read();
			int temp_imag =shift_register_s7_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7 -1];// stageInterface[STAGE_NUMBER_s7].read();
			L_shiftInputSampleInBuffer_s7:
			for(i=FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7-1;i>0;i--)
			{
				shift_register_s7_real[i]= 65535 &  shift_register_s7_real[i-1];
				shift_register_s7_imag[i]= 65535 &  shift_register_s7_imag[i-1];
				// read the input sample and store in the buffer
			}
			mem_reg3=sample_input_stage7.real;
			mem_reg4=sample_input_stage7.imag;
			//GLOBAL_INNER_ITERATION_COUNTER_s7=(GLOBAL_INNER_ITERATION_COUNTER_s7+1)&GLOBAL_INNER_ITERATION_COUNTER_MASK_s7;
			#ifdef TIMED_MODEL22
			wait();
			#endif
		} else {
		#endif
		 // calculate the outputs for current frame store half of them
		 // and, calculate and stream out half of the outputs for butterflies
		#ifdef USE_CIRCULAR_BUFFERS
		L_execSingleButterflyPerIteration_s7:
		//else( GLOBAL_INNER_ITERATION_COUNTER_s7 <= (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7 + FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7 -1) )
		//{
			// read the input and process to execute butterflies
			dtype_f temp1_real,temp2_real;
			dtype_f temp1_imag,temp2_imag;
			dtype_f bout_imag,bout_real;
			dtype_f bout_imag_part1,bout_real_part1;
			dtype_f bout_imag_part2,bout_real_part2;
			dtype_f twiddle_imag,twiddle_real;
			dtype_f temp_out_sum_real,temp_out_diff_real;
			dtype_f temp_out_sum_imag,temp_out_diff_imag;
			// Read Twiddle table enteries and input samples to be processes in temporary variables.
			j_s7 = GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7 - FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7;
			twiddle_real=twiddle_table_s7[(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7) & ((FFT_LEN>>7)-1)];
			twiddle_imag=twiddle_table_imag_s7[(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7) & ((FFT_LEN>>7)-1)];
			temp1_real = mem_reg1; //last value from buffer
			temp1_imag = mem_reg2; //last value from buffer
			temp2_real = sample_input_stage7.real;
			temp2_imag = sample_input_stage7.imag;
			// execute butterfly
			butterfly( temp1_real,  temp1_imag ,  temp2_real ,  twiddle_imag, twiddle_real,  temp2_imag ,  &temp_out_sum_real,  &temp_out_sum_imag,  &bout_real, &bout_imag, INPUT_SAMPLE_BIT_WIDTH , INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE ,SATURATION_MODE,0);
			// Stream out the sum output
			// Stream out the calculated value
			// store the difference sample in buffer and shift the buffer
			// Store the calculated out sample it will be streamed out in next phase
			mem_reg3=bout_real;
			mem_reg4=bout_imag;
			//if(GLOBAL_OUTER_ITERATION_COUNTER_s7 >=  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s7 )
				//GLOBAL_OUTER_ITERATION_COUNTER_s7=0;
			output_ret->real=temp_out_sum_real;
			output_ret->imag=temp_out_sum_imag;
			#ifdef TIMED_MODEL22
			wait();
			#endif
		 }
		 shift_register_s7_real[RD_PTR_s7]=mem_reg3;
		 shift_register_s7_imag[RD_PTR_s7]=mem_reg4;
			RD_PTR_s7=((RD_PTR_s7+1)&RD_PTR_MASK_s7);
			//GLOBAL_INNER_ITERATION_COUNTER_s7=(GLOBAL_INNER_ITERATION_COUNTER_s7+1)&GLOBAL_INNER_ITERATION_COUNTER_MASK_s7;
			if((GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7) == (GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s7))
			{
			//	GLOBAL_INNER_ITERATION_COUNTER_s7=0;
			//	GLOBAL_OUTER_ITERATION_COUNTER_s7=(GLOBAL_OUTER_ITERATION_COUNTER_s7 + 1) %  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s7;
				if(GLOBAL_OUTER_ITERATION_COUNTER_s7==( GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s7-1))
				GLOBAL_OUTER_ITERATION_COUNTER_s7=0;
				else
				GLOBAL_OUTER_ITERATION_COUNTER_s7=(GLOBAL_OUTER_ITERATION_COUNTER_s7 + 1)&GLOBAL_OUTER_ITERATION_COUNTER_MASK_s7;
			}
	//}
		#else
		// else( GLOBAL_INNER_ITERATION_COUNTER_s7  <= (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7 + FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7 -1) )
		//{
			// read the input and process to execute butterflies
			dtype_f temp1_real,temp2_real;
			dtype_f temp1_imag,temp2_imag;
			dtype_f bout_imag,bout_real;
			dtype_f bout_imag_part1,bout_real_part1;
			dtype_f bout_imag_part2,bout_real_part2;
			dtype_f twiddle_imag,twiddle_real;
			dtype_f temp_out_sum_imag,temp_out_diff_imag;
			dtype_f temp_out_sum_real,temp_out_diff_real;
			j_s7 = (GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7) - FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7;
			twiddle_real=twiddle_table_s7[(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7) % (FFT_LEN>>7)];
			twiddle_imag=twiddle_table_imag_s7[(GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7) % (FFT_LEN>>7)];
		//	temp1_real = shift_register_s7_real[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7-1]; //last value from buffer
		//	temp1_imag = shift_register_s7_imag[FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7-1]; //last value from buffer
			temp1_real = mem_reg1; //last value from buffer
			temp1_imag = mem_reg2; //last value from buffer
			temp2_real = sample_input_stage7.real;
			temp2_imag = sample_input_stage7.imag;
			// execute butterfly
			butterfly( temp1_real,  temp1_imag ,  temp2_real ,  twiddle_imag, twiddle_real,  temp2_imag ,  &temp_out_sum_real,  &temp_out_sum_imag,  &bout_real, &bout_imag, INPUT_SAMPLE_BIT_WIDTH , INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH,TWIDDLE_FACTORS_BIT_WIDTH,TWIDDLE_FACTORS_FRACTION_PART_BIT_WIDTH,TRUNCATE_MODE ,SATURATION_MODE,0);
			output_ret->real=temp_out_sum_real;
			output_ret->imag=temp_out_sum_imag;
			// store the difference sample in buffer and shift the buffer
			L_storeOutputsInShiftRegister_s7:
			for(i=FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7-1;i>0;i--)
			{
				shift_register_s7_real[i]= 65535 & shift_register_s7_real[i-1];
				shift_register_s7_imag[i]= 65535 & shift_register_s7_imag[i-1];
			}
			// Store the calculated out sample it will be streamed out in next phase
			//shift_register_s7_real[0]=bout_real;
			//shift_register_s7_imag[0]=bout_imag;
			mem_reg3=bout_real;
			mem_reg4=bout_imag;
			//if(GLOBAL_OUTER_ITERATION_COUNTER_s7 >=  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s7 )
				//GLOBAL_OUTER_ITERATION_COUNTER_s7=0;
			#ifdef TIMED_MODEL22
			wait();
			#endif
		}
		shift_register_s7_real[0]=mem_reg3;
		shift_register_s7_imag[0]=mem_reg4;
			//GLOBAL_INNER_ITERATION_COUNTER_s1 INNER_ITERATION_COUNTER_MASK_s7 =(GLOBAL_INNER_ITERATION_COUNTER_s7+1) & GLOBAL_INNER_ITERATION_COUNTER_MASK_s7;
			if((GLOBAL_INNER_ITERATION_COUNTER_s1 & INNER_ITERATION_COUNTER_MASK_s7) == (GLOBAL_INNER_ITERATION_COUNTER_BUTTERFLY_LIMIT_s7))
			{
			//	GLOBAL_INNER_ITERATION_COUNTER_s7=0;
				//GLOBAL_OUTER_ITERATION_COUNTER_s7=((GLOBAL_OUTER_ITERATION_COUNTER_s7 + 1) %  GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s7)&GLOBAL_OUTER_ITERATION_COUNTER_MASK_s7;
				if(GLOBAL_OUTER_ITERATION_COUNTER_s7== GLOBAL_OUTER_ITERATION_COUNTER_LIMIT_s7)
				GLOBAL_OUTER_ITERATION_COUNTER_s7=0;
				else
				GLOBAL_OUTER_ITERATION_COUNTER_s7=(GLOBAL_OUTER_ITERATION_COUNTER_s7 + 1)&GLOBAL_OUTER_ITERATION_COUNTER_MASK_s7;
				//GLOBAL_OUTER_ITERATION_COUNTER_s7=(GLOBAL_OUTER_ITERATION_COUNTER_s7 + 1)&GLOBAL_OUTER_ITERATION_COUNTER_MASK_s7;
			}
	//}
		 #endif
	//}
}


#endif /* UNCTIONAL_BEHAVIOR_STAGE7_H_ */ 
