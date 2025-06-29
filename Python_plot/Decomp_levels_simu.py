# Chuong trinh mo phong bien doi DWT
import numpy as np
import pywt
import matplotlib.pyplot as plt

# Tao tin hieu gia lap 
t = np.linspace(0, 1, 1024)
signal = np.sin(20 * 2 * np.pi * t) + 0.5 * np.random.randn(1024)

# Thu nhieu cap phan ra - Mot lan phan ra tuong ung voi 1 lam downsampling
J_values = [1, 2, 3, 4]

fig, axes  = plt.subplots(len(J_values), 2, figsize=(12, 3 * len(J_values)))
fig.suptitle("Mo phong bien doi & tai tao tin hieu voi nhieu cap phan ra (J)", fontsize=14)

for idx, J in enumerate(J_values):
  # Bien doi DWT voi wavelet db4
  coeffs = pywt.wavedec(signal, wavelet="db4", level=J)

  # Ghep lai tin hieu (IDWT)
  reconstructed = pywt.waverec(coeffs, wavelet="db4")

  # Dam bao do dai khop
  reconstructed = reconstructed[:len(signal)]

  # Tinh sai so
  rmse = np.sqrt(np.mean((signal - reconstructed) ** 2))
  corr = np.corrcoef(signal, reconstructed)[0, 1]

  # Ve lai tin hieu goc
  axes[idx, 0].plot(signal, color='blue', label="Tin hieu goc")
  axes[idx, 0].set_title(f'J = {J} | Tin hieu goc')
  axes[idx, 0].set_xlim([0, 1024])

  # Ve lai tin hieu tai tao 
  axes[idx, 1].plot(reconstructed, color='green', label="Tin hieu tai tao")
  axes[idx, 1].set_title(f'J = {J} | Tai tao\nRMSE = {rmse:.4f}, Corr = {corr:.4f}')

plt.tight_layout(rect=[0, 0.03, 1, 0.95])
plt.show()