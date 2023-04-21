#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "ArduinoTrace.h"
#include "ptScheduler.h"
#include "ezButton.h"

#include "Circle.h"
#include "Rect.h"

ptScheduler TasksSch=ptScheduler(100000);

#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET            4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Rect myRect(display,0,0);
Rect myRect2(display,0,0);
Circle myCircle(display,0,0);
Circle myCircle2(display,0,0);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  



  // initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay(); //clear display
  myRect.init();
  myRect2.init();
  myCircle.init();
  myCircle2.init();

  display.display();
  delay(2000);
  display.clearDisplay(); //clear display
}

void loop() {
  // put your main code here, to run repeatedly:
  if(TasksSch.call())
  {
    myRect.seq();
    myRect2.seq();
    myCircle.seq();
    myCircle2.seq();
    display.display();
    display.clearDisplay(); //borra el buffer
  }
}

