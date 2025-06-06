# **Phân biệt biến đổi Wavelet và biến đôi Fourier** #
## 1. Biến đổi Fourier (Fourier Transform) ##
*MỤC TIÊU:* <br>
Chuyển tín hiệu từ miền thời gian sang miền tần số <br>
*ĐẶC ĐIỂM:* <br>
* Dùng các hàm sin và cos (sóng hình sin) làm cơ sở để phân tích tín hiệu 
* Giả định tín hiệu là tuần hoàn và kéo dài vô tận 
* Không biết tại thời điểm nào tần số cụ thể nào xuất hiện, chỉ biết có những tần số nào xuất hiện trong tín hiệu <br> 

## 2. Biến đổi Wavelet (Wavelet Transform) ##
*MỤC TIÊU:* <br>
Cung cấp thông tin tần số theo thời gian, tức là biết khi nào tần số nào xuất hiện <br>
*ĐẶC ĐIỂM:* <br>
* Dùng wavelet (sóng nhỏ) - Các hàm có thời gian giới hạn 
* Cho phép phân tích tín hiệu ở nhiều độ phân giải khác nhau: tốt ở tần số cao (chi tiết) và tốt ở thời gian dài(thấp)
* Rất phù hợp với tín hiệu phi tuyến, không định trạm , ví dụ như:
  - Tín hiệu y sinh (PPG, ECG,...)
  - Tiếng nói, tiếng chim, âm thanh,... 

# **Biến đổi wavelet hoạt động như thế nào ?** #
## a. Ý tưởng chính ##
Thay vì dùng các sóng sin như trng Fourier, biến đổi Wavelet lại dùng các sóng nhỏ (wavelet), để quét tín hiệu ở các vị trí và các thang đo khác nhau <br>
Tín hiệu được phân tích bằng: 
* Dịch chuyển (translation): Kiểm tra wavelet tại các vị trí khác nhau (trên trục thời gian)
* Co giãn (scaling): Kiểm tra ở nhiều độ phân giải khác nhau, từ thô đến chi tiết 
> Tưởng tưởng như bạn zoom vào 1 ảnh ở nhiều mức độ phóng đại, bạn thấy cả tổng thể lẫn chi tiết 

## b. Các kiểu biến đổi Wavelet trong xử lý tín hiệu ##
Trong xử lý tín hiệu, chủ yếu dùng 2 loại chính:
* Dicrete Wavelet Transform (DWT): Biến đổi Wavelet rời rạc
* Continuous Wavelet Transform (CWT): Biến đổi Wavelet liên tục

### 1. Biến đổi Wavelet liên tục (CWT) ###
#### *Ý tưởng:* #### 
CWT quét tín hiệu bằng 1 wavelet mẹ được co giãn liên tục (thang a) và dịch chuyển liên tục (dịch b). Tức là ta 
kiểm tra tín hiệu ở mọi độ rộng và mọi vị trí - cực kỳ chi tiết <br>
#### *Công thức*: ####
![image](https://github.com/user-attachments/assets/1a9edeac-40d8-49af-bc07-5c5f1c252873)

#### 📊 *Kết quả*: #### 
   - Trả về ma trận 2D: Hàng là thang (scale), cột là thời gian
   - Biểu diễn rất chi tiết về thời gian - tần số
   - Có thể vẽ biểu đồ thời gian đồ thị thời gian - tần số giống như spectrogram nhưng mượt hơn
  ![image](https://github.com/user-attachments/assets/28917c3e-53db-449c-a082-0d98776bc7e0)
#### ✅ *Ưu điểm*: #### 
  - Hiển thị trực quan, đẹp, lý tưởng cho phân tích tín hiệu y sinh và xem biến thiên tín hiệu
  - Không bỏ sót thông tin (do liên tục) <br>
#### ❌ *Nhược điểm*: #### 
  - Rất tốn thời gian và bộ nhớ (vì tính ở mọi a và b)
  - Không dùng trực tiếp cho xử lý hoặc nén (quá dư thừa thông tin) <br>
#### *Ứng dụng*: ####
  - Phân tích dạng sóng (Waveform scalogram)
  - Kiểm tra nhanh vùng có nhiễu, đỉnh, biên
  - Visualize ECG, PCG, PPG theo thời gian - tần số

### 2. Biến đổi Wavelet rời rạc (DWT) ###
#### *Ý tưởng*: #### 
Chỉ lấy một số hữu hạn giá trị của hệ số co giãn và dịch chuyển - thường theo dạng nhị phân:
- scale: a = 2^j (Thang)
- shift: b = k.2^j (Dịch)
Tức là: mỗi tầng phân tích tín hiệu ở độ phân giải thấp hơn gấp đôi

#### *Công thức*: ####
![image](https://github.com/user-attachments/assets/5d394ef4-3957-4d9b-b137-aa0a3045f294)
> Đây là công thức tích chập (Convolution) - nền tảng cốt lõi và là công thức tổng quát trong biến đổi wavelet rời rạc 
> * Với x[k] là tín hiệu đầu vào
> * g[n - k] là đáp ứng xung (là phản ứng của hệ thống để đáp ứng với một số thay đổi bên ngoài, có thể là bộ học hay một hàm gì đó,...) 
> * y[n] là tín hiệu đầu ra 
- Khi thực hiện tích chập x[n] với g[n] bất kỳ, nghĩa là bạn đang áp dụng hệ thống có đáp ứng xung là g[n] lên tín hiệu x[n]
- Trong trường hợp của Wavelet, đáp ứng xung là bộ lọc thông thấp `g[n]` và bộ lọc thông cao `h[n]`, dưới đây là công thức được áp dụng vào việc chia tần số ban đầu
thành các hệ lọc con (subband filters) trong biến đổi wavelet <br>
![image](https://github.com/user-attachments/assets/666b0a68-7cbb-43ca-a76c-7838208d8add)
