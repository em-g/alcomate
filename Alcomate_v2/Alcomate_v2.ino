//___________________________|
//___________________________|
// Project:     Alcomate_v2.2|
// Date:        29.11.2019   |
// Author:      Emre Günes   |
//___________________________|
//___________________________|

#include "defines.h"

#include "leds.h"

#include "main_menu.h"

#include "settings_menu.h"

int ledI = 0;
void setup() {
  rotary.setErrorDelay(5);
  pulldown();
  initDisplay();
  ledstrip();
}

void loop() {
  while (menulvl == 0) startMenu();
  while (menulvl == 1) drinkMenu();
  while (menulvl == 2) drinkSelected();
  while (menulvl == 90) settingsstartMenu();
  while (menulvl == 91) setPumps();
  while (menulvl == 92) setPump();
  while (menulvl == 93) setGlassSize();
  while (menulvl == 94) setShotDose();
  while (menulvl == 95) testPumps();
  while (menulvl == 96) showFlowCounter();
  while (menulvl == 100) cleaningMenu();
}
