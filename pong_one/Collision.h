#pragma once

#include "Circle.h"
#include "Paddle.h"
#include "ArduinoTrace.h"

class Collision
{
  public:

  Circle &circle;
  Paddle &paddle;

  enum {null,s1,s2,s3,s4,s5,s6,s7};
  int step=s1,pstep=null;
  int timer=0;
  bool entry=true;

  //---------------------------------------
  Collision(Circle &circle,Paddle &paddle);
  void processSeq();
  void processSeqB();

};