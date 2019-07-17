/* File Name : pipeLinedFFT_WRAPPER.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef IPELINEDFFT_WRAPPER_H_
#define IPELINEDFFT_WRAPPER_H_

#include "global_constants.h"
#ifndef HLS_MODEL
#include <stdio.h>
#endif
#include "systemc.h"
#include "dtype.h"
#include "hls_fixed_point_lib.h"
#include "global_constants_stage1.h"
#include "global_constants_stage2.h"
#include "global_constants_stage3.h"
#include "global_constants_stage4.h"
#include "global_constants_stage5.h"
#include "global_constants_stage6.h"
#include "global_constants_stage7.h"
#include "global_constants_stage8.h"
#include "global_constants_stage9.h"
#include "global_constants_stage10.h"
#include "global_constants_stage11.h"
class pipeLinedFFT_WRAPPER:public sc_module
{
	/* public data and function members */
	public:
		pipeLinedFFT_WRAPPER(sc_module_name name); // constructor
		SC_HAS_PROCESS(pipeLinedFFT_WRAPPER); //
		#ifdef LOG_FILE 
		FILE * logFile;
		void logThread();
		#endif
//Stitch together all the global variables from different pipeline stages as class members
		#include "global_variables_stage1.h"
		#include "global_variables_stage2.h"
		#include "global_variables_stage3.h"
		#include "global_variables_stage4.h"
		#include "global_variables_stage5.h"
		#include "global_variables_stage6.h"
		#include "global_variables_stage7.h"
		#include "global_variables_stage8.h"
		#include "global_variables_stage9.h"
		#include "global_variables_stage10.h"
		#include "global_variables_stage11.h"
		//define interface signals
		sc_signal < sc_int < 16 > > stageInterface_real[FFT_LEN_LOG2+1];
		sc_signal < sc_int < 16 > > stageInterface_imag[FFT_LEN_LOG2+1];
		//Define all the signal that will be used for synchronization between the stages
		//All these signals will be internal to overall FFT.
		sc_signal < bool > hshake[FFT_LEN_LOG2+1];
		/////////////////////////////////////////////////////////////////////
		// Inputs
		/////////////////////////////////////////////////////////////////////
		sc_in<bool> clk;
		sc_in< bool > reset;
		sc_in< bool > start;
		sc_out< bool > done;
		sc_in< sc_int <INTERFACE_WIDTH> > sample_input_real;
		sc_in< sc_int <INTERFACE_WIDTH> > sample_input_imag;
		/////////////////////////////////////////////////////////////////////
		// Outputs
		/////////////////////////////////////////////////////////////////////
		sc_out< bool > ready;
		sc_out< sc_int <OUTPUT_INTERFACE_WIDTH> > sample_output_real;
		sc_out< sc_int <OUTPUT_INTERFACE_WIDTH> > sample_output_imag;
		/////////////////////////////////////
		/// Stage-1
		void init_stage1(void);
		/// Stage-2
		void init_stage2(void);
		/// Stage-3
		void init_stage3(void);
		/// Stage-4
		void init_stage4(void);
		/// Stage-5
		void init_stage5(void);
		/// Stage-6
		void init_stage6(void);
		/// Stage-7
		void init_stage7(void);
		/// Stage-8
		void init_stage8(void);
		/// Stage-9
		void init_stage9(void);
		/// Stage-10
		void init_stage10(void);
		/// Stage-11
		void init_stage11(void);
		/////////////////////////////////////
		#ifdef CREATE_LOG
		void log_var(char *file_name,int variable);
      void log_varf(char *file_name,double variable);
		#endif
		void init_all(void);
		// output assigning process
		void assign_outputs(void);
		// input assigning process
		void assign_inputs(void);
		// Possible Functional Behaviour of PipeLined Stages that allows to achieve higher level of concurrency...
		void functional_behavior_stage1(struct mcomplex sample_input_stage1,struct mcomplex *output_ret);
		void functional_behavior_stage2(struct mcomplex sample_input_stage2,struct mcomplex *output_ret);
		void functional_behavior_stage3(struct mcomplex sample_input_stage3,struct mcomplex *output_ret);
		void functional_behavior_stage4(struct mcomplex sample_input_stage4,struct mcomplex *output_ret);
		void functional_behavior_stage5(struct mcomplex sample_input_stage5,struct mcomplex *output_ret);
		void functional_behavior_stage6(struct mcomplex sample_input_stage6,struct mcomplex *output_ret);
		void functional_behavior_stage7(struct mcomplex sample_input_stage7,struct mcomplex *output_ret);
		void functional_behavior_stage8(struct mcomplex sample_input_stage8,struct mcomplex *output_ret);
		void functional_behavior_stage9(struct mcomplex sample_input_stage9,struct mcomplex *output_ret);
		void functional_behavior_stage10(struct mcomplex sample_input_stage10,struct mcomplex *output_ret);
		void functional_behavior_stage11(struct mcomplex sample_input_stage11,struct mcomplex *output_ret);
		// constructor
		// Declare all the thread wrapper for pipeline stages
		// These thread wrappers will allow us to define level of concurrency.
		void stage1_exec_WRAPPER(void);
		void stage2_exec_WRAPPER(void);
		void stage3_exec_WRAPPER(void);
		void stage4_exec_WRAPPER(void);
		void stage5_exec_WRAPPER(void);
		void stage6_exec_WRAPPER(void);
		void stage7_exec_WRAPPER(void);
		void stage8_exec_WRAPPER(void);
		void stage9_exec_WRAPPER(void);
		void stage10_exec_WRAPPER(void);
		void stage11_exec_WRAPPER(void);
#ifdef SINGLE_THREAD_WRAPPER
	void single_thread_wrapper(void);
#endif
};


#endif /* IPELINEDFFT_WRAPPER_H_ */ 
