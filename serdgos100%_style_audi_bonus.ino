/*
serdgos100%
Данный скетч предлагается обсолютно бесплатно
Для развития и поддержания проектов
=================
Донат / Поддержка:
Карта Сбербанка: 5336 6900 0836 6488
=================
Большое спасибо!

*/

#include <EEPROM.h> // подключаем библиотеку EEPROM
int n_Key = 0;   //считаем число нажатий на кнопку
int ledPins[] = {3,5,6,9,10,11};
int regim = 0; // Переключалка
int index=0;


unsigned long previousMillis1 = 0; // Счетчик нажатии кнопки

unsigned long previousMillis3 = 0; // Счетчик ЭФЕКТ1
unsigned long previousMillis4 = 0; // Счетчик ЭФЕКТ2
unsigned long previousMillis5 = 0; // Счетчик ЭФЕКТ3
unsigned long previousMillis6 = 0; // Счетчик ЭФЕКТ4

boolean button_state2      = false; //Статусы кнопки 8
boolean button_long_state2 = false; //Статусы кнопки 8
unsigned long previousMillis2 = 0; // счетчик времени кнопки 8
const int but2 = 2; // Кнопка №8
int Longpresskey2;  //Переменная для хранения и сравнения состояния кнопки 
int Presskey2=0;    //Переменная для хранения и сравнения состояния кнопки 



void setup()
{
     
  Serial.begin(9600);
  pinMode(but2, INPUT);  
  int index;
  for(index = 0; index <= 5; index++)
  {
  pinMode(ledPins[index],OUTPUT);
  }
  
  n_Key = EEPROM.read(0);
}

 
void loop()
{
unsigned long currentMillis = millis(); // текущее время в миллисекундах
/**************************************
Обработка кнопки №2 Начало
****************************************/   
    
unsigned long ms2    = millis();
   boolean pin_state2 = digitalRead(but2);
// Фиксируем нажатие кнопки   
   if( pin_state2  == HIGH && !button_state2 && ( ms2 - previousMillis2 ) > 50 ){
      button_state2      = true;
      button_long_state2 = false;  
      previousMillis2    = ms2;
   }
   
   // Фиксируем длинное нажатие кнопки   
   if( pin_state2  == HIGH && !button_long_state2 && ( ms2 - previousMillis2 ) > 1000 ){
      button_long_state2 = true;
       Longpresskey2=1;
      
   }
   // Фиксируем отпускание кнопки   
   if( pin_state2 == LOW && button_state2 && ( ms2 - previousMillis2 ) > 50  ){
      button_state2      = false;   
      previousMillis2      = ms2;
     if( !button_long_state2 )Presskey2=1;
   //  StatusStanbay = 1;
   
   }
  /**************************************
Обработка кнопки №8 Конец
****************************************/   

if(Presskey2 == 1){
  n_Key ++;
         //  tone(3, 2550, 20);
      if(n_Key > 3)                     // Если номер режима превышает требуемого
        {                               // то отсчет начинается с нуля
          n_Key = 0;
        } 

        EEPROM.write(0, n_Key);

     Presskey2 = 0;
       
   digitalWrite(ledPins[0], LOW);
   digitalWrite(ledPins[1], LOW);
   digitalWrite(ledPins[2], LOW);
   digitalWrite(ledPins[3], LOW);
   digitalWrite(ledPins[4], LOW);
   digitalWrite(ledPins[5], LOW);
   index = 0;
   regim = 0;
    }

  Serial.println("index");
Serial.println( index );

    Serial.println("n_Key");
Serial.println( n_Key );



    switch (n_Key) {
  
  //Эффект №1, Ауди стиль.AudiStyle
  case 0: 

      if(index < 8 && currentMillis - previousMillis3  >= 25)
  {
      previousMillis3 = currentMillis; // запоминаем момент времени

  digitalWrite(ledPins[index], HIGH);
       
index++;
       }

    

if(index == 8)
{
  
   digitalWrite(ledPins[0], LOW);
   digitalWrite(ledPins[1], LOW);
   digitalWrite(ledPins[2], LOW);
   digitalWrite(ledPins[3], LOW);
   digitalWrite(ledPins[4], LOW);
   digitalWrite(ledPins[5], LOW);
   if(currentMillis - previousMillis3  > 500)
  {
      previousMillis3 = currentMillis; // запоминаем момент времени
index=0;
  
    }
  }

     break;

    
  //Эффект №2, Один за другим поочередно сохраня свое состояние.
    case 1: 


if(regim == 0 && currentMillis - previousMillis4  >= 120)
  {
      previousMillis4 = currentMillis; // запоминаем момент времени

  digitalWrite(ledPins[index], HIGH);
       index++;
if(index == 6)
{
regim = 1;
}
    }

if(regim == 1 && currentMillis - previousMillis4  >= 120)
  {
      previousMillis4 = currentMillis; // запоминаем момент времени

  digitalWrite(ledPins[index], LOW);
       index--;
if(index == -1)
{
regim = 0;
}
    }
        break;
      

        
//Эффект №3, Один за другим загораются поочередно с лево на право.
case 2:  

if(currentMillis - previousMillis5  >= 130)
  {
     digitalWrite(ledPins[index], LOW);
    
      previousMillis5 = currentMillis; // запоминаем момент времени
       index++;
    
if(index == 6)
{
index = 0;
}
  digitalWrite(ledPins[index], HIGH);
    }


/* */
     
       break;




//Эффект №4, пин понг.
case 3: 

if(regim == 0 && currentMillis - previousMillis4  >= 120)
  {
      previousMillis4 = currentMillis; // запоминаем момент времени

  digitalWrite(ledPins[index], LOW);
       index++;
if(index == 5)
{
regim = 1;
}

 digitalWrite(ledPins[index], HIGH);
    }

if(regim == 1 && currentMillis - previousMillis4  >= 120)
  {
      previousMillis4 = currentMillis; // запоминаем момент времени

  digitalWrite(ledPins[index], LOW);
       index--;
if(index == 0)
{
regim = 0;
}

digitalWrite(ledPins[index], HIGH);
    }

    
       break;
     
     
      }

}





