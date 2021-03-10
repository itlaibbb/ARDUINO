#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>

#define debug_1

#define j1_x  A0
#define j1_y  A1
#define j2_x  A2
#define j2_y  A3
#define sw1   8     //кнопка правого джойстика
#define sw2   7     //кнопка левого джойстика
#define LED   6     //светодиод возле джойстиков

#define CE_PIN 9    //
#define CSN_PIN 10  //
const uint64_t readingPipe = 0xE8E8F0F0AALL;
const uint64_t writingPipe = 0xE8E8F0F0ABLL;
//массив для передачи
  int16_t dataToBeTransmitted[16] = {0, 0, 0, 0, 4};
  float dataj=0;
//[0] - j1_x
//[1] - j1_y
//[2] - j2_x
//[3] - j2_y
//
float joy_c[]={1,1,1,1};
//
  int16_t message;  // Эта переменная для сбора обратного сообщения от приемника;

RF24 radio(CE_PIN, CSN_PIN);
//
//опрос джойситков
void joy(void)
{
  dataj=analogRead(j1_x)*joy_c[0];
  dataToBeTransmitted[0]=dataj;
  dataj=analogRead(j1_y)*joy_c[1];
  dataToBeTransmitted[1]=dataj;
  dataj=analogRead(j2_x)*joy_c[2];
  dataToBeTransmitted[2]=dataj;
  dataj=analogRead(j2_y)*joy_c[3];
  dataToBeTransmitted[3]=dataj;

  return;
}
//
//
#ifdef debug_1
void serial_out()
{
  Serial.print(dataToBeTransmitted[0]);
  Serial.print("  ");
  Serial.print(dataToBeTransmitted[1]);
  Serial.print("  ");
  Serial.print(dataToBeTransmitted[2]);
  Serial.print("  ");
  Serial.print(dataToBeTransmitted[3]);
  Serial.print("\n");
  return;  
}
#endif
//
//
void setup() {
  delay (2000);                           //задержка для заряда конденсаторов в БП NRF24
//
  pinMode(j1_x,INPUT);                    //правый джойстик
  pinMode(j1_y,INPUT);
  pinMode(j2_x,INPUT);                    //левый джойстик
  pinMode(j2_y,INPUT);
//  pinMode(LED,OUTPUT);                    //светодиод возле джойстиков
//
#ifdef debug_1
   Serial.begin(1000000); /* установка соединения */
#endif
//
/*************************                Модуль NRF24                **********************/
    radio.begin();                          // Включение модуля;
    radio.setChannel(5);                    // Установка канала вещания;
    radio.setRetries(15,15);                // Установка интервала и количества попыток "дозвона" до приемника;
    radio.setDataRate(RF24_250KBPS);        // Установка минимальной скорости;
    radio.setPALevel(RF24_PA_MAX);          // Установка максимальной мощности;
    radio.setAutoAck(true);                    // Установка режима подтверждения приема;
    radio.enableAckPayload(); 
    radio.setAddressWidth(5);     //установить длину идентификатора трубы
    radio.openWritingPipe(writingPipe);     // Активация данных для отправки
    radio.openReadingPipe(1,readingPipe);   // Активация данных для чтения
//    radio.startListening();                 // Слушаем эфир.
//    radio.stopListening();                 // Слушаем эфир.
//калибровка джойстов
    joy();
    for(int i=0;i<4;i++)
    {
      joy_c[i]=511.0/dataToBeTransmitted[i];
    }
   
}
void loop() {
  // put your main code here, to run repeatedly:
//  radio.stopListening();                 // Слушаем эфир.
  joy();
  delay(5);
#ifdef debug_1
  serial_out();
#endif
//  radio.writeFast(&dataToBeTransmitted, 32);
  radio.write(&dataToBeTransmitted, 16);
//  radio.startListening();                 // Слушаем эфир.
      if ( radio.isAckPayloadAvailable() ) {  // Ждем получения...
        radio.read(&message,sizeof(message));  //... и имеем переменную message с числом 111 от приемника.
                                           }
                dataToBeTransmitted[4]=message;
/*      if(message != 111)
      {
        digitalWrite (LED,HIGH);
      }
      else
      {
         digitalWrite (LED,LOW);
      }
    */
  delay (10);
    }

  
