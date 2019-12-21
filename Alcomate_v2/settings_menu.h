// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  SETTINGS FUNCTIONS -----------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------

void settingsstartMenu() {
  pixels.setPixelColor(9, 255, 255, 255);
  pixels.show();
  rotDet = rotary.rotate();
  if ((rotDet == cw) && (chosenOption < (amountOfSettings - 1))) {
    chosenOption++;

    wttd("SETTINGS", 0, centerX("SETTINGS"), "-> " + settings[chosenOption], 1, 0);
  }
  if ((rotDet == ccw) && (chosenOption > 0)) {
    chosenOption--;

    wttd("SETTINGS", 0, centerX("SETTINGS"), "-> " + settings[chosenOption], 1, 0);
  }

  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (settings[chosenOption] == backCommando) {
      wttd(welcomeLine, 0, (20 - welcomeLine.length()) / 2, "", 1, 0);
      menulvl = 0;
      chosenOption = 0;
    } else if (settings[chosenOption] == "Pumpsettings") {
      wttd("PUMPSETTINGS", 0, centerX("PUMPSETTINGS"), "-> " + pumpsettings[0], 1, 0);
      menulvl = 91;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    } else if (settings[chosenOption] == "Glasssize") {
      wttd("GLASSSIZE", 0, centerX("GLASSSIZE"), sizeOfGlass, 1, 0);
      menulvl = 93;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    } else if (settings[chosenOption] == "Small shots") {
      wttd("SHOTSIZE", 0, centerX("SHOTSIZE"), smallDoseAmount, 1, 0);
      menulvl = 94;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    } else if (settings[chosenOption] == "CLEANING") {
      wttd("CLEANING", 0, centerX("CLEANING"), "-> " + cleaner[0] + " (off)", 1, 0);
      menulvl = 100;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    } else if (settings[chosenOption] == "Test pumps") {
      wttd("TEST PUMPS", 0, centerX("TEST PUMPS"), "-> " + pumpsettings[0], 1, 0);
      menulvl = 95;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    } else if (settings[chosenOption] == "Flow counter") {
      String displayCounter = String(drinksCounter[0]) + "x " + String(drinks[0]);
      wttd("FLOW COUNTER", 0, centerX("FLOW COUNTER"), displayCounter, 1, 0);
      menulvl = 96;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    }
  }
}

void cleaningMenu() {
  pixels.setPixelColor(9, 255, 0, 255);
  pixels.show();
  rotDet = rotary.rotate();
  if ((rotDet == cw) && (chosenOption < (3 - 1))) {
    chosenOption++;
    wttd("CLEANING", 0, centerX("CLEANING"), "-> " + cleaner[chosenOption], 1, 0);
  }
  if ((rotDet == ccw) && (chosenOption > 0)) {
    chosenOption--;
    wttd("CLEANING", 0, centerX("CLEANING"), "-> " + cleaner[chosenOption], 1, 0);
  }

  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (!cleanStart) cleanStart = true;
    else if (cleanStart) cleanStart = false;

    if (cleaner[chosenOption] == backCommando) {
      wttd("SETTINGS", 0, centerX("SETTINGS"), "-> " + settings[0], 1, 0);
      menulvl = 90;
      chosenOption = 0;
    } else if (cleaner[chosenOption] == "P1 + P2") {
      if (cleanStart) {
        wttd("CLEANING", 0, centerX("CLEANING"), "-> " + cleaner[chosenOption] + " (on)", 1, 0);
        digitalWrite(pump1[1], LOW);
        digitalWrite(pump2[1], LOW);
      }
      if (!cleanStart) {
        wttd("CLEANING", 0, centerX("CLEANING"), "-> " + cleaner[chosenOption] + " (off)", 1, 0);
        digitalWrite(pump1[1], HIGH);
        digitalWrite(pump2[1], HIGH);
      }
    } else if (cleaner[chosenOption] == "P3 + P4") {
      wttd("CLEANING", 0, centerX("CLEANING"), "-> " + cleaner[0], 1, 0);
      if (cleanStart) {
        digitalWrite(pump3[1], LOW);
        digitalWrite(pump4[1], LOW);
      }
      if (!cleanStart) {
        digitalWrite(pump3[1], HIGH);
        digitalWrite(pump4[1], HIGH);
      }
    }
  }
}

