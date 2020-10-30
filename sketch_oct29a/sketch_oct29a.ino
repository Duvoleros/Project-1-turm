/*Данный проект - "секундомер", позволяющий засекать время с точностью до секунд
Этапы осуществления проекта :
1. Продумка идеи
2. Получение необходимых компонентов : плата esp8266, диспей oled 1306 128*32, соединительные провода, макетная плата
3. Сборка модели (пины gnd-gnd,3u3-vcc,sda-d2,scl-d3)
4. Создание 3D модели обводки экрана, нарезка модели в pursa
5. Распечатка обводки экрана для дисплея на принтере
6. Написание кода на основе примеров из библиотек*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>//подключение библиотек

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     5 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Wire.begin(4,0);  ///пины gnd-gnd,3u3-vcc,sda-d2,scl-d3
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
Serial.println("SSD1306 started");
  
  display.display();
  
  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();

  display.clearDisplay();
mini();//Инициализация метода
  
}



void loop() {}

void mini(){//наш метод
 int sek=0;
int minu=0;
int h=0;//инициализация переменных
  while(true){
  sek++;
  if(sek==60){
    minu=minu+1;
    sek=0;}
  if(minu==60){
    h=h+1;
    minu=0;}
   display.clearDisplay();
  String s;
  if(sek<10&&minu<10){
    s=h;
    s=s+":0";
    s=s+minu;
    s=s+":0";
    s=s+sek;
    }else{
     if(sek<10){
      s=h;
      s=s+":";
      s=s+minu;
      s=s+":0";
      s=s+sek;
      }else{
        if(minu<10){
          s=h;
          s=s+":0";
          s=s+minu;
          s=s+":";
          s=s+sek;
          }else{
          s=h;
          s=s+":";
          s=s+minu;
          s=s+":";
          s=s+sek;  }//Описание для изменения времени
      }}
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);             // Start at top-left corner
  display.println(s);  //вывод времени
  display.display();    //вывод изображения на дисплей
  delay(999);//промежуток 1 сек
}}
