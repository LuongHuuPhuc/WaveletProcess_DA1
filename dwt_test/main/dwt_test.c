#include <stdio.h>
#include <stdlib.h>
#include <wauxlib.h>
#include <wavelib.h>
#include <waux.h>
#include <math.h>
#include <string.h>
#include "Signal_Erreck.h"

#define MAX_SIZE    100000
#define INPUT_PATH  "D:/C-C++_project/WaveletProcess/Data_text/PCG_samples/noFilter/HeartBeat_raw/800Hz/test2.csv"
#define APPROX_PATH "D:/C-C++_project/WaveletProcess/dwt_test/result_files/cprocess_files/approx_files/output.csv"
#define DETAIL_PATH "D:/C-C++_project/WaveletProcess/dwt_test/result_files/cprocess_files/detail_files/output.csv"
#define RECONS_PATH "D:/C-C++_project/WaveletProcess/dwt_test/result_files/reconstructed_files/output.csv"

/**
 * @brief Ham luu gia tri he so phan ra Approximation/Detail cua tin hieu vao file.csv
 * 
 * @param wt Doi tuong cua cau truc wt_object chua cac thong tin cua xu ly 
 * @param decomp mang chua du lieu sau khi phan ra 
 * @param file_path duong dan den file can luu
 */
static void __attribute((unused))decomposignal(wt_object wt, double *decomp, const char *file_path){
  // getDWTAppx(wt, decomp, wt->length[0]); //Ham nay luu ve gia tri cua he so xap xi thap nhat

  // getDWTDetail(wt, decomp, wt->length[1], 4); //Ham nay luu ve gia tri cua he so chi tiet o level cu the

  memcpy(decomp, wt->output, sizeof(double) * wt->outlength);

  FILE *file_decomp = fopen(file_path, "w");
  if(!file_decomp){
    printf("Can not open file to write decomposition !\r\n");
    return;
  }
  for(int i = 0; i < wt->outlength; ++i){
    fprintf(file_decomp, "%lf\n", decomp[i]);
  }
  fclose(file_decomp);
  printf("Da luu data decompostion vao file.csv !\r\n");
}

/**
 * @brief Ham luu gia tri tin hieu tai tao lai vao file.csv
 * 
 * @param wt Doi tuong cua wt_object chua cac thanh phan de xu ly
 * @param recons mang chua du lieu sau khi tai tao
 * @param file_path duong dan den file.csv
 */
static void __attribute__((unused))reconsignal(wt_object wt, double *recons, const char *file_path){
  idwt(wt, recons);

  FILE *file_recons = fopen(file_path, "w");
  if(!file_recons){
    printf("Can not open file to write reconstruction ! \r\n");
    return;
  }

  for(int i = 0; i < wt->siglength; ++i){
    fprintf(file_recons, "%lf\n", recons[i]);
  }
  fclose(file_recons);
  printf("Da luu data reconstruction vao file.csv !\r\n");
}

/**
 * @brief Ham kiem tra do dai he so cua tung muc phan ra 
 * 
 * @param wt Doi tuong cua wt_object 
 * @param J muc phan ra cua tin hieu
 * 
 * @note Tat ca cac gia tri cua ket qua wavelet decomposition duoc luu ben trong vector wt->output nhu sau: 
 * \note `[A(J) D(J) D(J-1) ..... D(1)]`
 * \note - Voi chieu dai cua A(J) luu tai = wt->length[0]
 * \note - Voi chieu dai cua D(J) luu tai wt->length[1]
 * \note - Voi chieu dai cua D(J - 1) luu tai wt->length[2]
 * \note ...
 * \note - Voi chieu dai cua D(1) luu tai wt->length[J]
 */
static void __attribute__((unused))decomposingal_coeffs(wt_object wt, int J){
  printf("siglength: %d\n", wt->siglength);
  printf("outlength: %d\n", wt->outlength);
  for(int i = 0; i <= J; i++){
    printf("Length[%d]: %d\n", i, wt->length[i]);
  }
}

// Ham main xu ly DWT downsampling + upsampling 
int main(void){
  double *input = NULL, *reconstructed = NULL, *diff = NULL, *decomposed = NULL;
  int N = 0; // So luong mau
  int capacity = MAX_SIZE;
  char line[128]; //Bien luu so ky tu cua 1 dong 
  FILE *file_in;

  // Doc file du lieu dau vao
  file_in = fopen(INPUT_PATH, "r");
  if(!file_in){
    printf("Can not open file input.csv\n");
    return -1;
  }

  // Cap phat bo nho dong cho bien ghi du lieu tu file dau vao
  input = (double*)malloc(capacity * sizeof(double));
  if(!input){
    printf("Fail to allocate memory\n");
    return -1;
  }

  // Thuc hien chep du lieu tu file sang input
  while(fgets(line, sizeof(line), file_in)){
    if(N >= capacity){
      capacity *= 2;
      input = (double*)realloc(input, sizeof(double) * capacity);
      if(!input){
        printf("Realloc Failed\n");
        fclose(file_in);
        return -1;
      }
    }
    input[N++] = atof(line);
  }
  fclose(file_in);

  // Khoi tao wavelet
  wave_object obj = wave_init("db4");
  int J = 4; // Cap phan ra wavelet

  wt_object wt  = wt_init(obj, "dwt", N, J);
  setDWTExtension(wt, "sym");
  setWTConv(wt, "direct");

  //Cap phat bo nho dong cho tin hieu phuc hoi - phan ra - sai so
  reconstructed = (double*)malloc(N * sizeof(double));
  decomposed = (double*)malloc(wt->outlength * sizeof(double));
  diff = (double*)malloc(N * sizeof(double)); // Mang chua sai so tin hieu goc va tin hieu phuc hoi

  if(!reconstructed || !diff || !decomposed){
    printf("Failed to allocate memory to reconstructed/diff\n");
    return -1;
  }

  // Thuc hien DWT 
  dwt(wt, input);

  decomposignal(wt, decomposed, DETAIL_PATH);

  reconsignal(wt, reconstructed, RECONS_PATH);

  //Tinh sai so tuyet doi
  for(int i = 0; i < wt->siglength; ++i){
    diff[i] =  input[i] - reconstructed[i];
  }

  //Tinh do chech lech giua 2 tin hieu phuc hoi - tin hieu goc
  printf("Gia tri sai so tuyet doi lon nhat (Max error): %lf\n", absmax(diff, wt->siglength));

  // In ra thong tin tong quan
  wt_summary(wt);

  // Giai phong tai nguyen
  free(input);
  free(reconstructed);
  free(decomposed);
  free(diff);
  wave_free(obj);
  wt_free(wt);

  printf("Xu ly hoan tat. Da ghi du lieu vao file csv\n");
  return 0;
}
