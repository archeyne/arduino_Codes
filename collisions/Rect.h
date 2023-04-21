#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ArduinoTrace.h"

class Rect
{
  public:
  Adafruit_SSD1306 &display;
  enum {null,s1,s2,s3,s4,s5,s6,s7};
  int step=s1,pstep=null;
  int timer=0;
  bool entry=true; 
  bool Q0=0,Q1=0;
  
  int incX=2,incY=-2;
  int x,y,a=12,l=12;;       //posicion centro del circulo y radio
  //------------------------------------------------------
  Rect (Adafruit_SSD1306 &display,int x,int y);
  void init();
  void seq();
};