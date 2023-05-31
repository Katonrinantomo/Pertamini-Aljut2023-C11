#include <Arduino.h>


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for(int i=1000; i<=1000000; i+=1000) {
   Serial.println(i);
   delay(10000); 
  }
}
