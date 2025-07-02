import matplotlib.pyplot as plt
import numpy as np
import csv

# Hàm đọc dữ liệu từ file CSV
def read_signal_from_csv(filename):
    signal = []
    with open(filename, 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            if row:  # bỏ qua dòng trống
                signal.append(float(row[0]))
    return np.array(signal)

# Đọc tín hiệu
original = read_signal_from_csv(r"D:\C-C++_project\WaveletProcess\Data_text\PCG_samples\NoFilter\HeartBeat_raw\800Hz\test2.csv")
denoised = read_signal_from_csv(r"D:\C-C++_project\WaveletProcess\dwt_test\result_files\pytprocess_files\reconstructed_files\HeartBeat_800Hz_db4dwt2.csv")

# Đảm bảo độ dài bằng nhau (nếu cần)
min_len = min(len(original), len(denoised))
original = original[:min_len]
denoised = denoised[:min_len]

# Vẽ đồ thị
plt.figure(figsize=(14, 5))
plt.plot(original, label='Tín hiệu gốc', color='gray', alpha=0.7)
plt.plot(denoised, label='Tín hiệu sau xử lý (wavelet)', color='blue', linewidth=2)
plt.title("So sánh tín hiệu gốc và sau xử lý bằng Wavelet")
plt.xlabel("Chỉ số mẫu (Sample Index)")
plt.ylabel("Biên độ (Amplitude)")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
