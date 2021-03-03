#include <LCD5110_SSVS.h>
#include <OneWire.h>

// Arduino таймер CTC прерывание
// avr-libc library includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include "clock.h"

/////
//#include <LCD5110_SSVS.h>//CLK, DIN, DC, RST
LCD5110 myGLCD(8, 9, 10, 12); //запускаем LCD

extern uint8_t SmallFont[];  //подключаем аглийский шрифт
extern uint8_t BigNumbers[];
extern uint8_t RusFont[];  //подключаем русский шрифт
/////
//ds1820
float  temperature = 0;          //переменная с измеренной температурой
//буфер строки
char teme[7];
long lastUpdateTime = 0; // Переменная для хранения времени последнего считывания с датчика
const int TEMP_UPDATE_TIME = 1000; // Определяем периодичность проверок
//
volatile int seconds=0;
volatile int minute=0;
volatile int hours=0;
volatile int yy=2020;
volatile int mm=1;
volatile int dd=0;


int sec_ed=0;
int sec_dec=0;
int min_dec=0;
int min_ed=0;
int hou_ed=0;
int hou_dec=0;

int yy_t=0;
int yy_s=0;
int yy_d=0;
int yy_e=0;

int mm_d=0;
int mm_e=0;
int dd_d=0;
int dd_e=0;
int max_dey;

char* dn;

//переменные для будильников
int bud_num=1;      //номер будильника (1-4)
boolean bud_en[5];
//boolean bud_1=0;   //включение/выключение 1-го будильника
int bud_hou[]={0,0,0,0,0,0};    //часы для N-го будильника
int bud_min[]={0,0,0,0,0,0};    //минуты для N-го будильника
int bud_povtor[]={0,0,0,0,0};  //количество повторов для 1-го будильника
int bud_1_mel;    //№ мелодии для 1-го будильника
int bud_1_nagr;    //переменная для режима внешней нагрузки

volatile int count=0;

volatile int flag=0;
volatile int flag1=0;

//блок переменных для кнопок
volatile int key_skan;

boolean s1 = 0;
boolean s2 = 0;
boolean s1s2 = 0;
boolean s3 = 0;
boolean s4 = 0;
//
//boolean vv = 0;

int uroven=0;
int poduroven=0;
boolean ledst = 0;

//
//
int Serial_command[7]; //массив для приема команд по COM порту
char Serial_char;
int Serial_tmp;
int Serial_flag=0;
int Serial_num = 0;
int Serial_num1 = 0;
//
  OneWire ds(dsp); // Объект OneWire

