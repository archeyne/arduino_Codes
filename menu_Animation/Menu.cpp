#include "Menu.h"

Menu::Menu(Adafruit_SSD1306 &display):display(display){}


void Menu::init()
{
  for(int i=0;i<3;i++)
  {
    display.setTextColor(WHITE);
    display.setCursor(itemPosX[i],itemPosY[i]);
    display.println(menuItem[i]);
  }
}

void Menu::itemDisplay(int item,bool highlight)
{
  if(!highlight)
  {
    display.setTextColor(WHITE);
    display.setCursor(itemPosX[item],itemPosY[item]);
    display.println(menuItem[item]);
  }
  else
  {
    display.setTextColor(BLACK);
    display.fillRect(0,itemPosY[item]-3,127,18,WHITE); 
    display.setCursor(itemPosX[item],itemPosY[item]);
    display.println(menuItem[item]);
  }
}

void Menu::seq()
{
  do
  {
    pstep=step;
    switch(step)
    {
      case s1:
        if(entry)
        {
          Q0=1;
        }
        step=s2;       
      break;
      case s2:  
        if (entry)
        {
          Q3=0;Q1=1;
          timer=20;
        }  
        if(timer==0) step=s3;
      break;
      case s3:  
        if (entry)
        {
          Q1=0; Q2=1;
          timer=20;
        }           
        if(timer==0) step=s4;
      break;
      case s4:              //bola se mueve hacia abajo
        if (entry)
        {
          Q2=0; Q3=1;
          timer=20;
        }    
        if(timer==0) step=s2;
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
 
  if(Q0)
  {
    init();
  }

  if(Q1)
  {
    itemDisplay(0,true);
  }
  else
  {
    itemDisplay(0,false);
  }

  if(Q2)
  {
    itemDisplay(1,true);
  }
  else
  {
    itemDisplay(1,false);
  }

  if(Q3)
  {
    itemDisplay(2,true);
  }
  else
  {
    itemDisplay(2,false);
  }

  if(timer>0) timer--;

}