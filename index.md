## Project Summary

This project was done over the course of about one month (November-December 2020). This project is more EE focused as it requires knowledge of circuit elements such as amplifiers, analog to digital conversion, and the Fourier Transform. An overview video of the project can be found [here](https://media.oregonstate.edu/media/t/1_tivwak29). The repository's README also provides a brief summary of the requirements.

### Languages Used and the purpose of each file

sampletesting.ino
- C/C++ Arduino sketch file
- Used to collect audio samples as fast as possible
- Data was exported and post processed in MATLAB to plot the power vs frequency spectrum

AP_Arduino.ino
- C/C++ Arduino sketch file
- After collecting the necessary data for MATLAB, this file was flashed to control the LEDs
- Uses Arduino FFT libraries to detect the musical note being played

PlotScript.m
- MATLAB file
- Performs the FFT based on the ADC values collected from sampletesting.ino
- Calculates the SNR of the system as well as plots the power vs frequency spectrum
