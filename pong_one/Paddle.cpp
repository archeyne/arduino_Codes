#include "Paddle.h"

Paddle::Paddle(Adafruit_SSD1306 &display,int x,int y):display(display),x(x),y(y){}


void Paddle::init()
{
  display.fillRect(x,y,w,h,WHITE);
}

void Paddle::movSeq()
{
  do
  {
    pstep=step;
    switch(step)
    {
      case s1:
        if(entry)
        {

        }
        Q1=1;
        if(y<=court.ymin+1)
        {
          Q1=0;
          step=s2;  
        } 
      break;
      case s2:  
        if (entry)
        {

        }  
        Q0=1;
        if(y>=court.ymax-h-1)
        {
          Q0=0;
          step=s1;
        }           
      break;
    }//end switch

    if(step!=pstep)
    {
      entry=true;
    }
    else
    {
      entry=false;
    }
  }while(step!=pstep);
 
  if(timer>0)timer--;

  if(Q0) y=y+incY;
  if(Q1) y=y-incY;

  display.fillRect(x,y,w,h,WHITE);
}


void Paddle::movSeqB()
{
  do
  {
    pstep=step;
    switch(step)
    {
      case s1:
        if(entry)
        {

        }
        Q0=1;
        if(y>=court.ymax-h-1)
        {
          Q0=0;
          step=s2;  
        } 
      break;
      case s2:  
        if (entry)
        {

        }  
        Q1=1;
        if(y<=court.ymin+1)
        {
          Q1=0;
          step=s1;
        }           
      break;
    }//end switch

    if(step!=pstep)
    {
      entry=true;
    }
    else
    {
      entry=false;
    }
  }while(step!=pstep);
 
  if(timer>0)timer--;

  if(Q0) y=y+incY2;
  if(Q1) y=y-incY2;

  display.fillRect(x,y,w,h,WHITE);
}