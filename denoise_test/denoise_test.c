#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <wavefunc.h>
#include <wavelib.h>
#include <wauxlib.h>

#define MAX_LEN 127340

/**
 * @note Muc dich cua su dung DWT la:
 * \note - Khu nhieu 
 * \note - Trich xuat dac trung 
 * \note - Nen du lieu khi can truyen tai qua mang (IoT, BLE, Wifi)
 * \note - Phat hien dieu kien y sinh (Dinh R trong ECG, S1-S2 trong PCG, Bien dong tin hieu huyet ap trong PPG)
 */

static const char *file_path = "D:/C-C++_project/WaveletProcess/Data_text/ECG_samples/NoFilter/data_ecg_noFilter_1st.csv";

/**
 * @brief Root Mean Square Error (RMSE) dung de danh gia muc do sai lech trung binh giua tin hieu goc va sau khi xu ly
 * \brief - Dung de danh gia muc nhieu da duoc loai bo hieu qua hay khong 
 * 
 * @note - RMSE = 0, Hai tin hieu giong nhau hoan toan
 * \note - RMSE lon, tin hieu da bi sai lech nhieu so voi tin hieu goc
 * 
 * @return Sai so tuyet doi
 * 
 * @param N So luong mau trong moi day tin hieu `x` va `y` 
 * @param x Day gia tri goc (chuan)
 * @param y Day gia tri can danh gia (sau khi da loc)
 */
static double __attribute__((unused))rmse(int N, double *x, double *y){
  double rms = 0.0f;
  int i;

  for(i = 0; i < N; ++i){
    rms += (x[i] - y[i] ) * (x[i] - y[i]);
  }

  rms = sqrt(rms / (double)N);
  return rms;
}

/**
 * @brief He so tuong quan (Correlation Coefficient) - Danh gia muc do tuong quan tuyen tinh giua 2 tin hieu 
 * \brief - Dung de danh gia muc do giong nhau ve hinh dang, xem song sau khi xu ly co giu duoc hay khong, 
 * khong quan trong do lon tuyet doi
 *
 * @note Nam trong khoang `[-1, 1]`
 * \note - 1: Tuong quan tuyet doi duong (giong het ve hinh dang, khac bien do)
 * \note - 0: Khong tuong quan
 * \note - -1: Tuong quan tuyet doi am (doi xung nguoc lai)
 *  
 * @param N So luong mau trong moi day tin hieu `x` va `y` 
 * @param x Day gia tri goc (chuan)
 * @param y Day gia tri can danh gia (sau khi da loc)
 */
static double __attribute__((unused))corrcoef(int N, double *x, double *y){
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

int main(void){
  FILE *file_in, *file_out;
  double *input = NULL, *output = NULL;
  int capacity = MAX_LEN;
  int N = 0; //So luong mau cua tin hieu (do dai)
  int J = 4; //So muc phan ra (Bao nhieu lan thuc hien downsampling)
  char line[128];

  //Mang tam chua du lieu (dung mang dong de chua duoc nhieu hon)
  input = (double*)malloc(MAX_LEN * sizeof(double));
  if(!input){
    printf("Memory allocate Failed !\n");
    return -1;
  }

  //Doc file dau vao
  file_in = fopen(file_path, "r");
  if(!file_in){
    printf("Can not open file.csv \n");
    return -1;
  }

  while(fgets(line, sizeof(line), file_in)){
    if(N >= MAX_LEN){
      capacity *= 2; //Tang gap doi bo nho 
      input =realloc(input, sizeof(double) * capacity);
      if(!input){
        printf("Realloc failed !\n");
        return -1;
      }
    }
    input[N++] = atof(line);
  }
  fclose(file_in);

  //Cap phat bo nho dau ra
  output = (double*)malloc(N * sizeof(double));

  //Xu ly 
  denoise_object obj = denoise_init(N, J, "db5");
  setDenoiseMethod(obj, "visushrink");
  setDenoiseWTMethod(obj, "dwt");
  setDenoiseWTExtension(obj, "sym");
  setDenoiseParameters(obj, "soft", "all");

  denoise(obj, input, output);

  // Ghi ket qua ra file
  file_out = fopen("D:/C-C++_project/WaveletProcess/denoise_test/result_files/ECG_results/output_denoised.csv", "w");
  if(!file_out){
    printf("Can not write to output file.csv\n");
    return -1;
  }

  for(int i = 0; i < N; ++i){
    fprintf(file_out, "%lf\n", output[i]);
  }
  fclose(file_out);

  // So sanh tin hieu dau vao voi chinh no de so sanh li tuong
  printf("Self-comparison (input vs input):\n");
  printf("RMSE: %lf\n", rmse(N, input, input));
  printf("Corr coeff: %lf\n", corrcoef(N, input, input));

  // So sanh tin hieu goc va tin hieu da xu ly
  printf("Orignal signal vs Denoised signal:\n");
  printf("RMSE: %lf\n", rmse(N, input, output));
  printf("Corr coeff: %lf\n", corrcoef(N, input, output));


  //Clear
  free(input);
  free(output);
  denoise_free(obj);

  printf("Xu ly hoan tat. Ket qua da luu trong file.csv !\n");
  return 0;
}