/* File Name : stimulus.h
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/


#ifndef TIMULUS_H_
#define TIMULUS_H_

#include "global_constants.h"
#include "systemc.h"
#include "hls_fixed_point_lib.h"
SC_MODULE(stimulus)
{
   sc_in < sc_int <OUTPUT_INTERFACE_WIDTH> > sample_output_real;
   sc_in < sc_int <OUTPUT_INTERFACE_WIDTH> > sample_output_imag;
   sc_in < bool > clk;
   sc_in < bool > done;
   sc_out < bool> reset;
   sc_out < bool> start;
   sc_out <bool> done_sim;
   sc_out < sc_int < INTERFACE_WIDTH > > sample_input_real;
   sc_out < sc_int < INTERFACE_WIDTH > > sample_input_imag;
   sc_in < bool > ready;
   void check_outputs(void);
   void genSim(void);
   SC_CTOR(stimulus)
   {
		SC_CTHREAD(genSim,clk.pos());
		dont_initialize();
		SC_CTHREAD(check_outputs,clk.pos());
		dont_initialize();
   };
};


#endif /* TIMULUS_H_ */ 
