/*
 * support_functions.h
 *
 *  Created on: Oct 5, 2012 : 5:09:00 PM
 *  Project : FFT IP/S-Fucntion generator
 *      Author: Shahzad Ahmad Butt
 */
#ifndef SUPPORT_FUNCTIONS_H_
#define SUPPORT_FUNCTIONS_H_
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include "fixed_point_lib.h"

void createTwiddleTable_image(FILE *fptr,int fft_len,int stage_number,int twiddle_factor_bit_width,int twiddle_table_fraction_width);
void createTwiddleTable(FILE *fptr,int fft_len,int stage_number,int twiddle_factor_bit_width,int twiddle_table_fraction_width);
void print_BODY_setup_script_dot_tcl(FILE *fptr,int fft_len,int total_stages);
void print_BODY_hls_fixed_point_lib_dot_h(FILE *fptr,int fft_len,int total_stages);
void print_BODY_hls_fixed_point_lib_dot_cpp(FILE *fptr,int fft_len,int total_stages);
void print_BODY_fixed_point_arithmetic_constants_dot_h(FILE *fptr,int fft_len,int total_stages);
void print_BODY_dtype_dot_h(FILE *fptr);




void print_BODY_global_constants_dot_h(FILE *fptr,int fft_len,int in_sample_width,int output_sample_width,int fft_threads,int circular_buffers,int ctos_model,int fft_input_sample_fractional_part_len,int fft_input_sample_integer_part_len,int fft_output_sample_fractional_part_len,int fft_output_sample_inetger_part_len);
//void print_BODY_global_constants_dot_h(FILE *fptr,int fft_len,int in_sample_width,int output_sample_width);
void print_BODY_global_variables_stageN_dot_h(FILE *fptr,int stage,int fft_len);
void print_BODY_global_constants_stageN_dot_h(FILE *fptr,int stage,int fft_len);
void print_BODY_functional_behavior_stageN_dot_h(FILE *fptr,int stage,int fft_len,int fft_output_bit_width);
void print_BODY_fftPipelined_wrapper_dot_h(FILE *fptr,int stage,int fft_len,int input_bit_width,int output_bit_width);
void print_BODY_fftPipelined_wrapper_dot_cpp(FILE *fptr,int total_stages,int fft_len,int twiddle_factors_bit_width,int twiddle_factors_fraction_width, int output_bit_width);
void print_BODY_stimulus_dot_h(FILE *fptr);

void print_BODY_stimulus_dot_cpp(FILE *fptr, int fft_len, int no_of_sim_frame);
void print_BODY_stimulus_top_dot_cpp(FILE *fptr, int fft_len, int input_sample_bit_width, int output_sample_bitwidth);

void printAuthor(FILE *fptr,char* file_name,char *file_ext);
void printFileGaurd_start(FILE *fptr, char *file_name,char *file_ext);
void printFileGaurd_end(FILE *fptr, char *file_name,char *file_ext);
char *covertToUpper(char *str);
#endif //SUPPORT_FUNCTIONS_H
