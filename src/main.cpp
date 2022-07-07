/*
        _          _ ______ _____ _____ 
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |  
 | '_ \| \ \/ / _ \ |  __| | |  | || |  
 | |_) | |>  <  __/ | |____| |__| || |_ 
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |                                    
 |_|                                    
                             
www.pixeledi.eu | twitter.com/pixeledi
Binary Clock | V1.0 | 06/2022

*/

#include <Arduino.h>

// according to the datasheet an external pullup resistor with 4,7k Ohm at SDA for I2C is required.
// The RTC module returns a binary coded decimal (halfbyte), this is converted.

#include <TinyWireM.h>
#define DS1307_ADDR 0x68 // i2c adress for the rtc module

const byte hour1 = 0;
const byte hour2 = 1;
const byte hour4 = 2;
const byte hour8 = 3;

const byte shiftPin = 10; // SHCP or SRCLK
const byte storePin = 9;  // STCP or RSLK
const byte dataPin = 8;   // DS or SER

int clockArray[6] = {1, 2, 4, 8, 16, 32};
int binaryMinutesArray[6];
int binaryHoursArray[4];
uint8_t seconds, minutes, hours, day_of_week, days, months, years, PM, hour12, DST; // time

// Convert binary coded decimal to normal decimal numbers
uint8_t bcdToDec(uint8_t val)
{
  return ((val / 16 * 10) + (val % 16));
}

void getTime(){

  //reset DS1307 register pointer
  TinyWireM.beginTransmission(DS1307_ADDR);
  TinyWireM.send(0);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(DS1307_ADDR,3);
  seconds = bcdToDec(TinyWireM.receive());
  minutes = bcdToDec(TinyWireM.receive());
  hours = bcdToDec(TinyWireM.receive());

}

void decimalMinutesToBinary(){

  for(int i =5; i>=0; i--){

    if(minutes>=clockArray[i]){
      binaryMinutesArray[i]=1;
      minutes = minutes - clockArray[i];
    }
    else {
      binaryMinutesArray[i]=0;
    }

  }
}

void decimalhourToBinary(){

 for(int i =3; i>=0; i--){

    if(hours>=clockArray[i]){
 
      binaryHoursArray[i]=1;
      hours = hours - clockArray[i];
    }
    else {
      binaryHoursArray[i]=0;
    }

  }
}

void hourToLed(){
  digitalWrite(hour8, binaryHoursArray[3]);
  digitalWrite(hour4, binaryHoursArray[2]);
  digitalWrite(hour2, binaryHoursArray[1]);
  digitalWrite(hour1, binaryHoursArray[0]);
}

void minutesToLED(){
   digitalWrite(storePin, LOW);

  for (byte i = 0; i < 6; i++)
  {
    digitalWrite(shiftPin, LOW);
    digitalWrite(dataPin, binaryMinutesArray[i]);
    digitalWrite(shiftPin, HIGH);
  }
  // activate pattern/output
  digitalWrite(storePin, HIGH);
}

void resetShiftregister()
{
  digitalWrite(storePin, LOW);

  for (byte i = 0; i < 6; i++)
  {
    digitalWrite(shiftPin, LOW);
    digitalWrite(dataPin, 0);
    digitalWrite(shiftPin, HIGH);
  }
  // activate pattern/output
  digitalWrite(storePin, HIGH);
}

void setup()
{
  TinyWireM.begin();

  // shiftregister
  pinMode(shiftPin, OUTPUT);
  pinMode(storePin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(hour1, OUTPUT);
  pinMode(hour2, OUTPUT);
  pinMode(hour4, OUTPUT);
  pinMode(hour8, OUTPUT);

  resetShiftregister();

  
  // Test the wiring and shiftregister
  // for (byte i = 0; i < 6; i++)
  // {
  //   digitalWrite(storePin, LOW);
  //   digitalWrite(shiftPin, LOW);
  //   digitalWrite(dataPin, 1);
  //   digitalWrite(shiftPin, HIGH);
  //   // activate pattern/output
  //   delay(1000);
  //   digitalWrite(storePin, HIGH);
  // }

  // delay(1000);
  // digitalWrite(hour1, HIGH);
  // delay(1000);
  // digitalWrite(hour2, HIGH);
  // delay(1000);
  // digitalWrite(hour4, HIGH);
  // delay(1000);
  // digitalWrite(hour8, HIGH);
  
}

void loop()
{
  getTime();
  decimalMinutesToBinary();
  minutesToLED();
  hours = hours%12 == 0? 12 : hours%12;
  decimalhourToBinary();
  hourToLed();
  delay(1000);
}