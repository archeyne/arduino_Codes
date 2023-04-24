#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "ArduinoTrace.h"
#include "ptScheduler.h"
#include "ezButton.h"
#include "Rect.h"
#include "Circle.h"

#include "Menu.h"

ptScheduler TasksSch=ptScheduler(100000);

#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET            4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Rect myRect2(display,32,25);
Circle myCircle(display,32,35);
//Define Visuals
#define FONT_SIZE 2

ezButton btnSel(7);

Menu myMenu(display);

bool mainMenuFlag=true;
bool display1Flag=false;
bool display2Flag=false;
bool display3Flag=false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  btnSel.setDebounceTime(20);

  display.clearDisplay(); //clear display
  myRect2.init();
  myCircle.init();
  display.setTextColor(WHITE);
  display.setTextSize(FONT_SIZE); 
  display.display();
}
void loop() {
  // put your main code here, to run repeatedly:
  btnSel.loop();
  if(btnSel.isPressed())
  {
    btnSelProcess(); 
  }
  if(TasksSch.call())
  {
    if(mainMenuFlag) myMenu.seq();
    if(display1Flag) display1();
    if(display2Flag) display2();
    if(display3Flag) display3();

    display.display();
    display.clearDisplay(); //borra el buffer
  }
}

void btnSelProcess()
{
  if(mainMenuFlag==true)
  {
    if(myMenu.Q1==1)
    {
      mainMenuFlag=false;
      display1Flag=true;
    }
    else if(myMenu.Q2==1)
    {
      mainMenuFlag=false;
      display2Flag=true;
    }
    else if(myMenu.Q3==1)
    {
      mainMenuFlag=false;
      display3Flag=true;
    }
  }  
  else if(display1Flag==true)
  {
      mainMenuFlag=true;
      display1Flag=false;
  }
  else if(display2Flag==true)
  {
      mainMenuFlag=true;
      display2Flag=false;
  }
  else if(display3Flag==true)
  {
      mainMenuFlag=true;
      display3Flag=false;
  }
}


void display1()
{
    display.setTextColor(WHITE);
    display.setCursor(54,18);
    //display.print("H");
    myCircle.seq();
    display.fillRect(4,43,23,17,WHITE); 
    display.setTextColor(BLACK);
    display.setCursor(4,45);
    display.print("<<");
}

void display2()
{
    display.setTextColor(WHITE);
    display.setCursor(54,18);
    myRect2.seq();
    display.fillRect(4,43,23,17,WHITE); 
    display.setTextColor(BLACK);
    display.setCursor(4,45);
    display.print("<<");
}

void display3()
{
    display.setTextColor(WHITE);
    display.setCursor(54,18);
    display.print("R");
    display.fillRect(4,43,23,17,WHITE); 
    display.setTextColor(BLACK);
    display.setCursor(4,45);
    display.print("<<");
}



