#include <Arduino.h>
volatile int state = LOW;
 int main() {
   init(); // Inicjalizacja biblioteki Arduino
   DDRB|= B00110000; // Konfiguracja portu PB4 i PB5 (D12 i D13) jako wyjście
   PORTD |= (1 << PORTD2); // Włączenie portu PD2 dla INT0
   EICRA |= (1 << ISC00); //Wykrywanie każdej zmiany stanu logicznego
   EIMSK |= (1 << INT0); //Włączenie przerwania INT0
   sei(); //Globalne włączenie przerwań
   while (1) {
     PORTB |= (1 << PORTB5);
     delay(500);
     PORTB &= !(1 << PORTB5);
     delay(500);
   }
 }
 
 ISR(INTO_vect){
   state = !state;
   digitalWrite(12, state);
 }