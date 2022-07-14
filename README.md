<img src="https://img.shields.io/badge/-ATtiny%20Project-blue.svg?&amp;style=flat-square&amp" style="max-width: 100%;"> <img src="https://img.shields.io/badge/-PlattformIO-orange.svg?&amp;style=flat-square&amp" style="max-width: 100%;"> <img src="https://img.shields.io/badge/-Arduino%20IDE-%2300979D.svg?&amp;style=flat-square&amp;logo=arduino&amp;logoColor=white" style="max-width: 100%;">


# General info
[![](https://yt-embed.live/embed?v=dzWNCmG-Q2c)](http://www.youtube.com/watch?v=dzWNCmG-Q2c "DIY Binary Clock")

## Code
- First we use the Arduino IDE and the "setRTCTime-FirstTime.ino" to set the Time on the RTC module.
- Adjust line 31 to the correct time and date and include this line for the first upload. 
- You can check your settings in the serial monitor.
- Than you have to upload this sketch **again but with the line 31 only as comment!!** That's important so that the time and date wouldn't be reseted every time you switch on the Clock.
 
- Now its time to programm the ATtiny with PlatformIO
- Set the pins for the hour LEDs and the shift register for the minute LEDs
- We first convert the binary coded decimal to normal decimal numbers
- Than we get the time and convert the minutes and hours to binary and store it in an array.
- For the hours we turn the LEDs on and of directly with digitalWrite and pinNumber (array).
- For the minutes we turn the LEDs on and of with the shift register.
- The last function resets the shift register so that no old values are displayed when you switch on the clock.
- 


## Hardware
- This DIY binary clock runns on an ATtiny44 combined with a 74HC595N shift register and a RTC Module DS1307.
- We added 100 Ω resistors for the LEDs and a 4,7k Ω for the SDA pin of the ATtiny whitch is connected to the RTC Module (I2C protocoll).

![Verdrahtung](https://github.com/pixelEDI/attiny_binaryclock/blob/main/binaryClockWithShiftRegister_wiring.jpg)


## 3D Case
- The case is small enough to fit in a pocket but at the same time large enough for all the components you need. It is equipped with a M3 threaded insert for 3D printing, so you can open and close the lid as often as you like.

Get the Case:  [thingiverser](https://www.thingiverse.com/thing:5430313)

![Case](https://github.com/pixelEDI/attiny_binaryclock/blob/main/BinaryClock3D.jpg)
