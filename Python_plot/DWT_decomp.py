import numpy as np 
import matplotlib.pyplot as plt
import pywt 
import csv

# === Cau hinh ====
wavelet_name = "db4" # Thay doi ho wavelet tai day 
level = 4  # So cap phan ra 
input_file = r"D:/C-C++_project/WaveletProcess/Data_text/PCG_samples/noFilter/HeartBeat_raw/1000Hz/test2.csv"

output_approx = r"D:\C-C++_project\WaveletProcess\dwt_test\result_files\pytprocess_files\approx_files/output.csv"

output_details = [r"D:\C-C++_project\WaveletProcess\dwt_test\result_files\pytprocess_files\detail_files/D4.csv", 
                  r"D:\C-C++_project\WaveletProcess\dwt_test\result_files\pytprocess_files\detail_files/D3.csv", 
                  r"D:\C-C++_project\WaveletProcess\dwt_test\result_files\pytprocess_files\detail_files/D2.csv",
                  r"D:\C-C++_project\WaveletProcess\dwt_test\result_files\pytprocess_files\detail_files/D1.csv"] # Luu cac he so chi tiet 

# === DOC DU LIEU CSV ===
signal = np.loadtxt(input_file, delimiter=',')

# === DWT phan ra ===
coeffs = pywt.wavedec(signal, wavelet= wavelet_name, level=level)

# coeffs = [A4, D4, D3, D3, D2, D1] -> Tuong ung voi wt->output trong C 

# === Luu ket qua ra CSV ===

# Approximation Coefficients 
np.savetxt(output_approx, coeffs[0], delimiter=',')

# Details Coefficients 
for i in range(1, len(coeffs)):
  np.savetxt(output_details[i - 1], coeffs[i], delimiter=',')

# === Ve bieu do ===
plt.figure(figsize=(12, 8))

plt.subplot(level + 2, 1, 1)
plt.plot(signal)
plt.title("Orginal signal")

plt.subplot(level + 2, 1, 2)
plt.plot(coeffs[0])
plt.title(f"Approximation Coefficients A{level}")

for i in range(1, len(coeffs)):
  plt.subplot(level + 2, 1, i + 2)
  plt.plot(coeffs[i], color="green")
  plt.title(f"Details Coefficients D{level - i + 1}")

plt.tight_layout()
plt.show()
