#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ToneESP32.h>
#include "pitches.h"

#include "ArduinoTrace.h"
#include "ptScheduler.h"
#include "ezButton.h"
#include "image.h"

#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64 // OLED display height, in pixels
#define BUZZER_PIN 33           // Pin buzzer
#define BUZZER_CHANNEL 0      


ToneESP32 buzzer(BUZZER_PIN, BUZZER_CHANNEL);

int potValue, potValue2;

const int potPin = 13;          // Jugador 1 (izquierda)
const int potPin2 = 12;         // Jugador 2 (derecha)

const int led1 = 18;
const int led2 = 19;

int paddlePlayer1 = 3;
int paddlePlayer2 = 3;

int scorePlayer1 = 0;
int scorePlayer2 = 0;

int ballX = 128 / 2;
int ballY = 64 / 2;

float ballSpeedX = 3;
float ballSpeedY = 2;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET            -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define FONT_SIZE 2

bool menuFlag=false;

bool upFlag=false;
bool downFlag=false;
bool execFlag=false;
bool showMenu=true;
bool showOptions=false;
bool showCredits=false;
bool showGame=false;

ezButton btnSel1(4);             //Selección arriba  (amarillo)
ezButton btnSel2(32);             //Selección abajo  (rojo)
ezButton btnStart(5);             //Confirmación (azul)

ptScheduler TaskMenu=ptScheduler(10000);

int menu = 1;
int menuOpt = 1;
int flagXD = 1;
int pointOpt = 1;
int diffOpt = 1;
int maxScore = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  randomSeed(analogRead(0));
  display.clearDisplay(); //clear display
  display.drawBitmap(0, 0,logo_bmp, 128, 64, WHITE);
  display.display();
  buzzer.tone(NOTE_C4, 250);
  buzzer.tone(NOTE_D4, 250);
  buzzer.tone(NOTE_E4, 250);
  buzzer.tone(NOTE_F4, 250);
  buzzer.tone(NOTE_G4, 250);
  buzzer.tone(NOTE_A4, 250);
  buzzer.tone(NOTE_B4, 250);
  buzzer.tone(NOTE_C5, 250);
  delay(250);
  buzzer.tone(NOTE_C5, 250);
  buzzer.tone(NOTE_B4, 250);
  buzzer.tone(NOTE_A4, 250);
  buzzer.tone(NOTE_G4, 250);
  buzzer.tone(NOTE_F4, 250);
  buzzer.tone(NOTE_E4, 250);
  buzzer.tone(NOTE_D4, 250);
  buzzer.tone(NOTE_C4, 250);
  buzzer.noTone();

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  btnSel1.setDebounceTime(50);
  btnSel2.setDebounceTime(50);
  btnStart.setDebounceTime(50);

  //Amogus intro

  display.clearDisplay(); //clear display


  display.display();
}

void loop() {
  btnSel1.loop();
  btnSel2.loop();
  btnStart.loop();

  if(menuFlag == false)
  {
    display.setTextColor(WHITE);
    display.setTextSize(FONT_SIZE); 
    display.fillRect(24,10,79,20,WHITE);
    display.setTextColor(BLACK);
    display.setCursor(28,13);
    
    display.println("PONG 2");
    
    
    display.setTextSize(FONT_SIZE - 1); 
    display.setTextColor(WHITE);
    display.setCursor(30,50);
    display.println("PRESS START");

    display.display();
  }
  else
  { 
    if(showMenu)
    {
      if (btnSel1.isPressed())
      {
        upFlag=true;
        downFlag=false;
        execFlag=false;
      } 
      else if (btnSel2.isPressed())
      {
        upFlag=false;
        downFlag=true;
        execFlag=false;
      } 
      else if (btnStart.isPressed())
      {
        upFlag=false;
        downFlag=false;
        execFlag=true;
      }
      display.clearDisplay(); 
      if(1)
      {
        if (downFlag){
          downFlag=false;
          menu++;
          Serial.println(menu);
        }
        if (upFlag){
          upFlag=false;
          menu--;
          Serial.println(menu);
        }
        if (execFlag){
          execFlag=false;
          execAction();
          Serial.println("Exec");
        }
      }   
      dispMenu();
      display.display();
    }
    else if(showGame) gameOn();
    else if(showOptions) options();
    else if(showCredits) credits();
  }

  if(btnStart.isPressed() && flagXD == 1)
  {
    flagXD = 0;
    menuFlag = true; 
  }
}

