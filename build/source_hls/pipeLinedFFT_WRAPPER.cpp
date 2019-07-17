/* File Name : pipeLinedFFT_WRAPPER.cpp
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/
#include "global_constants.h"
#include "pipeLinedFFT_WRAPPER.h"
#ifdef __CTOS__
SC_MODULE_EXPORT (pipeLinedFFT_WRAPPER);
#endif
///////////////INCLUDE STAGES.CPP START//////////////////
#include "systemc.h"
///#include "hw_sw_interface.h"
//#include "pipeLinedFFT_WRAPPER.h"
#include "dtype.h"
#ifndef HLS_MODEL
#include "stdio.h"
#endif
#define TIMED_MODEL
///////////////INCLUDE STAGES.CPP END//////////////////
pipeLinedFFT_WRAPPER::pipeLinedFFT_WRAPPER(sc_module_name name)
	:sc_module(name),
		clk("clk"),
		reset("reset"),
		ready("ready"),
		start("start"),
		done("done"),
		sample_input_real("sample_input_real"),
		sample_input_imag("sample_input_imag"),
		sample_output_real("sample_output_real"),
		sample_output_imag("sample_output_imag")
{
	//SC_CTHREAD(step, clk.pos());
#ifdef SINGLE_THREAD_WRAPPER
	SC_CTHREAD(single_thread_wrapper,clk.pos());
	reset_signal_is(reset,true);
	#else
	SC_CTHREAD(stage1_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage2_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage3_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage4_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage5_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage6_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage7_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage8_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage9_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage10_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(stage11_exec_WRAPPER, clk.pos());	reset_signal_is(reset, true);

	SC_CTHREAD(assign_outputs,clk.pos());
	reset_signal_is(reset,true);
	#endif
	
	#ifdef LOG_FILE
	SC_CTHREAD(logThread,clk.pos());
	reset_signal_is(reset,true);

	logFile=fopen("Data_log.lg","w");
	fclose(logFile);

	#endif

}
#ifdef SINGLE_THREAD_WRAPPER
void pipeLinedFFT_WRAPPER::single_thread_wrapper(void)
{
	struct mcomplex in,out1,out2,out3,out4,out5,out6,out7,out8,out9,out10,out11;
	struct mcomplex ind,out1d,out2d,out3d,out4d,out5d,out6d,out7d,out8d,out9d,out10d,out11d;
sc_int < 16 > trans_real;
sc_int < 16 > trans_imag;
	int count;
	sample_output_real.write(0);
	sample_output_imag.write(0);
	done.write(0);
	init_all();
	wait();
	ready.write(true);
	wait();
	while(start.read()==false) wait();
	while(1)
	{
	done.write(false);
	trans_real=(int)sample_input_real.read();//in.real=count;
	trans_imag=(int)sample_input_imag.read();//in.imag=count;
	in.real=trans_real;
	in.imag=trans_imag;
	functional_behavior_stage1(in,&out1d);
	trans_real=out1d.real;
	trans_imag=out1d.imag;;
	out1.real = trans_real;
	out1.imag = trans_imag;
	wait();
	functional_behavior_stage2(out1,&out2d);
	trans_real=out2d.real;
	trans_imag=out2d.imag;;
	out2.real = trans_real;
	out2.imag = trans_imag;
	wait();
	functional_behavior_stage3(out2,&out3d);
	trans_real=out3d.real;
	trans_imag=out3d.imag;;
	out3.real = trans_real;
	out3.imag = trans_imag;
	wait();
	functional_behavior_stage4(out3,&out4d);
	trans_real=out4d.real;
	trans_imag=out4d.imag;;
	out4.real = trans_real;
	out4.imag = trans_imag;
	wait();
	functional_behavior_stage5(out4,&out5d);
	trans_real=out5d.real;
	trans_imag=out5d.imag;;
	out5.real = trans_real;
	out5.imag = trans_imag;
	wait();
	functional_behavior_stage6(out5,&out6d);
	trans_real=out6d.real;
	trans_imag=out6d.imag;;
	out6.real = trans_real;
	out6.imag = trans_imag;
	wait();
	functional_behavior_stage7(out6,&out7d);
	trans_real=out7d.real;
	trans_imag=out7d.imag;;
	out7.real = trans_real;
	out7.imag = trans_imag;
	wait();
	functional_behavior_stage8(out7,&out8d);
	trans_real=out8d.real;
	trans_imag=out8d.imag;;
	out8.real = trans_real;
	out8.imag = trans_imag;
	wait();
	functional_behavior_stage9(out8,&out9d);
	trans_real=out9d.real;
	trans_imag=out9d.imag;;
	out9.real = trans_real;
	out9.imag = trans_imag;
	wait();
	functional_behavior_stage10(out9,&out10d);
	trans_real=out10d.real;
	trans_imag=out10d.imag;;
	out10.real = trans_real;
	out10.imag = trans_imag;
	wait();
	functional_behavior_stage11(out10,&out11);
	wait();
    //count++;
	sample_output_real.write(out11.real);
	sample_output_imag.write(out11.imag);
	#ifdef CREATE_LOG
		log_var("stage1_out_real.lg",out1.real);
		log_var("stage1_out_imag.lg",out1.imag);
		log_varf("stage1_out_real.lgf",toFloat(out1.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage1_out_imag.lgf",toFloat(out1.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage2_out_real.lg",out2.real);
		log_var("stage2_out_imag.lg",out2.imag);
		log_varf("stage2_out_real.lgf",toFloat(out2.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage2_out_imag.lgf",toFloat(out2.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage3_out_real.lg",out3.real);
		log_var("stage3_out_imag.lg",out3.imag);
		log_varf("stage3_out_real.lgf",toFloat(out3.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage3_out_imag.lgf",toFloat(out3.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage4_out_real.lg",out4.real);
		log_var("stage4_out_imag.lg",out4.imag);
		log_varf("stage4_out_real.lgf",toFloat(out4.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage4_out_imag.lgf",toFloat(out4.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage5_out_real.lg",out5.real);
		log_var("stage5_out_imag.lg",out5.imag);
		log_varf("stage5_out_real.lgf",toFloat(out5.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage5_out_imag.lgf",toFloat(out5.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage6_out_real.lg",out6.real);
		log_var("stage6_out_imag.lg",out6.imag);
		log_varf("stage6_out_real.lgf",toFloat(out6.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage6_out_imag.lgf",toFloat(out6.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage7_out_real.lg",out7.real);
		log_var("stage7_out_imag.lg",out7.imag);
		log_varf("stage7_out_real.lgf",toFloat(out7.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage7_out_imag.lgf",toFloat(out7.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage8_out_real.lg",out8.real);
		log_var("stage8_out_imag.lg",out8.imag);
		log_varf("stage8_out_real.lgf",toFloat(out8.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage8_out_imag.lgf",toFloat(out8.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage9_out_real.lg",out9.real);
		log_var("stage9_out_imag.lg",out9.imag);
		log_varf("stage9_out_real.lgf",toFloat(out9.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage9_out_imag.lgf",toFloat(out9.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage10_out_real.lg",out10.real);
		log_var("stage10_out_imag.lg",out10.imag);
		log_varf("stage10_out_real.lgf",toFloat(out10.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage10_out_imag.lgf",toFloat(out10.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage11_out_real.lg",out11.real);
		log_var("stage11_out_imag.lg",out11.imag);
		log_varf("stage11_out_real.lgf",toFloat(out11.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage11_out_imag.lgf",toFloat(out11.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage1_in_real.lg",in.real);
		log_var("stage1_in_imag.lg",in.imag);
		log_varf("stage1_in_real.lgf",toFloat(in.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage1_in_imag.lgf",toFloat(in.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage2_in_real.lg",out1.real);
		log_var("stage2_in_imag.lg",out1.imag);
		log_varf("stage2_in_real.lgf",toFloat(out1.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage2_in_imag.lgf",toFloat(out1.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage3_in_real.lg",out2.real);
		log_var("stage3_in_imag.lg",out2.imag);
		log_varf("stage3_in_real.lgf",toFloat(out2.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage3_in_imag.lgf",toFloat(out2.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage4_in_real.lg",out3.real);
		log_var("stage4_in_imag.lg",out3.imag);
		log_varf("stage4_in_real.lgf",toFloat(out3.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage4_in_imag.lgf",toFloat(out3.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage5_in_real.lg",out4.real);
		log_var("stage5_in_imag.lg",out4.imag);
		log_varf("stage5_in_real.lgf",toFloat(out4.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage5_in_imag.lgf",toFloat(out4.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage6_in_real.lg",out5.real);
		log_var("stage6_in_imag.lg",out5.imag);
		log_varf("stage6_in_real.lgf",toFloat(out5.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage6_in_imag.lgf",toFloat(out5.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage7_in_real.lg",out6.real);
		log_var("stage7_in_imag.lg",out6.imag);
		log_varf("stage7_in_real.lgf",toFloat(out6.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage7_in_imag.lgf",toFloat(out6.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage8_in_real.lg",out7.real);
		log_var("stage8_in_imag.lg",out7.imag);
		log_varf("stage8_in_real.lgf",toFloat(out7.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage8_in_imag.lgf",toFloat(out7.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage9_in_real.lg",out8.real);
		log_var("stage9_in_imag.lg",out8.imag);
		log_varf("stage9_in_real.lgf",toFloat(out8.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage9_in_imag.lgf",toFloat(out8.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage10_in_real.lg",out9.real);
		log_var("stage10_in_imag.lg",out9.imag);
		log_varf("stage10_in_real.lgf",toFloat(out9.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage10_in_imag.lgf",toFloat(out9.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_var("stage11_in_real.lg",out10.real);
		log_var("stage11_in_imag.lg",out10.imag);
		log_varf("stage11_in_real.lgf",toFloat(out10.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage11_in_imag.lgf",toFloat(out10.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
	#endif
	done.write(true);
	wait();
	}

}
#endif
#ifdef CREATE_LOG
void pipeLinedFFT_WRAPPER::log_var(char *file_name,int variable)
{
 FILE *fptr;
 fptr = fopen(file_name,"a");
 fprintf(fptr,"%d\n",variable);
 fclose(fptr);
}
void pipeLinedFFT_WRAPPER::log_varf(char *file_name,double variable)
{
 FILE *fptr;
 fptr = fopen(file_name,"a");
 fprintf(fptr,"%f\n",variable);
 fclose(fptr);
}
#endif
#ifdef LOG_FILE
void pipeLinedFFT_WRAPPER::logThread(void)
{
	FILE *logFile_real,*logFile_imag;	while(start.read()==false) wait();
	while(1)
	{
		
	logFile_real=fopen("Data_log_real.lg","a");
	logFile_imag=fopen("Data_log_imag.lg","a");
	fprintf(logFile_real,"%d\n",(int)sample_output_real.read());
	fprintf(logFile_imag,"%d\n",(int)sample_output_imag.read());
	fclose(logFile_real);
	fclose(logFile_imag);
	wait();
	}
}
#endif

//Define all thread wrappers for pipeline stages
void pipeLinedFFT_WRAPPER::stage1_exec_WRAPPER(void)
{
	//int input_sample;
	//int output_calculated;
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	int count;
	ready.write(false);
	done.write(false);
	count=0;
	wait(); 
	init_stage1();
	wait();
	ready.write(true);
	wait();
	while(start.read()==false) wait();
	hshake[STAGE_NUMBER_s1].write(true);
	while(1)
	{
	input_sample.real =(int)sample_input_real.read();//count
	input_sample.imag =(int)sample_input_imag.read();//count
	functional_behavior_stage1(input_sample,&output_calculated);
	stageInterface_real[STAGE_NUMBER_s1].write(output_calculated.real);
	stageInterface_imag[STAGE_NUMBER_s1].write(output_calculated.imag);
	if(count==FFT_LEN)
	{
	count=0;
	done.write(true);
	}
	else
	{
	count++;
	done.write(false);
	}
	//count++;
	#ifdef CREATE_LOG
	int temp_real = (int)stageInterface_real[STAGE_NUMBER_s1].read();
	int temp_imag = (int)stageInterface_imag[STAGE_NUMBER_s1].read();
		log_var("stage1_out_real.lg",output_calculated.real);
		log_var("stage1_out_imag.lg",output_calculated.imag);
		log_var("stage1_in_imag.lg",input_sample.imag);
		log_var("stage1_in_real.lg",input_sample.real);
		log_varf("stage1_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage1_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage1_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage1_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
	#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage2_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=0;
	hshake[STAGE_NUMBER_s2].write(false);
	 wait();
	init_stage2();
	 wait();
	while(hshake[STAGE_NUMBER_s1].read()==false) wait();
	hshake[STAGE_NUMBER_s2].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s2-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s2-1].read();
		functional_behavior_stage2(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s2].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s2].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage2_out_real.lg",output_calculated.real);
		log_var("stage2_out_imag.lg",output_calculated.imag);
		log_var("stage2_in_real.lg",input_sample.real);
		log_var("stage2_in_imag.lg",input_sample.imag);
		log_varf("stage2_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage2_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage2_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage2_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage3_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=0;
	hshake[STAGE_NUMBER_s3].write(false);
	 wait();
	init_stage3();
	 wait();
	while(hshake[STAGE_NUMBER_s2].read()==false) wait();
	hshake[STAGE_NUMBER_s3].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s3-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s3-1].read();
		functional_behavior_stage3(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s3].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s3].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage3_out_real.lg",output_calculated.real);
		log_var("stage3_out_imag.lg",output_calculated.imag);
		log_var("stage3_in_real.lg",input_sample.real);
		log_var("stage3_in_imag.lg",input_sample.imag);
		log_varf("stage3_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage3_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage3_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage3_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage4_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=0;
	hshake[STAGE_NUMBER_s4].write(false);
	 wait();
	init_stage4();
	 wait();
	while(hshake[STAGE_NUMBER_s3].read()==false) wait();
	hshake[STAGE_NUMBER_s4].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s4-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s4-1].read();
		functional_behavior_stage4(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s4].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s4].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage4_out_real.lg",output_calculated.real);
		log_var("stage4_out_imag.lg",output_calculated.imag);
		log_var("stage4_in_real.lg",input_sample.real);
		log_var("stage4_in_imag.lg",input_sample.imag);
		log_varf("stage4_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage4_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage4_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage4_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage5_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=0;
	hshake[STAGE_NUMBER_s5].write(false);
	 wait();
	init_stage5();
	 wait();
	while(hshake[STAGE_NUMBER_s4].read()==false) wait();
	hshake[STAGE_NUMBER_s5].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s5-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s5-1].read();
		functional_behavior_stage5(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s5].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s5].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage5_out_real.lg",output_calculated.real);
		log_var("stage5_out_imag.lg",output_calculated.imag);
		log_var("stage5_in_real.lg",input_sample.real);
		log_var("stage5_in_imag.lg",input_sample.imag);
		log_varf("stage5_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage5_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage5_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage5_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage6_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=0;
	hshake[STAGE_NUMBER_s6].write(false);
	 wait();
	init_stage6();
	 wait();
	while(hshake[STAGE_NUMBER_s5].read()==false) wait();
	hshake[STAGE_NUMBER_s6].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s6-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s6-1].read();
		functional_behavior_stage6(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s6].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s6].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage6_out_real.lg",output_calculated.real);
		log_var("stage6_out_imag.lg",output_calculated.imag);
		log_var("stage6_in_real.lg",input_sample.real);
		log_var("stage6_in_imag.lg",input_sample.imag);
		log_varf("stage6_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage6_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage6_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage6_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage7_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=0;
	hshake[STAGE_NUMBER_s7].write(false);
	 wait();
	init_stage7();
	 wait();
	while(hshake[STAGE_NUMBER_s6].read()==false) wait();
	hshake[STAGE_NUMBER_s7].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s7-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s7-1].read();
		functional_behavior_stage7(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s7].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s7].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage7_out_real.lg",output_calculated.real);
		log_var("stage7_out_imag.lg",output_calculated.imag);
		log_var("stage7_in_real.lg",input_sample.real);
		log_var("stage7_in_imag.lg",input_sample.imag);
		log_varf("stage7_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage7_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage7_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage7_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage8_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=0;
	hshake[STAGE_NUMBER_s8].write(false);
	 wait();
	init_stage8();
	 wait();
	while(hshake[STAGE_NUMBER_s7].read()==false) wait();
	hshake[STAGE_NUMBER_s8].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s8-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s8-1].read();
		functional_behavior_stage8(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s8].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s8].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage8_out_real.lg",output_calculated.real);
		log_var("stage8_out_imag.lg",output_calculated.imag);
		log_var("stage8_in_real.lg",input_sample.real);
		log_var("stage8_in_imag.lg",input_sample.imag);
		log_varf("stage8_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage8_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage8_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage8_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage9_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=0;
	hshake[STAGE_NUMBER_s9].write(false);
	 wait();
	init_stage9();
	 wait();
	while(hshake[STAGE_NUMBER_s8].read()==false) wait();
	hshake[STAGE_NUMBER_s9].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s9-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s9-1].read();
		functional_behavior_stage9(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s9].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s9].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage9_out_real.lg",output_calculated.real);
		log_var("stage9_out_imag.lg",output_calculated.imag);
		log_var("stage9_in_real.lg",input_sample.real);
		log_var("stage9_in_imag.lg",input_sample.imag);
		log_varf("stage9_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage9_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage9_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage9_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage10_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=0;
	hshake[STAGE_NUMBER_s10].write(false);
	 wait();
	init_stage10();
	 wait();
	while(hshake[STAGE_NUMBER_s9].read()==false) wait();
	hshake[STAGE_NUMBER_s10].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s10-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s10-1].read();
		functional_behavior_stage10(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s10].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s10].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage10_out_real.lg",output_calculated.real);
		log_var("stage10_out_imag.lg",output_calculated.imag);
		log_var("stage10_in_real.lg",input_sample.real);
		log_var("stage10_in_imag.lg",input_sample.imag);
		log_varf("stage10_in_real.lgf",toFloat(input_sample.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage10_in_imag.lgf",toFloat(input_sample.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage10_out_real.lgf",toFloat(output_calculated.real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		log_varf("stage10_out_imag.lgf",toFloat(output_calculated.imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_INTEGER_PART_BIT_WIDTH));
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}
void pipeLinedFFT_WRAPPER::stage11_exec_WRAPPER(void)
{
	struct mcomplex input_sample;
	struct mcomplex output_calculated;
	//int count=1;
	hshake[STAGE_NUMBER_s11].write(false);
	wait();
	init_stage11();
	wait();
	while(hshake[STAGE_NUMBER_s11-1].read()==false) wait();
	hshake[STAGE_NUMBER_s11].write(true);
	while(1)
	{
		input_sample.real = (int)stageInterface_real[STAGE_NUMBER_s11-1].read();
		input_sample.imag = (int)stageInterface_imag[STAGE_NUMBER_s11-1].read();
		functional_behavior_stage11(input_sample,&output_calculated);
		//count++;
		stageInterface_real[STAGE_NUMBER_s11].write(output_calculated.real);
		stageInterface_imag[STAGE_NUMBER_s11].write(output_calculated.imag);
		#ifdef CREATE_LOG
		log_var("stage11_out_real.lg",output_calculated.real);
		log_var("stage11_out_imag.lg",output_calculated.imag);
		log_var("stage11_in_real.lg",input_sample.real);
		log_var("stage11_in_imag.lg",input_sample.imag);
		#endif
	#ifdef HLS_MODEL
	wait();
	#endif
	}
}

/// IO interface
void pipeLinedFFT_WRAPPER::assign_outputs (void)
{
	sample_output_real.write(0);
	sample_output_imag.write(0);
	wait();
	while(ready.read()==false) wait();
	while(1)
	{
		sample_output_real.write((int)stageInterface_real[FFT_LEN_LOG2].read());
		sample_output_imag.write((int)stageInterface_imag[FFT_LEN_LOG2].read());
		wait();
	}
}
void pipeLinedFFT_WRAPPER::assign_inputs (void)
{

	int temp1_real=(int)sample_input_real.read();
	int temp1_imag=(int)sample_input_imag.read();
	stageInterface_real[0].write(sample_input_real.read());
	stageInterface_real[0].write(sample_input_real.read());
	int temp2_real = (int)stageInterface_real[0].read();
	int temp2_imag = (int)stageInterface_imag[0].read();
}

/// STAGES.CPP
////////////////STAGES.CPP START/////////////////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_all(void)
#else
void init_all(void)
#endif
{
	init_stage1();
	init_stage2();
	init_stage3();
	init_stage4();
	init_stage5();
	init_stage6();
	init_stage7();
	init_stage8();
	init_stage9();
	init_stage10();
	init_stage11();
}
/////////////////////////////////////////////////////////////////////////
//////////// Stage-1 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage1(void)
#else
void init_stage1(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage1_out_real.lg","w");
	tptr_imag=fopen("stage1_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage1_out_real.lgf","w");
	tptr_imag=fopen("stage1_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage1_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage1_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage1_in_real.lgf","w");
	tptr_imag=fopen("stage1_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s1=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s1=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s1) &RD_PTR_MASK_s1 )-1;
	 #endif
	 INIT_STAGE1:;
}
// END:init_stage1/////////////////////////////////////////////////////////////////////////
//////////// Stage-2 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage2(void)
#else
void init_stage2(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage2_out_real.lg","w");
	tptr_imag=fopen("stage2_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage2_out_real.lgf","w");
	tptr_imag=fopen("stage2_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage2_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage2_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage2_in_real.lgf","w");
	tptr_imag=fopen("stage2_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s2=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s2=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s2) &RD_PTR_MASK_s2 )-1;
	 #endif
	 INIT_STAGE2:;
}
// END:init_stage2/////////////////////////////////////////////////////////////////////////
//////////// Stage-3 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage3(void)
#else
void init_stage3(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage3_out_real.lg","w");
	tptr_imag=fopen("stage3_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage3_out_real.lgf","w");
	tptr_imag=fopen("stage3_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage3_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage3_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage3_in_real.lgf","w");
	tptr_imag=fopen("stage3_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s3=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s3=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s3) &RD_PTR_MASK_s3 )-1;
	 #endif
	 INIT_STAGE3:;
}
// END:init_stage3/////////////////////////////////////////////////////////////////////////
//////////// Stage-4 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage4(void)
#else
void init_stage4(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage4_out_real.lg","w");
	tptr_imag=fopen("stage4_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage4_out_real.lgf","w");
	tptr_imag=fopen("stage4_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage4_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage4_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage4_in_real.lgf","w");
	tptr_imag=fopen("stage4_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s4=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s4=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s4) &RD_PTR_MASK_s4 )-1;
	 #endif
	 INIT_STAGE4:;
}
// END:init_stage4/////////////////////////////////////////////////////////////////////////
//////////// Stage-5 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage5(void)
#else
void init_stage5(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage5_out_real.lg","w");
	tptr_imag=fopen("stage5_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage5_out_real.lgf","w");
	tptr_imag=fopen("stage5_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage5_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage5_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage5_in_real.lgf","w");
	tptr_imag=fopen("stage5_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s5=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s5=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s5) &RD_PTR_MASK_s5 )-1;
	 #endif
	 INIT_STAGE5:;
}
// END:init_stage5/////////////////////////////////////////////////////////////////////////
//////////// Stage-6 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage6(void)
#else
void init_stage6(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage6_out_real.lg","w");
	tptr_imag=fopen("stage6_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage6_out_real.lgf","w");
	tptr_imag=fopen("stage6_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage6_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage6_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage6_in_real.lgf","w");
	tptr_imag=fopen("stage6_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s6=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s6=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s6) &RD_PTR_MASK_s6 )-1;
	 #endif
	 INIT_STAGE6:;
}
// END:init_stage6/////////////////////////////////////////////////////////////////////////
//////////// Stage-7 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage7(void)
#else
void init_stage7(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage7_out_real.lg","w");
	tptr_imag=fopen("stage7_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage7_out_real.lgf","w");
	tptr_imag=fopen("stage7_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage7_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage7_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage7_in_real.lgf","w");
	tptr_imag=fopen("stage7_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s7=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s7=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s7) &RD_PTR_MASK_s7 )-1;
	 #endif
	 INIT_STAGE7:;
}
// END:init_stage7/////////////////////////////////////////////////////////////////////////
//////////// Stage-8 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage8(void)
#else
void init_stage8(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage8_out_real.lg","w");
	tptr_imag=fopen("stage8_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage8_out_real.lgf","w");
	tptr_imag=fopen("stage8_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage8_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage8_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage8_in_real.lgf","w");
	tptr_imag=fopen("stage8_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s8=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s8=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s8) &RD_PTR_MASK_s8 )-1;
	 #endif
	 INIT_STAGE8:;
}
// END:init_stage8/////////////////////////////////////////////////////////////////////////
//////////// Stage-9 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage9(void)
#else
void init_stage9(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage9_out_real.lg","w");
	tptr_imag=fopen("stage9_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage9_out_real.lgf","w");
	tptr_imag=fopen("stage9_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage9_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage9_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage9_in_real.lgf","w");
	tptr_imag=fopen("stage9_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s9=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s9=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s9) &RD_PTR_MASK_s9 )-1;
	 #endif
	 INIT_STAGE9:;
}
// END:init_stage9/////////////////////////////////////////////////////////////////////////
//////////// Stage-10 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage10(void)
#else
void init_stage10(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage10_out_real.lg","w");
	tptr_imag=fopen("stage10_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage10_out_real.lgf","w");
	tptr_imag=fopen("stage10_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage10_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage10_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage10_in_real.lgf","w");
	tptr_imag=fopen("stage10_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s10=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s10=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s10) &RD_PTR_MASK_s10 )-1;
	 #endif
	 INIT_STAGE10:;
}
// END:init_stage10/////////////////////////////////////////////////////////////////////////
//////////// Stage-11 Initialization ....////////////
#ifdef	HLS_MODEL
void pipeLinedFFT_WRAPPER::init_stage11(void)
#else
void init_stage11(void)
#endif
{
	int i;
	#ifdef CREATE_LOG
	FILE *tptr_real;
	FILE *tptr_imag;
	tptr_real=fopen("stage11_out_real.lg","w");
	tptr_imag=fopen("stage11_out_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage11_out_real.lgf","w");
	tptr_imag=fopen("stage11_out_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage11_in_real.lGLOBAL_INNER_ITERATION_COUNTER_s1g","w");
	tptr_imag=fopen("stage11_in_imag.lg","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	tptr_real=fopen("stage11_in_real.lgf","w");
	tptr_imag=fopen("stage11_in_imag.lgf","w");
	fclose(tptr_real);
	fclose(tptr_imag);
	#endif
	 GLOBAL_OUTER_ITERATION_COUNTER_s11=0;
	 GLOBAL_INNER_ITERATION_COUNTER_s1=0;
	 #ifdef USE_CIRCULAR_BUFFERS

	 RD_PTR_s11=( (FFT_LEN/STAGE_NUMBER_TO_POWER_2_s11) &RD_PTR_MASK_s11 )-1;
	 #endif
	 INIT_STAGE11:;
}
// END:init_stage11////////////////STAGES.CPP END/////////////////////////
//////////////////////STATIC_CONSTANTS.H START///////////////
#ifdef HLS_MODEL
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s1[FFT_LEN>>1] ={ 127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,
127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,
126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,125,125,125,
125,125,125,125,125,125,125,125,125,125,124,124,124,124,124,124,124,124,124,124,
124,123,123,123,123,123,123,123,123,123,123,122,122,122,122,122,122,122,122,122,
121,121,121,121,121,121,121,121,120,120,120,120,120,120,120,119,119,119,119,119,
119,119,118,118,118,118,118,118,118,117,117,117,117,117,117,117,116,116,116,116,
116,116,115,115,115,115,115,115,114,114,114,114,114,113,113,113,113,113,113,112,
112,112,112,112,111,111,111,111,111,110,110,110,110,110,109,109,109,109,109,108,
108,108,108,108,107,107,107,107,107,106,106,106,106,105,105,105,105,105,104,104,
104,104,103,103,103,103,103,102,102,102,102,101,101,101,101,100,100,100,100,99,
99,99,99,98,98,98,98,97,97,97,97,96,96,96,96,95,95,95,95,94,
94,94,94,93,93,93,92,92,92,92,91,91,91,91,90,90,90,89,89,89,
89,88,88,88,87,87,87,87,86,86,86,85,85,85,85,84,84,84,83,83,
83,82,82,82,82,81,81,81,80,80,80,79,79,79,79,78,78,78,77,77,
77,76,76,76,75,75,75,74,74,74,73,73,73,73,72,72,72,71,71,71,
70,70,70,69,69,69,68,68,68,67,67,67,66,66,66,65,65,65,64,64,
64,63,63,63,62,62,62,61,61,60,60,60,59,59,59,58,58,58,57,57,
57,56,56,56,55,55,55,54,54,53,53,53,52,52,52,51,51,51,50,50,
50,49,49,48,48,48,47,47,47,46,46,46,45,45,44,44,44,43,43,43,
42,42,41,41,41,40,40,40,39,39,38,38,38,37,37,37,36,36,35,35,
35,34,34,34,33,33,32,32,32,31,31,31,30,30,29,29,29,28,28,27,
27,27,26,26,26,25,25,24,24,24,23,23,22,22,22,21,21,21,20,20,
19,19,19,18,18,17,17,17,16,16,15,15,15,14,14,14,13,13,12,12,
12,11,11,10,10,10,9,9,8,8,8,7,7,6,6,6,5,5,5,4,
4,3,3,3,2,2,1,1,1,0,0,0,0,0,-1,-1,-2,-2,-2,-3,
-3,-4,-4,-4,-5,-5,-5,-6,-6,-7,-7,-7,-8,-8,-9,-9,-9,-10,-10,-11,
-11,-11,-12,-12,-13,-13,-13,-14,-14,-14,-15,-15,-16,-16,-16,-17,-17,-18,-18,-18,
-19,-19,-20,-20,-20,-21,-21,-21,-22,-22,-23,-23,-23,-24,-24,-25,-25,-25,-26,-26,
-26,-27,-27,-28,-28,-28,-29,-29,-30,-30,-30,-31,-31,-31,-32,-32,-33,-33,-33,-34,
-34,-34,-35,-35,-36,-36,-36,-37,-37,-37,-38,-38,-39,-39,-39,-40,-40,-40,-41,-41,
-42,-42,-42,-43,-43,-43,-44,-44,-45,-45,-45,-46,-46,-46,-47,-47,-47,-48,-48,-49,
-49,-49,-50,-50,-50,-51,-51,-51,-52,-52,-53,-53,-53,-54,-54,-54,-55,-55,-55,-56,
-56,-56,-57,-57,-57,-58,-58,-59,-59,-59,-60,-60,-60,-61,-61,-61,-62,-62,-62,-63,
-63,-63,-64,-64,-64,-65,-65,-65,-66,-66,-66,-67,-67,-67,-68,-68,-68,-69,-69,-69,
-70,-70,-70,-71,-71,-71,-72,-72,-72,-73,-73,-73,-74,-74,-74,-75,-75,-75,-76,-76,
-76,-76,-77,-77,-77,-78,-78,-78,-79,-79,-79,-80,-80,-80,-80,-81,-81,-81,-82,-82,
-82,-83,-83,-83,-83,-84,-84,-84,-85,-85,-85,-86,-86,-86,-86,-87,-87,-87,-88,-88,
-88,-88,-89,-89,-89,-90,-90,-90,-90,-91,-91,-91,-91,-92,-92,-92,-93,-93,-93,-93,
-94,-94,-94,-94,-95,-95,-95,-95,-96,-96,-96,-97,-97,-97,-97,-98,-98,-98,-98,-99,
-99,-99,-99,-100,-100,-100,-100,-100,-101,-101,-101,-101,-102,-102,-102,-102,-103,-103,-103,-103,
-104,-104,-104,-104,-104,-105,-105,-105,-105,-106,-106,-106,-106,-106,-107,-107,-107,-107,-108,-108,
-108,-108,-108,-109,-109,-109,-109,-109,-110,-110,-110,-110,-110,-111,-111,-111,-111,-111,-112,-112,
-112,-112,-112,-112,-113,-113,-113,-113,-113,-114,-114,-114,-114,-114,-114,-115,-115,-115,-115,-115,
-115,-116,-116,-116,-116,-116,-116,-117,-117,-117,-117,-117,-117,-118,-118,-118,-118,-118,-118,-118,
-119,-119,-119,-119,-119,-119,-119,-120,-120,-120,-120,-120,-120,-120,-120,-121,-121,-121,-121,-121,
-121,-121,-121,-122,-122,-122,-122,-122,-122,-122,-122,-122,-123,-123,-123,-123,-123,-123,-123,-123,
-123,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-125,-125,-125,-125,-125,-125,-125,-125,
-125,-125,-125,-125,-125,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,
-126,-126,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127, -127 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s2[FFT_LEN>>2] ={ 127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,
126,126,126,126,126,126,126,126,125,125,125,125,125,125,125,124,124,124,124,124,
123,123,123,123,123,122,122,122,122,122,121,121,121,121,120,120,120,119,119,119,
119,118,118,118,117,117,117,117,116,116,116,115,115,115,114,114,113,113,113,112,
112,112,111,111,110,110,110,109,109,108,108,108,107,107,106,106,105,105,105,104,
104,103,103,102,102,101,101,100,100,99,99,98,98,97,97,96,96,95,95,94,
94,93,93,92,92,91,91,90,89,89,88,88,87,87,86,85,85,84,84,83,
82,82,81,81,80,79,79,78,78,77,76,76,75,74,74,73,73,72,71,71,
70,69,69,68,67,67,66,65,65,64,63,63,62,61,60,60,59,58,58,57,
56,56,55,54,53,53,52,51,51,50,49,48,48,47,46,46,45,44,43,43,
42,41,40,40,39,38,37,37,36,35,34,34,33,32,31,31,30,29,28,27,
27,26,25,24,24,23,22,21,21,20,19,18,17,17,16,15,14,14,13,12,
11,10,10,9,8,7,6,6,5,4,3,3,2,1,0,0,0,-1,-2,-3,
-4,-4,-5,-6,-7,-7,-8,-9,-10,-11,-11,-12,-13,-14,-14,-15,-16,-17,-18,-18,
-19,-20,-21,-21,-22,-23,-24,-25,-25,-26,-27,-28,-28,-29,-30,-31,-31,-32,-33,-34,
-34,-35,-36,-37,-37,-38,-39,-40,-40,-41,-42,-43,-43,-44,-45,-46,-46,-47,-48,-49,
-49,-50,-51,-51,-52,-53,-54,-54,-55,-56,-56,-57,-58,-59,-59,-60,-61,-61,-62,-63,
-63,-64,-65,-65,-66,-67,-67,-68,-69,-69,-70,-71,-71,-72,-73,-73,-74,-75,-75,-76,
-76,-77,-78,-78,-79,-80,-80,-81,-81,-82,-83,-83,-84,-84,-85,-86,-86,-87,-87,-88,
-88,-89,-90,-90,-91,-91,-92,-92,-93,-93,-94,-94,-95,-95,-96,-97,-97,-98,-98,-99,
-99,-100,-100,-100,-101,-101,-102,-102,-103,-103,-104,-104,-105,-105,-106,-106,-106,-107,-107,-108,
-108,-109,-109,-109,-110,-110,-111,-111,-111,-112,-112,-112,-113,-113,-114,-114,-114,-115,-115,-115,
-116,-116,-116,-117,-117,-117,-118,-118,-118,-118,-119,-119,-119,-120,-120,-120,-120,-121,-121,-121,
-121,-122,-122,-122,-122,-122,-123,-123,-123,-123,-124,-124,-124,-124,-124,-124,-125,-125,-125,-125,
-125,-125,-126,-126,-126,-126,-126,-126,-126,-126,-126,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127, -127 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s3[FFT_LEN>>3] ={ 127,127,127,127,127,127,127,127,127,127,127,126,126,126,126,125,125,125,124,124,124,
123,123,122,122,122,121,121,120,119,119,118,118,117,117,116,115,115,114,113,112,
112,111,110,109,108,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,
93,92,91,90,89,88,87,85,84,83,82,81,79,78,77,76,74,73,72,71,
69,68,67,65,64,63,61,60,58,57,56,54,53,51,50,48,47,46,44,43,
41,40,38,37,35,34,32,31,29,27,26,24,23,21,20,18,17,15,14,12,
10,9,7,6,4,3,1,0,-1,-3,-4,-6,-7,-9,-11,-12,-14,-15,-17,-18,
-20,-21,-23,-25,-26,-28,-29,-31,-32,-34,-35,-37,-38,-40,-41,-43,-44,-46,-47,-49,
-50,-51,-53,-54,-56,-57,-59,-60,-61,-63,-64,-65,-67,-68,-69,-71,-72,-73,-75,-76,
-77,-78,-80,-81,-82,-83,-84,-86,-87,-88,-89,-90,-91,-92,-93,-94,-95,-97,-98,-99,
-100,-100,-101,-102,-103,-104,-105,-106,-107,-108,-109,-109,-110,-111,-112,-112,-113,-114,-115,-115,
-116,-117,-117,-118,-118,-119,-120,-120,-121,-121,-122,-122,-122,-123,-123,-124,-124,-124,-125,-125,
-125,-126,-126,-126,-126,-127,-127,-127,-127,-127,-127,-127,-127,-127, -127 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s4[FFT_LEN>>4] ={ 127,127,127,127,127,127,126,126,125,124,124,123,122,121,120,119,118,117,115,114,112,
111,109,108,106,104,102,100,98,96,94,92,90,88,85,83,81,78,76,73,71,
68,65,63,60,57,54,51,48,46,43,40,37,34,31,27,24,21,18,15,12,
9,6,3,0,-3,-6,-9,-12,-15,-18,-21,-25,-28,-31,-34,-37,-40,-43,-46,-49,
-51,-54,-57,-60,-63,-65,-68,-71,-73,-76,-78,-81,-83,-86,-88,-90,-92,-94,-97,-99,
-100,-102,-104,-106,-108,-109,-111,-112,-114,-115,-117,-118,-119,-120,-121,-122,-123,-124,-124,-125,
-126,-126,-127,-127,-127,-127, -127 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s5[FFT_LEN>>5] ={ 127,127,127,126,125,124,122,120,118,115,112,109,106,102,98,94,90,85,81,76,71,
65,60,54,48,43,37,31,24,18,12,6,0,-6,-12,-18,-25,-31,-37,-43,-49,
-54,-60,-65,-71,-76,-81,-86,-90,-94,-99,-102,-106,-109,-112,-115,-118,-120,-122,-124,-125,
-126,-127, -127 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s6[FFT_LEN>>6] ={ 127,127,125,122,118,112,106,98,90,81,71,60,48,37,24,12,0,-12,-25,-37,-49,
-60,-71,-81,-90,-99,-106,-112,-118,-122,-125, -127 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s7[FFT_LEN>>7] ={ 127,125,118,106,90,71,48,24,0,-25,-49,-71,-90,-106,-118, -125 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s8[FFT_LEN>>8] ={ 127,118,90,48,0,-49,-90, -118 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s9[FFT_LEN>>9] ={ 127,90,0, -90 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s10[FFT_LEN>>10] ={ 127, 0 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_s11[FFT_LEN>>11] ={ 127};
#else
  const dtype_f twiddle_table_s1[FFT_LEN>>1] ={ 127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,
127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,
126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,125,125,125,
125,125,125,125,125,125,125,125,125,125,124,124,124,124,124,124,124,124,124,124,
124,123,123,123,123,123,123,123,123,123,123,122,122,122,122,122,122,122,122,122,
121,121,121,121,121,121,121,121,120,120,120,120,120,120,120,119,119,119,119,119,
119,119,118,118,118,118,118,118,118,117,117,117,117,117,117,117,116,116,116,116,
116,116,115,115,115,115,115,115,114,114,114,114,114,113,113,113,113,113,113,112,
112,112,112,112,111,111,111,111,111,110,110,110,110,110,109,109,109,109,109,108,
108,108,108,108,107,107,107,107,107,106,106,106,106,105,105,105,105,105,104,104,
104,104,103,103,103,103,103,102,102,102,102,101,101,101,101,100,100,100,100,99,
99,99,99,98,98,98,98,97,97,97,97,96,96,96,96,95,95,95,95,94,
94,94,94,93,93,93,92,92,92,92,91,91,91,91,90,90,90,89,89,89,
89,88,88,88,87,87,87,87,86,86,86,85,85,85,85,84,84,84,83,83,
83,82,82,82,82,81,81,81,80,80,80,79,79,79,79,78,78,78,77,77,
77,76,76,76,75,75,75,74,74,74,73,73,73,73,72,72,72,71,71,71,
70,70,70,69,69,69,68,68,68,67,67,67,66,66,66,65,65,65,64,64,
64,63,63,63,62,62,62,61,61,60,60,60,59,59,59,58,58,58,57,57,
57,56,56,56,55,55,55,54,54,53,53,53,52,52,52,51,51,51,50,50,
50,49,49,48,48,48,47,47,47,46,46,46,45,45,44,44,44,43,43,43,
42,42,41,41,41,40,40,40,39,39,38,38,38,37,37,37,36,36,35,35,
35,34,34,34,33,33,32,32,32,31,31,31,30,30,29,29,29,28,28,27,
27,27,26,26,26,25,25,24,24,24,23,23,22,22,22,21,21,21,20,20,
19,19,19,18,18,17,17,17,16,16,15,15,15,14,14,14,13,13,12,12,
12,11,11,10,10,10,9,9,8,8,8,7,7,6,6,6,5,5,5,4,
4,3,3,3,2,2,1,1,1,0,0,0,0,0,-1,-1,-2,-2,-2,-3,
-3,-4,-4,-4,-5,-5,-5,-6,-6,-7,-7,-7,-8,-8,-9,-9,-9,-10,-10,-11,
-11,-11,-12,-12,-13,-13,-13,-14,-14,-14,-15,-15,-16,-16,-16,-17,-17,-18,-18,-18,
-19,-19,-20,-20,-20,-21,-21,-21,-22,-22,-23,-23,-23,-24,-24,-25,-25,-25,-26,-26,
-26,-27,-27,-28,-28,-28,-29,-29,-30,-30,-30,-31,-31,-31,-32,-32,-33,-33,-33,-34,
-34,-34,-35,-35,-36,-36,-36,-37,-37,-37,-38,-38,-39,-39,-39,-40,-40,-40,-41,-41,
-42,-42,-42,-43,-43,-43,-44,-44,-45,-45,-45,-46,-46,-46,-47,-47,-47,-48,-48,-49,
-49,-49,-50,-50,-50,-51,-51,-51,-52,-52,-53,-53,-53,-54,-54,-54,-55,-55,-55,-56,
-56,-56,-57,-57,-57,-58,-58,-59,-59,-59,-60,-60,-60,-61,-61,-61,-62,-62,-62,-63,
-63,-63,-64,-64,-64,-65,-65,-65,-66,-66,-66,-67,-67,-67,-68,-68,-68,-69,-69,-69,
-70,-70,-70,-71,-71,-71,-72,-72,-72,-73,-73,-73,-74,-74,-74,-75,-75,-75,-76,-76,
-76,-76,-77,-77,-77,-78,-78,-78,-79,-79,-79,-80,-80,-80,-80,-81,-81,-81,-82,-82,
-82,-83,-83,-83,-83,-84,-84,-84,-85,-85,-85,-86,-86,-86,-86,-87,-87,-87,-88,-88,
-88,-88,-89,-89,-89,-90,-90,-90,-90,-91,-91,-91,-91,-92,-92,-92,-93,-93,-93,-93,
-94,-94,-94,-94,-95,-95,-95,-95,-96,-96,-96,-97,-97,-97,-97,-98,-98,-98,-98,-99,
-99,-99,-99,-100,-100,-100,-100,-100,-101,-101,-101,-101,-102,-102,-102,-102,-103,-103,-103,-103,
-104,-104,-104,-104,-104,-105,-105,-105,-105,-106,-106,-106,-106,-106,-107,-107,-107,-107,-108,-108,
-108,-108,-108,-109,-109,-109,-109,-109,-110,-110,-110,-110,-110,-111,-111,-111,-111,-111,-112,-112,
-112,-112,-112,-112,-113,-113,-113,-113,-113,-114,-114,-114,-114,-114,-114,-115,-115,-115,-115,-115,
-115,-116,-116,-116,-116,-116,-116,-117,-117,-117,-117,-117,-117,-118,-118,-118,-118,-118,-118,-118,
-119,-119,-119,-119,-119,-119,-119,-120,-120,-120,-120,-120,-120,-120,-120,-121,-121,-121,-121,-121,
-121,-121,-121,-122,-122,-122,-122,-122,-122,-122,-122,-122,-123,-123,-123,-123,-123,-123,-123,-123,
-123,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-125,-125,-125,-125,-125,-125,-125,-125,
-125,-125,-125,-125,-125,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,
-126,-126,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127, -127 };
  const dtype_f twiddle_table_s2[FFT_LEN>>2] ={ 127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,
126,126,126,126,126,126,126,126,125,125,125,125,125,125,125,124,124,124,124,124,
123,123,123,123,123,122,122,122,122,122,121,121,121,121,120,120,120,119,119,119,
119,118,118,118,117,117,117,117,116,116,116,115,115,115,114,114,113,113,113,112,
112,112,111,111,110,110,110,109,109,108,108,108,107,107,106,106,105,105,105,104,
104,103,103,102,102,101,101,100,100,99,99,98,98,97,97,96,96,95,95,94,
94,93,93,92,92,91,91,90,89,89,88,88,87,87,86,85,85,84,84,83,
82,82,81,81,80,79,79,78,78,77,76,76,75,74,74,73,73,72,71,71,
70,69,69,68,67,67,66,65,65,64,63,63,62,61,60,60,59,58,58,57,
56,56,55,54,53,53,52,51,51,50,49,48,48,47,46,46,45,44,43,43,
42,41,40,40,39,38,37,37,36,35,34,34,33,32,31,31,30,29,28,27,
27,26,25,24,24,23,22,21,21,20,19,18,17,17,16,15,14,14,13,12,
11,10,10,9,8,7,6,6,5,4,3,3,2,1,0,0,0,-1,-2,-3,
-4,-4,-5,-6,-7,-7,-8,-9,-10,-11,-11,-12,-13,-14,-14,-15,-16,-17,-18,-18,
-19,-20,-21,-21,-22,-23,-24,-25,-25,-26,-27,-28,-28,-29,-30,-31,-31,-32,-33,-34,
-34,-35,-36,-37,-37,-38,-39,-40,-40,-41,-42,-43,-43,-44,-45,-46,-46,-47,-48,-49,
-49,-50,-51,-51,-52,-53,-54,-54,-55,-56,-56,-57,-58,-59,-59,-60,-61,-61,-62,-63,
-63,-64,-65,-65,-66,-67,-67,-68,-69,-69,-70,-71,-71,-72,-73,-73,-74,-75,-75,-76,
-76,-77,-78,-78,-79,-80,-80,-81,-81,-82,-83,-83,-84,-84,-85,-86,-86,-87,-87,-88,
-88,-89,-90,-90,-91,-91,-92,-92,-93,-93,-94,-94,-95,-95,-96,-97,-97,-98,-98,-99,
-99,-100,-100,-100,-101,-101,-102,-102,-103,-103,-104,-104,-105,-105,-106,-106,-106,-107,-107,-108,
-108,-109,-109,-109,-110,-110,-111,-111,-111,-112,-112,-112,-113,-113,-114,-114,-114,-115,-115,-115,
-116,-116,-116,-117,-117,-117,-118,-118,-118,-118,-119,-119,-119,-120,-120,-120,-120,-121,-121,-121,
-121,-122,-122,-122,-122,-122,-123,-123,-123,-123,-124,-124,-124,-124,-124,-124,-125,-125,-125,-125,
-125,-125,-126,-126,-126,-126,-126,-126,-126,-126,-126,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127, -127 };
  const dtype_f twiddle_table_s3[FFT_LEN>>3] ={ 127,127,127,127,127,127,127,127,127,127,127,126,126,126,126,125,125,125,124,124,124,
123,123,122,122,122,121,121,120,119,119,118,118,117,117,116,115,115,114,113,112,
112,111,110,109,108,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,
93,92,91,90,89,88,87,85,84,83,82,81,79,78,77,76,74,73,72,71,
69,68,67,65,64,63,61,60,58,57,56,54,53,51,50,48,47,46,44,43,
41,40,38,37,35,34,32,31,29,27,26,24,23,21,20,18,17,15,14,12,
10,9,7,6,4,3,1,0,-1,-3,-4,-6,-7,-9,-11,-12,-14,-15,-17,-18,
-20,-21,-23,-25,-26,-28,-29,-31,-32,-34,-35,-37,-38,-40,-41,-43,-44,-46,-47,-49,
-50,-51,-53,-54,-56,-57,-59,-60,-61,-63,-64,-65,-67,-68,-69,-71,-72,-73,-75,-76,
-77,-78,-80,-81,-82,-83,-84,-86,-87,-88,-89,-90,-91,-92,-93,-94,-95,-97,-98,-99,
-100,-100,-101,-102,-103,-104,-105,-106,-107,-108,-109,-109,-110,-111,-112,-112,-113,-114,-115,-115,
-116,-117,-117,-118,-118,-119,-120,-120,-121,-121,-122,-122,-122,-123,-123,-124,-124,-124,-125,-125,
-125,-126,-126,-126,-126,-127,-127,-127,-127,-127,-127,-127,-127,-127, -127 };
  const dtype_f twiddle_table_s4[FFT_LEN>>4] ={ 127,127,127,127,127,127,126,126,125,124,124,123,122,121,120,119,118,117,115,114,112,
111,109,108,106,104,102,100,98,96,94,92,90,88,85,83,81,78,76,73,71,
68,65,63,60,57,54,51,48,46,43,40,37,34,31,27,24,21,18,15,12,
9,6,3,0,-3,-6,-9,-12,-15,-18,-21,-25,-28,-31,-34,-37,-40,-43,-46,-49,
-51,-54,-57,-60,-63,-65,-68,-71,-73,-76,-78,-81,-83,-86,-88,-90,-92,-94,-97,-99,
-100,-102,-104,-106,-108,-109,-111,-112,-114,-115,-117,-118,-119,-120,-121,-122,-123,-124,-124,-125,
-126,-126,-127,-127,-127,-127, -127 };
  const dtype_f twiddle_table_s5[FFT_LEN>>5] ={ 127,127,127,126,125,124,122,120,118,115,112,109,106,102,98,94,90,85,81,76,71,
65,60,54,48,43,37,31,24,18,12,6,0,-6,-12,-18,-25,-31,-37,-43,-49,
-54,-60,-65,-71,-76,-81,-86,-90,-94,-99,-102,-106,-109,-112,-115,-118,-120,-122,-124,-125,
-126,-127, -127 };
  const dtype_f twiddle_table_s6[FFT_LEN>>6] ={ 127,127,125,122,118,112,106,98,90,81,71,60,48,37,24,12,0,-12,-25,-37,-49,
-60,-71,-81,-90,-99,-106,-112,-118,-122,-125, -127 };
  const dtype_f twiddle_table_s7[FFT_LEN>>7] ={ 127,125,118,106,90,71,48,24,0,-25,-49,-71,-90,-106,-118, -125 };
  const dtype_f twiddle_table_s8[FFT_LEN>>8] ={ 127,118,90,48,0,-49,-90, -118 };
  const dtype_f twiddle_table_s9[FFT_LEN>>9] ={ 127,90,0, -90 };
  const dtype_f twiddle_table_s10[FFT_LEN>>10] ={ 127, 0 };
  const dtype_f twiddle_table_s11[FFT_LEN>>11] ={ 127};
#endif
#ifdef HLS_MODEL
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s1[FFT_LEN>>1] ={ 0,0,0,-1,-1,-1,-2,-2,-3,-3,-3,-4,-4,-5,-5,-5,-6,-6,-7,-7,-7,
-8,-8,-9,-9,-9,-10,-10,-10,-11,-11,-12,-12,-12,-13,-13,-14,-14,-14,-15,-15,
-16,-16,-16,-17,-17,-18,-18,-18,-19,-19,-19,-20,-20,-21,-21,-21,-22,-22,-23,-23,
-23,-24,-24,-24,-25,-25,-26,-26,-26,-27,-27,-28,-28,-28,-29,-29,-29,-30,-30,-31,
-31,-31,-32,-32,-33,-33,-33,-34,-34,-34,-35,-35,-36,-36,-36,-37,-37,-37,-38,-38,
-39,-39,-39,-40,-40,-40,-41,-41,-42,-42,-42,-43,-43,-43,-44,-44,-44,-45,-45,-46,
-46,-46,-47,-47,-47,-48,-48,-49,-49,-49,-50,-50,-50,-51,-51,-51,-52,-52,-52,-53,
-53,-54,-54,-54,-55,-55,-55,-56,-56,-56,-57,-57,-57,-58,-58,-58,-59,-59,-60,-60,
-60,-61,-61,-61,-62,-62,-62,-63,-63,-63,-64,-64,-64,-65,-65,-65,-66,-66,-66,-67,
-67,-67,-68,-68,-68,-69,-69,-69,-70,-70,-70,-71,-71,-71,-72,-72,-72,-73,-73,-73,
-74,-74,-74,-75,-75,-75,-75,-76,-76,-76,-77,-77,-77,-78,-78,-78,-79,-79,-79,-80,
-80,-80,-80,-81,-81,-81,-82,-82,-82,-83,-83,-83,-83,-84,-84,-84,-85,-85,-85,-85,
-86,-86,-86,-87,-87,-87,-88,-88,-88,-88,-89,-89,-89,-89,-90,-90,-90,-91,-91,-91,
-91,-92,-92,-92,-93,-93,-93,-93,-94,-94,-94,-94,-95,-95,-95,-95,-96,-96,-96,-96,
-97,-97,-97,-97,-98,-98,-98,-98,-99,-99,-99,-99,-100,-100,-100,-100,-101,-101,-101,-101,
-102,-102,-102,-102,-103,-103,-103,-103,-103,-104,-104,-104,-104,-105,-105,-105,-105,-106,-106,-106,
-106,-106,-107,-107,-107,-107,-107,-108,-108,-108,-108,-109,-109,-109,-109,-109,-110,-110,-110,-110,
-110,-111,-111,-111,-111,-111,-111,-112,-112,-112,-112,-112,-113,-113,-113,-113,-113,-114,-114,-114,
-114,-114,-114,-115,-115,-115,-115,-115,-115,-116,-116,-116,-116,-116,-116,-117,-117,-117,-117,-117,
-117,-117,-118,-118,-118,-118,-118,-118,-119,-119,-119,-119,-119,-119,-119,-120,-120,-120,-120,-120,
-120,-120,-120,-121,-121,-121,-121,-121,-121,-121,-121,-122,-122,-122,-122,-122,-122,-122,-122,-122,
-123,-123,-123,-123,-123,-123,-123,-123,-123,-123,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,
-124,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-126,-126,-126,-126,-126,-126,
-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-126,-126,-126,-126,-126,-126,-126,-126,
-126,-126,-126,-126,-126,-126,-126,-126,-126,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,
-125,-125,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-123,-123,-123,-123,-123,-123,-123,
-123,-123,-123,-122,-122,-122,-122,-122,-122,-122,-122,-121,-121,-121,-121,-121,-121,-121,-121,-121,
-120,-120,-120,-120,-120,-120,-120,-119,-119,-119,-119,-119,-119,-119,-118,-118,-118,-118,-118,-118,
-118,-117,-117,-117,-117,-117,-117,-116,-116,-116,-116,-116,-116,-116,-115,-115,-115,-115,-115,-114,
-114,-114,-114,-114,-114,-113,-113,-113,-113,-113,-113,-112,-112,-112,-112,-112,-111,-111,-111,-111,
-111,-110,-110,-110,-110,-110,-109,-109,-109,-109,-109,-108,-108,-108,-108,-108,-107,-107,-107,-107,
-107,-106,-106,-106,-106,-105,-105,-105,-105,-105,-104,-104,-104,-104,-103,-103,-103,-103,-102,-102,
-102,-102,-102,-101,-101,-101,-101,-100,-100,-100,-100,-99,-99,-99,-99,-98,-98,-98,-98,-97,
-97,-97,-97,-96,-96,-96,-96,-95,-95,-95,-95,-94,-94,-94,-93,-93,-93,-93,-92,-92,
-92,-92,-91,-91,-91,-90,-90,-90,-90,-89,-89,-89,-89,-88,-88,-88,-87,-87,-87,-87,
-86,-86,-86,-85,-85,-85,-84,-84,-84,-84,-83,-83,-83,-82,-82,-82,-82,-81,-81,-81,
-80,-80,-80,-79,-79,-79,-78,-78,-78,-78,-77,-77,-77,-76,-76,-76,-75,-75,-75,-74,
-74,-74,-73,-73,-73,-72,-72,-72,-71,-71,-71,-71,-70,-70,-70,-69,-69,-69,-68,-68,
-68,-67,-67,-67,-66,-66,-66,-65,-65,-65,-64,-64,-63,-63,-63,-62,-62,-62,-61,-61,
-61,-60,-60,-60,-59,-59,-59,-58,-58,-58,-57,-57,-57,-56,-56,-56,-55,-55,-54,-54,
-54,-53,-53,-53,-52,-52,-52,-51,-51,-51,-50,-50,-49,-49,-49,-48,-48,-48,-47,-47,
-47,-46,-46,-45,-45,-45,-44,-44,-44,-43,-43,-42,-42,-42,-41,-41,-41,-40,-40,-40,
-39,-39,-38,-38,-38,-37,-37,-37,-36,-36,-35,-35,-35,-34,-34,-33,-33,-33,-32,-32,
-32,-31,-31,-30,-30,-30,-29,-29,-29,-28,-28,-27,-27,-27,-26,-26,-25,-25,-25,-24,
-24,-24,-23,-23,-22,-22,-22,-21,-21,-20,-20,-20,-19,-19,-19,-18,-18,-17,-17,-17,
-16,-16,-15,-15,-15,-14,-14,-13,-13,-13,-12,-12,-11,-11,-11,-10,-10,-10,-9,-9,
-8,-8,-8,-7,-7,-6,-6,-6,-5,-5,-4,-4,-4,-3,-3,-2,-2,-2,-1,-1,
-1,0, 0 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s2[FFT_LEN>>2] ={ 0,0,-1,-2,-3,-3,-4,-5,-6,-7,-7,-8,-9,-10,-10,-11,-12,-13,-14,-14,-15,
-16,-17,-18,-18,-19,-20,-21,-21,-22,-23,-24,-24,-25,-26,-27,-28,-28,-29,-30,-31,
-31,-32,-33,-34,-34,-35,-36,-37,-37,-38,-39,-40,-40,-41,-42,-43,-43,-44,-45,-46,
-46,-47,-48,-49,-49,-50,-51,-51,-52,-53,-54,-54,-55,-56,-56,-57,-58,-58,-59,-60,
-61,-61,-62,-63,-63,-64,-65,-65,-66,-67,-67,-68,-69,-69,-70,-71,-71,-72,-73,-73,
-74,-75,-75,-76,-76,-77,-78,-78,-79,-80,-80,-81,-81,-82,-83,-83,-84,-84,-85,-85,
-86,-87,-87,-88,-88,-89,-89,-90,-91,-91,-92,-92,-93,-93,-94,-94,-95,-95,-96,-96,
-97,-97,-98,-98,-99,-99,-100,-100,-101,-101,-102,-102,-103,-103,-104,-104,-105,-105,-106,-106,
-106,-107,-107,-108,-108,-109,-109,-109,-110,-110,-111,-111,-111,-112,-112,-112,-113,-113,-114,-114,
-114,-115,-115,-115,-116,-116,-116,-117,-117,-117,-117,-118,-118,-118,-119,-119,-119,-120,-120,-120,
-120,-121,-121,-121,-121,-122,-122,-122,-122,-122,-123,-123,-123,-123,-123,-124,-124,-124,-124,-124,
-125,-125,-125,-125,-125,-125,-125,-126,-126,-126,-126,-126,-126,-126,-126,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-126,-126,-126,-126,
-126,-126,-126,-126,-125,-125,-125,-125,-125,-125,-125,-124,-124,-124,-124,-124,-123,-123,-123,-123,
-123,-122,-122,-122,-122,-121,-121,-121,-121,-121,-120,-120,-120,-119,-119,-119,-119,-118,-118,-118,
-117,-117,-117,-116,-116,-116,-116,-115,-115,-114,-114,-114,-113,-113,-113,-112,-112,-112,-111,-111,
-110,-110,-110,-109,-109,-108,-108,-108,-107,-107,-106,-106,-105,-105,-105,-104,-104,-103,-103,-102,
-102,-101,-101,-100,-100,-99,-99,-98,-98,-97,-97,-96,-96,-95,-95,-94,-94,-93,-93,-92,
-92,-91,-90,-90,-89,-89,-88,-88,-87,-87,-86,-85,-85,-84,-84,-83,-82,-82,-81,-81,
-80,-79,-79,-78,-78,-77,-76,-76,-75,-74,-74,-73,-72,-72,-71,-71,-70,-69,-69,-68,
-67,-67,-66,-65,-65,-64,-63,-62,-62,-61,-60,-60,-59,-58,-58,-57,-56,-56,-55,-54,
-53,-53,-52,-51,-51,-50,-49,-48,-48,-47,-46,-45,-45,-44,-43,-42,-42,-41,-40,-40,
-39,-38,-37,-37,-36,-35,-34,-33,-33,-32,-31,-30,-30,-29,-28,-27,-27,-26,-25,-24,
-24,-23,-22,-21,-20,-20,-19,-18,-17,-17,-16,-15,-14,-13,-13,-12,-11,-10,-10,-9,
-8,-7,-6,-6,-5,-4,-3,-2,-2,-1, 0 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s3[FFT_LEN>>3] ={ 0,-1,-3,-4,-6,-7,-9,-10,-12,-14,-15,-17,-18,-20,-21,-23,-24,-26,-28,-29,-31,
-32,-34,-35,-37,-38,-40,-41,-43,-44,-46,-47,-49,-50,-51,-53,-54,-56,-57,-58,-60,
-61,-63,-64,-65,-67,-68,-69,-71,-72,-73,-75,-76,-77,-78,-80,-81,-82,-83,-84,-85,
-87,-88,-89,-90,-91,-92,-93,-94,-95,-96,-97,-98,-99,-100,-101,-102,-103,-104,-105,-106,
-107,-108,-109,-109,-110,-111,-112,-112,-113,-114,-115,-115,-116,-117,-117,-118,-118,-119,-120,-120,
-121,-121,-122,-122,-122,-123,-123,-124,-124,-124,-125,-125,-125,-126,-126,-126,-126,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-126,-126,
-126,-126,-125,-125,-125,-124,-124,-124,-123,-123,-122,-122,-121,-121,-121,-120,-119,-119,-118,-118,
-117,-116,-116,-115,-114,-114,-113,-112,-112,-111,-110,-109,-108,-108,-107,-106,-105,-104,-103,-102,
-101,-100,-99,-98,-97,-96,-95,-94,-93,-92,-91,-90,-89,-88,-87,-85,-84,-83,-82,-81,
-79,-78,-77,-76,-74,-73,-72,-71,-69,-68,-67,-65,-64,-62,-61,-60,-58,-57,-56,-54,
-53,-51,-50,-48,-47,-45,-44,-42,-41,-40,-38,-37,-35,-33,-32,-30,-29,-27,-26,-24,
-23,-21,-20,-18,-17,-15,-13,-12,-10,-9,-7,-6,-4,-2, -1 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s4[FFT_LEN>>4] ={ 0,-3,-6,-9,-12,-15,-18,-21,-24,-28,-31,-34,-37,-40,-43,-46,-49,-51,-54,-57,-60,
-63,-65,-68,-71,-73,-76,-78,-81,-83,-85,-88,-90,-92,-94,-96,-98,-100,-102,-104,-106,
-108,-109,-111,-112,-114,-115,-117,-118,-119,-120,-121,-122,-123,-124,-124,-125,-126,-126,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-126,-126,-125,-124,-124,-123,-122,-121,-120,-119,-118,
-116,-115,-114,-112,-111,-109,-108,-106,-104,-102,-100,-98,-96,-94,-92,-90,-88,-85,-83,-81,
-78,-76,-73,-71,-68,-65,-62,-60,-57,-54,-51,-48,-45,-42,-40,-37,-33,-30,-27,-24,
-21,-18,-15,-12,-9,-6, -2 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s5[FFT_LEN>>5] ={ 0,-6,-12,-18,-24,-31,-37,-43,-49,-54,-60,-65,-71,-76,-81,-85,-90,-94,-98,-102,-106,
-109,-112,-115,-118,-120,-122,-124,-125,-126,-127,-127,-127,-127,-127,-126,-125,-124,-122,-120,-118,
-115,-112,-109,-106,-102,-98,-94,-90,-85,-81,-76,-71,-65,-60,-54,-48,-42,-37,-30,-24,
-18,-12, -6 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s6[FFT_LEN>>6] ={ 0,-12,-24,-37,-49,-60,-71,-81,-90,-98,-106,-112,-118,-122,-125,-127,-127,-127,-125,-122,-118,
-112,-106,-98,-90,-81,-71,-60,-48,-37,-24, -12 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s7[FFT_LEN>>7] ={ 0,-24,-49,-71,-90,-106,-118,-125,-127,-125,-118,-106,-90,-71,-48, -24 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s8[FFT_LEN>>8] ={ 0,-49,-90,-118,-127,-118,-90, -48 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s9[FFT_LEN>>9] ={ 0,-90,-127, -90 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s10[FFT_LEN>>10] ={ 0, -127 };
  const dtype_f pipeLinedFFT_WRAPPER::twiddle_table_imag_s11[FFT_LEN>>11] ={ 0};
#else
  const dtype_f twiddle_table_imag_s1[FFT_LEN>>1] ={ 0,0,0,-1,-1,-1,-2,-2,-3,-3,-3,-4,-4,-5,-5,-5,-6,-6,-7,-7,-7,
-8,-8,-9,-9,-9,-10,-10,-10,-11,-11,-12,-12,-12,-13,-13,-14,-14,-14,-15,-15,
-16,-16,-16,-17,-17,-18,-18,-18,-19,-19,-19,-20,-20,-21,-21,-21,-22,-22,-23,-23,
-23,-24,-24,-24,-25,-25,-26,-26,-26,-27,-27,-28,-28,-28,-29,-29,-29,-30,-30,-31,
-31,-31,-32,-32,-33,-33,-33,-34,-34,-34,-35,-35,-36,-36,-36,-37,-37,-37,-38,-38,
-39,-39,-39,-40,-40,-40,-41,-41,-42,-42,-42,-43,-43,-43,-44,-44,-44,-45,-45,-46,
-46,-46,-47,-47,-47,-48,-48,-49,-49,-49,-50,-50,-50,-51,-51,-51,-52,-52,-52,-53,
-53,-54,-54,-54,-55,-55,-55,-56,-56,-56,-57,-57,-57,-58,-58,-58,-59,-59,-60,-60,
-60,-61,-61,-61,-62,-62,-62,-63,-63,-63,-64,-64,-64,-65,-65,-65,-66,-66,-66,-67,
-67,-67,-68,-68,-68,-69,-69,-69,-70,-70,-70,-71,-71,-71,-72,-72,-72,-73,-73,-73,
-74,-74,-74,-75,-75,-75,-75,-76,-76,-76,-77,-77,-77,-78,-78,-78,-79,-79,-79,-80,
-80,-80,-80,-81,-81,-81,-82,-82,-82,-83,-83,-83,-83,-84,-84,-84,-85,-85,-85,-85,
-86,-86,-86,-87,-87,-87,-88,-88,-88,-88,-89,-89,-89,-89,-90,-90,-90,-91,-91,-91,
-91,-92,-92,-92,-93,-93,-93,-93,-94,-94,-94,-94,-95,-95,-95,-95,-96,-96,-96,-96,
-97,-97,-97,-97,-98,-98,-98,-98,-99,-99,-99,-99,-100,-100,-100,-100,-101,-101,-101,-101,
-102,-102,-102,-102,-103,-103,-103,-103,-103,-104,-104,-104,-104,-105,-105,-105,-105,-106,-106,-106,
-106,-106,-107,-107,-107,-107,-107,-108,-108,-108,-108,-109,-109,-109,-109,-109,-110,-110,-110,-110,
-110,-111,-111,-111,-111,-111,-111,-112,-112,-112,-112,-112,-113,-113,-113,-113,-113,-114,-114,-114,
-114,-114,-114,-115,-115,-115,-115,-115,-115,-116,-116,-116,-116,-116,-116,-117,-117,-117,-117,-117,
-117,-117,-118,-118,-118,-118,-118,-118,-119,-119,-119,-119,-119,-119,-119,-120,-120,-120,-120,-120,
-120,-120,-120,-121,-121,-121,-121,-121,-121,-121,-121,-122,-122,-122,-122,-122,-122,-122,-122,-122,
-123,-123,-123,-123,-123,-123,-123,-123,-123,-123,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,
-124,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-126,-126,-126,-126,-126,-126,
-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-126,-126,-126,-126,-126,-126,-126,-126,
-126,-126,-126,-126,-126,-126,-126,-126,-126,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,-125,
-125,-125,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-123,-123,-123,-123,-123,-123,-123,
-123,-123,-123,-122,-122,-122,-122,-122,-122,-122,-122,-121,-121,-121,-121,-121,-121,-121,-121,-121,
-120,-120,-120,-120,-120,-120,-120,-119,-119,-119,-119,-119,-119,-119,-118,-118,-118,-118,-118,-118,
-118,-117,-117,-117,-117,-117,-117,-116,-116,-116,-116,-116,-116,-116,-115,-115,-115,-115,-115,-114,
-114,-114,-114,-114,-114,-113,-113,-113,-113,-113,-113,-112,-112,-112,-112,-112,-111,-111,-111,-111,
-111,-110,-110,-110,-110,-110,-109,-109,-109,-109,-109,-108,-108,-108,-108,-108,-107,-107,-107,-107,
-107,-106,-106,-106,-106,-105,-105,-105,-105,-105,-104,-104,-104,-104,-103,-103,-103,-103,-102,-102,
-102,-102,-102,-101,-101,-101,-101,-100,-100,-100,-100,-99,-99,-99,-99,-98,-98,-98,-98,-97,
-97,-97,-97,-96,-96,-96,-96,-95,-95,-95,-95,-94,-94,-94,-93,-93,-93,-93,-92,-92,
-92,-92,-91,-91,-91,-90,-90,-90,-90,-89,-89,-89,-89,-88,-88,-88,-87,-87,-87,-87,
-86,-86,-86,-85,-85,-85,-84,-84,-84,-84,-83,-83,-83,-82,-82,-82,-82,-81,-81,-81,
-80,-80,-80,-79,-79,-79,-78,-78,-78,-78,-77,-77,-77,-76,-76,-76,-75,-75,-75,-74,
-74,-74,-73,-73,-73,-72,-72,-72,-71,-71,-71,-71,-70,-70,-70,-69,-69,-69,-68,-68,
-68,-67,-67,-67,-66,-66,-66,-65,-65,-65,-64,-64,-63,-63,-63,-62,-62,-62,-61,-61,
-61,-60,-60,-60,-59,-59,-59,-58,-58,-58,-57,-57,-57,-56,-56,-56,-55,-55,-54,-54,
-54,-53,-53,-53,-52,-52,-52,-51,-51,-51,-50,-50,-49,-49,-49,-48,-48,-48,-47,-47,
-47,-46,-46,-45,-45,-45,-44,-44,-44,-43,-43,-42,-42,-42,-41,-41,-41,-40,-40,-40,
-39,-39,-38,-38,-38,-37,-37,-37,-36,-36,-35,-35,-35,-34,-34,-33,-33,-33,-32,-32,
-32,-31,-31,-30,-30,-30,-29,-29,-29,-28,-28,-27,-27,-27,-26,-26,-25,-25,-25,-24,
-24,-24,-23,-23,-22,-22,-22,-21,-21,-20,-20,-20,-19,-19,-19,-18,-18,-17,-17,-17,
-16,-16,-15,-15,-15,-14,-14,-13,-13,-13,-12,-12,-11,-11,-11,-10,-10,-10,-9,-9,
-8,-8,-8,-7,-7,-6,-6,-6,-5,-5,-4,-4,-4,-3,-3,-2,-2,-2,-1,-1,
-1,0, 0 };
  const dtype_f twiddle_table_imag_s2[FFT_LEN>>2] ={ 0,0,-1,-2,-3,-3,-4,-5,-6,-7,-7,-8,-9,-10,-10,-11,-12,-13,-14,-14,-15,
-16,-17,-18,-18,-19,-20,-21,-21,-22,-23,-24,-24,-25,-26,-27,-28,-28,-29,-30,-31,
-31,-32,-33,-34,-34,-35,-36,-37,-37,-38,-39,-40,-40,-41,-42,-43,-43,-44,-45,-46,
-46,-47,-48,-49,-49,-50,-51,-51,-52,-53,-54,-54,-55,-56,-56,-57,-58,-58,-59,-60,
-61,-61,-62,-63,-63,-64,-65,-65,-66,-67,-67,-68,-69,-69,-70,-71,-71,-72,-73,-73,
-74,-75,-75,-76,-76,-77,-78,-78,-79,-80,-80,-81,-81,-82,-83,-83,-84,-84,-85,-85,
-86,-87,-87,-88,-88,-89,-89,-90,-91,-91,-92,-92,-93,-93,-94,-94,-95,-95,-96,-96,
-97,-97,-98,-98,-99,-99,-100,-100,-101,-101,-102,-102,-103,-103,-104,-104,-105,-105,-106,-106,
-106,-107,-107,-108,-108,-109,-109,-109,-110,-110,-111,-111,-111,-112,-112,-112,-113,-113,-114,-114,
-114,-115,-115,-115,-116,-116,-116,-117,-117,-117,-117,-118,-118,-118,-119,-119,-119,-120,-120,-120,
-120,-121,-121,-121,-121,-122,-122,-122,-122,-122,-123,-123,-123,-123,-123,-124,-124,-124,-124,-124,
-125,-125,-125,-125,-125,-125,-125,-126,-126,-126,-126,-126,-126,-126,-126,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-126,-126,-126,-126,
-126,-126,-126,-126,-125,-125,-125,-125,-125,-125,-125,-124,-124,-124,-124,-124,-123,-123,-123,-123,
-123,-122,-122,-122,-122,-121,-121,-121,-121,-121,-120,-120,-120,-119,-119,-119,-119,-118,-118,-118,
-117,-117,-117,-116,-116,-116,-116,-115,-115,-114,-114,-114,-113,-113,-113,-112,-112,-112,-111,-111,
-110,-110,-110,-109,-109,-108,-108,-108,-107,-107,-106,-106,-105,-105,-105,-104,-104,-103,-103,-102,
-102,-101,-101,-100,-100,-99,-99,-98,-98,-97,-97,-96,-96,-95,-95,-94,-94,-93,-93,-92,
-92,-91,-90,-90,-89,-89,-88,-88,-87,-87,-86,-85,-85,-84,-84,-83,-82,-82,-81,-81,
-80,-79,-79,-78,-78,-77,-76,-76,-75,-74,-74,-73,-72,-72,-71,-71,-70,-69,-69,-68,
-67,-67,-66,-65,-65,-64,-63,-62,-62,-61,-60,-60,-59,-58,-58,-57,-56,-56,-55,-54,
-53,-53,-52,-51,-51,-50,-49,-48,-48,-47,-46,-45,-45,-44,-43,-42,-42,-41,-40,-40,
-39,-38,-37,-37,-36,-35,-34,-33,-33,-32,-31,-30,-30,-29,-28,-27,-27,-26,-25,-24,
-24,-23,-22,-21,-20,-20,-19,-18,-17,-17,-16,-15,-14,-13,-13,-12,-11,-10,-10,-9,
-8,-7,-6,-6,-5,-4,-3,-2,-2,-1, 0 };
  const dtype_f twiddle_table_imag_s3[FFT_LEN>>3] ={ 0,-1,-3,-4,-6,-7,-9,-10,-12,-14,-15,-17,-18,-20,-21,-23,-24,-26,-28,-29,-31,
-32,-34,-35,-37,-38,-40,-41,-43,-44,-46,-47,-49,-50,-51,-53,-54,-56,-57,-58,-60,
-61,-63,-64,-65,-67,-68,-69,-71,-72,-73,-75,-76,-77,-78,-80,-81,-82,-83,-84,-85,
-87,-88,-89,-90,-91,-92,-93,-94,-95,-96,-97,-98,-99,-100,-101,-102,-103,-104,-105,-106,
-107,-108,-109,-109,-110,-111,-112,-112,-113,-114,-115,-115,-116,-117,-117,-118,-118,-119,-120,-120,
-121,-121,-122,-122,-122,-123,-123,-124,-124,-124,-125,-125,-125,-126,-126,-126,-126,-127,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-126,-126,
-126,-126,-125,-125,-125,-124,-124,-124,-123,-123,-122,-122,-121,-121,-121,-120,-119,-119,-118,-118,
-117,-116,-116,-115,-114,-114,-113,-112,-112,-111,-110,-109,-108,-108,-107,-106,-105,-104,-103,-102,
-101,-100,-99,-98,-97,-96,-95,-94,-93,-92,-91,-90,-89,-88,-87,-85,-84,-83,-82,-81,
-79,-78,-77,-76,-74,-73,-72,-71,-69,-68,-67,-65,-64,-62,-61,-60,-58,-57,-56,-54,
-53,-51,-50,-48,-47,-45,-44,-42,-41,-40,-38,-37,-35,-33,-32,-30,-29,-27,-26,-24,
-23,-21,-20,-18,-17,-15,-13,-12,-10,-9,-7,-6,-4,-2, -1 };
  const dtype_f twiddle_table_imag_s4[FFT_LEN>>4] ={ 0,-3,-6,-9,-12,-15,-18,-21,-24,-28,-31,-34,-37,-40,-43,-46,-49,-51,-54,-57,-60,
-63,-65,-68,-71,-73,-76,-78,-81,-83,-85,-88,-90,-92,-94,-96,-98,-100,-102,-104,-106,
-108,-109,-111,-112,-114,-115,-117,-118,-119,-120,-121,-122,-123,-124,-124,-125,-126,-126,-127,-127,
-127,-127,-127,-127,-127,-127,-127,-127,-127,-126,-126,-125,-124,-124,-123,-122,-121,-120,-119,-118,
-116,-115,-114,-112,-111,-109,-108,-106,-104,-102,-100,-98,-96,-94,-92,-90,-88,-85,-83,-81,
-78,-76,-73,-71,-68,-65,-62,-60,-57,-54,-51,-48,-45,-42,-40,-37,-33,-30,-27,-24,
-21,-18,-15,-12,-9,-6, -2 };
  const dtype_f twiddle_table_imag_s5[FFT_LEN>>5] ={ 0,-6,-12,-18,-24,-31,-37,-43,-49,-54,-60,-65,-71,-76,-81,-85,-90,-94,-98,-102,-106,
-109,-112,-115,-118,-120,-122,-124,-125,-126,-127,-127,-127,-127,-127,-126,-125,-124,-122,-120,-118,
-115,-112,-109,-106,-102,-98,-94,-90,-85,-81,-76,-71,-65,-60,-54,-48,-42,-37,-30,-24,
-18,-12, -6 };
  const dtype_f twiddle_table_imag_s6[FFT_LEN>>6] ={ 0,-12,-24,-37,-49,-60,-71,-81,-90,-98,-106,-112,-118,-122,-125,-127,-127,-127,-125,-122,-118,
-112,-106,-98,-90,-81,-71,-60,-48,-37,-24, -12 };
  const dtype_f twiddle_table_imag_s7[FFT_LEN>>7] ={ 0,-24,-49,-71,-90,-106,-118,-125,-127,-125,-118,-106,-90,-71,-48, -24 };
  const dtype_f twiddle_table_imag_s8[FFT_LEN>>8] ={ 0,-49,-90,-118,-127,-118,-90, -48 };
  const dtype_f twiddle_table_imag_s9[FFT_LEN>>9] ={ 0,-90,-127, -90 };
  const dtype_f twiddle_table_imag_s10[FFT_LEN>>10] ={ 0, -127 };
  const dtype_f twiddle_table_imag_s11[FFT_LEN>>11] ={ 0};
#endif
//////////////////////Inlcude code that defines functional behavior of butterfly stages start///////////////
#include "functional_behavior_stage1.h"
#include "functional_behavior_stage2.h"
#include "functional_behavior_stage3.h"
#include "functional_behavior_stage4.h"
#include "functional_behavior_stage5.h"
#include "functional_behavior_stage6.h"
#include "functional_behavior_stage7.h"
#include "functional_behavior_stage8.h"
#include "functional_behavior_stage9.h"
#include "functional_behavior_stage10.h"
#include "functional_behavior_stage11.h"
