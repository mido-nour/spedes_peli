#include "leds.h"

void initializeLeds()
{
  Serial.begin(9600);
   for(int i = 0; i < 4; i++){
  pinMode(led[i],OUTPUT); // määritellään ledi lähdöt outputeiksi
   }
// see requirements for this function from leds.h
}

void setLed(byte ledNumber)
{
  if (ledNumber>=0 && ledNumber<4) // && eli ja operaatio
  { 
    digitalWrite(led[ledNumber], HIGH); //pitäisi sytyttää ledi
  }     //ledin numerot 0-3
// see requirements for this function from leds.h

}


void clearAllLeds()
{
  for(int i = 0; i<4; i++){
  digitalWrite(led[i],LOW); // sammuttaa led
  }
// see requirements for this function from leds.h
 
}

void setAllLeds()
{
  for(int i = 0; i<4; i++){
  digitalWrite(led[i],HIGH); //sytyttää led
  }
// see requirements for this function from leds.h
}


void show1()
{
  for (int number = 0; number < 16; number++){ // numerot 0-15
  for(int i = 0; i<4; i++){
  digitalWrite(led[i], (number & (1 << (3 - i)))); // kirjoittaa luvut 0-15 ledeillä binäärinä
  }
  delay(1000);  // sekunnin viive
  }


// see requirements for this function from leds.h
}

void show2(int rounds)
{
 
  int delayAika = 2000; // alussa kahden sekunnin välein valaistuu
  const int minDelay = 100; // minimi delay
 
  int Kaikkikierros = rounds*4;
  for(int kierros = 0; kierros < Kaikkikierros; kierros++){
    int randomNumber = random(4);

    for(int i = 0; i < 4; i++){ // numeroa vastaava ledi syttyisi
    if(i==randomNumber){ 
    digitalWrite(led[i], HIGH); // serial monitor numeroa vastaava valo syttyy 
    }
    else{
      digitalWrite(led[i],LOW); // kaikki muut ledit pois päältä 
    }
  }  
        
    delay(delayAika); //tällä hetkellä delay
    if(delayAika>minDelay){
      delayAika -= 50; //vähennetään delaytä
    }
  }
// see requirements for this function from leds.h  
}

