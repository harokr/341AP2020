
%%Code based on the "Noisy Signal" example from Mathworks
%for more information, visit
%https://www.mathworks.com/help/matlab/ref/fft.html
%% Read ADC Values from files
clear,clc,clear all

file = dlmread('voltagesamples.csv') * 5 / 1023; 
%This file contains 1500 samples and will be used for the FFT
file2 = dlmread('shortsample.csv') * 5 / 1023; 
%This file contains about 80 samples, and is used to plot the voltages

for i = 1:numel(file2)
   
    time(i) = 181*i/1000000;
	%181 is the calculated time per sample
	%in microseconds
end

%% Plot Voltage over sample count
subplot(3,1,1)
plot(time, smoothdata(file2));
title('Audio Data')
xlabel('Time (s)')
ylabel('Voltage (V)');

%% SNR calculation
subplot(3,1,2)
snr(smooth(file,0.01,'rloess'), 5500)

%% FFT
%The next few lines normalize the signal data
%If these were omitted, there would be an offsetting
%spike at 0Hz
file = double(file);
mean = mean(file, 'all');
file = file - mean;
file = normalize(file);
Fs = 5524; %Value based on measurement perfomed in Arduino IDE
T = 1/Fs;
L =1500;
Y = fft(file);
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = Fs*(0:(L/2))/L;
subplot(3,1,3)
plot(f,P1) 
title('Single-Sided Amplitude Spectrum')
xlabel('Frequency (Hz)')
ylabel('Amplitude');

 