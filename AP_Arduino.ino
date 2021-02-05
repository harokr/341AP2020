/*
 * Orignal Author: Clyde A. Lettsome, PhD, PE, MEM
 * Alterations by Kris Haro, Francisco Velasco, and Maxim Feoktistov
 * Team 16's alterations speed up the ADC clock speed and added 
 * a section based on the value of the frequency after the FFT
 * calculation.
 * Lettsome's work is also based on the examples provided by
 * the Arduino FFT library. For Lettsome's orignal code and the
 * Arduino FFT examples, visit
 * the link in the footnote, as well as
 * https://github.com/kosme/arduinoFFT
*/
#include "arduinoFFT.h"
 
#define SAMPLES 128 //SAMPLES-pt FFT. Max 128 for Arduino Nano 328
#define SAMPLING_FREQUENCY 1046
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;

int led1 = 5; //Corresponding LED Pin
int led2 = 6; //Corresponding LED Pin
int led3 = 7; //Corresponding LED Pin
int led4 = 8; //Corresponding LED Pin
int led5 = 9; //Corresponding LED Pin
int led6 = 10; //Corresponding LED Pin
int led7 = 11; //Corresponding LED Pin
int led8 = 12; //Corresponding LED Pin

 
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
    sbi(ADCSRA,ADPS2) ; //64 prescaler for speeding up analogRead
    sbi(ADCSRA,ADPS1) ;
    cbi(ADCSRA,ADPS0) ;
}
 
void loop() 
{  
    /*Sample SAMPLES times*/
    for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros(); //Finds elapsed time     
     
        vReal[i] = analogRead(0); 
		//Reads the value from analog pin 0 (A0), 
		//quantize it and save it as a real term.
        vImag[i] = 0; //Makes imaginary term 0 always

        /*remaining wait time between samples if necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    /*Perform FFT on samples*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //Weigh data
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD); //Compute FFT, this would be the
	//equivalent of MATLAB's fft function
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES); //Computes the magnitudes
	//in the frequency domain

    /*Find peak frequency and print peak*/
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    Serial.println(peak);     //Print out the most dominant frequency.

    //Turn on LED based on the value of peak
       if(peak >= 251 && peak < 271){
      digitalWrite(led1, HIGH); // this will turn on LED1
    }

    else if(peak >= 283 && peak < 303 ){
      digitalWrite(led2, HIGH); // this will turn on LED2
    }
    
    else if(peak >= 319 && peak < 339){
      digitalWrite(led3, HIGH); // this will turn on LED3
    }

    else if(peak >= 339 && peak < 359){
      digitalWrite(led4, HIGH); // this will turn on LED4
    }
    
    else if(peak >= 382 && peak < 402){
      digitalWrite(led5, HIGH); // this will turn on LED5
    }

    else if(peak >= 430 && peak < 450){
      digitalWrite(led6, HIGH); // this will turn on LED6
    }
    
    else if(peak >= 483 && peak < 503){
      digitalWrite(led7, HIGH); // this will turn on LED7
    }

    else if(peak >= 513 && peak <= 533){
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
    delay(1000);
    //Turn off all LEDs before sampling again
    digitalWrite(led1, LOW); 
    digitalWrite(led2, LOW); 
    digitalWrite(led3, LOW); 
    digitalWrite(led4, LOW); 
    digitalWrite(led5, LOW); 
    digitalWrite(led6, LOW); 
    digitalWrite(led7, LOW); 
    digitalWrite(led8, LOW); 
 
    
    delay(200);
}
