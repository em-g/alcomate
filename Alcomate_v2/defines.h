#include <SimpleRotary.h>

static String welcomeLine = "ALCOMATE";
static String backCommando = "GO BACK";
static String mixer = "Mixer only";
static String liquor = "Liquor only";
static String noContent = "--NONE--";
static String chosenSetting;
static String chosenDrink;

static int sizeOfGlass = 245;
static int menulvl = 0;
static int rotDet;
static int cw = 1;
static int ccw = 2;
static int chosenMixtureRelation;
static int chosenOption;
static int chosenPump;
static int originalChosenOption;

static double pspeed = 8.4; // 8.4ml in 1sec ---> 500ml in 1min
static double smallDoseAmount = 400;

static bool globalflag = true;
static bool cancelflag = false;
static bool cleanStart;

static byte buttonPushed;
static byte buttonPushType;
static byte cancelPushed;

int CLK = 2;
int DT = 3;
int SW = 4;

SimpleRotary rotary(CLK, DT, SW);

static int allPumps[8] = {
  23,
  22,
  25,
  24,
  29,
  28,
  27,
  26
};

int pump1[2] = {
  allPumps[0],
  allPumps[1]
};
int pump2[2] = {
  allPumps[2],
  allPumps[3]
};
int pump3[2] = {
  allPumps[4],
  allPumps[5]
};
int pump4[2] = {
  allPumps[6],
  allPumps[7]
};

static int mixRelInts[] = {
  0,
  15,
  20,
  30,
  50
};
static int drinksCounter[] = {
  0,
  0,
  0,
  0,
  0
};

static String pumpsettings[] = {
  "P1",
  "P2",
  "P3",
  "P4",
  backCommando
};
static String drinks[] = {
  "Wodka Energy",
  "Malibu Maracuja",
  "Gin Tonic",
  "Smokey Martini",
  "Cuba Libre",
  backCommando
};
static String mixRel[] = {
  "0%",
  "15%",
  "20%",
  "30%",
  "50%",
  mixer,
  liquor,
  backCommando
};
static String settings[] = {
  "Pumpsettings",
  "Flow counter",
  "Glasssize",
  "Small shots",
  "CLEANING",
  "Test pumps",
  backCommando
};
static String cleaner[] = {
  "P1 + P2",
  "P3 + P4",
  backCommando
};
static String fluids[] = {
  noContent,
  "Cola",
  "Energy",
  "Gin",
  "Malibu",
  "Maracuja",
  "Rum",
  "Tonic",
  "Whisky",
  "Wodka",
  backCommando
};
static String pumpContent[] = {
  "Wodka",
  "Energy",
  "Malibu",
  "Maracuja"
};

static bool check[19] = {
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true
};

int amountOfPumps = sizeof(pumpsettings) / sizeof(pumpsettings[0]);
int amountOfDrinks = sizeof(drinks) / sizeof(drinks[0]);
int amountOfMixRel = sizeof(mixRel) / sizeof(mixRel[0]);
int amountOfSettings = sizeof(settings) / sizeof(settings[0]);
int amountOfFluids = sizeof(fluids) / sizeof(fluids[0]);
int amountOfPumpContent = sizeof(pumpContent) / sizeof(pumpContent[0]);
int amountOfCounters = sizeof(drinksCounter) / sizeof(drinksCounter[0]);
int amountOfChecks = sizeof(check) / sizeof(check[0]);

void pulldown() {
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
}
