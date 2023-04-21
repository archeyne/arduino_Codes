#include "Rect.h"

Rect::Rect (Adafruit_SSD1306 &display,int x,int y):display(display),x(x),y(y){}

void Rect::init()
{
  randomSeed(analogRead(0));
  x = random(0,115);
  y = random(0,51);
  display.drawRect(x,y,a,l,WHITE);
  
}

void Rect::seq()
{
  do
  {
    pstep=step;
    switch(step)
    {
      case s1:
        if(entry)
        {
          Q0=0;
          Q1=0;
        }
        if(x<=0)
        {
          step=s2;  
        } 
        else if(x>=115)
        {
          step=s3;
        }
        else if(y<=0)
        {
          step=s4;
        }
        else if(y>=51)
        {
          step=s5;
        }        
      break;
      case s2:  
        if (entry)
        {
          Q0=1;
          x=1;
          timer=1;
        }  
        if(timer==0)
        {
          step=s1;
        }           
      break;
      case s3:  
        if (entry)
        {
          Q0=1;
          x=114;
          timer=1;
        }    
        if(timer==0)
        {
          step=s1;
        }         
      break;
      case s4:  
        if (entry)
        {
          Q1=1;
          y=1;
          timer=1;
        }  
        if(timer==0)
        {
          step=s1;
        }           
      break;
      case s5:  
        if (entry)
        {
          Q1=1;
          y=50;
          timer=1;
        }    
        if(timer==0)
        {
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

  if(Q0) incX=-incX;
  if(Q1) incY=-incY;

  x=x+incX;
  y=y+incY;

  display.drawRect(x,y,a,l,WHITE);
}