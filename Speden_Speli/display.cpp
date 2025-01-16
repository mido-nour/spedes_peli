#include "display.h"

uint8_t segmentDigits[] = {
  0b00111111,  // 0
  0b00000110,  // 1
  0b01011011,  // 2
  0b01001111,  // 3
  0b01100110,  // 4              // Tässä määritelty BCD-koodit numeroille, jotka tulostetaan 7seg näytölle
  0b01101101,  // 5
  0b01111101,  // 6
  0b00000111,  // 7
  0b01111111,  // 8
  0b01101111   // 9
};

void initializeDisplay(void) {
  pinMode(12, OUTPUT);  
  pinMode(11, OUTPUT);  
  pinMode(10, OUTPUT);            // pinnit 12,11,10,9,8 määritelty OUTPUT 
  pinMode(9, OUTPUT);  
  pinMode(8, OUTPUT);

  digitalWrite(12, LOW);          // pinni 12 alustettu LOW tilaan
  delay(100);                     // 100 millisekunnin viive
  digitalWrite(12, HIGH);         // pinni 12 alustettu HIGH tilaan

  digitalWrite(11, LOW);          // pinni 11 alustettu LOW tilaan
  digitalWrite(10, LOW);          // pinni 10 alustettu LOW tilaan
  digitalWrite(9, HIGH);          // pinni 9 alustettu HIGH tilaan
  digitalWrite(8, LOW);           // pinni 8 alustettu LOW tilaan
}

void writeByte(uint8_t bits, bool last) {   // Funktio, jolla kirjoitetaan bittejä (8) näytölle
  for (int i = 7; i >= 0; i--) {            // Looppi joka looppaa jokaisen bitin merkittävimmästä (MSB) vähiten merkittävään (LSB)
    digitalWrite(8, (bits >> i) & 1);       // Siirtää bitin vähiten merkittävään bittiin muuttujassa i, ja syöttää sen pinniin 8
    digitalWrite(11, HIGH);  
    digitalWrite(11, LOW);                  // pinni indikoi kellosykliä asettamalla se ensin HIGH tilaan ja sitten heti LOW tilaan
  }

  if (last) {                     // jos "last" on true, tämä tarkoittaa sitä että tämä bitti on viimeinen joka kirjoitetaan ylös
    digitalWrite(10, HIGH);       // pinnin 10 asettaminen ensin HIGH ja sitten LOW merkitsee sitä, että bitin siirto on suoritettu
    digitalWrite(10, LOW);  
    digitalWrite(9, LOW);   
  } else {                        // pinnin 9 asettaminen LOW tarkoittaa resettiä ja HIGH tarkoittaa valmistautumista seuraavaan bittisiirtoon
    digitalWrite(9, HIGH);  
  }
}

void writeHighAndLowNumber(uint8_t tens, uint8_t ones) {  // funktio jolla kirjataan kaksinumeroinen luku 7seg näytölle
  writeByte(segmentDigits[tens], false);          // "tens" kohtaan kirjataan kymmenykset, "false" tarkoittaa että tämä ei ole viimeinen bitti, joten seuraava bitti seuraa
  writeByte(segmentDigits[ones], true);           // "ones" kohtaan kirjataan yksittäiset numerot, "true" tarkoittaa viimeistä bittiä joka lopettaa datan siirron
}

void showResult(uint8_t number) {    // funktio jolla tulostetaan luku erottelemalla kympit ja ykköset
  uint8_t tens = number / 10;        // kymppien paikka lasketaan jakamalla kymmenellä
  uint8_t ones = number % 10;        // ykkösten paikka lasketaan ottamalla prosentuaalinen osuus siitä, mitä jää kun jaetaan 10

  writeHighAndLowNumber(ones, tens); // numerot tulostuu näytölle oikeille paikoilleen
}