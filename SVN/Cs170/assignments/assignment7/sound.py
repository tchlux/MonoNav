import math
import wave
import struct
import sys
import random


SAMPLE_WIDTH = 2
MAX_SAMPLE = 2 ** ((8 * SAMPLE_WIDTH) - 1) - 1
CONCERT_A = 440
STEPS_IN_OCTAVE = 12
SAMPLES_PER_SECOND = 44100

class Sound:

    def __init__(self, sample_rate):
        self.sample_rate = sample_rate
        self.samples = []

    def add_sample(self, sample):
        if sample < -1 or sample > 1:
            raise ValueError("sample must be between -1 and 1")
        self.samples.append(sample)

    def write(self, file_name):
        wav = wave.open(file_name, "wb")
        wav.setnchannels(1)
        wav.setsampwidth(SAMPLE_WIDTH)
        wav.setframerate(self.sample_rate)
        waveData = [int(sample * MAX_SAMPLE) for sample in self.samples]
        waveData = struct.pack("h" * len(self.samples), *waveData)
        wav.writeframes(waveData)
        wav.close()

def create_sound():
    sample_rate = 44100
    number_of_seconds = 1 
    number_of_samples = number_of_seconds * sample_rate
    sound = Sound(sample_rate)
    pitch = 0.1
    for iterator in range(number_of_samples):
        sound.add_sample(math.sin(iterator * pitch))
    sound.write("output.wav")

if __name__ == "__main__":
    create_sound()


