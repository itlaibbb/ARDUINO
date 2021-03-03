#include "clock.h"

void bud_beep(int num)
{
  switch (num)
  {
    case 1:
      beep1();
      break;
    case 2:
      beep2();
      break;
    case 3:
      beep3();
      break;
    case 4:
      beep4();
      break;
    default:
      beep3();
      break;
  }
}

//процедура вывода мелодии
//Нас утро встречает рассветом
void beep1 ()
 {

/*  int notes[] = {
700, 700, 700, 700, 625, 590, 520, 460, 350, 0, 0,
350, 460, 520, 500, 625, 590, 520, 700, 700, 780,
700, 625, 590, 520, 560, 350, 0,
360, 525, 590, 520, 700, 590, 520, 460
};

  int times[] = {
300, 300, 150, 150, 450, 150, 150, 450, 450, 600, 600,
450, 450, 150, 150, 450, 150, 150, 1350, 300, 150,
150, 1350, 300, 300, 150, 150, 450, 450, 600, 600,
450, 450, 150, 150, 450, 150, 150, 1350
};
     for (int i = 0; i < 39; i++)
      {
      tone(SOUNDPIN, notes[i], times[i]*2);
      delay(times[i]);
      noTone(SOUNDPIN);
      }
          return; 
}*/


  tone(SOUNDPIN, 700, 300);
  delay(600);
  tone(SOUNDPIN, 700, 300);
  delay(600);
  tone(SOUNDPIN, 780, 150);
  delay(300);
  tone(SOUNDPIN, 700, 150);
  delay(300);
  tone(SOUNDPIN, 625, 450);
  delay(600);
  tone(SOUNDPIN, 590, 150);
  delay(300);
  tone(SOUNDPIN, 520, 150);
  delay(300);
  tone(SOUNDPIN, 460, 450);
  delay(600);
  tone(SOUNDPIN, 350, 450);
  delay(600);
  delay(600);
  tone(SOUNDPIN, 350, 450);
  delay(600);
  tone(SOUNDPIN, 460, 450);
  delay(600);
  tone(SOUNDPIN, 520, 150);
  delay(300);
  tone(SOUNDPIN, 590, 150);
  delay(300);
  tone(SOUNDPIN, 625, 450);
  delay(600);
  tone(SOUNDPIN, 590, 150);
  delay(300);
  tone(SOUNDPIN, 520, 150);
  delay(300);
  tone(SOUNDPIN, 700, 1350);
  delay(1800);
  tone(SOUNDPIN, 700, 300);
  delay(600);
  tone(SOUNDPIN, 700, 300);
  delay(600);
  tone(SOUNDPIN, 780, 150);
  delay(300);
  tone(SOUNDPIN, 700, 150);
  delay(300);
  tone(SOUNDPIN, 625, 450);
  delay(600);
  tone(SOUNDPIN, 590, 150);
  delay(300);
  tone(SOUNDPIN, 520, 150);
  delay(300);
  tone(SOUNDPIN, 460, 450);
  delay(600);
  tone(SOUNDPIN, 350, 450);
  delay(600);
  delay(600);
  tone(SOUNDPIN, 350, 450);
  delay(600);
  tone(SOUNDPIN, 625, 450);
  delay(600);
  tone(SOUNDPIN, 590, 150);
  delay(300);
  tone(SOUNDPIN, 520, 150);
  delay(300);
  tone(SOUNDPIN, 700, 450);
  delay(600);
  tone(SOUNDPIN, 590, 150);
  delay(300);
  tone(SOUNDPIN, 520, 150);
  delay(300);
  tone(SOUNDPIN, 460, 1350);
  delay(5000);
            return;
}
//
//процедура вывода мелодии
//Имперский марш из "Звездных войн"
//
void beep2 ()
{
  int notes[] = {
392, 392, 392, 311, 466, 392, 311, 466, 392,
587, 587, 587, 622, 466, 369, 311, 466, 392,
784, 392, 392, 784, 739, 698, 659, 622, 659,
415, 554, 523, 493, 466, 440, 466,
311, 369, 311, 466, 392
};
int times[] = {
350, 350, 350, 250, 100, 350, 250, 100, 700,
350, 350, 350, 250, 100, 350, 250, 100, 700,
350, 250, 100, 350, 250, 100, 100, 100, 450,
150, 350, 250, 100, 100, 100, 450,
150, 350, 250, 100, 750
};
      for (int i = 0; i < 39; i++)
      {
      tone(SOUNDPIN, notes[i], times[i]*2);
      delay(times[i]*2);
      noTone(SOUNDPIN);
      }
    return;
}


//песенка рокодила Гены

void  Beep (int note, int time) {
tone(SOUNDPIN, note, time);
delay(time); // Пауза для заданой ноты
noTone(SOUNDPIN); // Останавливаем звук
}


