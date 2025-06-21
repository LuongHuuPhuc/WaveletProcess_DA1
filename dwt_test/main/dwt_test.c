#include <stdio.h>
#include <stdlib.h>
#include <wauxlib.h>
#include <wavelib.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE    100000
#define INPUT_PATH  "D:/C-C++_project/WaveletProcess/Data_text/PCG_samples/noFilter/HeartBeat_raw/1000Hz/test1.csv"
#define OUTPUT_PATH "D:/C-C++_project/WaveletProcess/dwt_test/result_files/approx_files/output.csv"

/**
 * @brief Ham tinh gia tri tuyet doi lon nhat cua 2 tin hieu goc va tin hieu ban dau
 * \brief - Cho biet tin hieu phuc hoi `reconstructed` chenh lech bao nhieu so voi tin hieu goc 
 * \brief - No tra ve gia tri sai khac lon nhat giua hai tin hieu, tuc la loi lon nhat xay ra tai 1 diem bat ky 
 * 
 * @return - Neu `absmax()` rat nho - Tin hieu duoc khoi phuc lai rat chinh xac
 * \return - Neu `absmax()` lon - co loi tinh toan, muc do phan ra khong du 
 */
static double __attribute__((unused))absmax(double *arr, int N){
  double max = 0.0f; 
  int i;

  for(i = 0; i < N; ++i){
    if(fabs(arr[i]) >= max){
      max = fabs(arr[i]);
    }
  }
  return max;
}

// Ham main xu ly DWT downsampling + upsampling 
int main(void){
  double *input = NULL, *reconstructed = NULL, *diff = NULL;
  int N = 0; // So luong mau
  int capacity = MAX_SIZE;
  char line[128]; //Bien luu so ky tu cua 1 dong 
  FILE *file_in, *file_out;

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
  wave_object obj = wave_init("sym4");
  int J = 4; // Cap phan ra wavelet

  wt_object wt  = wt_init(obj, "dwt", N, J);
  setDWTExtension(wt, "sym");
  setWTConv(wt, "direct");

  //Cap phat bo nho dong cho tin hieu phuc hoi va sai so 
  reconstructed = (double*)malloc(N * sizeof(double));
  diff = (double*)malloc(N * sizeof(double)); // Mang chua sai so tin hieu goc va tin hieu phuc hoi

  if(!reconstructed || !diff){
    printf("Failed to allocate memory to reconstructed/diff\n");
    return -1;
  }

  // Thuc hien DWT 
  dwt(wt, input);

  // Thuc hien IDWT (Inverse Dicrete Wavelet Transform) de phuc hoi lai tin hieu
  idwt(wt, reconstructed);

  //Tinh sai so tuyet doi
  for(int i = 0; i < wt->siglength; ++i){
    diff[i] =  input[i] - reconstructed[i];
  }

  //Tinh do chech lech giua 2 tin hieu phuc hoi - tin hieu goc
  printf("Gia tri sai so tuyet doi lon nhat (MAX error): %lf\n", absmax(diff, wt->siglength));

  //Ghi tin hieu phuc hoi ra file 
  file_out = fopen(OUTPUT_PATH, "w");
  if(!file_out){
    printf("Can not write to output.csv\n");
    return -1;
  }

  for(int i = 0; i < N; ++i){
    fprintf(file_out, "%lf\n", reconstructed[i]);
  }
  fclose(file_out);

  // In ra thong tin tong quan
  wt_summary(wt);

  // Giai phong tai nguyen
  free(input);
  free(reconstructed);
  free(diff);
  wave_free(obj);
  wt_free(wt);

  printf("Xu ly oan tat. Da ghi du lieu vao file csv\n");
  return 0;
}
