#include <Adafruit_Sensor.h>
#include "Adafruit_BMP280.h"
#include <MQ2.h> // газ
#include "Wire.h"
// #include <iarduino_RF433_Transmitter.h>                   // Подключаем библиотеку для работы с передатчиком FS1000A
// iarduino_RF433_Transmitter radio(12);                     // Создаём объект radio для работы с библиотекой iarduino_RF433, указывая номер вывода к которому подключён передатчик
// int data[2];                                              // Создаём массив для передачи данных

int photocellPin = A0;

int photocellReading;

MQ2 mq2(A1);
Adafruit_BMP280 bme;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  bool status = bme.begin();
  // radio.begin();                                   // Инициируем работу передатчика FS1000A (в качестве параметра можно указать скорость ЧИСЛО бит/сек, тогда можно не вызывать функцию setDataRate)
  // radio.setDataRate(i433_1KBPS);                   // Указываем скорость передачи данных (i433_5KBPS, i433_4KBPS, i433_3KBPS, i433_2KBPS, i433_1KBPS, i433_500BPS, i433_100BPS), i433_1KBPS - 1кбит/сек
  // radio.openWritingPipe (5);                       // Открываем 5 трубу для передачи данных (передатчик может передавать данные только по одной из труб: 0...7)
}

void loop() {

  photocellReading = analogRead(photocellPin);

  Serial.print("Давление в атмосфере: ");
   Serial.println(bme.readPressure());
  Serial.print("Температура: ");
   Serial.println(bme.readTemperature());

  Serial.print("Содержание дыма в атмосфере: ");
    Serial.println(mq2.readSmoke());
  Serial.print("Влажность в атмосфере: ");
   Serial.println(mq2.readRatio());
  Serial.print("Содержание метана в атмосфере: ");
   Serial.println(mq2.readMethane());
   Serial.print("Содержание водорода в атмосфере: ");
   Serial.println(mq2.readHydrogen());
  Serial.print("Содержание сжи́женных углеводоро́дных га́зов в атмосфере: ");
   Serial.println(mq2.readLPG());
  Serial.print("Уровень освещенности: ");
   Serial.println(photocellReading); 

  Serial.println();
  // giver();
  delay(1500);
}

void giver() {
    data[0,1,2,3,4,5,6,7]                                 // это мы записываем данные датчика чтобы потом отправить, можно немного переделать код, чтобы не делать лишний массив
    radio.write(&data, sizeof(data));                     // отправляем данные из массива data указывая сколько байт массива мы хотим отправить
    delay(9000);                                          // пауза между пакетами необязательно если будет задержка в другом месте
}

// data[0] = analogRead(A1);                             // считываем показания Trema слайдера с вывода A1 и записываем их в 0 элемент массива data          |
  //   data[1] = analogRead(A2);                             // считываем показания Trema потенциометра с вывода A2 и записываем их в 1 элемент массива data | альтернатива. Вместо Serial.print() сразу отправлять