// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  HELPING FUNCTIONS ------------------------------------------------------
// ---------------------------------------------------  ARDUINO/PUMPS/DISPLAY  ---------------------------------------------------

#include "display.h"

int getShotPump(String drinkName) {
  int shotPump = -1;

  if (drinkName == drinks[0]) {
    for (int i = 0; i < amountOfPumpContent; i++) {
      if (pumpContent[i] == "Wodka") shotPump = i + 1;
    }

  }
  if (drinkName == drinks[1]) {
    for (int i = 0; i <= amountOfPumpContent; i++) {
      if (pumpContent[i] == "Malibu") shotPump = i + 1;
    }
  }
  if (drinkName == drinks[2]) {
    for (int i = 0; i <= amountOfPumpContent; i++) {
      if (pumpContent[i] == "Gin") shotPump = i + 1;
    }
  }
  pixels.clear();

  if (shotPump == 1) pixels.setPixelColor(0, 255, 255, 255);
  if (shotPump == 2) pixels.setPixelColor(1, 255, 255, 255);
  if (shotPump == 3) pixels.setPixelColor(3, 255, 255, 255);
  if (shotPump == 4) pixels.setPixelColor(4, 255, 255, 255);
  pixels.show();
  delay(500);
  return shotPump;
}

int getMixPump(String drinkName) {
  int mixPump = -1;
  if (drinkName == drinks[0]) {
    for (int i = 0; i < amountOfPumpContent; i++) {
      if (pumpContent[i] == "Energy") mixPump = i + 1;
    }

  }
  if (drinkName == drinks[1]) {
    for (int i = 0; i <= amountOfPumpContent; i++) {
      if (pumpContent[i] == "Maracuja") mixPump = i + 1;
    }
  }
  if (drinkName == drinks[2]) {
    for (int i = 0; i <= amountOfPumpContent; i++) {
      if (pumpContent[i] == "Tonic") mixPump = i + 1;
    }
  }
  pixels.clear();
  if (mixPump == 1) pixels.setPixelColor(0, 255, 255, 255);
  if (mixPump == 2) pixels.setPixelColor(1, 255, 255, 255);
  if (mixPump == 3) pixels.setPixelColor(3, 255, 255, 255);
  if (mixPump == 4) pixels.setPixelColor(4, 255, 255, 255);
  pixels.show();
  delay(500);
  return mixPump;
}

void pumpDos(int shotPump, int mixPump, double shotDelay, double mixDelay) {
  for (int i = 0; i < amountOfChecks; i++) check[i] = true;
  wttd("Please wait OR", 0, centerX("Please wait OR"), "CANCEL PROCESS!", 1, centerX("CANCEL PROCESS!"));
  pulse(255, 0, 0);
  delay(1000);
  lcd.clear();

  double starttime = millis(); // now static
  double actualTime = millis(); // now based on runtime
  double endtime = actualTime + shotDelay;
  double delayTime = mixDelay - shotDelay;

  double totalTime = (sizeOfGlass - ((shotDelay / 1000) * pspeed)) / pspeed;
  double progressBarStep = totalTime * 1000 / 18;

  while (actualTime < endtime) {
    actualTime = millis();
    cancelPushed = rotary.push();
    if (cancelPushed == 1) {
      if (shotPump == 1) digitalWrite(pump1[1], LOW);
      if (shotPump == 2) digitalWrite(pump2[1], LOW);
      if (shotPump == 3) digitalWrite(pump3[1], LOW);
      if (shotPump == 4) digitalWrite(pump4[1], LOW);
      cancelflag = true;
      break;
    } else {
      lcdLevelIndicator(actualTime - starttime, progressBarStep);
      if (shotPump == 1) digitalWrite(pump1[1], HIGH);
      if (shotPump == 2) digitalWrite(pump2[1], HIGH);
      if (shotPump == 3) digitalWrite(pump3[1], HIGH);
      if (shotPump == 4) digitalWrite(pump4[1], HIGH);
      if (mixPump == 1) digitalWrite(pump1[1], HIGH);
      if (mixPump == 2) digitalWrite(pump2[1], HIGH);
      if (mixPump == 3) digitalWrite(pump3[1], HIGH);
      if (mixPump == 4) digitalWrite(pump4[1], HIGH);
    }
  }
  if (shotPump == 1) digitalWrite(pump1[1], LOW);
  if (shotPump == 2) digitalWrite(pump2[1], LOW);
  if (shotPump == 3) digitalWrite(pump3[1], LOW);
  if (shotPump == 4) digitalWrite(pump4[1], LOW);

  actualTime = millis();
  double globalendtime = actualTime + delayTime;

  if (mixPump == 1) digitalWrite(pump1[1], HIGH);
  if (mixPump == 2) digitalWrite(pump2[1], HIGH);
  if (mixPump == 3) digitalWrite(pump3[1], HIGH);
  if (mixPump == 4) digitalWrite(pump4[1], HIGH);
  while ((actualTime < globalendtime) && !cancelflag) {
    actualTime = millis();
    cancelPushed = rotary.push();
    lcdLevelIndicator(actualTime - starttime, progressBarStep);

    if (cancelPushed == 1) {
      cancelflag = true;
      break;
    }
  }
  if (mixPump == 1) digitalWrite(pump1[1], LOW);
  if (mixPump == 2) digitalWrite(pump2[1], LOW);
  if (mixPump == 3) digitalWrite(pump3[1], LOW);
  if (mixPump == 4) digitalWrite(pump4[1], LOW);
}