void dispMenu()
{
  display.setTextColor(WHITE);
  display.setTextSize(FONT_SIZE); 
  display.fillRect(24,10,79,20,WHITE);
  display.setTextColor(BLACK);
  display.setCursor(28,13);
    
  display.println("PONG 2");

  display.setTextSize(FONT_SIZE - 1);

  display.setTextColor(WHITE);

  switch (menu) 
  {
    case -1:
      menu = 1;
      break;
    case 0:
      menu = 1;
      break;
    case 1:
      display.setCursor(25,35);
      display.print(">>");
      break;
    case 2:
      display.setCursor(28,45);
      display.print(">>");
      break;
    case 3:
      display.setCursor(28,55);
      display.print(">>");
      break;
    case 4:
      menu = 3;
      break;
    case 5:
      menu = 3;
      break;
  }
  display.setCursor(40,35);
  display.println("NEW GAME");
  display.setCursor(43,45);
  display.println("OPTIONS");
  display.setCursor(43,55);
  display.println("CREDITS");

}

void execAction()
{
  switch (menu) 
  {
    case 1:
      showMenu = false;
      showGame = true;
      scorePlayer1 = 0;
      scorePlayer2 = 0;
      ballX = 128 / 2 + random(0, 5);
      ballY = 64 / 2 + random(0, 5);
      //ballSpeedX = 4;       //Puedo ponerlo en menú de opciones
      //ballSpeedY = 2;
      break;
    case 2:
      showMenu = false;
      showOptions = true;
      menuOpt = 1;
      break;
    case 3:
      showMenu = false;
      showCredits = true;
      break;
  }
}

void gameOn() 
{
  display.clearDisplay(); 

  potValue = map(analogRead(potPin),0,4095,3,44);
  potValue2 = map(analogRead(potPin2),0,4095,3,44);

  paddlePlayer1 = potValue;
  paddlePlayer2 = potValue2;

  drawField(scorePlayer1, scorePlayer2);
  collisionControl();
  drawBall(); //dibujamos la bola en las ccordenadas que nos mandan.
  //Posibilidad para hacer que la pelota vaya más rapido a medida que pase el tiempo

  display.display();
}

void credits() 
{
  if(btnStart.isPressed())
  {
    showMenu = true;
    showCredits = false;
  }

  display.clearDisplay(); 
  //Serial.println("CREDITOS");
  display.setTextSize(FONT_SIZE-1); 
  display.fillRect(12,3,103,14,WHITE);
  display.setTextColor(BLACK);
  display.setCursor(18,6);
    
  display.println("JUEGO HECHO POR:");

  display.setTextColor(WHITE);
  display.setTextSize(FONT_SIZE-1.2);
  display.setCursor(8,20);
  display.println("ALEJANDRO MARTIN");
  display.setCursor(8,30);
  display.println("SANTIAGO PARDO");
  display.setCursor(8,40);
  display.println("JULIAN COLMENARES");
  display.setCursor(8,50);
  display.println("ALAN CHEYNE");

  display.setCursor(100,55);
  display.print("<<");
  
  display.display();
}

