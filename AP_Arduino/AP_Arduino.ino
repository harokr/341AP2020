/*
 File/Sketch Name: AudioFrequencyDetector
 Version No.: v1.0 Created 12 December, 2019
 
 Original Author: Clyde A. Lettsome, PhD, PE, MEM
 
 Description:  This code/sketch makes displays the approximate frequency of the loudest sound detected by a sound detection module. For this project, the analog output from the 
 sound module detector sends the analog audio signal detected to A0 of the Arduino Uno. The analog signal is sampled and quantized (digitized). A Fast Fourier Transform (FFT) is
 then performed on the digitized data. The FFT converts the digital data from the approximate discrete-time domain result. The maximum frequency of the approximate discrete-time
 domain result is then determined and displayed via the Arduino IDE Serial Monitor.
 Note: The arduinoFFT.h library needs to be added to the Arduino IDE before compiling and uploading this script/sketch to an Arduino.
 License: This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License (GPL) version 3, or any later
 version of your choice, as published by the Free Software Foundation.
 Notes: Copyright (c) 2019 by C. A. Lettsome Services, LLC
 For more information visit https://clydelettsome.com/blog/2019/12/18/my-weekend-project-audio-frequency-detector-using-an-arduino/
*/

#include "arduinoFFT.h"
 
#define SAMPLES 128             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 1046 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;

int led1 = 5; //Corresponding LED Pin, D2
int led2 = 6; //Corresponding LED Pin, D3
int led3 = 7; //Corresponding LED Pin, D4
int led4 = 8; //Corresponding LED Pin, D5
int led5 = 9; //Corresponding LED Pin, D6
int led6 = 10; //Corresponding LED Pin, D7
int led7 = 11; //Corresponding LED Pin, D8
int led8 = 12; //Corresponding LED Pin, D9

 
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values
 
void setup() 
{
    Serial.begin(115200); //Baud rate for the Serial Monitor
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
    pinMode(led1, OUTPUT); // modify LED1 to be an output
    pinMode(led2, OUTPUT); // modify LED2 to be an output
    pinMode(led3, OUTPUT); // modify LED3 to be an output
    pinMode(led4, OUTPUT); // modify LED4 to be an output
    pinMode(led5, OUTPUT); // modify LED5 to be an output
    pinMode(led6, OUTPUT); // modify LED6 to be an output
    pinMode(led7, OUTPUT); // modify LED7 to be an output
    pinMode(led8, OUTPUT); // modify LED8 to be an output


}
 
void loop() 
{  
    /*Sample SAMPLES times*/
    for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[i] = analogRead(3); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[i] = 0; //Makes imaginary term 0 always

        /*remaining wait time between samples if necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    /*Perform FFT on samples*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    /*Find peak frequency and print peak*/
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    Serial.println(peak);     //Print out the most dominant frequency.

    
    if(peak >= 260.32185 && peak < 292.1917){
      digitalWrite(led1, HIGH); // this will turn on LED1
    }

    else if(peak >= 292.1917 && peak < 327.98185 ){
      digitalWrite(led2, HIGH); // this will turn on LED2
    }
    
    else if(peak >= 327.98185 && peak < 347.48385){
      digitalWrite(led3, HIGH); // this will turn on LED3
    }

    else if(peak >= 347.48385 && peak < 390.04){
      digitalWrite(led4, HIGH); // this will turn on LED4
    }
    
    else if(peak >= 390.04 && peak < 437.80){
      digitalWrite(led5, HIGH); // this will turn on LED5
    }

    else if(peak >= 437.80 && peak < 491.4106){
      digitalWrite(led6, HIGH); // this will turn on LED6
    }
    
    else if(peak >= 491.4106 && peak < 520.634745){
      digitalWrite(led7, HIGH); // this will turn on LED7
    }

    else if(peak >= 520.634745 && peak <= 525.867255){
      digitalWrite(led8, HIGH); // this will turn on LED8
    }

    else{
       digitalWrite(led1, LOW); // this will turn off the LED
       digitalWrite(led2, LOW); // this will turn off the LED
       digitalWrite(led3, LOW); // this will turn off the LED
       digitalWrite(led4, LOW); // this will turn off the LED
       digitalWrite(led5, LOW); // this will turn off the LED
       digitalWrite(led6, LOW); // this will turn off the LED
       digitalWrite(led7, LOW); // this will turn off the LED
       digitalWrite(led8, LOW); // this will turn off the LED
          
    }
 
    /*Script stops here. Hardware reset required.*/
    //while (5); //do one time
    delay(200);
}
