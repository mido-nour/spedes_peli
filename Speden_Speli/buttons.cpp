#include "buttons.h"

volatile unsigned long viimePainallusAika2 = 0;
volatile unsigned long viimePainallusAika3 = 0;
volatile unsigned long viimePainallusAika4 = 0; //tässä muuttujat joka talenta viimeiset painelusaika 2--6 
volatile unsigned long viimePainallusAika5 = 0;
volatile unsigned long viimePainallusAika6 = 0;
const unsigned long debounceViive = 500; // tässä aika joka määrää hyväksytäänkö toinen napin painallus 500 millisekunti

void initButtonsAndButtonInterrupts(void)
{
    interrupts();                 // tässä joka varmisat toimiko keskeytykset. 
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);     // tässä asetelaan pinnit 2-6 ja sisäistä ylösvedo vastu eli input_ pullup
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    PCICR |= (1 << PCIE2);        // kun otetaan D pinneillä niiin käytetään PCICR jokta määritelään change interrupt jota halutaan 2-7
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22); // PCMSK jota määritelin mikä portin hluan että keskeytykst toimi 
}


ISR(PCINT2_vect)
{
    unsigned long nykyAika0 = millis(); // tässä talenetaan nykyaika millisekuntina pelinapeille jokaiselle erikseen
    unsigned long nykyAika1 = millis();
    unsigned long nykyAika2 = millis();
    unsigned long nykyAika3 = millis();

    if (digitalRead(2) == LOW && (nykyAika0 - viimePainallusAika2) > debounceViive) { // tarkista että nappi 2 painettu ja debounce - viive toimi
        viimePainallusAika2 = nykyAika0;
        nappiNumber = 0; // talenta napin numero
        nappiBool = true; //ilmoitaa että nappia on painettu
    }
    if (digitalRead(3) == LOW && (nykyAika1 - viimePainallusAika3) > debounceViive) { // tarkista että nappi 3 painettu ja debounce - viive toimi
        viimePainallusAika3 = nykyAika1;
        nappiNumber = 1; // talenta napin numero
        nappiBool = true; //ilmoitaa että nappia on painettu
    }
    if (digitalRead(4) == LOW && (nykyAika2 - viimePainallusAika4) > debounceViive) { // tarkista että nappi 4 painettu ja debounce - viive toimi
        viimePainallusAika4 = nykyAika2;
        nappiNumber = 2; // talenta napin numero
        nappiBool = true; //ilmoitaa että nappia on painettu
    }
    if (digitalRead(5) == LOW && (nykyAika3 - viimePainallusAika5) > debounceViive) { // tarkista että nappi 5 painettu ja debounce - viive toimi
        viimePainallusAika5 = nykyAika3;
        nappiNumber = 3; // talenta napin numero
        nappiBool = true; //ilmoitaa että nappia on painettu
    }
    if (digitalRead(6) == LOW && (nykyAika1 - viimePainallusAika6) > debounceViive) { // tarkista että nappi 6 painettu ja debounce - viive toimi
        viimePainallusAika6 = nykyAika1;
        nappiNumber = 4; // talenta napin numero 
        // viides on  start nappi joten sen tehtävä pikusen eri kun muut joite ei nappibool. 
    }
}