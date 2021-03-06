#include "immintrin.h"
#include<stdio.h>
#include <stdlib.h>

extern double rtclock (void);

void hypterm_opt (double *t_flux_0, double *t_flux_1, double *t_flux_2, double *t_flux_3, double *t_flux_4, double *t_cons_1, double *t_cons_2, double *t_cons_3, double *t_cons_4, double *t_q_1, double *t_q_2, double *t_q_3, double *t_q_4, double *dxinv, int N) {
	double (*flux_0)[308+37][308+37] = (double (*)[308+37][308+37]) t_flux_0;
	double (*flux_1)[308+37][308+37] = (double (*)[308+37][308+37]) t_flux_1;
	double (*flux_2)[308+37][308+37] = (double (*)[308+37][308+37]) t_flux_2;
	double (*flux_3)[308+37][308+37] = (double (*)[308+37][308+37]) t_flux_3;
	double (*flux_4)[308+37][308+37] = (double (*)[308+37][308+37]) t_flux_4;
	double (*cons_1)[308+37][308+37] = (double (*)[308+37][308+37]) t_cons_1;
	double (*cons_2)[308+37][308+37] = (double (*)[308+37][308+37]) t_cons_2;
	double (*cons_3)[308+37][308+37] = (double (*)[308+37][308+37]) t_cons_3;
	double (*cons_4)[308+37][308+37] = (double (*)[308+37][308+37]) t_cons_4;
	double (*q_1)[308+37][308+37] = (double (*)[308+37][308+37]) t_q_1;
	double (*q_2)[308+37][308+37] = (double (*)[308+37][308+37]) t_q_2;
	double (*q_3)[308+37][308+37] = (double (*)[308+37][308+37]) t_q_3;
	double (*q_4)[308+37][308+37] = (double (*)[308+37][308+37]) t_q_4;

	int i, j, k, ii, jj, kk, t;
	double start_time, end_time;

	//Cold run
	for (t=0; t<1; t++) {
#pragma omp parallel 
		{
#pragma omp for private(j,i) 
			for (k = 4; k < N-4; k++) {
				for (j = 4; j < N-4; j++) {
#pragma GCC ivdep
#pragma clang loop vectorize (enable) interleave(enable)
					for (i = 4; i < N-4; i++) {
						flux_0[k][j][i] += ((0.8*(cons_1[k][j][i+1]+cons_1[k][j][i-1])+0.2*(cons_1[k][j][i+2]+cons_1[k][j][i-2])+0.038*(cons_1[k][j][i+3]+cons_1[k][j][i-3])+0.0035*(cons_1[k][j][i+4]+cons_1[k][j][i-4]))*dxinv[0]);
						flux_0[k][j][i] += (0.8*(cons_2[k][j+1][i]+cons_2[k][j-1][i])+0.2*(cons_2[k][j+2][i]+cons_2[k][j-2][i])+0.038*(cons_2[k][j+3][i]+cons_2[k][j-3][i])+0.0035*(cons_2[k][j+4][i]+cons_2[k][j-4][i]))*dxinv[1];
						flux_0[k][j][i] += 0.1 * (0.8*(cons_3[k+1][j][i]+cons_3[k-1][j][i])+0.2*(cons_3[k+2][j][i]+cons_3[k-2][j][i])+0.038*(cons_3[k+3][j][i]+cons_3[k-3][j][i])+0.0035*(cons_3[k+4][j][i]+cons_3[k-4][j][i]))*dxinv[2];
					}
				} 
			}
		}
#pragma omp parallel 
		{
#pragma omp for private(j,i) 
			for (k = 4; k < N-4; k++) {
				for (j = 4; j < N-4; j++) {
#pragma GCC ivdep
#pragma clang loop vectorize (enable) interleave(enable)
					for (i = 4; i < N-4; i++) {
						flux_1[k][j][i] += ((0.8*(cons_1[k][j][i+1]*q_1[k][j][i+1]+cons_1[k][j][i-1]*q_1[k][j][i-1]+(q_4[k][j][i+1]+q_4[k][j][i-1]))+0.2*(cons_1[k][j][i+2]*q_1[k][j][i+2]+cons_1[k][j][i-2]*q_1[k][j][i-2]+(q_4[k][j][i+2]+q_4[k][j][i-2]))+0.038*(cons_1[k][j][i+3]*q_1[k][j][i+3]+cons_1[k][j][i-3]*q_1[k][j][i-3]+(q_4[k][j][i+3]+q_4[k][j][i-3]))+0.0035*(cons_1[k][j][i+4]*q_1[k][j][i+4]+cons_1[k][j][i-4]*q_1[k][j][i-4]+(q_4[k][j][i+4]+q_4[k][j][i-4])))*dxinv[0]);
						flux_1[k][j][i] += (0.8*(cons_1[k][j+1][i]*q_2[k][j+1][i]+cons_1[k][j-1][i]*q_2[k][j-1][i])+0.2*(cons_1[k][j+2][i]*q_2[k][j+2][i]+cons_1[k][j-2][i]*q_2[k][j-2][i])+0.038*(cons_1[k][j+3][i]*q_2[k][j+3][i]+cons_1[k][j-3][i]*q_2[k][j-3][i])+0.0035*(cons_1[k][j+4][i]*q_2[k][j+4][i]+cons_1[k][j-4][i]*q_2[k][j-4][i]))*dxinv[1];
						flux_1[k][j][i] += 0.1 * (0.8*(cons_1[k+1][j][i]*q_3[k+1][j][i]+cons_1[k-1][j][i]*q_3[k-1][j][i])+0.2*(cons_1[k+2][j][i]*q_3[k+2][j][i]+cons_1[k-2][j][i]*q_3[k-2][j][i])+0.038*(cons_1[k+3][j][i]*q_3[k+3][j][i]+cons_1[k-3][j][i]*q_3[k-3][j][i])+0.0035*(cons_1[k+4][j][i]*q_3[k+4][j][i]+cons_1[k-4][j][i]*q_3[k-4][j][i]))*dxinv[2];
					}
				}
			}
		}
#pragma omp parallel 
		{
#pragma omp for private(j,i) 
			for (k = 4; k < N-4; k++) {
				for (j = 4; j < N-4; j++) {
#pragma GCC ivdep
#pragma clang loop vectorize (enable) interleave(enable)
					for (i = 4; i < N-4; i++) {
						flux_2[k][j][i] += ((0.8*(cons_2[k][j][i+1]*q_1[k][j][i+1]+cons_2[k][j][i-1]*q_1[k][j][i-1])+0.2*(cons_2[k][j][i+2]*q_1[k][j][i+2]+cons_2[k][j][i-2]*q_1[k][j][i-2])+0.038*(cons_2[k][j][i+3]*q_1[k][j][i+3]+cons_2[k][j][i-3]*q_1[k][j][i-3])+0.0035*(cons_2[k][j][i+4]*q_1[k][j][i+4]+cons_2[k][j][i-4]*q_1[k][j][i-4]))*dxinv[0]);
						flux_2[k][j][i] += (0.8*(cons_2[k][j+1][i]*q_2[k][j+1][i]+cons_2[k][j-1][i]*q_2[k][j-1][i]+(q_4[k][j+1][i]+q_4[k][j-1][i]))+0.2*(cons_2[k][j+2][i]*q_2[k][j+2][i]+cons_2[k][j-2][i]*q_2[k][j-2][i]+(q_4[k][j+2][i]+q_4[k][j-2][i]))+0.038*(cons_2[k][j+3][i]*q_2[k][j+3][i]+cons_2[k][j-3][i]*q_2[k][j-3][i]+(q_4[k][j+3][i]+q_4[k][j-3][i]))+0.0035*(cons_2[k][j+4][i]*q_2[k][j+4][i]+cons_2[k][j-4][i]*q_2[k][j-4][i]+(q_4[k][j+4][i]+q_4[k][j-4][i])))*dxinv[1];
						flux_2[k][j][i] += 0.1 * (0.8*(cons_2[k+1][j][i]*q_3[k+1][j][i]+cons_2[k-1][j][i]*q_3[k-1][j][i])+0.2*(cons_2[k+2][j][i]*q_3[k+2][j][i]+cons_2[k-2][j][i]*q_3[k-2][j][i])+0.038*(cons_2[k+3][j][i]*q_3[k+3][j][i]+cons_2[k-3][j][i]*q_3[k-3][j][i])+0.0035*(cons_2[k+4][j][i]*q_3[k+4][j][i]+cons_2[k-4][j][i]*q_3[k-4][j][i]))*dxinv[2];
					}
				}
			}
		} 
#pragma omp parallel 
		{
#pragma omp for private(j,i)
			for (k = 4; k < N-4; k++) {
				for (j = 4; j < N-4; j++) {
#pragma GCC ivdep
#pragma clang loop vectorize (enable) interleave(enable)
					for (i = 4; i < N-4; i++) {
						flux_3[k][j][i] += ((0.8*(cons_3[k][j][i+1]*q_1[k][j][i+1]+cons_3[k][j][i-1]*q_1[k][j][i-1])+0.2*(cons_3[k][j][i+2]*q_1[k][j][i+2]+cons_3[k][j][i-2]*q_1[k][j][i-2])+0.038*(cons_3[k][j][i+3]*q_1[k][j][i+3]+cons_3[k][j][i-3]*q_1[k][j][i-3])+0.0035*(cons_3[k][j][i+4]*q_1[k][j][i+4]+cons_3[k][j][i-4]*q_1[k][j][i-4]))*dxinv[0]);
						flux_3[k][j][i] += (0.8*(cons_3[k][j+1][i]*q_2[k][j+1][i]+cons_3[k][j-1][i]*q_2[k][j-1][i])+0.2*(cons_3[k][j+2][i]*q_2[k][j+2][i]+cons_3[k][j-2][i]*q_2[k][j-2][i])+0.038*(cons_3[k][j+3][i]*q_2[k][j+3][i]+cons_3[k][j-3][i]*q_2[k][j-3][i])+0.0035*(cons_3[k][j+4][i]*q_2[k][j+4][i]+cons_3[k][j-4][i]*q_2[k][j-4][i]))*dxinv[1];
						flux_3[k][j][i] += 0.1 * (0.8*(cons_3[k+1][j][i]*q_3[k+1][j][i]+cons_3[k-1][j][i]*q_3[k-1][j][i]+(q_4[k+1][j][i]+q_4[k-1][j][i]))+0.2*(cons_3[k+2][j][i]*q_3[k+2][j][i]+cons_3[k-2][j][i]*q_3[k-2][j][i]+(q_4[k+2][j][i]+q_4[k-2][j][i]))+0.038*(cons_3[k+3][j][i]*q_3[k+3][j][i]+cons_3[k-3][j][i]*q_3[k-3][j][i]+(q_4[k+3][j][i]+q_4[k-3][j][i]))+0.0035*(cons_3[k+4][j][i]*q_3[k+4][j][i]+cons_3[k-4][j][i]*q_3[k-4][j][i]+(q_4[k+4][j][i]+q_4[k-4][j][i])))*dxinv[2];
					}
				}
			}
		}
#pragma omp parallel 
		{
#pragma omp for private(j,i)
			for (k = 4; k < N-4; k++) {
				for (j = 4; j < N-4; j++) {
#pragma GCC ivdep 
#pragma clang loop vectorize (enable) interleave(enable)
					for (i = 4; i < N-4; i++) {
						flux_4[k][j][i] += ((0.8*(cons_4[k][j][i+1]*q_1[k][j][i+1]+cons_4[k][j][i-1]*q_1[k][j][i-1]+(q_4[k][j][i+1]*q_1[k][j][i+1]+q_4[k][j][i-1]*q_1[k][j][i-1]))+0.2*(cons_4[k][j][i+2]*q_1[k][j][i+2]+cons_4[k][j][i-2]*q_1[k][j][i-2]+(q_4[k][j][i+2]*q_1[k][j][i+2]+q_4[k][j][i-2]*q_1[k][j][i-2]))+0.038*(cons_4[k][j][i+3]*q_1[k][j][i+3]+cons_4[k][j][i-3]*q_1[k][j][i-3]+(q_4[k][j][i+3]*q_1[k][j][i+3]+q_4[k][j][i-3]*q_1[k][j][i-3]))+0.0035*(cons_4[k][j][i+4]*q_1[k][j][i+4]+cons_4[k][j][i-4]*q_1[k][j][i-4]+(q_4[k][j][i+4]*q_1[k][j][i+4]+q_4[k][j][i-4]*q_1[k][j][i-4])))*dxinv[0]);
						flux_4[k][j][i] += (0.8*(cons_4[k+1][j][i]*q_3[k+1][j][i]+cons_4[k-1][j][i]*q_3[k-1][j][i]+(q_4[k+1][j][i]*q_3[k+1][j][i]+q_4[k-1][j][i]*q_3[k-1][j][i]))+0.2*(cons_4[k+2][j][i]*q_3[k+2][j][i]+cons_4[k-2][j][i]*q_3[k-2][j][i]+(q_4[k+2][j][i]*q_3[k+2][j][i]+q_4[k-2][j][i]*q_3[k-2][j][i]))+0.038*(cons_4[k+3][j][i]*q_3[k+3][j][i]+cons_4[k-3][j][i]*q_3[k-3][j][i]+(q_4[k+3][j][i]*q_3[k+3][j][i]+q_4[k-3][j][i]*q_3[k-3][j][i]))+0.0035*(cons_4[k+4][j][i]*q_3[k+4][j][i]+cons_4[k-4][j][i]*q_3[k-4][j][i]+(q_4[k+4][j][i]*q_3[k+4][j][i]+q_4[k-4][j][i]*q_3[k-4][j][i])))*dxinv[2];
						flux_4[k][j][i] += 0.1 * (0.8*(cons_4[k][j+1][i]*q_2[k][j+1][i]+cons_4[k][j-1][i]*q_2[k][j-1][i]+(q_4[k][j+1][i]*q_2[k][j+1][i]+q_4[k][j-1][i]*q_2[k][j-1][i]))+0.2*(cons_4[k][j+2][i]*q_2[k][j+2][i]+cons_4[k][j-2][i]*q_2[k][j-2][i]+(q_4[k][j+2][i]*q_2[k][j+2][i]+q_4[k][j-2][i]*q_2[k][j-2][i]))+0.038*(cons_4[k][j+3][i]*q_2[k][j+3][i]+cons_4[k][j-3][i]*q_2[k][j-3][i]+(q_4[k][j+3][i]*q_2[k][j+3][i]+q_4[k][j-3][i]*q_2[k][j-3][i]))+0.0035*(cons_4[k][j+4][i]*q_2[k][j+4][i]+cons_4[k][j-4][i]*q_2[k][j-4][i]+(q_4[k][j+4][i]*q_2[k][j+4][i]+q_4[k][j-4][i]*q_2[k][j-4][i])))*dxinv[1];
					}
				}
			}
		}
	}

	start_time = rtclock ();
	for (t=0; t<2; t++) {
#pragma omp parallel for private (jj,ii,k,j,i)
		for (kk=2; kk < N-2; kk+=8) {
			for (jj=2; jj<N-2; jj+=4) {
				for (ii=2; ii<N-2; ii+=64) {
					for (k = kk; k < kk+8; k++) {
						for (j = jj; j < jj+4; j++) {
							for (i = ii; i < ii+64; i+=4) {
#pragma begin stencil1 unroll k=1,j=1,i=1 print-intrinsics true acc-size 1
								flux_0[k][j][i] += ((0.8*(cons_1[k][j][i+1]+cons_1[k][j][i-1])+0.2*(cons_1[k][j][i+2]+cons_1[k][j][i-2])+0.038*(cons_1[k][j][i+3]+cons_1[k][j][i-3])+0.0035*(cons_1[k][j][i+4]+cons_1[k][j][i-4]))*dxinv[0]);
								flux_0[k][j][i] += (0.8*(cons_2[k][j+1][i]+cons_2[k][j-1][i])+0.2*(cons_2[k][j+2][i]+cons_2[k][j-2][i])+0.038*(cons_2[k][j+3][i]+cons_2[k][j-3][i])+0.0035*(cons_2[k][j+4][i]+cons_2[k][j-4][i]))*dxinv[1];
								flux_0[k][j][i] += (0.8*(cons_3[k+1][j][i]+cons_3[k-1][j][i])+0.2*(cons_3[k+2][j][i]+cons_3[k-2][j][i])+0.038*(cons_3[k+3][j][i]+cons_3[k-3][j][i])+0.0035*(cons_3[k+4][j][i]+cons_3[k-4][j][i]))*dxinv[2];

								flux_1[k][j][i] += ((0.8*(cons_1[k][j][i+1]*q_1[k][j][i+1]+cons_1[k][j][i-1]*q_1[k][j][i-1]+(q_4[k][j][i+1]+q_4[k][j][i-1]))+0.2*(cons_1[k][j][i+2]*q_1[k][j][i+2]+cons_1[k][j][i-2]*q_1[k][j][i-2]+(q_4[k][j][i+2]+q_4[k][j][i-2]))+0.038*(cons_1[k][j][i+3]*q_1[k][j][i+3]+cons_1[k][j][i-3]*q_1[k][j][i-3]+(q_4[k][j][i+3]+q_4[k][j][i-3]))+0.0035*(cons_1[k][j][i+4]*q_1[k][j][i+4]+cons_1[k][j][i-4]*q_1[k][j][i-4]+(q_4[k][j][i+4]+q_4[k][j][i-4])))*dxinv[0]);
								flux_1[k][j][i] += (0.8*(cons_1[k][j+1][i]*q_2[k][j+1][i]+cons_1[k][j-1][i]*q_2[k][j-1][i])+0.2*(cons_1[k][j+2][i]*q_2[k][j+2][i]+cons_1[k][j-2][i]*q_2[k][j-2][i])+0.038*(cons_1[k][j+3][i]*q_2[k][j+3][i]+cons_1[k][j-3][i]*q_2[k][j-3][i])+0.0035*(cons_1[k][j+4][i]*q_2[k][j+4][i]+cons_1[k][j-4][i]*q_2[k][j-4][i]))*dxinv[1];
								flux_1[k][j][i] += (0.8*(cons_1[k+1][j][i]*q_3[k+1][j][i]+cons_1[k-1][j][i]*q_3[k-1][j][i])+0.2*(cons_1[k+2][j][i]*q_3[k+2][j][i]+cons_1[k-2][j][i]*q_3[k-2][j][i])+0.038*(cons_1[k+3][j][i]*q_3[k+3][j][i]+cons_1[k-3][j][i]*q_3[k-3][j][i])+0.0035*(cons_1[k+4][j][i]*q_3[k+4][j][i]+cons_1[k-4][j][i]*q_3[k-4][j][i]))*dxinv[2];

								flux_2[k][j][i] += ((0.8*(cons_2[k][j][i+1]*q_1[k][j][i+1]+cons_2[k][j][i-1]*q_1[k][j][i-1])+0.2*(cons_2[k][j][i+2]*q_1[k][j][i+2]+cons_2[k][j][i-2]*q_1[k][j][i-2])+0.038*(cons_2[k][j][i+3]*q_1[k][j][i+3]+cons_2[k][j][i-3]*q_1[k][j][i-3])+0.0035*(cons_2[k][j][i+4]*q_1[k][j][i+4]+cons_2[k][j][i-4]*q_1[k][j][i-4]))*dxinv[0]);
								flux_2[k][j][i] += (0.8*(cons_2[k][j+1][i]*q_2[k][j+1][i]+cons_2[k][j-1][i]*q_2[k][j-1][i]+(q_4[k][j+1][i]+q_4[k][j-1][i]))+0.2*(cons_2[k][j+2][i]*q_2[k][j+2][i]+cons_2[k][j-2][i]*q_2[k][j-2][i]+(q_4[k][j+2][i]+q_4[k][j-2][i]))+0.038*(cons_2[k][j+3][i]*q_2[k][j+3][i]+cons_2[k][j-3][i]*q_2[k][j-3][i]+(q_4[k][j+3][i]+q_4[k][j-3][i]))+0.0035*(cons_2[k][j+4][i]*q_2[k][j+4][i]+cons_2[k][j-4][i]*q_2[k][j-4][i]+(q_4[k][j+4][i]+q_4[k][j-4][i])))*dxinv[1];
								flux_2[k][j][i] += (0.8*(cons_2[k+1][j][i]*q_3[k+1][j][i]+cons_2[k-1][j][i]*q_3[k-1][j][i])+0.2*(cons_2[k+2][j][i]*q_3[k+2][j][i]+cons_2[k-2][j][i]*q_3[k-2][j][i])+0.038*(cons_2[k+3][j][i]*q_3[k+3][j][i]+cons_2[k-3][j][i]*q_3[k-3][j][i])+0.0035*(cons_2[k+4][j][i]*q_3[k+4][j][i]+cons_2[k-4][j][i]*q_3[k-4][j][i]))*dxinv[2];

								flux_3[k][j][i] += ((0.8*(cons_3[k][j][i+1]*q_1[k][j][i+1]+cons_3[k][j][i-1]*q_1[k][j][i-1])+0.2*(cons_3[k][j][i+2]*q_1[k][j][i+2]+cons_3[k][j][i-2]*q_1[k][j][i-2])+0.038*(cons_3[k][j][i+3]*q_1[k][j][i+3]+cons_3[k][j][i-3]*q_1[k][j][i-3])+0.0035*(cons_3[k][j][i+4]*q_1[k][j][i+4]+cons_3[k][j][i-4]*q_1[k][j][i-4]))*dxinv[0]);
								flux_3[k][j][i] += (0.8*(cons_3[k][j+1][i]*q_2[k][j+1][i]+cons_3[k][j-1][i]*q_2[k][j-1][i])+0.2*(cons_3[k][j+2][i]*q_2[k][j+2][i]+cons_3[k][j-2][i]*q_2[k][j-2][i])+0.038*(cons_3[k][j+3][i]*q_2[k][j+3][i]+cons_3[k][j-3][i]*q_2[k][j-3][i])+0.0035*(cons_3[k][j+4][i]*q_2[k][j+4][i]+cons_3[k][j-4][i]*q_2[k][j-4][i]))*dxinv[1];
								flux_3[k][j][i] += (0.8*(cons_3[k+1][j][i]*q_3[k+1][j][i]+cons_3[k-1][j][i]*q_3[k-1][j][i]+(q_4[k+1][j][i]+q_4[k-1][j][i]))+0.2*(cons_3[k+2][j][i]*q_3[k+2][j][i]+cons_3[k-2][j][i]*q_3[k-2][j][i]+(q_4[k+2][j][i]+q_4[k-2][j][i]))+0.038*(cons_3[k+3][j][i]*q_3[k+3][j][i]+cons_3[k-3][j][i]*q_3[k-3][j][i]+(q_4[k+3][j][i]+q_4[k-3][j][i]))+0.0035*(cons_3[k+4][j][i]*q_3[k+4][j][i]+cons_3[k-4][j][i]*q_3[k-4][j][i]+(q_4[k+4][j][i]+q_4[k-4][j][i])))*dxinv[2];

								flux_4[k][j][i] += ((0.8*(cons_4[k][j][i+1]*q_1[k][j][i+1]+cons_4[k][j][i-1]*q_1[k][j][i-1]+(q_4[k][j][i+1]*q_1[k][j][i+1]+q_4[k][j][i-1]*q_1[k][j][i-1]))+0.2*(cons_4[k][j][i+2]*q_1[k][j][i+2]+cons_4[k][j][i-2]*q_1[k][j][i-2]+(q_4[k][j][i+2]*q_1[k][j][i+2]+q_4[k][j][i-2]*q_1[k][j][i-2]))+0.038*(cons_4[k][j][i+3]*q_1[k][j][i+3]+cons_4[k][j][i-3]*q_1[k][j][i-3]+(q_4[k][j][i+3]*q_1[k][j][i+3]+q_4[k][j][i-3]*q_1[k][j][i-3]))+0.0035*(cons_4[k][j][i+4]*q_1[k][j][i+4]+cons_4[k][j][i-4]*q_1[k][j][i-4]+(q_4[k][j][i+4]*q_1[k][j][i+4]+q_4[k][j][i-4]*q_1[k][j][i-4])))*dxinv[0]);
								flux_4[k][j][i] += (0.8*(cons_4[k+1][j][i]*q_3[k+1][j][i]+cons_4[k-1][j][i]*q_3[k-1][j][i]+(q_4[k+1][j][i]*q_3[k+1][j][i]+q_4[k-1][j][i]*q_3[k-1][j][i]))+0.2*(cons_4[k+2][j][i]*q_3[k+2][j][i]+cons_4[k-2][j][i]*q_3[k-2][j][i]+(q_4[k+2][j][i]*q_3[k+2][j][i]+q_4[k-2][j][i]*q_3[k-2][j][i]))+0.038*(cons_4[k+3][j][i]*q_3[k+3][j][i]+cons_4[k-3][j][i]*q_3[k-3][j][i]+(q_4[k+3][j][i]*q_3[k+3][j][i]+q_4[k-3][j][i]*q_3[k-3][j][i]))+0.0035*(cons_4[k+4][j][i]*q_3[k+4][j][i]+cons_4[k-4][j][i]*q_3[k-4][j][i]+(q_4[k+4][j][i]*q_3[k+4][j][i]+q_4[k-4][j][i]*q_3[k-4][j][i])))*dxinv[2];
								flux_4[k][j][i] += (0.8*(cons_4[k][j+1][i]*q_2[k][j+1][i]+cons_4[k][j-1][i]*q_2[k][j-1][i]+(q_4[k][j+1][i]*q_2[k][j+1][i]+q_4[k][j-1][i]*q_2[k][j-1][i]))+0.2*(cons_4[k][j+2][i]*q_2[k][j+2][i]+cons_4[k][j-2][i]*q_2[k][j-2][i]+(q_4[k][j+2][i]*q_2[k][j+2][i]+q_4[k][j-2][i]*q_2[k][j-2][i]))+0.038*(cons_4[k][j+3][i]*q_2[k][j+3][i]+cons_4[k][j-3][i]*q_2[k][j-3][i]+(q_4[k][j+3][i]*q_2[k][j+3][i]+q_4[k][j-3][i]*q_2[k][j-3][i]))+0.0035*(cons_4[k][j+4][i]*q_2[k][j+4][i]+cons_4[k][j-4][i]*q_2[k][j-4][i]+(q_4[k][j+4][i]*q_2[k][j+4][i]+q_4[k][j-4][i]*q_2[k][j-4][i])))*dxinv[1];
#pragma end stencil1
							}
						}
					}
				}
			}
		}
	}
	end_time = rtclock ();
	printf ("opt: %6lf\n", (double)300*300*300*358*2/(end_time - start_time)/1e9);
}