void beep3() {
Beep(330, 200); Beep(439, 200); Beep(414, 200); Beep(439, 200);
Beep(493, 200); Beep(439, 200); Beep(391, 200); Beep(439, 200);
Beep(391, 400); Beep(349, 400); Beep(348, 600); Beep(32767, 200);
Beep(293, 200); Beep(391, 200); Beep(369, 200); Beep(391, 200);
Beep(439, 200); Beep(391, 200); Beep(293, 200); Beep(348, 200);
Beep(329, 600); Beep(32767, 600);
Beep(329, 200); Beep(439, 200); Beep(414, 200); Beep(439, 200);
Beep(493, 200); Beep(439, 200); Beep(391, 200); Beep(348, 200);
Beep(329, 400); Beep(293, 400); Beep(439, 600); Beep(32767, 200);
Beep(329, 200); Beep(523, 200); Beep(493, 200); Beep(439, 200);
Beep(414, 200); Beep(439, 200); Beep(493, 200); Beep(414, 200);
Beep(439, 600); Beep(32767, 600);
delay(100);
}

//Гимн СССР
void beep4(){
  
tone(SOUNDPIN, 174, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 233, 499.9995);
delay(555.555);
tone(SOUNDPIN, 174, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 195, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 220, 499.9995);
delay(555.555);
tone(SOUNDPIN, 146, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 146, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 195, 499.9995);
delay(555.555);
tone(SOUNDPIN, 174, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 155, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 174, 499.9995);
delay(555.555);
tone(SOUNDPIN, 116, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 116, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 130, 499.9995);
delay(555.555);
tone(SOUNDPIN, 130, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 146, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 155, 499.9995);
delay(555.555);
tone(SOUNDPIN, 155, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 174, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 195, 499.9995);
delay(555.555);
tone(SOUNDPIN, 220, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 233, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 261, 749.99925);
delay(833.3325);
tone(SOUNDPIN, 174, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 293, 499.9995);
delay(555.555);
tone(SOUNDPIN, 261, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 233, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 261, 499.9995);
delay(555.555);
tone(SOUNDPIN, 174, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 174, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 233, 499.9995);
delay(555.555);
tone(SOUNDPIN, 220, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 195, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 220, 499.9995);
delay(555.555);
tone(SOUNDPIN, 146, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 146, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 195, 499.9995);
delay(555.555);
tone(SOUNDPIN, 174, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 155, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 174, 499.9995);
delay(555.555);
tone(SOUNDPIN, 116, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 116, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 233, 499.9995);
delay(555.555);
tone(SOUNDPIN, 220, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 195, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 174, 999.999);
delay(1111.11);
tone(SOUNDPIN, 293, 999.999);
delay(1111.11);
tone(SOUNDPIN, 261, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 233, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 220, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 233, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 261, 749.99925);
delay(833.3325);
tone(SOUNDPIN, 174, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 174, 999.999);
delay(1111.11);
tone(SOUNDPIN, 233, 999.999);
delay(1111.11);
tone(SOUNDPIN, 220, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 195, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 174, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 195, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 220, 749.99925);
delay(833.3325);
tone(SOUNDPIN, 146, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 146, 999.999);
delay(1111.11);
tone(SOUNDPIN, 233, 499.9995);
delay(555.555);
tone(SOUNDPIN, 195, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 220, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 233, 499.9995);
delay(555.555);
tone(SOUNDPIN, 195, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 220, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 233, 499.9995);
delay(555.555);
tone(SOUNDPIN, 195, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 233, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 311, 999.999);
delay(1111.11);
tone(SOUNDPIN, 311, 999.999);
delay(1111.11);
tone(SOUNDPIN, 293, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 261, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 233, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 261, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 293, 749.99925);
delay(833.3325);
tone(SOUNDPIN, 233, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 233, 999.999);
delay(1111.11);
tone(SOUNDPIN, 261, 999.999);
delay(1111.11);
tone(SOUNDPIN, 233, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 220, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 195, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 220, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 233, 749.99925);
delay(833.3325);
tone(SOUNDPIN, 195, 249.99975);
delay(277.7775);
tone(SOUNDPIN, 195, 999.999);
delay(1111.11);
tone(SOUNDPIN, 233, 499.9995);
delay(555.555);
tone(SOUNDPIN, 220, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 195, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 174, 499.9995);
delay(555.555);
tone(SOUNDPIN, 116, 374.999625);
delay(416.66625);
tone(SOUNDPIN, 116, 124.999875);
delay(138.88875);
tone(SOUNDPIN, 174, 999.999);
delay(1111.11);
tone(SOUNDPIN, 195, 499.9995);
delay(555.555);
tone(SOUNDPIN, 220, 499.9995);
delay(555.555);
tone(SOUNDPIN, 233, 1999.998);
delay(2222.22);
}