void options () 
{
  display.clearDisplay(); 
  
  display.setTextSize(FONT_SIZE-1); 
  display.fillRect(12,3,103,14,WHITE);
  display.setTextColor(BLACK);
  display.setCursor(18,6);

  display.println("OPCIONES");

  display.setTextSize(FONT_SIZE-1.2);
  display.setTextColor(WHITE);

  //Actualiza 

  if (btnSel1.isPressed())
  {
    menuOpt--;
  }
  if (btnSel2.isPressed())
  {
    menuOpt++;
  }
  if (btnStart.isPressed())
  {
    switch (menuOpt) 
    {
      case 1:
        pointOpt = (pointOpt + 1)%3;
        display.setCursor(0,20);
        display.print(">>");
        break;
      case 2:
        diffOpt = (diffOpt + 1)%3;
        display.setCursor(0,40);
        display.print(">>");
        break;
      case 3:
        showMenu = true;
        showOptions = false;
        break;
    }
  }

  switch (menuOpt) 
    {
      case -1:
        menuOpt = 1;
        break;
      case 0:
        menuOpt = 1;
        break;
      case 1:
        display.setCursor(0,20);
        display.print(">>");
        break;
      case 2:
        display.setCursor(0,40);
        display.print(">>");
        break;
      case 3:
        display.setCursor(80,55);
        display.print(">>");
        break;
      case 4:
        menuOpt = 3;
        break;
      case 5:
        menuOpt = 3;
        break;
    }

  

  display.setCursor(20,22);
  display.println("BEST OF");

  switch (pointOpt)
  {
    case 0:
    display.fillRect(70, 20, 10, 10, WHITE); 
    display.drawRect(85, 20, 10, 10, WHITE); 
    display.drawRect(100, 20, 10, 10, WHITE); 
    maxScore = 2;
    display.setCursor(115,21);
    display.println("3");
    break;
    case 1:
    display.drawRect(70, 20, 10, 10, WHITE); 
    display.fillRect(85, 20, 10, 10, WHITE); 
    display.drawRect(100, 20, 10, 10, WHITE); 
    maxScore = 3;
    display.setCursor(115,21);
    display.println("5");
    break;
    case 2:
    display.drawRect(70, 20, 10, 10, WHITE); 
    display.drawRect(85, 20, 10, 10, WHITE); 
    display.fillRect(100, 20, 10, 10, WHITE);
    maxScore = 4; 
    display.setCursor(115,21);
    display.println("7");
    break;
  }
  
  display.setCursor(20,42);
  display.println("SPEED");

  switch (diffOpt)
  {
    case 0:
    display.fillRect(70, 40, 10, 10, WHITE); 
    display.drawRect(85, 40, 10, 10, WHITE); 
    display.drawRect(100, 40, 10, 10, WHITE); 
    ballSpeedX = 2;       
    ballSpeedY = 1;
    display.setCursor(115,41);
    display.println("1");
    break;
    case 1:
    display.drawRect(70, 40, 10, 10, WHITE); 
    display.fillRect(85, 40, 10, 10, WHITE); 
    display.drawRect(100, 40, 10, 10, WHITE); 
    ballSpeedX = 3;       
    ballSpeedY = 2;
    display.setCursor(115,41);
    display.println("2");
    break;
    case 2:
    display.drawRect(70, 40, 10, 10, WHITE); 
    display.drawRect(85, 40, 10, 10, WHITE); 
    display.fillRect(100, 40, 10, 10, WHITE);
    ballSpeedX = 4;       
    ballSpeedY = 3;
    display.setCursor(115,41);
    display.println("3");
    break;
  }

  display.setCursor(100,55);
  display.print("<<");
  

  display.display();
}

void drawField(int score1, int score2) 
{
  display.drawFastVLine(63,0,63, WHITE);
  display.drawRect(1, 1, 127, 63, WHITE); 

  display.fillRect(3, round(paddlePlayer1), 2, 18, 1);
  display.fillRect(124, round(paddlePlayer2), 2, 18, 1);

  display.setCursor(48,10);
  display.print(score1);
  display.setCursor(74,10);
  display.print(score2);
}

