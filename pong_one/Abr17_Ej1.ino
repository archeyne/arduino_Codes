#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "ArduinoTrace.h"
#include "ptScheduler.h"
#include "ezButton.h"

#include "Circle.h"
#include "Paddle.h"
#include "Collision.h"
#include "Score.h"

ptScheduler TasksSch=ptScheduler(100000);

#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET            4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Paddle myPaddle(display,124,40);    //Derecha
Paddle myPaddle2(display,3,3);      //Izquierda
Circle myCircle(display,myPaddle,myPaddle2,7,32);

Collision myCollision(myCircle,myPaddle);
Collision myCollision2(myCircle,myPaddle2);

Score myScore(myCircle, display, 0 ,0);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay(); //clear display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  myCircle.init();
  myPaddle.init();       
  myPaddle2.init();
  myScore.init();
  display.drawFastVLine(63,0,63, WHITE);
  display.drawRect(1, 1, 127, 63, WHITE); 
  display.display();
  delay(2000);
  display.clearDisplay(); //clear display

}

void loop() {
  // put your main code here, to run repeatedly:
  if(TasksSch.call())
  {
    display.drawFastVLine(63,0,63, WHITE);
    display.drawRect(1, 1, 127, 63, WHITE); 
    myCircle.seq();
    myPaddle.movSeq();
    myPaddle2.movSeqB();
    myCollision.processSeq();
    myCollision2.processSeqB();
    myScore.processSeq();
    display.display();
    display.clearDisplay(); //borra el buffer
  }
}

