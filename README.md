# **Phân biệt biến đổi Wavelet và biến đổi Fourier** #
## 1. Biến đổi Fourier (Fourier Transform) ##
*MỤC TIÊU:* <br>
Chuyển tín hiệu từ miền thời gian sang miền tần số <br>
*ĐẶC ĐIỂM:* <br>
* Dùng các hàm sin và cos (sóng hình sin) làm cơ sở để phân tích tín hiệu 
* Giả định tín hiệu là tuần hoàn và kéo dài vô tận 
* Không biết tại thời điểm nào tần số cụ thể nào xuất hiện, chỉ biết có những tần số nào xuất hiện trong tín hiệu <br> 
![image](https://github.com/user-attachments/assets/bc8348da-455f-41b1-afb8-852c4bcdc7f2)

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
Thay vì dùng các sóng sin như trong Fourier, biến đổi Wavelet lại dùng các sóng nhỏ (wavelet), để quét tín hiệu ở các vị trí và các thang đo khác nhau <br>
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
- scale: `a = 2^j` (Thang)
- shift: `b = k.2^j` (Dịch)
Tức là: mỗi tầng phân tích tín hiệu ở độ phân giải thấp hơn gấp đôi (Downsampling) 

#### *Công thức*: ####
![image](https://github.com/user-attachments/assets/5d394ef4-3957-4d9b-b137-aa0a3045f294)
> Đây là công thức tích chập (Convolution) - nền tảng cốt lõi và là công thức tổng quát trong biến đổi wavelet rời rạc 
> * Với `x[k]` là tín hiệu đầu vào
> * `g[n - k]` là đáp ứng xung (là phản ứng của hệ thống để đáp ứng với một số thay đổi bên ngoài, có thể là bộ học hay một hàm gì đó,...) 
> * `y[n]` là tín hiệu đầu ra 
- Khi thực hiện tích chập `x[n]` với `g[n]` bất kỳ, nghĩa là bạn đang áp dụng hệ thống có đáp ứng xung là `g[n]` lên tín hiệu `x[n]`
- Trong trường hợp của Wavelet, đáp ứng xung là bộ lọc thông thấp `g[n]` và bộ lọc thông cao `h[n]`, dưới đây là công thức được áp dụng vào việc chia tần số ban đầu thành các hệ lọc con (subband filters) trong biến đổi wavelet <br>
![image](https://github.com/user-attachments/assets/666b0a68-7cbb-43ca-a76c-7838208d8add)

#### 📊 *Kết quả* ####
Tín hiệu được chia thành:
 - Thành phần xấp xỉ (`Approximation`): thành phần tần số thấp (thô)
 - Thành thần chi tiết (`Details`): thành phần tần số cao (nét, đỉnh)

Như hình ảnh bạn thấy, nó chính là công thức tích chập, nhưng sau đó ta chỉ giữ mỗi giá trị cách 2 mẫu (downsampling) để giảm kích thước dữ liệu <br>
Sau mỗi tầng, phần xấp xỉ - Approximation (**thành phần tần số thấp**) sẽ được tiếp tục phân tích tiếp - tạo thành 1 cây phân rã, cây phân rã này còn được gọi là **filter bank** <br>
![image](https://github.com/user-attachments/assets/b9b24823-e6f3-4310-a35c-3f15d27deaa9)
#### ✅ *Ưu điểm*: #### 
 - Gọn nhẹ, hiệu quả, dễ áp dụng
 - Dễ dàng lọc nhiễu, phát hiện đỉnh, trích xuất đặc trưng
 - Có thể tái tạo lại tín hiệu gốc rõ ràng
#### ❌ *Nhược điểm*: ####
 - DWT truyền thống vốn chỉ phân tách nút hệ số tần thấp (low pass) tại mỗi mức, còn tần cao (high pass) thì không xử lý
 - Có thể bỏ sót một số chi tiết (do lấy mẫu rời rạc)
 - Không hiển thị mượt như CWT
``` yaml
Level 0:         X
                 |
Level 1:       [L]     H
               |
Level 2:     [LL]     LH

```
#### *Ứng dụng*: ####
 - Lọc nhiễu ECG, PPG, PCG
 - Phát hiện đỉnh R trong ECG
 - Trích xuất đặc trưng cho học máy
 - Nén tín hiệu y sinh
#### *Ngoài lề*: ####
DWT chính là một dạng đặc biệt của mã hóa băng con (subband coding), nhưng có thêm một số điều kiện để đảm bảo tái tạo tín hiệu hoàn hảo (perfect reconstruction) <br>
##### Giải thích #####
- Mã hóa băng con là kỹ thuật chia tín hiệu thành các dải tần số con (low-pass và high-pass) → nén hoặc xử lý từng dải
- DWT làm đúng việc đó, nhưng thêm:
   * Bộ lọc orthogonal hoặc biothogonal
   * Downsampling sau lọc để giảm dữ liệu
   * Có thể tái tạo lại tín hiệu gốc từ các hệ số (inverse DWT), gọi là Upsampling 

**Do đó, DWT = mã hóa băng con + downsampling + đảm bảo tái tạo tín hiệu** 

- Tín hiệu khi Upsampling nếu ta không vì mục đích lọc nhiễu thì nó sẽ sử dụng toàn bộ thành phần `Approximation coeff` và `Detail coeff` để khôi phục lại (reconstruct) tín hiệu 
- Bản chất của DWT là để denoise bằng cách khi ta upsampling lại, ta sẽ bỏ đi hoặc giảm trọng số của một vài thành phần tần số của chi tiết (`Detail coeff`) vì nhiễu thường nằm ở tần số cao. Giữ lại `Approximation coeff` vì nó là thành phần chính của tín hiệu 

###  Khi nào nên dùng cái nào ? ###
| Mục tiêu | Nên dùng | Giải thích |
|----------|----------|------------|
|Xem tín hiệu trên không gian thời gian - tần số | CWT | Hiển thị chi tiết các vùng biến đổi |
| Lọc nhiễu tín hiệu PCG, ECG, PPG | DWT | Loại bỏ hệ số chi tiết nhỏ, tái tạo tín hiệu | 
| Trích xuất đặc trưng để đưa vào học máy | DWT | Dễ lượng hóa và lưu trữ |
| Phân tích sâu về nhịp tim, âm tim |  CWT/DWT | Tùy vào mục tiêu trực quan (CWT) hay xử lý (DWT) |

# **Các họ trong Wavelet** # 
Wavelet sinh ra để khắc phục nhược điểm của Biến đổi Fourier: Không thể phân tích tín hiệu theo thời gian - tần số khi tín hiệu biến thiên <br>
Tuy nhiên môi loại tín hiệu lại cần "góc nhìn" riêng: có cái cần độ phân giải thời gian cao, cái cần độ mượt, có cái cần đối xứng,... nên không có "1 wavelet mẹ" nào phù hợp với mọi loại tín hiệu <br>
Vì thế các nhà toán học, kỹ sư đã phát triển ra nhiều họ wavelet, mỗi họ là một dòng "kính lúp đặc biệt" để nhìn tín hiệu theo cách tối ưu cho bài toán cụ thể 

## **Các họ wavelet phổ biến** ## 
| Họ Wavelet | Tên |  Đặc điểm chính | Dùng tốt cho | Nhược điểm |
|------------|-----|-----------------|--------------|------------|
| Haar | `db1` | Đơn giản nhất, không trơn, phi đối xứng, phản ứng tốt với biên | Tín hiệu rời rạc, nhảy đột ngột, phân tích thô, ảnh | Gây méo tín hiệu, không mượt |
| Daubechies | `dbN` | Rất phổ biến, mượt, không đối xứng, ngắn, được định nghĩa bằng bộ lọc tuyến tính (filter coefficients), số momemt tăng theo bậc -> Giữ được nhiều thông tin hơn| Tín hiệu sinh học, speech (âm thanh) |   |
| Symlets | `symN` | Gần giống Daubechies nhưng đối xứng hơn | Tránh lêch pha, giữ biên dạng | | 
| Coiflets | `coifN` | Giữ moment tốt hơn, cân bằng hài hòa | Nén dữ liêu, xử lý sinh học | | 
| Biorthogonal | `biorX.Y` | Có hai loại wavelet mẹ: phân tích và tái tạo, đối xứng hoàn toàn | Nén ảnh (JPEG 2000), truyền thông | | 
| Meyer, Morlet, Mexican Hat | Liên tục, dùng trong CWT | Phân tích tần số - thời gian chính xác |  |  | 

### Momemt (Moment triệt tiêu) là gì ? ###

Moment của 1 hàm là các phép đó định lượng nhất định liên quan đến hình dạng của đồ thị <br>
Moment trong toán học là đại lượng thể hiện đặc tính tổng quát của một hàm theo kiểu thống kê:
> * Moment bậc 0: Tổng của tất cả các giá trị 
> * Moment bậc 1: Trung bình (mean)
> * Moment bậc 2: Phương sai (variance)
> * ....
> * Moment bậc n: Đo sự thay đối của hàm theo cấp số n

Nói đơn giản, moment giúp ta đo "hình dạng" hoặc "tính chất" của tín hiệu ở mức độ sâu hơn
* Một wavelet được gọi là có n moment (triệt tiêu) nếu tích phân của wavelet với bất kỳ đa thức bậc < n đều bằng 0 (trả hết giá trị về 0)

> Hay dễ hiểu hơn, Wavelet có n moment triệt tiêu thì nó không "nhìn thấy" hay "nhạy cảm" hoặc "Phản ứng" với các tín hiệu mượt mà, biến đổi chậm (như đa thức tuyến tính, bậc 2,...), chỉ "nhạy cảm" với các tín hiệu có độ biến động nhanh, mạnh (biến thiên đột ngột)
* Moment triệt tiêu càng cao thì khả năng lọc nhiễu càng tốt, làm mượt tín hiệu tốt hơn (do không phản ứng với các thành phần mượt, giao động ít), bắt được các chi tiết nhỏ, thay đổi đột ngột, giúp mô tả chính xác các đặc trưng cục bộ. 
* Ngoài ra còn loại bỏ tốt nhiễu nền hoặc baseline mượt (Ví dụ như trong ECG có **nhiễu trôi nền** (baseline drift) dạng đường cong mượt do ảnh hưởng bởi di chuyển và môi trường xung quanh)
![image](https://github.com/user-attachments/assets/8b538ad9-bce8-426e-b85d-593991f6749f)


