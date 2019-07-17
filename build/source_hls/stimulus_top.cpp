/* File Name : stimulus_top.cpp
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/

#include "systemc.h"
#include "stimulus.h"
#include "pipeLinedFFT_WRAPPER.h"
int sc_main(int argc, char *argv [])
{
	// Declare Signals for to connect processor and stimulus generator
	//////////////////////////////////////////////////////////////////
	sc_clock clk;
	sc_signal < bool > reset;
	sc_signal < bool > start;
	sc_signal < bool > done;
	sc_signal < sc_int <32> > sample_input_real;
	sc_signal < sc_int <32> > sample_input_imag;
	sc_signal <sc_int <16> > sample_output_real;
	sc_signal <sc_int <16> > sample_output_imag;
	sc_signal <bool> ready;
	sc_signal <bool> done_sim ; // this signal will be asserted true when simulation finishes
	//////////////////////////////////////////////////////////////////

	// Create a VCD file for signal tracing
	//////////////////////////////////////////////////////////////////
	sc_trace_file *wf= sc_create_vcd_trace_file("pipeLineFFT.vcd");

	// trace signals to file
	/////////////////////////////////////////////////////////////////
	sc_trace(wf,clk,"clk");
	sc_trace(wf,reset,"reset");
	sc_trace(wf,done,"done");
	sc_trace(wf,sample_input_real,"sample_input_real");
	sc_trace(wf,sample_input_imag,"sample_input_imag");
	sc_trace(wf,ready,"ready");
	sc_trace(wf,start,"start");
	sc_trace(wf,sample_output_imag,"sample_output_imag");
	sc_trace(wf,sample_output_real,"sample_output_real");
	// Instantiate a pipelined FFT processor for Simulation
	/////////////////////////////////////////////////////////////////
	pipeLinedFFT_WRAPPER pipeFFTInstance("pipeFFTInstanceName");

	// Wire the FFT processor
	/////////////////////////////////////////////////////////////////
	pipeFFTInstance.clk(clk.signal());
	pipeFFTInstance.reset(reset);
	pipeFFTInstance.start(start);
	pipeFFTInstance.done(done);
	pipeFFTInstance.sample_input_real(sample_input_real);
	pipeFFTInstance.sample_input_imag(sample_input_imag);
	//pipeFFTInstance.clk(clk.signal());
	pipeFFTInstance.sample_output_real(sample_output_real);
	pipeFFTInstance.sample_output_imag(sample_output_imag);
	pipeFFTInstance.ready(ready);
    // Instantiate a stimulus generator for FFT processor
	/////////////////////////////////////////////////////////////////
	stimulus stimGeneratorInstance("stimGeneratorInstanceName");
	// Wire stimulus generator to FFT processor
	//////////////////////////////////////////////////////////////////
	stimGeneratorInstance.clk(clk.signal());
	stimGeneratorInstance.reset(reset);
	stimGeneratorInstance.start(start);
	stimGeneratorInstance.done(done);
	stimGeneratorInstance.sample_input_real(sample_input_real);
	stimGeneratorInstance.sample_input_imag(sample_input_imag);
	stimGeneratorInstance.sample_output_imag(sample_output_imag);
	stimGeneratorInstance.sample_output_real(sample_output_real);
	stimGeneratorInstance.ready(ready);
	stimGeneratorInstance.done_sim(done_sim);
    // Start simulation and wait until it is finished
	sc_start();
	while(done_sim.read()==false) wait();
	// stop signal tracing
	sc_close_vcd_trace_file(wf);
	wait();
	// stop simulation and return
	sc_stop();
	return 0;
}

