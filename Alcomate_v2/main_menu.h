// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------  MENU FUNCTIONS -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------

#include "toolbox.h"

void startMenu() {
  colorFlow();
  buttonPushType = rotary.pushType(1500);
  //delay(100);
  if (buttonPushType == 2) {
    wttd(welcomeLine, 0, centerX(welcomeLine), "-> Settings (3)", 1, 0);
    delay(400);
    wttd(welcomeLine, 0, centerX(welcomeLine), "-> Settings (2)", 1, 0);
    delay(400);
    wttd(welcomeLine, 0, centerX(welcomeLine), "-> Settings (1)", 1, 0);
    delay(400);
    wttd(welcomeLine, 0, centerX(welcomeLine), "-> Settings (0)", 1, 0);

    menulvl = 90;
    chosenOption = 0;
    wttd("SETTINGS", 0, centerX("SETTINGS"), "-> " + settings[0], 1, 0);
  }
  if (buttonPushType == 1) {
    menulvl = 1;
    wttd("DRINKS", 0, centerX("DRINKS"), "-> " + drinks[0], 1, 0);
  }

}

void drinkMenu() {
  colorFlow();
  rotDet = rotary.rotate();
  if ((rotDet == cw) && (chosenOption < (amountOfDrinks - 1))) {
    chosenOption++;
    wttd("DRINKS", 0, centerX("DRINKS"), "-> " + drinks[chosenOption], 1, 0);
  }
  if ((rotDet == ccw) && (chosenOption > 0)) {
    chosenOption--;
    wttd("DRINKS", 0, centerX("DRINKS"), "-> " + drinks[chosenOption], 1, 0);
  }
  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (drinks[chosenOption] == backCommando) {
      wttd(welcomeLine, 0, centerX(welcomeLine), "", 0, 0);
      menulvl = 0;
      chosenOption = 0;
    } else {
      menulvl = 2;
      chosenDrink = drinks[chosenOption];
      int lengthDrinkString = (maxX - chosenDrink.length()) / 2;
      originalChosenOption = chosenOption;
      chosenOption = 2;
      wttd(drinks[originalChosenOption], 0, lengthDrinkString, "-> " + mixRel[chosenOption], 1, 0);
    }
  }
}

void drinkSelected() {
  pulse(0,0,255);
  int lengthDrinkString = (maxX - chosenDrink.length()) / 2;
  rotDet = rotary.rotate();
  if ((rotDet == cw) && (chosenOption < (amountOfMixRel - 1))) {
    chosenOption++;
    wttd(drinks[originalChosenOption], 0, lengthDrinkString, "-> " + mixRel[chosenOption], 1, 0);
  }
  if ((rotDet == ccw) && (chosenOption > 0)) {
    chosenOption--;
    wttd(drinks[originalChosenOption], 0, lengthDrinkString, "-> " + mixRel[chosenOption], 1, 0);
  }
  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (mixRel[chosenOption] == backCommando) {
      shortPulse(255,0,0);
      delay(300);
      menulvl = 1;
      chosenMixtureRelation = "";
      chosenDrink = "";
      wttd("DRINKS", 0, 5, "-> " + drinks[0], 1, 0);
      chosenOption = 0;
    } else if (mixRel[chosenOption] == mixer) {
      globalflag = false;
      smallDose("mix", getMixPump(chosenDrink), smallDoseAmount);
    } else if (mixRel[chosenOption] == liquor) {
      globalflag = false;
      smallDose("shot", getShotPump(chosenDrink), smallDoseAmount);
    } else if ((mixRel[chosenOption] != mixer) && (mixRel[chosenOption] != liquor)) { // Array Element in der Mixverhältnisliste
      globalflag = true;
      shortPulse(0,255,0);
      delay(300);
      drinkAndRelMixSelected(chosenDrink, chosenOption);
      chosenOption = 0; // Name des Drinks
    }
  }
}