void collisionControl() 
{
  if (ballY >= 64 - 3 || ballY <= 3) {
    ballSpeedY *= -1;
    tone(BUZZER_PIN, NOTE_C4, 125);
    noTone(BUZZER_PIN); //SOnido rebote
  }
  //bounce from player1
  if (ballX >= 0 && ballX <= 8 && ballSpeedX < 0) {
    if (ballY > round(paddlePlayer1) - 2 && ballY < round(paddlePlayer1) + 18) {
      ballSpeedX *= -1;
      //cuentagolpes++;
      tone(BUZZER_PIN, NOTE_C4, 125);
      noTone(BUZZER_PIN); //SOnido rebote

      ballSpeedY = ballSpeedY + random(-ballSpeedY, ballSpeedY)/6; //Cambio el ángulo de rebote un poco
      Serial.println(random(-ballSpeedY, ballSpeedY)/6);
    }
  }
  //bounce from player2
  if (ballX >= 128 - 2 - 6 && ballX <= 128 - 2 && ballSpeedX > 0) {
    if (ballY > round(paddlePlayer2) - 2 && ballY < round(paddlePlayer2) + 18) {
      ballSpeedX *= -1;
      //cuentagolpes++;
      tone(BUZZER_PIN, NOTE_C4, 125);
      noTone(BUZZER_PIN); //SOnido rebote
      
      ballSpeedY = ballSpeedY + random(-ballSpeedY, ballSpeedY)/6; //Cambio el ángulo de rebote un poco
      Serial.println(random(-ballSpeedY, ballSpeedY)/6);
    }

  }
  if (ballX >= 128 - 2 || ballX <= 0) {
    if (ballSpeedX > 0) {
      scorePlayer1++;
      //gol(); // Goal tone
      tone(BUZZER_PIN, NOTE_G4, 125);
      tone(BUZZER_PIN, NOTE_A4, 125);
      tone(BUZZER_PIN, NOTE_B4, 125);
      noTone(BUZZER_PIN); //SOnido rebote
      digitalWrite(led1, HIGH);
      delay(1000);
      digitalWrite(led1, LOW);
      ballX = (128 / 4) + random(-3, 3); //Small random position variation



    }
    if (ballSpeedX < 0) {
      scorePlayer2++;
      tone(BUZZER_PIN, NOTE_G4, 125);
      tone(BUZZER_PIN, NOTE_A4, 125);
      tone(BUZZER_PIN, NOTE_B4, 125);
      noTone(BUZZER_PIN); //SOnido rebote
      digitalWrite(led2, HIGH);
      delay(1000);
      digitalWrite(led2, LOW);
      ballX = 128 / 4 * 3 + random(-3, 3); //Small random position variation


    }
    if (scorePlayer1 == maxScore || scorePlayer2 == maxScore) {
      //gameState = 2;
      tone(BUZZER_PIN, NOTE_F4, 125);
      tone(BUZZER_PIN, NOTE_G4, 125);
      tone(BUZZER_PIN, NOTE_A4, 125);
      tone(BUZZER_PIN, NOTE_G4, 125);
      tone(BUZZER_PIN, NOTE_F4, 125);
      tone(BUZZER_PIN, NOTE_E4, 125);
      tone(BUZZER_PIN, NOTE_F4, 125);
      noTone(BUZZER_PIN); //SOnido rebote
      endScreen();
      //gol(); // end tone
      //gol();
    }
  }
}

void drawBall()
{
  display.fillCircle(ballX, ballY, 2, WHITE);
  ballX += ballSpeedX;
  ballY += ballSpeedY;
}

void endScreen()
{
  if(scorePlayer1 > scorePlayer2)
  {
    display.clearDisplay();
    display.setTextSize(FONT_SIZE); 
    display.fillRect(12,17,108,20,WHITE);
    display.setTextColor(BLACK);
    display.setCursor(13,20);

    display.println("JUGADOR 1");
      
    display.display();

    digitalWrite(led2, HIGH);
    digitalWrite(led1, HIGH);

    delay(500);

    digitalWrite(led2, LOW);
    digitalWrite(led1, LOW);

    delay(500);

    digitalWrite(led2, HIGH);
    digitalWrite(led1, HIGH);
      

    display.fillRect(40,40,49,20,WHITE);
    display.setCursor(41,43);
    display.println("GANA");
    display.display();

    delay(3000);
    digitalWrite(led2, LOW);
    digitalWrite(led1, LOW);
    showMenu = true;
    showGame = false;
  }
  else if (scorePlayer2 > scorePlayer1)
  {
    display.clearDisplay();
    display.setTextSize(FONT_SIZE); 
    display.fillRect(12,17,108,20,WHITE);
    display.setTextColor(BLACK);
    display.setCursor(13,20);

    display.println("JUGADOR 2");
      
    display.display();

    digitalWrite(led2, HIGH);
    digitalWrite(led1, HIGH);

    delay(500);

    digitalWrite(led2, LOW);
    digitalWrite(led1, LOW);

    delay(500);

    digitalWrite(led2, HIGH);
    digitalWrite(led1, HIGH);
      
    
    display.fillRect(40,40,49,20,WHITE);
    display.setCursor(41,43);
    display.println("GANA");
    display.display();

    delay(3000);
    digitalWrite(led2, LOW);
    digitalWrite(led1, LOW);
    showMenu = true;
    showGame = false;
  }
  
}
