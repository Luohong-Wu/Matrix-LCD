#include "Matrix.h"
#include "LCD.h"

//Pins of MATRIX
#define SER_ROW 19
#define CLK_ROW 18
#define LATCH 17
#define SER_COL 16
#define CLK_COL 15

MATRIX matrix(SER_ROW, CLK_ROW, SER_COL, CLK_COL, LATCH);

//Pins of LCD

#define BACKLIGHT_BLUE 12
#define BACKLIGHT_GREEN 11
#define BACKLIGHT_RED 10
#define SID 9
#define SCLK 8
#define RS 7
#define RST 6
#define CS 5

LCD glcd(SID, SCLK, RS, RST, CS, BACKLIGHT_RED, BACKLIGHT_GREEN, BACKLIGHT_BLUE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //LCD's functions
  glcd.initialize();
  glcd.setBacklight(BLUE);

  // draw a string at location (0,0)
  glcd.writeLine(0, 0, "UPM ETSISI");
  glcd.writeLine(0, 2, "10.128.48.10");
  glcd.display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

}

void loop() {

  // put your main code here, to run repeatedly:
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  // MATRIX's funtions
  matrix.setStack(32);
  //    matrix.setDouble(8.3);
  //    matrix.setInteger(9);
  //   matrix.setLevel(3.2, 7);
  //  matrix.setText("Luohong Wu",5);
  ////////////////////////////////////////////////////////////////////////////////////////////////////




}
