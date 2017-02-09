// UTFT_Demo_480x320 (C)2013 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made for modules with a screen resolution
// of 480x320 pixels.
//
// This program requires the UTFT library.
//

#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
UTFTGLUE myGLCD(0x9488, A2, A1, A3, A4, A0);

uint32_t targetTime = 0;                    // for next 1 second timeout
int ss = 0;
int mm = 0;
int hh = 0;
int omm = -1;
int sheight;
int swidth;
String smm;


void setup() {
  // Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setTextSize(1);
  myGLCD.setRotation(180);
  //  myGLCD.setBackColor(64, 64, 64);
  sheight = myGLCD.height();
  swidth = myGLCD.width();
  targetTime = millis() + 1000;
  myGLCD.clrScr();
}

void loop()
{
  count_time();
}

void refresh() {
  d_time();
}

void count_time() {
  if (targetTime < millis()) {
    // Set next update for 1 second later
    targetTime = millis() + 1000;

    // Adjust the time values by adding 1 second
    ss++;              // Advance second
    if (ss == 60) {    // Check for roll-over
      ss = 0;          // Reset seconds to zero
      omm = mm;        // Save last minute time for display update
      mm++;            // Advance minute
      if (mm > 59) {   // Check for roll-over
        mm = 0;
        hh++;          // Advance hour
        if (hh > 23) { // Check for 24hr roll-over (could roll-over on 13)
          hh = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
        }
      }
    }
    if (omm != mm) refresh();
  }
}

void d_time() {
  myGLCD.setTextSize(10);
  myGLCD.clrScr();
  omm++;
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

