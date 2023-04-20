#pragma once

#include "Court.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ArduinoTrace.h"

class Paddle
{
  public:
  Court court;
  Adafruit_SSD1306 &display;
  enum {null,s1,s2,s3,s4,s5,s6,s7};
  int step=s1,pstep=null;
  int timer=0;
  bool entry=true;
  bool Q0=0,Q1=0;

  int incY=2;
  int incY2=2;

  int x,y,w=2,h=18;   //posicion, ancho y alto
  //---------------------------------------------
  Paddle (Adafruit_SSD1306 &display,int x,int y);
  void init();
  void movSeq();
  void movSeqB();

};