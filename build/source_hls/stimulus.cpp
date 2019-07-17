/* File Name : stimulus.cpp
* This is an automatically generated file using HLS IP generator
* File creation time:17-7-2019 15:55:17
* Author Name : Shahzad Ahmad Butt
* Author Email : shahzad.butt@polito.it,shehzad.ee@gmail.com
* PostDoctoral Researcher at Micro-electronics Group
* Department of Electronics and Telecommunications 
* Politecnico di Torino, Torino, Italy
* http://polimage.polito.it/wsn/people/shahzad-ahmad-butt
*/
#include "stimulus.h"
#include <stdio.h>
#include <math.h>
void stimulus::genSim(void)
{
	int i,real,imag;
	float real_in,imag_in,pi,angle;
float f0=0.2;
	wait();
	reset.write(true);
	wait();
	reset.write(false);
	wait();
	while(ready.read()==false)
	wait();
	start.write(true);
	GEN_SIM:
	for(i=0;i<(2048*4);i++)
	{
		pi = (float)22/(float)7;
		angle = 2*pi*f0*(i%(FFT_LEN>>1));
		imag_in =0;//sin(angle);
		real_in =(i%FFT_LEN)+1; //cos(angle);
		imag=toQ(imag_in,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH);
		real=toQ(real_in,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH);
		sample_input_real.write(real);
		sample_input_imag.write(imag);
		wait();
	}
}

void stimulus::check_outputs(void)
{
	int temp_real,temp_imag;   
   	int count=0;
   	done_sim.write(false);
   	wait();
   	while(start.read()==false) wait();
   	while(count < (2048*4))
   	{



#ifdef ADD_SYSTEMC_SIMULATION_SUPPORT_FUCNTIONS

temp_real= (int)sample_output_real.read();  	
temp_imag= (int)sample_output_imag.read();   	
if(temp_imag < 0)  	
   		printf ("The output sample no %d------------ : ( %f - %fi )\n",count,toFloat(temp_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH),-toFloat(temp_imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH));
else  	
   		printf ("The output sample no %d------------ : ( %f + %fi )\n",count,toFloat(temp_real,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH),toFloat(temp_imag,INPUT_SAMPLE_BIT_WIDTH,INPUT_SAMPLE_FRACTION_PART_BIT_WIDTH));
#else
if(temp_imag < 0)  	
   		printf ("The output sample  no %d------------ : ( %d - %di )\n",count,(int)sample_output_real.read()),(int)sample_output_imag.read());
else  	
   		printf ("The output sample  no %d------------ : ( %d + %di )\n",count,(int)sample_output_real.read()),(int)sample_output_imag.read());
#endif
		count++;
		wait();
   	}
    done_sim.write(true);
	sc_stop();
	wait();
	wait(10);
	while(1) wait();
}

