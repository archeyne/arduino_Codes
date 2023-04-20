#include "Circle.h"

Circle::Circle (Adafruit_SSD1306 &display,Paddle &paddle,Paddle &paddle2,int x,int y):display(display),paddle(paddle),paddle2(paddle2),x(x),y(y){}

void Circle::init()
{
  display.fillCircle(x,y,r,WHITE);
}

void Circle::seq()
{
  do
  {
    bool C0=(x<=court.xmin-r);
    bool C1=(x>=court.xmax+r);
    bool C2=(y<=court.ymin+r);
    bool C3=(y>=court.ymax-r);

    pstep=step;
    switch(step)
    {
      case s1:
        if(entry)
        {
          Q0=0;
          Q1=0;
        }
        if(C0)       //bola sale por arista izquierda
        {
          step=s2;  
        } 
        else if(C1)  //bola sale por arista derecha
        {
          step=s3;
        }
        else if(C2)  //bola pega en arista superior
        {
          step=s4;
        }
        else if(C3)  //bola pega en arista inferior
        {
          step=s5;
        }        
      break;
      case s2:  
        if (entry)
        {
          Q0=0;
          A0=1;
          // x=paddle.x-r-1;  //bola en el paddle del jugador a la derecha
          // y=paddle.y;      // ...
          timer=1;
        }  
        A0=1;
        if(timer==0)
        {
          A0=0;
          step=s1;
        }           
      break;
      case s3:  
        if (entry)
        {
          Q0=0;
          // x=paddle2.x+r+1;  //bola en el paddle del jugador a la izquierda
          // y=paddle2.y;      // ...
          timer=1;
        }    
        A1=1;
        if(timer==0)
        {
          A1=0;
          step=s1;
        }         
      break;
      case s4:              //bola se mueve hacia abajo
        if (entry)
        {
          Q1=1;
          y=court.ymin+r+1;   
          timer=1;
        }  
        A2=1;
        if(timer==0)
        {
          A2=0;
          step=s1;
        }           
      break;
      case s5:              //bola se mueve hacia arriba
        if (entry)
        {
          Q1=1;
          timer=1;
        }    
        A3=1;
        if(timer==0)
        {
          A3=0;
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

  if(A0)
  {
    x=paddle.x-r-1;  //bola en el paddle del jugador a la derecha
    y=paddle.y;      // ...
  }

  if(A1)
  {
    x=paddle2.x+r+1;  //bola en el paddle del jugador a la izquierda
    y=paddle2.y;      // ...
  }

  if(A2)
  {
    y=court.ymin+r+1; 
  }

  if(A3)
  {
    y=court.ymax-r-1;
  }

  x=x+incX;
  y=y+incY;

  display.fillCircle(x,y,r,WHITE);
}