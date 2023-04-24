#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ArduinoTrace.h"

class Menu
{
  public:
  Adafruit_SSD1306 &display;
  enum {null,s1,s2,s3,s4,s5,s6,s7};
  int step=s1,pstep=null;
  int timer=0;
  bool entry=true;
  bool Q0=0,Q1=0,Q2=0,Q3=0;

  String menuItem[3]={"HOLA","KOLA","ROLA"};

  //------------------------------------------------------
  Menu (Adafruit_SSD1306 &display);
  void init();
  void itemDisplay(int item,bool highlight);
  int itemPosX[3]={5,5,5};
  int itemPosY[3]={5,25,45};
  void seq();
};