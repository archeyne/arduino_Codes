#pragma once

#include "Court.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ArduinoTrace.h"
#include "Paddle.h"

class Circle
{
  public:
  Court court;
  Paddle &paddle;
  Paddle &paddle2;
  Adafruit_SSD1306 &display;
  enum {null,s1,s2,s3,s4,s5,s6,s7};
  int step=s1,pstep=null;
  int timer=0;
  bool entry=true;
  bool Q0=0,Q1=0;
  bool A0=0,A1=0,A2=0,A3=0;

  int incX=2,incY=2;
  int x=6,y=6,r=3;   //posicion centro del circulo y radio
  //int d=r+r;
  //------------------------------------------------------
  Circle (Adafruit_SSD1306 &display,Paddle &paddle,Paddle &paddle2,int x,int y);
  void init();
  void seq();
};