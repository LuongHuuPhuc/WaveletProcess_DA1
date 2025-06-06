## **Phân biệt biến đổi Wavelet và biến đôi Fourier** ##
### 1. Biến đổi Fourier (Fourier Transform) ###
MỤC TIÊU: <br>
Chuyển tín hiệu từ miền thời gian sang miền tần số <br>
ĐẶC ĐIỂM: <br>
* Dùng các hàm sin và cos (sóng hình sin) làm cơ sở để phân tích tín hiệu 
* Giả định tín hiệu là tuần hoàn và kéo dài vô tận 
* Không biết tại thời điểm nào tần số cụ thể nào xuất hiện, chỉ biết có những tần số nào xuất hiện trong tín hiệu <br> 

### 2. Biến đổi Wavelet (Wavelet Transform) ###
MỤC TIÊU: <br>
Cung cấp thông tin tần số theo thời gian, tức là biết khi nào tần số nào xuất hiện <br>
ĐẶC ĐIỂM: <br>
* Dùng wavelet (sóng nhỏ) - Các hàm có thời gian giới hạn 
* Cho phép phân tích tín hiệu ở nhiều độ phân giải khác nhau: tốt ở tần số cao (chi tiết) và tốt ở thời gian dài(thấp)
* Rất phù hợp với tín hiệu phi tuyến, không định trạm , ví dụ như:
  - Tín hiệu y sinh (PPG, ECG,...)
  - Tiếng nói, tiếng chim, âm thanh,... 

## **Biến đổi wavelet hoạt động như thế nào ?** ## 
### a. Ý tưởng chính ###
Thay vì dùng các sóng sin như trng Fourier, biến đổi Wavelet lại dùng các sóng nhỏ (wavelet), để quét tín hiệu ở các vị trí và các thang đo khác nhau <br>
Tín hiệu được phân tích bằng: 
* Dịch chuyển (translation): Kiểm tra wavelet tại các vị trí khác nhau (trên trục thời gian)
* Co giãn (scaling): Kiểm tra ở nhiều độ phân giải khác nhau, từ thô đến chi tiết 
> Tưởng tưởng như bạn zoom vào 1 ảnh ở nhiều mức độ phóng đại, bạn thấy cả tổng thể lẫn chi tiết 

### b. Các kiểu biến đổi Wavelet trong xử lý tín hiệu ###
Trong xử lý tín hiệu, chủ yếu dùng 2 loại chính:
* Dicrete Wavelet Transform (DWT): Biến đổi Wavelet rời rạc
* Continuous Wavelet Transform (CWT): Biến đổi Wavelet liên tục
#### 1. Biến đổi Wavelet liên tục (CWT) ####
*Ý tưởng:* CWT quét tín hiệu bằng 1 wavelet mẹ được co giãn liên tục (thang a) và dịch chuyển liên tục (dịch b). Tức là ta 
kiểm tra tín hiệu ở mọi độ rộng và mọi vị trí - cực kỳ chi tiết <br>
*Công thức*: <br> 
![image](https://github.com/user-attachments/assets/1a9edeac-40d8-49af-bc07-5c5f1c252873)

