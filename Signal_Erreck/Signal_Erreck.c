#ifdef __cplusplus
extern "C"{
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "Signal_Erreck.h"

double __attribute__((unused))rmse(int N, double *x, double *y){
  return sqrt(mse(N, x, y));
}

double __attribute__((unused))corrcoef(int N, double *x, double *y){
  double cc, xm, ym, tx, ty, num, den1, den2;
  int i ;
  xm = ym = 0.0f;
  for(i = 0; i < N; ++i){
    xm += x[i];
    ym += y[i];
  }

  xm = xm / N;
  ym = ym / N;
  num = den1 = den2 = 0.0f;

  for(i = 0; i < N; ++i){
    tx = x[i] - xm;
    ty = y[i] - ym;
    num += (tx * ty);
    den1 += (tx * tx);
    den2 += (ty * ty);
  }

  cc = num / sqrt(den1 *den2);

  return cc;
}

double __attribute__((unused))absmax(double *arr, int N){
  double max = 0.0f; 
  for(int i = 0; i < N; ++i){
    if(fabs(arr[i]) >= max){
      max = fabs(arr[i]);
    }
  }
  return max;
}

double __attribute__((unused))mae(int N, double *X, double *Y){
  double sum = 0.0f;
  for(int i = 0; i < N; ++i){
    sum += fabs(X[i] - Y[i]);
  }
  return (sum / N);
}

double __attribute__((unused))mse(int N, double *X, double *Y){
  double sum = 0.0f;
  for(int i = 0; i < N; ++i){
    double diff = X[i] - Y[i];
    sum += diff * diff;
  }
  return sum / N;
}

double __attribute__((unused))snr(int N, double *original, double *processed){
  double signal_power = 0.0;
  double noise_power = 0.0;
  for(int i = 0; i < N; ++i){
    signal_power += original[i] * original[i];
    double diff = original[i] - processed[i];
    noise_power += diff * diff;
  }
  if(noise_power == 0.0){
    return INFINITY;
  }
  return 10.0 * log10(signal_power / noise_power);
}

double __attribute__((unused))psnr(int N, double *original, double *processed){
  double max_val = 0.0;
  for(int i = 0; i < N; ++i){
    if(fabs(original[i]) > max_val){
      max_val = fabs(original[i]);
    }
  }
  double mse_val = mse(N, original, processed);
  if(mse_val == 0.0){
    return INFINITY;
  }
  return 10.0 * log10((max_val * max_val) / mse_val);
}

double __attribute__((unused))process_count_ms(){
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0); // Chuyen thanh ms
}

#ifdef __cplusplus
}
#endif