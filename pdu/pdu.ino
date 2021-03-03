#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdint.h>

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
//  uint16_t dataToBeTransmitted[16] = {0, 0, 0, 0, 4};
  int16_t dataToBeTransmitted[16] = {0, 0, 0, 0, 4};
//[0] - j1_x
//[1] - j1_y
//[2] - j2_x
//[3] - j2_y
//
int joy_c1x=0;
int joy_c1y=0;
int joy_c2x=0;
int joy_c2y=0;
//
uint32_t message;  // Эта переменная для сбора обратного сообщения от приемника;

RF24 radio(CE_PIN, CSN_PIN);
//
//опрос джойситков
void joy(void)
{
  dataToBeTransmitted[0]=analogRead(j1_x);
  dataToBeTransmitted[1]=analogRead(j1_y);
  dataToBeTransmitted[2]=analogRead(j2_x);
  dataToBeTransmitted[3]=analogRead(j2_y);
  return;
}
//
//
void setup() {
  delay (2000);                           //задержка для заряда конденсаторов в БП NRF24
//
  pinMode(j1_x,INPUT);                    //правый джойстик
  pinMode(j1_y,INPUT);
  pinMode(j2_x,INPUT);                    //левый джойстик
  pinMode(j2_y,INPUT);

/*************************                Модуль NRF24                **********************/
    radio.begin();                          // Включение модуля;
    radio.setChannel(5);                    // Установка канала вещания;
    radio.setRetries(15,15);                // Установка интервала и количества попыток "дозвона" до приемника;
    radio.setDataRate(RF24_250KBPS);        // Установка минимальной скорости;
    radio.setPALevel(RF24_PA_MAX);          // Установка максимальной мощности;
    radio.setAutoAck(false);                    // Установка режима подтверждения приема;
    radio.enableAckPayload(); 
    radio.setAddressWidth(5);     //установить длину идентификатора трубы
    radio.openWritingPipe(writingPipe);     // Активация данных для отправки
    radio.openReadingPipe(1,readingPipe);   // Активация данных для чтения
//    radio.startListening();                 // Слушаем эфир.
//    radio.stopListening();                 // Слушаем эфир.
//калибровка джойстов
    joy();
    joy_c1x=511-dataToBeTransmitted[0];
    joy_c1y=511-dataToBeTransmitted[1];
    joy_c2x=511-dataToBeTransmitted[2];
    joy_c2y=511-dataToBeTransmitted[3];
}
void loop() {
  // put your main code here, to run repeatedly:
//  radio.stopListening();                 // Слушаем эфир.
  joy();
  delay(5);
//  radio.writeFast(&dataToBeTransmitted, 32);
  radio.write(&dataToBeTransmitted, 32);
//  radio.startListening();                 // Слушаем эфир.
if ( radio.isAckPayloadAvailable() ) {  // Ждем получения...
      radio.read(&message,sizeof(message));  //... и имеем переменную message с числом 111 от приемника.
                                      }

  delay(10);
}
