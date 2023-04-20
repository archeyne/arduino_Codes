#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ArduinoTrace.h"
#include "Circle.h"
#include "Court.h"

class Score
{
  public:

  Circle &circle;
  Adafruit_SSD1306 &display;
  Court court;

  enum {null,s1,s2,s3,s4,s5,s6,s7};
  int step=s1,pstep=null;
  int timer=0;
  bool entry=true;
  bool Q0=0,Q1=0;

  //---------------------------------------
  Score(Circle &circle,Adafruit_SSD1306 &display, int scorex, int scorey);

  int x1=48,x2=74,y1=10,y2=10;
  int scorex, scorey;

  void init();
  void processSeq();
};
