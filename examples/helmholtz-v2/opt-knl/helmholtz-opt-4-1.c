#include "immintrin.h"
#include<stdio.h>
#include<stdlib.h>

extern double rtclock (void);

void helmholtz_opt (double * __restrict__ t_out, double * __restrict__ t_alpha, double * __restrict__ t_x, double * __restrict__ t_beta_i, double * __restrict__ t_beta_j, double * __restrict__ t_beta_k, int N) {
	double (*out)[514+37][514+37] = (double (*)[514+37][514+37]) t_out;
	double (*alpha)[514+37][514+37] = (double (*)[514+37][514+37]) t_alpha;
	double (*x)[514+37][514+37] = (double (*)[514+37][514+37]) t_x;
	double (*beta_i)[514+37][514+37] = (double (*)[514+37][514+37]) t_beta_i;
	double (*beta_j)[514+37][514+37] = (double (*)[514+37][514+37]) t_beta_j;
	double (*beta_k)[514+37][514+37] = (double (*)[514+37][514+37]) t_beta_k;

	double a = 1.141;
	double b = 0.121;
	double h2inv = 6.215;

	int i, j, k, t;
	double start_time, end_time;

	//Cold run
	for (t=0; t<1; t++) {
#pragma omp parallel 
		{
#pragma omp for private(j,i)
			for (k = 1; k < N-1; k+=1) {
				for (j = 1; j < N-1; j++) {
#pragma clang loop vectorize (enable) interleave(enable)
#pragma GCC ivdep
					for (i = 1; i < N-1; i++) {
						out[k][j][i] = 0.1 * a*alpha[k][j][i]*x[k][j][i] - b*h2inv*(
								beta_i[k][j][i+1] * (x[k][j][i+1] - x[k][j][i]) + 
								beta_i[k][j][i] * (x[k][j][i-1] - x[k][j][i]) + 
								beta_j[k][j+1][i] * (x[k][j+1][i] - x[k][j][i]) + 
								beta_j[k][j][i] * (x[k][j-1][i] - x[k][j][i]) + 
								beta_k[k+1][j][i] * (x[k+1][j][i] - x[k][j][i]) + 
								beta_k[k][j][i] * (x[k-1][j][i] - x[k][j][i]));
					}
				}
			}
		}
	}

	start_time = rtclock ();
	for (t=0; t<5; t++) {
#pragma omp parallel 
		{
#pragma omp for private(j,i)
			for (k = 1; k < N-1; k+=4) {
				for (j = 1; j < N-1; j++) {
					for (i = 1; i < N-1; i+=8) {
#pragma begin stencil1 unroll k=4,j=1,i=1 print-intrinsics true acc-size 1
						out[k][j][i] = a*alpha[k][j][i]*x[k][j][i] - b*h2inv*(
								beta_i[k][j][i+1] * (x[k][j][i+1] - x[k][j][i]) + 
								beta_i[k][j][i] * (x[k][j][i-1] - x[k][j][i]) + 
								beta_j[k][j+1][i] * (x[k][j+1][i] - x[k][j][i]) + 
								beta_j[k][j][i] * (x[k][j-1][i] - x[k][j][i]) + 
								beta_k[k+1][j][i] * (x[k+1][j][i] - x[k][j][i]) + 
								beta_k[k][j][i] * (x[k-1][j][i] - x[k][j][i]));
#pragma end stencil1
					}
				}
			}
		}
	}
	end_time = rtclock ();
	printf ("opt: %6lf\n", (double)512*512*512*22*5/(end_time  - start_time)/1e9);
}