void setPumps() {
  pixels.setPixelColor(9, 0, 255, 255);
  pixels.show();
  rotDet = rotary.rotate();
  if ((rotDet == cw) && (chosenOption < (amountOfPumps - 1))) {
    chosenOption++;
    wttd("PUMPSETTINGS", 0, centerX("PUMPSETTINGS"), "-> " + pumpsettings[chosenOption], 1, 0);
  }
  if ((rotDet == ccw) && (chosenOption > 0)) {
    chosenOption--;
    wttd("PUMPSETTINGS", 0, centerX("PUMPSETTINGS"), "-> " + pumpsettings[chosenOption], 1, 0);
  }

  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (pumpsettings[chosenOption] == backCommando) {
      wttd("SETTINGS", 0, centerX("SETTINGS"), "-> " + settings[0], 1, 0);
      menulvl = 90;
      chosenOption = 0;
    } else if (pumpsettings[chosenOption] == "P1") {
      wttd("P1", 0, centerX("P1"), "= " + fluids[0], 1, 0);
      menulvl = 92;
      chosenPump = 1;
      chosenOption = 0;
    } else if (pumpsettings[chosenOption] == "P2") {
      wttd("P2", 0, centerX("P2"), "= " + fluids[0], 1, 0);
      menulvl = 92;
      chosenPump = 2;
      chosenOption = 0;
    } else if (pumpsettings[chosenOption] == "P3") {
      wttd("P3", 0, centerX("P3"), "= " + fluids[0], 1, 0);
      menulvl = 92;
      chosenPump = 3;
      chosenOption = 0;
    } else if (pumpsettings[chosenOption] == "P4") {
      wttd("P4", 0, centerX("P4"), "= " + fluids[0], 1, 0);
      menulvl = 92;
      chosenPump = 4;
      chosenOption = 0;
    }
  }
}

void setPump() {
  pixels.setPixelColor(9, 255, 255, 0);
  pixels.show();
  rotDet = rotary.rotate();
  bool drinkExisting = false;
  if ((rotDet == cw) && (chosenOption < (amountOfFluids - 1))) {
    chosenOption++;
    if (fluids[chosenOption] == pumpContent[chosenPump - 1]) drinkExisting = true;

    if (drinkExisting) {
      wttd(pumpsettings[chosenPump - 1], 0, centerX(pumpsettings[chosenPump - 1]), "= " + fluids[chosenOption] + " *", 1, 0);
    } else {
      wttd(pumpsettings[chosenPump - 1], 0, centerX(pumpsettings[chosenPump - 1]), "= " + fluids[chosenOption], 1, 0);
    }
  }
  if ((rotDet == ccw) && (chosenOption > 0)) {
    chosenOption--;

    if (fluids[chosenOption] == pumpContent[chosenPump - 1]) drinkExisting = true;

    if (drinkExisting) {
      wttd(pumpsettings[chosenPump - 1], 0, centerX(pumpsettings[chosenPump - 1]), "= " + fluids[chosenOption] + " *", 1, 0);
    } else {
      wttd(pumpsettings[chosenPump - 1], 0, centerX(pumpsettings[chosenPump - 1]), "= " + fluids[chosenOption], 1, 0);
    }
  }

  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (fluids[chosenOption] == backCommando) {
      wttd("PUMPSETTINGS", 0, centerX("PUMPSETTINGS"), "-> " + pumpsettings[0], 1, 0);
      menulvl = 91;
      chosenOption = 0;
    } else if (fluids[chosenOption] == noContent) {
      pumpContent[chosenPump - 1] = "";
      wttd(pumpsettings[chosenPump - 1], 0, centerX(pumpsettings[chosenPump - 1]), "= " + fluids[chosenOption] + " *", 1, 0);
      delay(1500);
      wttd("PUMPSETTINGS", 0, centerX("PUMPSETTINGS"), "-> " + pumpsettings[0], 1, 0);
      menulvl = 91;

      chosenPump = 0;
      chosenOption = 0;
    } else {
      pumpContent[chosenPump - 1] = fluids[chosenOption];
      wttd(pumpsettings[chosenPump - 1], 0, centerX(pumpsettings[chosenPump - 1]), "= " + fluids[chosenOption] + " *", 1, 0);
      delay(1500);
      wttd("PUMPSETTINGS", 0, centerX("PUMPSETTINGS"), "-> " + pumpsettings[0], 1, 0);
      menulvl = 91;

      chosenPump = 0;
      chosenOption = 0;
    }
  }
}

