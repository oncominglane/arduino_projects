#include "TimerOne.h"
#define a 2
#define b 3
#define c 4
#define d 5
#define e 6
#define f 7
#define g 8

#define d1 A1
#define d2 A2
#define d3 A3
#define d4 A4

#define PIN_TRIG 9
#define PIN_ECHO 10

#define PIN_DIOD 11
#define PIN_BUZZER 13


long n = 0;
int x = 100;
int count = 0;


const int numReadings = 10; // Количество измерений для усреднения
long duration, cm;
long readings[numReadings]; // Массив для хранения измерений
int index = 0;              // Индекс текущего измерения
long total = 0;             // Сумма измерений

void setup() {
  // Инициализируем взаимодействие по последовательному порту
  Serial.begin(9600);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  
  pinMode(A0, INPUT);



  // Определяем вводы и выводы
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_DIOD, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  // Инициализируем массив измерений нулями
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Убираем старейшее измерение из суммы
  total -= readings[index];

  // Генерируем короткий импульс длительностью 2-5 микросекунд.
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);

  // Выставив высокий уровень сигнала, ждем около 10 микросекунд.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Время задержки акустического сигнала на эхолокаторе.
  duration = pulseIn(PIN_ECHO, HIGH);

  // Преобразуем время в расстояние
  cm = (duration / 2) / 29.1;

  // Добавляем новое измерение в массив и к общей сумме
  readings[index] = cm;
  total += readings[index];

  // Переходим к следующему элементу массива
  index = (index + 1) % numReadings;

  // Вычисляем среднее значение
  long average = total / numReadings;


  // Управляем светодиодом
  if (average < 5) {
    digitalWrite(PIN_DIOD, 1);
     tone (PIN_BUZZER, 900); // включаем на пьезодинамик 600 Гц
     delay(50); // ждем 1 секунду
     noTone(PIN_BUZZER); 

  } else if (average < 15) {
    digitalWrite(PIN_DIOD, 1);
     tone (PIN_BUZZER, 900); // включаем на пьезодинамик 600 Гц
     delay(100); // ждем 1 секунду
     noTone(PIN_BUZZER); 
  } else {
    digitalWrite(PIN_DIOD, 0);
  }

  // Выводим среднее значение расстояния
  Serial.print("Среднее расстояние до объекта: ");
  Serial.print(average);
  Serial.println(" см.");

  // Задержка между измерениями для корректной работы
  delay(100);
  n = average;
  //while(1) {}
  if (digitalRead(A0) == LOW) {
      clearLEDs();
      pickDigit(3); // включаем первую цифру (тысячи)
      pickNumber((n / 1000));
      delay(5);

      clearLEDs();
      pickDigit(2); // включаем вторую цифру (сотни)
      pickNumber((n % 1000) / 100);
      delay(5);

      clearLEDs();
      pickDigit(1); // включаем третью цифру (десятки)
      pickNumber(n % 100 / 10);
      delay(5);

      clearLEDs();
      pickDigit(0); // включаем четвертую цифру (единицы)
      pickNumber(n % 10);
      delay(5);
    }

}






// определение разряда
void pickDigit(int x) {
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  switch (x) {
    case 0: digitalWrite(d1, LOW);  break;
    case 1: digitalWrite(d2, LOW);  break;
    case 2: digitalWrite(d3, LOW);  break;
    default: digitalWrite(d4, LOW); break;
  }
}

// определение символа (цифры)
void pickNumber(int x) {
  switch (x) {
    case 1: one();     break;
    case 2: two();     break;
    case 3: three();   break;
    case 4: four();    break;
    case 5: five();    break;
    case 6: six();     break;
    case 7: seven();   break;
    case 8: eight();   break;
    case 9: nine();    break;
    default: zero();   break;
  }
}

// очистка индикатора
void clearLEDs() {
  digitalWrite(a, 0);
  digitalWrite(b, 0);
  digitalWrite(c, 0);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 0);
}

void zero() {
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 0);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
}



void one() {
  digitalWrite(a, 0);
  digitalWrite(b, 1);
  digitalWrite(c, 0);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 0);
}

void two() {
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 0);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 0);
  digitalWrite(g, 1);
}

void three() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void four() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void five() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void six() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void seven() {
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 0);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 1);
}

void eight() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void nine() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void add() {
  count ++;
  if (count == 10) {
    count = 0;  n++;
    if (n == 10000) { n = 0; }
  }
}