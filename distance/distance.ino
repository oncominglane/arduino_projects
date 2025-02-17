#define PIN_TRIG 9
#define PIN_ECHO 10

#define PIN_DIOD 11
#define PIN_BUZZER 13


const int numReadings = 10; // Количество измерений для усреднения
long duration, cm;
long readings[numReadings]; // Массив для хранения измерений
int index = 0;              // Индекс текущего измерения
long total = 0;             // Сумма измерений

void setup() {
  // Инициализируем взаимодействие по последовательному порту
  Serial.begin(9600);

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
  if (average < 15) {
    digitalWrite(PIN_DIOD, 1);
     tone (PIN_BUZZER, 600); // включаем на пьезодинамик 600 Гц
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
  delay(10);
  //while(1) {}


}