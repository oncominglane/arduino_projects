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

long n = 0;
int x = 100;
int count = 0;

void setup() {
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

  Timer1.initialize(100000);
  Timer1.attachInterrupt( add );
}

void loop() {
  while (digitalRead(A0) == LOW) {
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
  if (digitalRead(A0) == HIGH) { n = 0; count = 0; }
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
  digitalWrite(g, 1);
}

void two() {
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 0);
  digitalWrite(g, 0);
}

void three() {
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 1);
}

void four() {
  digitalWrite(a, 0);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
}

void five() {
  digitalWrite(a, 1);
  digitalWrite(b, 0);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
}

void six() {
  digitalWrite(a, 1);
  digitalWrite(b, 0);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
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
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
}

void nine() {
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
}

void add() {
  count ++;
  if (count == 10) {
    count = 0;  n++;
    if (n == 10000) { n = 0; }
  }
}