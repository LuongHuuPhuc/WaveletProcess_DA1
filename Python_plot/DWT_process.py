import pywt
import pandas as pd
import numpy as np


def dwt_reconstruct(input_file, output_file, wavelet='db4', level=None):
    # Đọc file tín hiệu từ CSV (giả sử cột đầu tiên là tín hiệu)
    data = pd.read_csv(input_file, header=None)
    signal = data.iloc[:, 0].values  # Lấy cột đầu tiên

    # Thực hiện phân rã DWT
    coeffs = pywt.wavedec(signal, wavelet=wavelet, level=level)

    # Để biết số cấp phân rã
    num_levels = len(coeffs) - 1
    print(f"Số cấp phân rã: {num_levels}")

    # In thông tin từng hệ số
    for i, c in enumerate(coeffs):
        if i == 0:
            print(f"A{num_levels} (Approximation cấp cao nhất): {len(c)} mẫu")
        else:
            print(f"D{num_levels - i + 1} (Detail cấp {num_levels - i + 1}): {len(c)} mẫu")

    # Tái tạo tín hiệu từ toàn bộ các hệ số
    reconstructed_signal = pywt.waverec(coeffs, wavelet=wavelet)

    # Do waverec có thể sinh ra tín hiệu dài hơn do padding, cắt lại cho đúng độ dài gốc
    reconstructed_signal = reconstructed_signal[:len(signal)]

    # Xuất ra file CSV
    output = pd.DataFrame(reconstructed_signal)
    output.to_csv(output_file, index=False, heade=False)

    print(f"Đã lưu tín hiệu tái tạo vào: {output_file}")


# 👉 Thay đổi đường dẫn file phù hợp
input_file = r"D:/C-C++_project/WaveletProcess/Data_text/PCG_samples/noFilter/HeartBeat_raw/800Hz/test2.csv"
output_file = r"D:\C-C++_project\WaveletProcess\dwt_test\result_files\pytprocess_files\reconstructed_files/output.csv"

# Gọi hàm
dwt_reconstruct(input_file, output_file, wavelet='db4', level=4)
