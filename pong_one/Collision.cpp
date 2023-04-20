#include "Collision.h"

Collision::Collision(Circle &circle,Paddle &paddle):circle(circle),paddle(paddle){}

void Collision::processSeq()
{
  bool C1=(circle.y>=paddle.y)&&(circle.y<=(paddle.y+paddle.h));
  bool C2=(((circle.x+circle.r)>=paddle.x) && ((circle.x+circle.r)<=(paddle.x+paddle.w)));
  do
  {
    pstep=step;
    switch(step)
    {
      case s1:
        if(entry)
        {
          circle.Q0=0;
        }
        if(C1)
        {
          step=s2;  
        } 
      break;
      case s2:  
        if (entry)
        {

        }  
        if(!C1) 
        {
          step=s1;
        }
        else if(C2)
        {
          step=s3;  
        }           
      break;
      case s3:  
        if (entry)
        {
          circle.Q0=1;
          circle.x=paddle.x-circle.r-1;
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
}


void Collision::processSeqB()
{
  bool C1=(circle.y>=paddle.y)&&(circle.y<=(paddle.y+paddle.h));
  bool C2=(((circle.x-circle.r)<=paddle.x) && ((circle.x-circle.r)>=(paddle.x-paddle.w)));
  do
  {
    pstep=step;
    switch(step)
    {
      case s1:
        if(entry)
        {
          circle.Q0=0;
        }
        if(C1)
        {
          step=s2;  
        } 
      break;
      case s2:  
        if (entry)
        {

        }  
        if(!C1) 
        {
          step=s1;
        }
        else if(C2)
        {
          step=s3;  
        }           
      break;
      case s3:  
        if (entry)
        {
          circle.Q0=1;
          circle.x=circle.x=paddle.x+circle.r+1;;
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
}