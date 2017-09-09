#include "Nintendo.h"
/* This code uses the Nicohood Library
 * Use this code at your own risk
 * Code written by Simple Controllers and this code is open source.
 * Meaning its free to share, improve on, or anything you like!
 * Just remember to mention you used my code!
 */
//This makes the controller bidirection data line on pin number3
CGamecubeConsole GamecubeConsole(3);      //Defines a "Gamecube Console" sending data to the console on pin 3
Gamecube_Data_t d = defaultGamecubeData;   //Structure for data to be sent to console

//This is needed but you don't need a controller on pin 7
CGamecubeController GamecubeController1(7);

//This is the pinout of the controller.  Can be changed to your liking.  I may have mixed up some of the tilt pins but you can change that physically in your build or through the code.  Just do test runs along the way.
const int A = 1;
const int B = 2;
const int X = 4;
const int Y = 5;
const int Z = 6;
const int START = 18;

const int R = 8;
const int L = 9;

//This is the value of analog shielding 74 is lightest possible on gamecube.  it varies from gamecube to dolphin no idea why..
//if this does not work on your system or something like that keep raising it by 1 until it works.
const int RLIGHTv = 74;
const int RLIGHT = 36; //doesnt exist

const int X1 = 10;
const int X2 = 11;
const int Y1 = 12;
const int Y2 = 0;

//C-stick
const int CLEFT = 14;
const int CRIGHT = 15;
const int CUP = 16;
const int CDOWN = 17;

void setup()
{
  //This is establishing the pin assignments up there to input pins
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(X, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(Z, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  
  pinMode(R, INPUT_PULLUP);
  pinMode(L, INPUT_PULLUP);
  pinMode(RLIGHT, INPUT_PULLUP);
  
//  pinMode(LEFT, INPUT_PULLUP);
//  pinMode(RIGHT, INPUT_PULLUP);
//  pinMode(UP, INPUT_PULLUP);
//  pinMode(DOWN, INPUT_PULLUP);
  
  pinMode(X1, INPUT_PULLUP);
  pinMode(X2, INPUT_PULLUP);
  pinMode(Y1, INPUT_PULLUP);
  pinMode(Y2, INPUT_PULLUP);
  
  pinMode(CLEFT, INPUT_PULLUP);
  pinMode(CRIGHT, INPUT_PULLUP);
  pinMode(CUP, INPUT_PULLUP);
  pinMode(CDOWN, INPUT_PULLUP);

  //This is needed to run the code.
  GamecubeController1.read();
}

void loop()
{
  //This resets and establishes all the values after the controller sends them to the console and helps with initial "zeroing"
  int pinA = 0;
  int pinB = 0;
  int pinX = 0;
  int pinY = 0;
  int pinZ = 0;
  int pinSTART = 0;

  int pinR = 0;
  int pinL = 0;
  int pinRLIGHT = 0;

  int pinLEFT = 0;
  int pinRIGHT = 0;
  int pinUP = 0;
  int pinDOWN = 0;

  int pinX1 = 0;
  int pinX2 = 0;
  int pinY1 = 0;
  int pinY2 = 0;

  int pinCLEFT = 0;
  int pinCRIGHT = 0;
  int pinCUP = 0;
  int pinCDOWN = 0;

  int pinxAxisC = 128;
  int pinyAxisC = 128;
  
  int pinxAxis = 128;
  int xmod = 0;
  int pinyAxis = 128;
   
  if (digitalRead(X1) == HIGH && digitalRead(X2) == LOW)pinxAxis = 255; //analog right
  if (digitalRead(X1) == LOW && digitalRead(X2) == HIGH)pinxAxis = 0; //analog left
  if (digitalRead(Y1) == HIGH && digitalRead(Y2) == LOW)pinyAxis = 255; // analog up
  if (digitalRead(Y1) == LOW && digitalRead(Y2) == HIGH)pinyAxis = 4; // analog down
  
  //Reads CStick pins, same logic as controlstick values.
  if (digitalRead(CLEFT) == HIGH && digitalRead(CRIGHT) == LOW)pinxAxisC = 255;
  if (digitalRead(CLEFT) == LOW && digitalRead(CRIGHT) == HIGH)pinxAxisC = 0;
  if (digitalRead(CDOWN) == HIGH && digitalRead(CUP) == LOW)pinyAxisC = 255;
  if (digitalRead(CDOWN) == LOW && digitalRead(CUP) == HIGH)pinyAxisC = 0;

  if (digitalRead(A) == LOW)pinA = 1;
  if (digitalRead(B) == LOW)pinB = 1;
  if (digitalRead(X) == LOW)pinX = 1;
  if (digitalRead(Y) == LOW)pinY = 1;
  if (digitalRead(Z) == LOW)pinZ = 1;
  if (digitalRead(START) == LOW)pinSTART = 1;
  if (digitalRead(RLIGHT) == LOW)pinRLIGHT = RLIGHTv;
  if (digitalRead(R) == LOW)pinR = 1;
  if (digitalRead(L) == LOW)pinL = 1;


  //reports data
  d.report.a = pinA;
  d.report.b = pinB;
  d.report.x = pinX;
  d.report.y = pinY;
  d.report.z = pinZ;
  d.report.start = pinSTART;
  d.report.r = pinR;
  d.report.l = pinL;
  d.report.left = pinRLIGHT;
  d.report.xAxis = pinxAxis;
  d.report.yAxis = pinyAxis;
  d.report.cxAxis = pinxAxisC;
  d.report.cyAxis = pinyAxisC;
  //sends the complied data to console when console polls for the input
  GamecubeConsole.write(d);


}

