//___________________________|
//___________________________|
// Project:     Alcomate_v2.0|
// Date:        29.11.2019   |
// Author:      Emre Günes   |
//___________________________|
//___________________________|

// library imports
#include <LiquidCrystal.h>
#include <SimpleRotary.h>
#include <Adafruit_NeoPixel.h>

// declaring pumps 
int pump1[2] = {
  23,
  22
}; // define digital pins to pump connectors
int pump2[2] = {
  25,
  24
};
int pump3[2] = {
  29,
  28
};
int pump4[2] = {
  27,
  26
};

String welcomeLine = "ALCOMATE";
String backCommando = "GO BACK";
String mixer = "Mixer only";
String liquor = "Liquor only";
String pumpsettings[] = {
  "P1",
  "P2",
  "P3",
  "P4",
  backCommando
};

static String pumpContent[] = {
  "Wodka",
  "Energy",
  "Malibu",
  "Maracuja"
};

String drinks[] = {
  "Wodka Energy",
  "Malibu Maracuja",
  "Gin Tonic",
  backCommando
};

int drinksCounter[] = {
  0,
  0,
  0
};

int allPumps[8] = {
  23,
  22,
  25,
  24,
  29,
  28,
  27,
  26
};

double pspeed = 8.4; // 8.4ml in 1sec ---> 500ml in 1min

// menu variables

static String chosenSetting;
static String chosenDrink;
static int    chosenMixtureRelation;
static int    chosenOption;
static int    chosenPump;
static int    originalChosenOption;
static bool   globalflag = true;
byte          buttonPushed;
byte          buttonPushType;
byte          cancelPushed;
bool          cancelflag = false;
bool check[15] = {true, true, true, true, true, true, true, true, true, true, true, true, true, true, true};


String mixRel[] = {
  "0%",
  "15%",
  "20%",
  "30%",
  "50%",
  mixer,
  liquor,
  backCommando
};
String settings[] = {
  "Pumpsettings",
  "Glasssize",
  "Small shots",
  "CLEAN",
  "Test pumps",
  backCommando
};
String fluids[] = {
  "Energy",
  "Gin",
  "Malibu",
  "Maracuja",
  "Tonic",
  "Wodka",
  backCommando
};

int mixRelInts[] = {
  0,
  15,
  20,
  30,
  50
};

// global variables

int rotDet;
int menulvl             = 0;
int sizeOfGlass         = 245;
int amountOfPumps       = sizeof(pumpsettings) / sizeof(pumpsettings[0]);
int amountOfDrinks      = sizeof(drinks) / sizeof(drinks[0]);
int amountOfMixRel      = sizeof(mixRel) / sizeof(mixRel[0]);
int amountOfSettings    = sizeof(settings) / sizeof(settings[0]);
int amountOfFluids      = sizeof(fluids) / sizeof(fluids[0]);
int amountOfPumpContent = sizeof(pumpContent) / sizeof(pumpContent[0]);
int amountOfChecks      = sizeof(check) / sizeof (check[0]);
double smallDoseAmount  = 200;

// hardware start
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);
SimpleRotary rotary(2, 3, 4); // define digital pins rotary encoder (2 = CLK, 3 = DT, 4 = SW)
Adafruit_NeoPixel pixels(30, 12, NEO_GRB + NEO_KHZ800); // define neopixel (12 = digital_in) amount=30 delay = 500

// boot function
void setup() {
  Serial.begin(9600);
  
  pixels.begin();
  pixels.setBrightness(50);

  lcd.begin(16, 2);
  wttd("", 0, 0, "booting...", 0, 1);
  delay(1000);
  wttd("READY!", 0, 5, "", 0, 1);
  delay(500);
  wttd(welcomeLine, 0, 4, "", 0, 0);

  pinMode(pump1[0], OUTPUT);
  pinMode(pump1[1], OUTPUT);
  pinMode(pump2[0], OUTPUT);
  pinMode(pump2[1], OUTPUT);
  pinMode(pump3[0], OUTPUT);
  pinMode(pump3[1], OUTPUT);
  pinMode(pump4[0], OUTPUT);
  pinMode(pump4[1], OUTPUT);

  digitalWrite(pump1[0], LOW);
  digitalWrite(pump1[1], LOW);
  digitalWrite(pump2[0], LOW);
  digitalWrite(pump2[1], LOW);
  digitalWrite(pump3[0], LOW);
  digitalWrite(pump3[1], LOW);
  digitalWrite(pump4[0], LOW);
  digitalWrite(pump4[1], LOW);

  wttd(welcomeLine, 0, (16 - welcomeLine.length()) / 2, "", 0, 0);
}

