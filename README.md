# Parametry projektu

Nazwa: pm-lab-2  
Autor: Paweł Dąbal (pawel.dabal@wat.edu.pl)  
Opis: Projekt bazowy repozytorium na drugie spotkanie laboratoryjne z przedmiotu _Technika mikroprocesorowa_.  
Wersja: v1.0  
Data: 30.11.2020 r.

# Informacje o studencie

Imię i nazwisko studenta: Mikołaj Żendarski
Numer albumu: 69665 
Grupa studencka: WELE18DX1S1

# Pytania do zadań z instrukcji

 W jaki sposób można określić czas trwania
opóźnienia zrealizowanego z użyciem pętli?
Na podstawie ilości akcji jaka jest do wykonania i dlugości ich trwania przy dwóch akcjach włącz i wyłącz trwajacej po sekundzie opóżnienie wyniesie 2 sekundy sekunde aby włączyc i sekunde aby wyłączyć.
Zpisuje tutaj kody bo nie ufam temu programowi, ponieważ na stronie po commit'cie i push'u widze tylko zmiane poprzez dodanie zdjecia stąd moje obawy

#include <avr/io.h>

int main() 
{
  uint32_t i;

  DDRB |= (1 << 5); // pinmode(13, OUTPUT);
  while (1)
  {
    PORTB |= (1 << 5); //digitalWrite(13. HIGH);
    i = 0x3FFFF;
    do
    {
      __asm__ __volatile__("nop");
    } while (i--);
    PORTB &= !(1 << 5); //digitalWrite(13,LOW);
    i = 0x3FFFF;
    do
    {
     __asm__ __volatile__("nop");
    } while (i--);
  }
}

Kod 2.2.3
#include <avr/io.h>

uint8_t ledState[] = {0xFF, 0x7E, 0x3C, 0x18, 0x00, 0x18, 0x3C, 0x7E};
uint8_t *pLedState = ledState;
bool state = true;

void togglePinD13(bool *state)
{
  PORTB = (*state << 5);
  *state = !(*state);
}

void delay()
{
  for (uint32_t j = 0x2FFFF; j > 0; j--)
  {
    __asm__ __volatile__("nop");
  }
}

int main()
{
  DDRB |= (1 << 5);
  DDRD |= 0xFF;
  while (1)
  {
    togglePinD13(&state);
    delay();
    for (uint8_t i = 0; i < sizeof(ledState); i++)
    {
      PORTD = ledState[i];
      delay();
    }    
    pLedState = ledState;
    for (uint8_t i = 0; i < sizeof(ledState); i++)
    {
     PORTD = *pLedState;
     pLedState++;
     delay();
    }
  }
}
2.2.4
#include <avr/io.h>
#define SOLUTION 0
uint8_t button;
bool state = true;

void togglePinD13(bool *state) { // Zmiana stanu wyjścia D13
 PORTB = (*state << 5);
 *state = !(*state);
}

void delay() {
  for (uint32_t j = 0x1FFFF; j > 0; j--)
   __asm__ __volatile__("nop");
}

int main () {
  DDRB &= !(1 << 0); // Skasowanie PB05 (D8) - praca jako wejście
  DDRB |= (1 << 5); // Ustawienie PB5 (D13) - praca jako wyjście
  while(1)
  {
#if (SOLUTION == 0)
     button = (PINB & (1 << PINB0)); // Odczytanie stanu PB0
     if (button == 0) { // Jeżeli przycisk puszczony -przełącz
      togglePinD13(&state); // Zmiana stanu PB5}
     delay(); // Pauza
     }
    else // W przeciwnym razie
     delay(); //Pauza
#elif (SOLUTION == 1)
   //Rozwiązanie alternatywne
   while (!(PINB & (1 << PinB0))) {
     tooglePinD13(&state); // Zmiana stanu PB5
     delay(); //Pauza
    }
#endif
  }
}