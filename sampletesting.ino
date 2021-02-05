#include <avr/io.h>
/** Code used to collect samples as quickly as possible.
	It is currently able to collect 10 samples per period at the
	highest frequency.
	For more information on how the registers were programmed,
	visit http://www.optiloading.be/willem/Arduino/speeding.pdf
*/

const int analogInPin = A0; 
int sensorValue = 0; 


void setup() 
{
  Serial.begin(1000000); //Baud rate for the Serial Monitor

  DDRC= 0b11111110; //sets bit 0 as input

  PORTC=0b00000000; //pullups are disabled

  ADMUX = 0b01100000; //Voltage refrence at AV_cc, connects ADC to A0

  ADCSRA = 0b11000110; //ADC is enabled, bits 3:0 use clock that is divided by 64
}


void loop() 
{  
  long start, finish ;

  start = micros();

  for(int i=0; i<1500; i++){ //makes 1500 samples
  
   int val=analogRead(analogInPin);
   Serial.println(val);  //prints sample
}
 finish= micros()-start;

 Serial.print("time per sample(us): ");
 Serial.println((float)finish/1500); //calculates time per sample
 
 Serial.print("frequency (HZ): ");
 Serial.println((float) 1500*1000000/ finish ); //calculates frequency
 Serial.println();

   while(1);
}