int getDrinknumberFromDrinkname(String drinkName) {
  for (int i = 0; i < amountOfDrinks; i++) {
    if (drinks[i] == drinkName) return i;
  }
}

void pumpItUp(String drinkName, double shot, double mixy) {
  double shotTime = double(shot / pspeed) * 1000;
  double mixyTime = double(mixy / pspeed) * 1000;
  int shotPump = getShotPump(drinkName);
  int mixPump = getMixPump(drinkName);

  if ((mixPump == -1) || (shotPump == -1)) {
    drinkNotConfigured(drinkName);
    menulvl = 1;
    wttd("DRINKS", 0, centerX("DRINKS"), "-> " + drinks[0], 1, 0);
  } else {
    wttd("Please wait OR", 0, centerX("Please wait OR"), "CANCEL PROCESS!", 1, centerX("CANCEL PROCESS!"));
    delay(600);
    pumpDos(shotPump, mixPump, shotTime, mixyTime);
    if (globalflag) {
      if ((shotTime > 0) && !cancelflag) drinksCounter[getDrinknumberFromDrinkname(drinkName)]++;
      String counterString = "Counter = " + (String(drinksCounter[getDrinknumberFromDrinkname(drinkName)]));
      wttd("-> " + drinkName, 0, 0, counterString, 1, 0);
      delay(3200);
      wttd("-> Returning", 0, centerX("-> Returning"), "to main menu", 1, centerX("to main menu"));
      delay(1000);
      wttd(welcomeLine, 0, centerX(welcomeLine), "", 0, 0);
      cancelflag = false;
      menulvl = 0;
      cancelflag = false;
    }
  }
}

void smallDose(String diff, int pump, double timer) {
  if (diff == "shot") {
    if (pump == 1) digitalWrite(pump1[1], HIGH);
    if (pump == 2) digitalWrite(pump2[1], HIGH);
    if (pump == 3) digitalWrite(pump3[1], HIGH);
    if (pump == 4) digitalWrite(pump4[1], HIGH);
    delay(timer);
  }
  if (diff == "mix") {
    if (pump == 1) digitalWrite(pump1[1], HIGH);
    if (pump == 2) digitalWrite(pump2[1], HIGH);
    if (pump == 3) digitalWrite(pump3[1], HIGH);
    if (pump == 4) digitalWrite(pump4[1], HIGH);
    delay(timer);
  }
  digitalWrite(pump1[1], LOW);
  digitalWrite(pump2[1], LOW);
  digitalWrite(pump3[1], LOW);
  digitalWrite(pump4[1], LOW);
}

void drinkAndRelMixSelected(String drinkName, int mixRelation) {
  int procent = mixRelInts[mixRelation];
  double shotSize = (sizeOfGlass * procent) / 100;
  double rest = sizeOfGlass - shotSize;

  if (procent == 0) {
    wttd("DRIVERMODE", 1, centerX("DRIVERMODE"), "activated", 2, centerX("activated"));
    delay(2500);
  }
  pumpItUp(drinkName, shotSize, rest);
}
