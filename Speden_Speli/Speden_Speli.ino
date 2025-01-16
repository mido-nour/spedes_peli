#include "buttons.h"
#include "leds.h"
#include "display.h"
#include "SpedenSpelit.h"

void setup()
{
  // initializoidaan kaikki moduulit ja muuttujat
  pinMode(buzzer, OUTPUT); // buzzer pin
  initializeGame(randomArray, 100);
  initializeGame(userArray, 100);
  initButtonsAndButtonInterrupts();
  initializeLeds();
  initializeDisplay();
}

void loop()
{
  if (nappiNumber >= 4) // jos start nappia painetaan
  {
    startTheGame(); // aloitetaan peli
    nappiNumber = -1; // alustetaan nappi takaisin lähtöarvoon
  }

  if (newTimerInterrupt == true)             // jos timerilta on tullut interrupt, antaa peli pelata kierroksen
  {
    newTimerInterrupt = false;              // asetetaan interruptin tila nollaan

    if (jono % 10 == 0)                  // jos kierroksen jakojäännös on nolla
    {
      nopeus = nopeus - (nopeus * 0.1);     // nopeutetaan peliä 10 prosenttia
    }

    initializeTimer(nopeus);                // alustetaan timerille uusi nopeus
    clearAllLeds();                        // kaikki ledit pois päältä ennenkuin sytytetään uusia
    jono++;                               // lisätään arvoa muuttujaan joka päättää kohdan taulukossa mihin random numero tallennetaan
    randomMuuttuja = random(0,4);        // arvotaan luku muuttujaa
    randomArray[jono] = randomMuuttuja; // muuttujan luku taulukkoon

    while (randomArray[jono] == randomArray[jono-1]) // while loop varmistaa ettei sama ledi syty monesti peräkkäin
    {
      randomArray[jono] = random(0,4); // jos arvottu numero on sama kuin edellinen, arvotaan uudelleen
    }

    switch (randomArray[jono]) // switch case päättää mikä ledi sytytetään
    {
      case 0:
        noTone(buzzer);
        setLed(0);
        tone(buzzer, 500);
        break;
      case 1:
        noTone(buzzer);
        setLed(1);
        tone(buzzer, 800);
        break;
      case 2:
        noTone(buzzer);
        setLed(2);
        tone(buzzer, 1450);
        break;
      default:
        noTone(buzzer);
        setLed(3);
        tone(buzzer, 2000);
        break;
    }

    nappiBool = 0; // nappibool nollaksi ettei edelliset painallukset vaikuta uusiin painalluksiin ledien arpomisen jälkeen
  }

  if (nappiBool == 1)          // jos nappia on painettu ja keskeytystä ei ole käsitelty
  {
    nappiJono++;             // lisätään arvoa muuttujaan joka määrää mihin kohtaan taulukossa painallus tallennetaan
    checkGame(nappiNumber); // tarkastetaan menikö oikein
    nappiBool = 0;         // asetetaan napin painallusta seuraava muuttuja takaisin nollille
  }
}

void initializeTimer(int nopeus) // alustetaan timer
{
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = nopeus; 
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (timerStopBool << CS12) | (0 << CS11) | (0 << CS10); // 256 prescaler
  TIMSK1 |= (1 << OCIE1A);                                       // Enabloidaan compare A match keskeytykset
}

ISR(TIMER1_COMPA_vect) 
{
  newTimerInterrupt = true;                                  // uusi keskeytys tallennetaan muuttujaan
}

void checkGame(int nappiNumber)                           // tämä funktio tarkistaa menikö napin painallus oikein
{
  userArray[nappiJono] = nappiNumber;                   // tallennetaan painettu nappi userArray taulukkoon
  newTimerInterrupt = false;                           // asetetaan TIMER ISR false ettei looppi pyörähdä selkäni takana
  if (userArray[nappiJono] == randomArray[nappiJono]) // katsotaan menikö oikein napin painallus
  {
    tulos++;            // oikein = tulos eli pisteet kasvaa
    if(tulos > 99)
    {
      tulos = 0;
    }
    showResult(tulos); // näytetään tulos segmenttinäytöllä
  }
  else                // jos oli väärä nappi
  {
    stopTheGame();  // pysäytetään peli
  }
}

void initializeGame(int *array, int size) // asetetaan muuttujien lähtöarvot nollille / nollataan peli!
{
  tulos = 0;
  jono = 0;
  for (int i = 0; i < size; i++)
  {
    array[i] = 5;
  }
}

void startTheGame()                        // aloita peli-funktio
{
  nappiJono = 0;                         // nollataan nappijono muuttuja
  timerStopBool = 1;                    // timeri käyntiin muuttamalla tämä arvoon 1
  nopeus = 62499;                      // aloitusnopeus
  initializeTimer(nopeus);            // alustetaan timer aloitusnopeuteen
  clearAllLeds();                    // ledit pois päältä kun aloitetaan peli, jotta yksi ledi palaa kerrallaan
  initializeGame(randomArray, 100); // kutsutaan pelin nollaus funktiota
}

void stopTheGame()                  // pysäytä peli-funktio
{
  nappiNumber = -1;               // napin painalluksia seuraavan muuttujan nollaus
  timerStopBool = 0;             // tämä pysäyttää timerin
  initializeTimer(nopeus);      // alustetaan timeri jotta se pysähtyy
  setAllLeds();                // käytetään kaikki ledit päällä pelin loppumisen merkiksi
  delay(200);                 // delay valoja varten
  clearAllLeds();            // kaikki ledit pois
  noTone(buzzer);           //  piezo buzzer hiljaiseksi
}