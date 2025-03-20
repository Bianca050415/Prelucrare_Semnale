import numpy as np
from scipy.signal import hilbert
import sys

input_file = "waveData_6_seconds.txt"
output_file = "envelopeData.txt"

wave_data = np.loadtxt(input_file)

analytic_signal = hilbert(wave_data)
amplitude_envelope = np.abs(analytic_signal)

np.savetxt(output_file, amplitude_envelope, fmt='%.6f')
print(f"Anvelopa semnalului salvata in {output_file}")