void loop() {
  while (menulvl == 0) mainMenu();
  while (menulvl == 1) drinkMenu();
  while (menulvl == 2) drinkSelected();
  while (menulvl == 90) settingsMainMenu();
  while (menulvl == 91) setPumps();
  while (menulvl == 92) setPump();
  while (menulvl == 93) setGlassSize();
  while (menulvl == 94) setShotDose();
  while (menulvl == 95) testPumps();
  //rainbowCycle(10);
}

// -------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------  MENU FUNCTIONS -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------
void mainMenu() {
  buttonPushType = rotary.pushType(1500);
  delay(100);
  if (buttonPushType == 2) {
    wttd(welcomeLine, 0, (16 - welcomeLine.length()) / 2, "-> Settings (3)", 1, 0);
    delay(1000);
    wttd(welcomeLine, 0, (16 - welcomeLine.length()) / 2, "-> Settings (2)", 1, 0);
    delay(1000);
    wttd(welcomeLine, 0, (16 - welcomeLine.length()) / 2, "-> Settings (1)", 1, 0);
    delay(1000);
    wttd(welcomeLine, 0, (16 - welcomeLine.length()) / 2, "-> Settings (0)", 1, 0);

    menulvl = 90;
    chosenOption = 0;
    wttd("SETTINGS", 0, 4, "-> " + settings[0], 1, 0);
  }
  if (buttonPushType == 1) {
    menulvl = 1;
    wttd("DRINKS", 0, 5, "-> " + drinks[0], 1, 0);
  }
}

void drinkMenu() {
  rotDet = rotary.rotate();
  if ((rotDet == 2) && (chosenOption < (amountOfDrinks - 1))) {
    chosenOption++;
    wttd("DRINKS", 0, 5, "-> " + drinks[chosenOption], 1, 0);
  }
  if ((rotDet == 1) && (chosenOption > 0)) {
    chosenOption--;
    wttd("DRINKS", 0, 5, "-> " + drinks[chosenOption], 1, 0);
  }
  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (drinks[chosenOption] == backCommando) {
      wttd(welcomeLine, 0, (16 - welcomeLine.length()) / 2, "", 0, 0);
      menulvl = 0;
      chosenOption = 0;
    } else {
      menulvl = 2;
      chosenDrink = drinks[chosenOption];
      int lengthDrinkString = (16 - chosenDrink.length()) / 2;
      originalChosenOption = chosenOption;
      chosenOption = 2;
      wttd(drinks[originalChosenOption], 0, lengthDrinkString, "-> " + mixRel[chosenOption], 1, 0);
    }
  }
}

void drinkSelected() {
  int lengthDrinkString = (16 - chosenDrink.length()) / 2;
  byte rotDetMix = rotary.rotate();
  if ((rotDetMix == 2) && (chosenOption < (amountOfMixRel - 1))) {
    chosenOption++;
    wttd(drinks[originalChosenOption], 0, lengthDrinkString, "-> " + mixRel[chosenOption], 1, 0);
  }
  if ((rotDetMix == 1) && (chosenOption > 0)) {
    chosenOption--;
    wttd(drinks[originalChosenOption], 0, lengthDrinkString, "-> " + mixRel[chosenOption], 1, 0);
  }
  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (mixRel[chosenOption] == backCommando) {
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
      drinkAndRelMixSelected(chosenDrink, chosenOption);
      chosenOption = 0; // Name des Drinks
    }
  }
}

// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  SETTINGS FUNCTIONS -----------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------

