#include "Circle.h"

Circle::Circle (Adafruit_SSD1306 &display,int x,int y):display(display),x(x),y(y){}

void Circle::init()
{
  randomSeed(analogRead(0));
  x = random(6,121);
  y = random(6,56);
  display.fillCircle(x,y,r,WHITE);
  
}

void Circle::seq()
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
        if(x<=6)
        {
          step=s2;  
        } 
        else if(x>=121)
        {
          step=s3;
        }
        else if(y<=6)
        {
          step=s4;
        }
        else if(y>=57)
        {
          step=s5;
        }        
      break;
      case s2:  
        if (entry)
        {
          Q0=1;
          x=7;
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
          x=120;
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
          y=7;
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
          y=56;
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

  display.fillCircle(x,y,r,WHITE);
}