void setGlassSize() {
  pixels.setPixelColor(9, 128, 255, 128);
  pixels.show();
  rotDet = rotary.rotate();
  if ((rotDet == cw) && (sizeOfGlass < 255)) {
    sizeOfGlass++;
    wttd("GLASSSIZE", 0, centerX("GLASSSIZE"), sizeOfGlass, 1, 0);
  }
  if ((rotDet == ccw) && (sizeOfGlass > 230)) {
    sizeOfGlass--;
    wttd("GLASSSIZE", 0, centerX("GLASSSIZE"), sizeOfGlass, 1, 0);
  }
  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    lcd.setCursor(5, 1);
    lcd.print("*");
    delay(1500);
    wttd("SETTINGS", 0, centerX("SETTINGS"), "-> " + settings[0], 1, 0);
    menulvl = 90;
    chosenOption = 0;
  }
}

void setShotDose() {
  pixels.setPixelColor(9, 128, 0, 128);
  pixels.show();
  rotDet = rotary.rotate();
  if ((rotDet == cw) && (smallDoseAmount < 900)) {
    smallDoseAmount += 100;
    wttd("SHOTSIZE", 0, centerX("SHOTSIZE"), smallDoseAmount, 1, 0);
  }
  if ((rotDet == ccw) && (smallDoseAmount > 100)) {
    smallDoseAmount -= 100;
    wttd("SHOTSIZE", 0, centerX("SHOTSIZE"), smallDoseAmount, 1, 0);
  }
  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    lcd.setCursor(5, 1);
    lcd.print("*");
    delay(1500);
    wttd("SETTINGS", 0, centerX("SETTINGS"), "-> " + settings[0], 1, 0);
    menulvl = 90;
    chosenOption = 0;
  }
}

void testPumps() {
  pixels.setPixelColor(9, 0, 0, 255);
  pixels.show();
  rotDet = rotary.rotate();
  if ((rotDet == cw) && (chosenOption < (amountOfPumps - 1))) {
    chosenOption++;
    wttd("TEST PUMPS", 0, centerX("TEST PUMPS"), "-> " + pumpsettings[chosenOption], 1, 0);
  }
  if ((rotDet == ccw) && (chosenOption > 0)) {
    chosenOption--;
    wttd("TEST PUMPS", 0, centerX("TEST PUMPS"), "-> " + pumpsettings[chosenOption], 1, 0);
  }

  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (pumpsettings[chosenOption] == backCommando) {
      wttd("SETTINGS", 0, centerX("SETTINGS"), "-> " + settings[0], 1, 0);
      menulvl = 90;
      chosenOption = 0;
    } else if (pumpsettings[chosenOption] == "P1") {
      digitalWrite(pump1[1], HIGH);
      delay(300);
      digitalWrite(pump1[1], LOW);
    } else if (pumpsettings[chosenOption] == "P2") {
      digitalWrite(pump2[1], HIGH);
      delay(300);
      digitalWrite(pump2[1], LOW);
    } else if (pumpsettings[chosenOption] == "P3") {
      digitalWrite(pump3[1], HIGH);
      delay(300);
      digitalWrite(pump3[1], LOW);
    } else if (pumpsettings[chosenOption] == "P4") {
      digitalWrite(pump4[1], HIGH);
      delay(300);
      digitalWrite(pump4[1], LOW);
    }
  }
}

void showFlowCounter() {
  pixels.setPixelColor(9, 255, 255, 255);
  pixels.show();
  rotDet = rotary.rotate();

  if ((rotDet == cw) && (chosenOption < (amountOfDrinks - 1)) && (drinks[chosenOption + 1] == backCommando)) {
    chosenOption++;
    wttd("FLOW COUNTER", 0, centerX("FLOW COUNTER"), backCommando, 1, 0);
  } else if ((rotDet == cw) && (chosenOption < (amountOfDrinks - 1))) {
    chosenOption++;
    String displayCounter = String(drinksCounter[chosenOption]) + "x " + String(drinks[chosenOption]);
    wttd("FLOW COUNTER", 0, centerX("FLOW COUNTER"), displayCounter, 1, 0);
  }

  if ((rotDet == ccw) && (chosenOption > 0)) {
    chosenOption--;
    String displayCounter = String(drinksCounter[chosenOption]) + "x " + String(drinks[chosenOption]);
    wttd("FLOW COUNTER", 0, centerX("FLOW COUNTER"), displayCounter, 1, 0);
  }
  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (drinks[chosenOption] == backCommando) {
      wttd("SETTINGS", 0, centerX("SETTINGS"), "-> " + settings[0], 1, 0);
      menulvl = 90;
      chosenOption = 0;
    }
  }
  pixels.clear();
  delay(30);
}