void settingsMainMenu() {
  rotDet = rotary.rotate();
  if ((rotDet == 2) && (chosenOption < (amountOfSettings - 1))) {
    chosenOption++;

    wttd("SETTINGS", 0, 4, "-> " + settings[chosenOption], 1, 0);
  }
  if ((rotDet == 1) && (chosenOption > 0)) {
    chosenOption--;

    wttd("SETTINGS", 0, 4, "-> " + settings[chosenOption], 1, 0);
  }

  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (settings[chosenOption] == backCommando) {
      wttd(welcomeLine, 0, (16 - welcomeLine.length()) / 2, "", 1, 0);
      menulvl = 0;
      chosenOption = 0;
    } else if (settings[chosenOption] == "Pumpsettings") {
      wttd("PUMPSETTINGS", 0, 2, "-> " + pumpsettings[0], 1, 0);
      menulvl = 91;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    } else if (settings[chosenOption] == "Glasssize") {
      wttd("GLASSSIZE", 0, 3, sizeOfGlass, 1, 0);
      menulvl = 93;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    } else if (settings[chosenOption] == "Small shots") {
      wttd("SHOTSIZE", 0, 4, smallDoseAmount, 1, 0);
      menulvl = 94;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    } else if (settings[chosenOption] == "Test pumps") {
      wttd("TEST PUMPS", 0, 3, "-> " + pumpsettings[0], 1, 0);
      menulvl = 95;
      chosenSetting = settings[chosenOption];
      chosenOption = 0;
    }
  }
}

void setPumps() {
  rotDet = rotary.rotate();
  if ((rotDet == 2) && (chosenOption < (amountOfPumps - 1))) {
    chosenOption++;
    wttd("PUMPSETTINGS", 0, 2, "-> " + pumpsettings[chosenOption], 1, 0);
  }
  if ((rotDet == 1) && (chosenOption > 0)) {
    chosenOption--;
    wttd("PUMPSETTINGS", 0, 2, "-> " + pumpsettings[chosenOption], 1, 0);
  }

  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (pumpsettings[chosenOption] == backCommando) {
      wttd("SETTINGS", 0, 4, "-> " + settings[0], 1, 0);
      menulvl = 90;
      chosenOption = 0;
    } else if (pumpsettings[chosenOption] == "P1") {
      wttd("P1", 0, 7, "= " + fluids[0], 1, 0);
      menulvl = 92;
      chosenPump = 1;
      chosenOption = 0;
    } else if (pumpsettings[chosenOption] == "P2") {
      wttd("P2", 0, 7, "= " + fluids[0], 1, 0);
      menulvl = 92;
      chosenPump = 2;
      chosenOption = 0;
    } else if (pumpsettings[chosenOption] == "P3") {
      wttd("P3", 0, 7, "= " + fluids[0], 1, 0);
      menulvl = 92;
      chosenPump = 3;
      chosenOption = 0;
    } else if (pumpsettings[chosenOption] == "P4") {
      wttd("P4", 0, 7, "= " + fluids[0], 1, 0);
      menulvl = 92;
      chosenPump = 4;
      chosenOption = 0;
    }
  }
}

void setPump() {
  rotDet = rotary.rotate();
  if ((rotDet == 2) && (chosenOption < (amountOfFluids - 1))) {
    chosenOption++;
    wttd(pumpsettings[chosenPump - 1], 0, 7, "= " + fluids[chosenOption], 1, 0);
  }
  if ((rotDet == 1) && (chosenOption > 0)) {
    chosenOption--;
    wttd(pumpsettings[chosenPump - 1], 0, 7, "= " + fluids[chosenOption], 1, 0);
  }

  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (fluids[chosenOption] == backCommando) {
      wttd("PUMPSETTINGS", 0, 2, "-> " + pumpsettings[0], 1, 0);
      menulvl = 91;
      chosenOption = 0;
    } else {
      pumpContent[chosenPump -1] = fluids[chosenOption];
      wttd(pumpsettings[chosenPump - 1], 0, 0, "= " + fluids[chosenOption] + " *", 1, 0);
      delay(1500);
      wttd("PUMPSETTINGS", 0, 2, "-> " + pumpsettings[0], 1, 0);
      menulvl = 91;

      chosenPump = 0;
      chosenOption = 0;
    }
  }
}

