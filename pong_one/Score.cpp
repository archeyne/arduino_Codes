#include "Score.h"

Score::Score(Circle &circle,Adafruit_SSD1306 &display,int scorex,int scorey):circle(circle),display(display),scorex(scorex),scorey(scorey){}

void Score::init()
{
  display.setCursor(x1,y1);
  display.print("0");
  display.setCursor(x2,y2);
  display.print("0");
}

void Score::processSeq()
{
  do
  {

    bool S0=(circle.x<=court.xmin-circle.r);
    bool S1=(circle.x>=court.xmax+circle.r);

    pstep=step;
    switch(step)
    {
      case s1:
        if (entry)
        {

        }
        if(S0)       
        {
          step=s2;  
        } 
        else if(S1)  
        {
          step=s3;
        }
      break;
      case s2:  
        if (entry)
        {
          timer=1;
        }  
        Q0=1;
        if(timer==0)
        {
          Q0=0;
          step=s1;
        }           
      break;
      case s3:  
        if (entry)
        {
          timer=1;
        }  
        Q1=1;
        if(timer==0)
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

  if(Q1) scorex = scorex + 1;
  if(Q0) scorey = scorey + 1;

  display.setCursor(x1,y1);
  display.print(scorex);
  display.setCursor(x2,y2);
  display.print(scorey);
}