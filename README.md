# HiSyFFT : Streaming FFT for HLS Applications
Streaming Fast Fourier Transform ( FFT/DFT ) High Level Synthesis IP Generator for FPGAs and ASICs

HiSynFFT is a fixed point IP generator producing single threaded or multi-threaded C++/SystemC implementation which can be used for high level synthesis
with software like CtoS from Cadence, Catapult from mentor graphics and Vivado HLS from Xilinx.
## How to Build IP Generator
Go to build folder and run
  1) make clean
  2) make all
## How to Generate FFT IP
Once the IP generator is build, FFT implementation can be generated by lauching the bash script as follows:
source packakge_all.sh
this script will generate an FFT implementation whose configuration ( size of FFT and fixed-pioint datapath) is described in
the file called fft.conf. This file is self explanatory please read the comments at the end of this file.
