

void detectTemperature()
{
  byte data[2];
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);

  if (millis() - lastUpdateTime > TEMP_UPDATE_TIME)
  {
    lastUpdateTime = millis();
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);
    data[0]= ds.read();
    data[1] = ds.read();

    // Формируем значение
 //   temperature = (data[1] << 8) + data[0]; temperature = temperature >> 4;
       temperature =  ((data[1] << 8) | data[0]) * 0.0625;
    // подготовка буфера строки
      for (int i=0; i<7; i++) {teme[i]=' ';}  // заполнение пробелами
      teme[6]='\r';
      teme[7]='\n';
      dtostrf(temperature, 2, 2, teme);      //в массиве teme строка о значением температуры
  }
    return;
}