void setGlassSize() {

  rotDet = rotary.rotate();
  if ((rotDet == 2) && (sizeOfGlass < 255)) {
    sizeOfGlass++;
    wttd("GLASSSIZE", 0, 3, sizeOfGlass, 1, 0);
  }
  if ((rotDet == 1) && (sizeOfGlass > 230)) {
    sizeOfGlass--;
    wttd("GLASSSIZE", 0, 3, sizeOfGlass, 1, 0);
  }
  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    lcd.setCursor(5, 1);
    lcd.print("*");
    delay(1500);
    wttd("SETTINGS", 0, 4, "-> " + settings[0], 1, 0);
    menulvl = 90;
    chosenOption = 0;
  }
}

void setShotDose() {
  rotDet = rotary.rotate();
  if ((rotDet == 2) && (smallDoseAmount < 900)) {
    smallDoseAmount += 100;
    wttd("SHOTSIZE", 0, 4, smallDoseAmount, 1, 0);
  }
  if ((rotDet == 1) && (smallDoseAmount > 100)) {
    smallDoseAmount -= 100;
    wttd("SHOTSIZE", 0, 4, smallDoseAmount, 1, 0);
  }
  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    lcd.setCursor(5, 1);
    lcd.print("*");
    delay(1500);
    wttd("SETTINGS", 0, 4, "-> " + settings[0], 1, 0);
    menulvl = 90;
    chosenOption = 0;
  }
}

