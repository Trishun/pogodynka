// Imports
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
#include <Wire.h>
#include <DS3231.h>

// inits
UTFTGLUE myGLCD(0x9488, A2, A1, A3, A4, A0);
DS3231 clock;
RTCDateTime dt;

int sheight;
int swidth;

int hh;
int mm;
int ss;
float temp, otemp;
String RTCTime;


void setup() {
  // Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setTextSize(1);
  myGLCD.setRotation(180);
  sheight = myGLCD.height();
  swidth = myGLCD.width();
  myGLCD.clrScr();

  clock.begin();

  // Clock set to compilation date
  clock.setDateTime(__DATE__, __TIME__); //to do: comparison if newer
  //  count_time();
  //  refresh();

}

void loop()
{
  count_time();
  count_temp();
}

void refresh() {
  myGLCD.clrScr();
  d_time();
  d_temp();
}

void count_temp() {
  clock.forceConversion();
  temp = clock.readTemperature();
  if (temp != otemp) {
    refresh();
    otemp = temp;
  }

}

void d_temp() {
  myGLCD.setTextSize(4);
  myGLCD.printNumF(temp, 2, 15, 200);
}

void count_time() {
  dt = clock.getDateTime();
  RTCTime = clock.dateFormat("H:i", dt);
  hh = dt.hour;
  mm = dt.minute;
  if (dt.second == 0) {
    refresh();
    delay(50);
  }
}

void d_time() {
  myGLCD.setTextSize(10);


  //  myGLCD.print(RTCTime, 15, 40);

  if (hh < 10) {
    myGLCD.printNumI(0, 15, 40);
    myGLCD.printNumI(hh, 75, 40);
  }
  else
    myGLCD.printNumI(hh, 15, 40);
  myGLCD.print(":", 135, 40);
  if (mm < 10) {
    myGLCD.printNumI(0, 195, 40);
    myGLCD.printNumI(mm, 255, 40);
  }
  else myGLCD.printNumI(mm, 195, 40);

}

