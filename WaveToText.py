import numpy as np

from scipy.io import wavfile
samplerate, data = wavfile.read('/content/drive/MyDrive/Copy of 24.wav')

num_seconds = 6
num_samples = num_seconds * samplerate

if len(data.shape) > 1:
    data = data[:, 0]

data_6_seconds = data[:num_samples]

with open("wafeInfo_6_seconds.txt", "a") as wavFileInfo:
    wavFileInfo.write(str(samplerate)+'\n')
    wavFileInfo.write(str(data_6_seconds.size)+'\n')


#wavFileInfo = open("wafeInfo.txt", "a")
#wavFileInfo.write(str(samplerate)+'\n')
#wavFileInfo.write(str(data.size)+'\n')
#wavFileInfo.close()

print(samplerate)
print(data.size)
print (data)

np.savetxt("waveData_6_seconds.txt", data_6_seconds, fmt="%2.0f")