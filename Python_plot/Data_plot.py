import pandas as pd
import matplotlib.pyplot as plt

file_path = r"D:\C-C++_project\WaveletProcess\dwt_test\result_files\cprocess_files\decomp_all\HeartBeat_800Hz_db4dwt2_decomp.csv"

data = pd.read_csv(file_path, header=None)

time = range(len(data))

plt.figure(figsize=(12, 5))
plt.plot(time, data[0], label="Signal", color='green')
plt.title("Signal data plot")
plt.xlabel("Sample index")
plt.ylabel("Amplitude")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()