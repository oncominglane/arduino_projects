#define PIN_BUZZER 13
void setup() {
   pinMode(PIN_BUZZER, OUTPUT); // объявляем пин 10 как выход
}

void loop() {
   // увеличиваем частоту звука
   for (int x = 750; x < 1500 ; x++){
     tone (PIN_BUZZER, x);
     delay(1);
     }
   // уменьшаем частоту звука
   for (int x = 1500; x > 750 ; x--){
     tone (PIN_BUZZER, x);
     delay(1);
     }
    noTone(PIN_BUZZER); 
    //while(1) {}
}