void testPumps() {

  rotDet = rotary.rotate();
  if ((rotDet == 2) && (chosenOption < (amountOfPumps - 1))) {
    chosenOption++;
    wttd("TEST PUMPS", 0, 3, "-> " + pumpsettings[chosenOption], 1, 0);
  }
  if ((rotDet == 1) && (chosenOption > 0)) {
    chosenOption--;
    wttd("TEST PUMPS", 0, 3, "-> " + pumpsettings[chosenOption], 1, 0);
  }

  buttonPushed = rotary.push();
  if (buttonPushed == 1) {
    if (pumpsettings[chosenOption] == backCommando) {
      wttd("SETTINGS", 0, 4, "-> " + settings[0], 1, 0);
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

// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  HELPING FUNCTIONS ------------------------------------------------------
// -------------------------------------------------------------LCD---------------------------------------------------------------

void drinkNotConfigured(String drinkName) {
  wttd("-> " + drinkName, 0, 0, "not configured", 1, 1);
  delay(2000);
}

void wttd(String line1, int pos1y, int pos1x, String line2, int pos2y, int pos2x) {
  lcd.clear();
  lcd.setCursor(pos1x, pos1y);
  lcd.print(line1);
  lcd.setCursor(pos2x, pos2y);
  lcd.print(line2);
}

void wttd(String line1, int pos1y, int pos1x, int line2, int pos2y, int pos2x) {
  lcd.clear();
  lcd.setCursor(pos1x, pos1y);
  lcd.print(line1);
  lcd.setCursor(pos2x, pos2y);
  lcd.print(line2);
}

// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  HELPING FUNCTIONS ------------------------------------------------------
// ------------------------------------------------------------PUMPS--------------------------------------------------------------

void drinkAndRelMixSelected(String drinkName, int mixRelation) {
  int procent = mixRelInts[mixRelation];
  double shotSize = (sizeOfGlass * procent) / 100;
  double rest = sizeOfGlass - shotSize;

  if (procent == 0) {
    wttd("Matthias Gerling", 0, 0, "mode activated", 1, 0);
    delay(2500);
  }
  pumpItUp(drinkName, shotSize, rest);
}

void pumpItUp(String drinkName, double shot, double mixy) {
  double shotTime = double(shot / pspeed) * 1000;
  double mixyTime = double(mixy / pspeed) * 1000;
  int shotPump = getShotPump(drinkName);
  int mixPump = getMixPump(drinkName);

  if ((mixPump == -1) || (shotPump == -1)) {
    drinkNotConfigured(drinkName);
    menulvl = 1;
    wttd("DRINKS", 0, 5, "-> " + drinks[0], 1, 0);
  } else {
    wttd("Please wait OR", 0, 1, "CANCEL PROCESS!", 1, 1);
    delay(600);
    pumpDos(shotPump, mixPump, shotTime, mixyTime);
    if (globalflag) {
      if(shotTime > 0) drinksCounter[getDrinknumberFromDrinkname(drinkName)]++;
      String counterString = "Counter = " + (String(drinksCounter[getDrinknumberFromDrinkname(drinkName)]));
      Serial.println(counterString);
      wttd("-> " + drinkName, 0, 0, counterString, 1, 0);
      delay(3200);
      wttd("-> Returning", 0, 2, "to main menu", 1, 2);
      delay(1000);
      wttd(welcomeLine, 0, (16 - welcomeLine.length()) / 2, "", 0, 0);
      cancelflag = false;
      menulvl = 0;
    }
  }

}

int getShotPump(String drinkName) {
  int shotPump = -1;

  if (drinkName == drinks[0]) {
    for (int i = 0; i < amountOfPumpContent; i++) {
      if (pumpContent[i] == "Wodka") shotPump = i+1;
    }

  }
  if (drinkName == drinks[1]) {
    for (int i = 0; i <= amountOfPumpContent; i++) {
      if (pumpContent[i] == "Malibu") shotPump = i+1;
    }
  }
  if (drinkName == drinks[2]) {
    for (int i = 0; i <= amountOfPumpContent; i++) {
      if (pumpContent[i] == "Gin") shotPump = i+1;
    }
  }
  return shotPump;
}

int getMixPump(String drinkName) {
  int mixPump = -1;
  if (drinkName == drinks[0]) {
    for (int i = 0; i < amountOfPumpContent; i++) {
      if (pumpContent[i] == "Energy") mixPump = i+1;
    }

  }
  if (drinkName == drinks[1]) {
    for (int i = 0; i <= amountOfPumpContent; i++) {
      if (pumpContent[i] == "Maracuja") mixPump = i+1;
    }
  }
  if (drinkName == drinks[2]) {
    for (int i = 0; i <= amountOfPumpContent; i++) {
      if (pumpContent[i] == "Tonic") mixPump = i+1;
    }
  }
  return mixPump;
}

void pumpDos(int shotPump, int mixPump, double shotDelay, double mixDelay) {
  for(int i = 0; i < amountOfChecks; i++) check[i] = true;
  wttd("Please wait OR", 0, 1, "CANCEL PROCESS!", 1, 1);
  delay(1000);
  lcd.clear();

  double starttime = millis(); // now static
  double actualTime = millis(); // now based on runtime
  double endtime = actualTime + shotDelay;
  double delayTime = mixDelay - shotDelay;
  
  double totalTime = (sizeOfGlass - ((shotDelay/1000)*pspeed))/pspeed;
  double progressBarStep = totalTime*1000 / 14;
  
  while(actualTime < endtime){
    actualTime = millis();
    cancelPushed = rotary.push();
    if (cancelPushed == 1) {
      if (shotPump == 1) digitalWrite(pump1[1], LOW);
      if (shotPump == 2) digitalWrite(pump2[1], LOW);
      if (shotPump == 3) digitalWrite(pump3[1], LOW);
      if (shotPump == 4) digitalWrite(pump4[1], LOW);
      cancelflag = true;
      break;
    }
    else{
      lcdLevelIndicator(actualTime-starttime, progressBarStep);
      if (shotPump == 1) digitalWrite(pump1[1], LOW);
      if (shotPump == 2) digitalWrite(pump2[1], LOW);
      if (shotPump == 3) digitalWrite(pump3[1], LOW);
      if (shotPump == 4) digitalWrite(pump4[1], LOW);
      if (mixPump == 1) digitalWrite(pump1[1], LOW);
      if (mixPump == 2) digitalWrite(pump2[1], LOW);
      if (mixPump == 3) digitalWrite(pump3[1], LOW);
      if (mixPump == 4) digitalWrite(pump4[1], LOW);
    }
  }
  if (shotPump == 1) digitalWrite(pump1[1], LOW);
  if (shotPump == 2) digitalWrite(pump2[1], LOW);
  if (shotPump == 3) digitalWrite(pump3[1], LOW);
  if (shotPump == 4) digitalWrite(pump4[1], LOW);

  actualTime = millis();
  double globalendtime = actualTime+delayTime;

  if (mixPump == 1) digitalWrite(pump1[1], LOW);
  if (mixPump == 2) digitalWrite(pump2[1], LOW);
  if (mixPump == 3) digitalWrite(pump3[1], LOW);
  if (mixPump == 4) digitalWrite(pump4[1], LOW);
  while((actualTime < globalendtime) && !cancelflag){
    actualTime = millis();
    cancelPushed = rotary.push();
    lcdLevelIndicator(actualTime-starttime, progressBarStep);
    
    if (cancelPushed == 1) break;
  }
  if (mixPump == 1) digitalWrite(pump1[1], LOW);
  if (mixPump == 2) digitalWrite(pump2[1], LOW);
  if (mixPump == 3) digitalWrite(pump3[1], LOW);
  if (mixPump == 4) digitalWrite(pump4[1], LOW);
}

void lcdLevelIndicator(double condition, double dot_param)
{ 
  if      ((condition > (13.5 * dot_param)) && check[14]){
    wttd("|------------->|", 0, 0, "Press to cancel!", 1, 0);
    check[14] = false;
  }
  else if ((condition > (13 * dot_param)) && check[13]){         
    wttd("|------------> |", 0, 0, "Press to cancel!", 1, 0);
    check[13] = false;
  }
  else if ((condition > (12 * dot_param)) && check[12]){
    wttd("|----------->  |", 0, 0, "Press to cancel!", 1, 0);
    check[12] = false;
  }
  else if ((condition > (11 * dot_param)) && check[11]){
    wttd("|---------->   |", 0, 0, "Press to cancel!", 1, 0);
    check[11] = false;
  }
  else if ((condition > (10 * dot_param)) && check[10]){
    wttd("|--------->    |", 0, 0, "Press to cancel!", 1, 0);
    check[10] = false;
  }
  else if ((condition > (9 * dot_param)) && check[9]){
    wttd("|-------->     |", 0, 0, "Press to cancel!", 1, 0);
    check[9] = false;
  }
  else if ((condition > (8 * dot_param)) && check[8]){
    wttd("|------->      |", 0, 0, "Press to cancel!", 1, 0);
    check[8] = false;
  }
  else if ((condition > (7 * dot_param)) && check[7]){
    wttd("|------>       |", 0, 0, "Press to cancel!", 1, 0);
    check[7] = false;
  }
  else if ((condition > (6 * dot_param)) && check[6]){
    wttd("|----->        |", 0, 0, "Press to cancel!", 1, 0);
    check[6] = false;
  }
  else if ((condition > (5 * dot_param)) && check[5]){
    wttd("|---->         |", 0, 0, "Press to cancel!", 1, 0);
    check[5] = false;
  }
  else if ((condition > (4 * dot_param)) && check[4]){
    wttd("|--->          |", 0, 0, "Press to cancel!", 1, 0);
    check[4] = false;
  }
  else if ((condition > (3 * dot_param)) && check[3]){
    wttd("|-->           |", 0, 0, "Press to cancel!", 1, 0);
    check[3] = false;
  }
  else if ((condition > (2 * dot_param)) && check[2]){
    wttd("|->            |", 0, 0, "Press to cancel!", 1, 0);
    check[2] = false;
  }
  else if ((condition > (1 * dot_param)) && check[1]){
    wttd("|>             |", 0, 0, "Press to cancel!", 1, 0);
    check[1] = false;
  }
  else if ((condition < (1 * dot_param)) && check[0]){
    wttd("|              |", 0, 0, "Press to cancel!", 1, 0);
    check[0] = false;
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

// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  HELPING FUNCTIONS ------------------------------------------------------
// -------------------------------------------------------------LEDS--------------------------------------------------------------

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  HELPING FUNCTIONS ------------------------------------------------------
// -----------------------------------------------------------ARDUINO-------------------------------------------------------------

int getDrinknumberFromDrinkname(String drinkName){
  for(int i=0; i<amountOfDrinks; i++){
    if(drinks[i] == drinkName) return i;
  }
}