void setup()
{
  pinMode(LEDPIN, OUTPUT);

  //////
  pinMode (light_pin, OUTPUT);      //настраиваем порт подсветки внут. дисплея
  pinMode (CSPIN, OUTPUT);          //настраиваем порт CS (можно заземлить и отсоединить от контроллера)
  //клавиатура. Порты на вход с подтягивающими резисторами
  pinMode (KEY1, INPUT_PULLUP);
  pinMode (KEY2, INPUT_PULLUP);
  pinMode (KEY3, INPUT_PULLUP);
  pinMode (KEY4, INPUT_PULLUP);
  //

  //
  digitalWrite(CSPIN,0);
  digitalWrite (light_pin, LCD_ON); //включаем подсветку
  myGLCD.InitLCD(55);          //запуск LCD контраст 65
  //  myGLCD.setFont(RusFont);   //устанавливаем русский шрифт
 // myGLCD.setFont(SmallFont);  //устанавливаем английский шрифт
  ///  myGLCD.setFont(BigNumbers);
  //инициализируем порты
  //

  //
  //сброс всех светодиодов
  //
  cli();  // отключить глобальные прерывания
  // инициализация Timer1
  TCCR1A = 0;   // установить регистры в 0
  TCCR1B = 0;

  //    OCR1A = 15624; // установка регистра совпадения (времязадающая констатнта)
  //        OCR1A = 15620; //отстают на 6 сек. за 6 часов (-1 сек в час)      (-24 сек в сутки)
  //        OCR1A = 15614; //спешит на 3 сек за 3 часа    (+1 сек в час)      (-24 сек в сутки)
  //        OCR1A = 15617;  //спешит на 2 сек за 4 часа   (+0,5 сек в час)    (+12 сек в сутки)
  //        OCR1A = 15619;  //отстает на 8 сек за 42 часа (-0.19 сек в час)   (-4.57 сек в сутки)
  OCR1A = 15618;

  TCCR1B |= (1 << WGM12);  // включить CTC режим (сброс таймера при совпадении с числом в OCRIA)
  TCCR1B |= (1 << CS10); // Установить биты на коэффициент деления 1024
  TCCR1B |= (1 << CS12);

  TIMSK1 |= (1 << OCIE1A);  // включить прерывание по совпадению таймера 

  // Timer0 уже используется millis() - мы создаем прерывание где-то
  // в середине и вызываем ниже функцию "Compare A"
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);

  sei(); // включить глобальные прерывания
  tone (SOUNDPIN, 600, 100);
  delay(100);
  tone (SOUNDPIN, 900, 100);
  Serial.begin(9600); // открывает последовательный порт, устанавливает скорость 9600 бит/c
  //
}
void loop()
{

  //
  //Вычисление единиц и десятков секунд
  sec_ed=seconds-((seconds/10)*10);
  sec_dec=seconds/10;
  //Вычисление единиц и десятков минут
  min_ed=minute -((minute/10)*10);
  min_dec=minute/10;
  //Вычисление единиц и десятков часов
  hou_ed=hours -((hours/10)*10);
  hou_dec=hours/10;
//Определение новой даты
  if((hours==00) && (minute == 00) && (seconds == 1) && (flag==0))
  {
    flag=1;
    max_dey=cal_maxd(yy,mm);
    if(dd==max_dey)
    {
      dd=1;
      if(mm==12)
      {
        mm=1;
        yy++;
      }
      else
      {
        mm++;
      }
    }
    else
    {
      dd++;
    }
  }
  
//Вычисление тысяч, сотен, десятков и единиц года
  yy_t=yy/1000;
  yy_s=(yy-(yy_t*1000))/100;
  yy_d=(yy-(yy_t*1000+yy_s*100))/10;
  yy_e=yy-(yy_t*1000+yy_s*100+yy_d*10);
//Вычисдение десятком и единиц месяцев
  mm_d=mm/10;
  mm_e=mm-(mm_d*10);
//Вычисление десятков и единиц дней
  dd_d=dd/10;
  dd_e=dd-(dd_d*10);
 //Определение дня недели
   dn=cal_dn(yy,mm,dd);
 //
  detectTemperature(); // Определяем температуру от датчика DS18b20
  
  
  ///
  //машина состояний
  //уровень 0
  if (uroven==0)
  {
    if(key_skan==S1S2)
    {
      s1=1;
      s2=1;
      s1s2=1;
      uroven=1;              //вход в меню (Уровень 1)
    }
    if((key_skan==S1) && (s1==0) && (s1s2==0))  //S1
    {
      s1=1;
      ledst=!ledst;
      digitalWrite (light_pin, ledst); //включаем/выключаем подсветку
    }

    key_off();          //отпускание кнопок
    disp_clock();
  }
  //уровень 1
  if (uroven==1)
  {
    if(key_skan==S1S2)
    {
      //уровень 1.1 (Меню)
       poduroven=1;                                    //установка часов
       disp_menu(poduroven);              //Меню по умолчаню - установка времени
    }
    digitalWrite (light_pin, 0); //включаем подсветку  
    if((key_skan==S3) && (s3==0))                      //Нажатие на кнопку S3 - ВНИЗ
    {
       poduroven++;
       s3=1;
       if(poduroven==6)
       {
         poduroven=1;
       }
       disp_menu(poduroven);
    }
    if(key_skan==S4)                                //нажатие на кнопку SET (S4)
    {
      myGLCD.clrScr();        //очистка экрана
      uroven=poduroven+1;                             //переход на уровень выбранный в меню + 1 (с учетом, что уровень меню == 1)
      poduroven=1;                                    //установка часов
      s1=0;
      s2=0;
      s3=0;
      s4=1;
      s1s2=0;
    }
    key_exit();
    key_off();              //отпускание кнопок
  }
  //
  //уровень 2 - Установка часиков
  if(uroven==2)
  {
    disp_u2(poduroven);
    if(poduroven==1)
    {
      if((key_skan==S2) && (s2==0))
      {
        s2=1;
        hours++;
        if(hours==24)
        {
          hours=0;
        }
      }
      if((key_skan==S3) && (s3==0))
      {
        s3=1;
        hours--;
        if(hours==-1)
        {
          hours=23;
        }
      }
    }

    if(poduroven==2)
    {
      if((key_skan==S2) && (s2==0))
      {
        s2=1;
        minute++;
        if(minute==60)
        {
          minute=0;
        }
      }
      if((key_skan==S3) && (s3==0))
      {
        s3=1;
        minute--;
        if(minute==-1)
        {
          minute=59;
        }
      }
    }

    if((key_skan==S4) && (s4==0))
    {
      s4=1;
      if(poduroven==1)
      {
        poduroven=2;
      }
      else
      {
        poduroven=1;
      }
    }
    key_off();              //отпускание кнопок
  }
  //уровень 3 (КАЛЕНДАРЬ)
  
    if(uroven==3)
    {
      disp_u3(poduroven);
    if(poduroven==1)
    {
     if((key_skan==S2) && (s2==0))
     {
       yy++;
       s2=1;
     }
     if((key_skan==S3) && (s3==0))
     {
       yy--;
       if(yy<0)
       {
         yy=0;
       }
       s3=1;
     }
     if((key_skan==S4 && s4==0))
      {
        s4=1;
        poduroven++;
      }
    }
    if(poduroven==2)
    {
     if((key_skan==S2) && (s2==0))
     {
       mm++;
       if(mm==13)
       {
         mm=1;
       }
       s2=1;
     }
     if((key_skan==S3) && (s3==0))
     {
       mm--;
       if(mm==0)
       {
         mm=12;
       }
       s3=1;
     }
     if((key_skan==S4 && s4==0))
      {
        s4=1;
        poduroven++;
      }
    }
    if(poduroven==3)
    {
     if((key_skan==S2) && (s2==0))
     {
       dd++;
       max_dey=cal_maxd(yy,mm);
       if(dd>=max_dey)
       {
         dd=1;
       }
       s2=1;
     }
     if((key_skan==S3) && (s3==0))
     {
       dd--;
       max_dey=cal_maxd(yy,mm);
       if(dd<=0)
       {
         dd=max_dey;
       }
       s3=1;
     }
     if((key_skan==S4 && s4==0))
      {
        s4=1;
        poduroven=1;
      }
    }
    

//          String(dd_d)+String(dd_e)+"."+String(mm_d)+String(mm_e)+"."+String(yy_t)+String(yy_s)+String(yy_d)+String(yy_e),RIGHT,32);
    key_off();              //отпускание кнопок
    key_exit();
    }
//уровень 4 (выбор будильника)
    if(uroven==4)
    {
      disp_u4(poduroven);
      if(key_skan==S2 && s2==0)
      {
        s2=1;
        poduroven++;
        if(poduroven==5)
        {
          poduroven=1;
        }
      }
      if(key_skan==S3 && s3==0)
      {
        s3=1;
        poduroven--;
        if(poduroven==0)
        {
          poduroven=4;
        }
      }
      if(key_skan==S4 && s4==0)
      {
        s4=1;
        uroven=5;
        bud_num=poduroven;
        poduroven=1;
               myGLCD.clrScr();        //очистка экрана
      }

    key_off();              //отпускание кнопок
    key_exit();
    }
//уровень 5 (БУДИЛЬНИКИ)  
    if(uroven==5)
  {
      disp_u5(bud_num,poduroven);
      if(poduroven==1)          //включение/выкдючение будильника
      {
        if(key_skan==S4 && s4==0)
        {
          s4=1;
          poduroven=2;
        }
        if(key_skan==S2 && s2==0)
        {
          s2=1;
          bud_en[bud_num] = !bud_en[bud_num];      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!FIXME!!!!!!!!!!!!!!!!!!!!!!!!!
        }
       if(key_skan==S3 && s3==0)
        {
          s2=3;
          bud_en[bud_num] = !bud_en[bud_num];      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!FIXME!!!!!!!!!!!!!!!!!!!!!!!!!
        }
      }
      if(poduroven==2)          //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!FIXME!!!!!!!!!!!!!!!!!!!!!!!!!
      {
        if(key_skan==S4 && s4==0)
        {
          s4=1;
          poduroven=3;
        }
      }
        if(poduroven==3)        //установка часов будильника
      {
        if(key_skan==S4 && s4==0)
        {
          s4=1;
          poduroven=4;
        }
        if(key_skan==S2 && s2==0)
        {
          s2=1;
          bud_hou[bud_num]++;
          if(bud_hou[bud_num] == 24)
          {
            bud_hou[bud_num]=0;
          }
        }
        if(key_skan==S3 && s3==0)
        {
          s3=1;
          bud_hou[bud_num]--;
          if(bud_hou[bud_num] == -1)
          {
            bud_hou[bud_num]=23;
          }
        }

        
      }
        if(poduroven==4)        //установка минут будильника
      {
        if(key_skan==S4 && s4==0)
        {
          s4=1;
          poduroven=5;
        }
        if(key_skan==S2 && s2==0)
        {
          s2=1;
          bud_min[bud_num]++;
          if(bud_min[bud_num] == 60)
          {
            bud_min[bud_num]=0;
          }
        }
        if(key_skan==S3 && s3==0)
        {
          s3=1;
          bud_min[bud_num]--;
          if(bud_min[bud_num] == -1)
          {
            bud_min[bud_num]=59;
          }
        }
      }


      
    key_off();              //отпускание кнопок
    key_exit();
  }

//уровень 6 (ТАЙМЕР)  
    if(uroven==6)
  {
           myGLCD.clrScr();        //очистка экрана
    myGLCD.print("5",LEFT,32);
  }
  //уровень 7 (CTREYLJVTH)  
    if(uroven==7)
  {
           myGLCD.clrScr();        //очистка экрана
    myGLCD.print("6",LEFT,32);
  }


  
  //!!!!!!!!!!!!!!!!!!!
    key_exit();                //ВОЗВРАТ НА УРОВЕНЬ 0
  //

  //key_skan=60 - кнопки не нажаты
  /*  if(key_skan==S1)  //S1
   {
   digitalWrite (light_pin, 1); //выключаем подсветку
   }
   if(key_skan==S2)  //S2
   {
   digitalWrite (light_pin, 0); //включаем подсветку
   }
   if(key_skan==S3)  //S3
   {
   digitalWrite (light_pin, 1); //выключаем подсветку
   }
   if(key_skan==S4)  //S4
   {
   digitalWrite (light_pin, 0); //включаем подсветку
   }
   */
  ///

  //!!!ОТЛАДОЧНАЯ ЧАСТЬ!!!
  // работа с COM портом
  //
  if(flag1==0)
  {
    flag1=1;
    //вывод времени в COM порт
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.print(seconds);
    Serial.print ("\n");
    Serial.print ("key_Skan");
    Serial.print(key_skan);
    Serial.print ("\n");

    //
    Serial_num=Serial.available();
    Serial_flag=0;
    Serial_num1 = 0;
    while(Serial_num > 0)
    {
      Serial_num--;
      Serial_char=Serial.read();
      Serial_tmp=Serial_char - '0';
      //
      //проверка допустимости символов
      //
      //выделяем цифры и двоеточие
      if((Serial_char >=48) && (Serial_char <= 58) && (Serial_flag == 0) && (Serial_num1 <= 5))
      {
        Serial_command[Serial_num1]=Serial_tmp;
        Serial_num1++;
        //              Serial.print(Serial_tmp);
        //              Serial.print ("\t");
      }
      else
      {
        Serial.println("BUUMM!");
        Serial_num1=0;
        Serial_flag=1;

      } 
      //
      if(Serial_num1 ==5)
      {

        //УСТАНОВКА МИНУТ
        minute=Serial_command[3]*10+Serial_command[4];
        //УСТАНОВКА ЧАСОВ hours
        hours=Serial_command[0]*10+Serial_command[1];
        //СБРОС СЕКУНД
        seconds=0;

        Serial_command[6]=Serial_command[1]*10+Serial_command[0];
        //          
      }


    }

  }
  //

/*bud_1=1;
bud_1_hou=0;
bud_1_min=0;
bud_1_povtor=1; //!!!!
bud_1_mel=3;    //!!!! */

  //будильник 1
  if ((bud_en[1]==1) && (seconds==1) && (hours==bud_hou[bud_num]) && (minute==bud_min[bud_num]))
  {
    myGLCD.invertText(true);
    myGLCD.print("1",78,40);
    bud_beep(3);
    myGLCD.invertText(false);
    myGLCD.print("1",78,40);

  }
  
  //начало рабочего дня
  if ((seconds==0) && (minute==0) && (hours==9))
  {
    beep1();
  }
  //будильник 2
  //конец рабочего дня
  if ((seconds==0) && (minute==00) && (hours==18))
  {
    beep2();
  }

  //будильник 3
  //Новые сутки
  if ((seconds==0) && (minute==0) && (hours==0))
  {
    beep4();
  }



  if(((seconds==0) && (minute==0) && (flag==0)))
  {
    //каждый час

    /*    tone (SOUNDPIN, 600, 100);
     delay(100);
     tone (SOUNDPIN, 900, 100);
     */
    //играем мелодию
    //    beep();










    //    flag=1;
  }
  if((seconds==0) && (flag==0))
  {
    //    tone (SOUNDPIN, 900, 100);
    flag=1;
  }


  // основная программа
}

//
// Прерывание вызывается один раз в миллисекунду 
//
//В этом месте можно делать регенерацию экрана
ISR(TIMER0_COMPA_vect)
{
  //задержка от дребезга
  count++;
  if(count==30)
  {
    count=0;
    key_skan=rd_key();
  }
}

//
//Прерывание от таймера секунд (TMR1)
//Прерывание вызывается раз в секунду

ISR(TIMER1_COMPA_vect)
{
  seconds++;
  flag1=0;
    flag=0;
  if(seconds==60)
  {
    seconds=0;
    minute++;
    if(minute==60)
    {
      minute=0;
      hours++;
      if(hours==24)
      {
        hours=0;
      }
    }
  }
  digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}
//


//


//возврат на уровень 0
void key_exit()
{
  if((key_skan==S1) && (s1s2 == 0) )
  {
    uroven=0;                  //возврат на 0-й уровень
    myGLCD.clrScr();        //очистка экрана
    return;
  }
}

//отпускание кнопок 
void key_off()
{
  if(key_skan==SN)              //отпускание кнопок
  {
    s1=0;
    s2=0;
    s3=0;
    s4=0;
    s1s2=0;
  }
  return;

}



