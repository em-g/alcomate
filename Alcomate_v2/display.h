// -------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------  HELPING FUNCTIONS ------------------------------------------------------
// -------------------------------------------------------------LCD---------------------------------------------------------------
#include <LiquidCrystal_I2C.h>


static int maxX                         = 20;
static int maxY                         = 4;
LiquidCrystal_I2C lcd(0x27, maxX, maxY);


int centerX(String a){
  int len = int((maxX - a.length())/2);
  return len;
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

void drinkNotConfigured(String drinkName) {
    wttd("-> " + drinkName, 0, centerX("-> " + drinkName), "not configured", 1, 1);
    delay(2000);
}

void initDisplay()
{
  lcd.init();
  lcd.backlight();
  wttd(welcomeLine, 0, centerX(welcomeLine), "", 0, 0);
}

void lcdLevelIndicator(double condition, double dot_param) {
  if ((condition > (17.5 * dot_param)) && check[18]) {
    wttd("|----------------->|", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[18] = false;
  } else if ((condition > (17 * dot_param)) && check[17]) {
    wttd("|----------------> |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[17] = false;
  } else if ((condition > (16 * dot_param)) && check[16]) {
    wttd("|--------------->  |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[16] = false;
  } else if ((condition > (15 * dot_param)) && check[15]) {
    wttd("|-------------->   |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[15] = false;
  } else if ((condition > (14 * dot_param)) && check[14]) {
    wttd("|------------->    |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[14] = false;
  } else if ((condition > (13 * dot_param)) && check[13]) {
    wttd("|------------>     |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[13] = false;
  } else if ((condition > (12 * dot_param)) && check[12]) {
    wttd("|----------->      |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[12] = false;
  } else if ((condition > (11 * dot_param)) && check[11]) {
    wttd("|---------->       |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[11] = false;
  } else if ((condition > (10 * dot_param)) && check[10]) {
    wttd("|--------->        |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[10] = false;
  } else if ((condition > (9 * dot_param)) && check[9]) {
    wttd("|-------->         |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[9] = false;
  } else if ((condition > (8 * dot_param)) && check[8]) {
    wttd("|------->          |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[8] = false;
  } else if ((condition > (7 * dot_param)) && check[7]) {
    wttd("|------>           |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[7] = false;
  } else if ((condition > (6 * dot_param)) && check[6]) {
    wttd("|----->            |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[6] = false;
  } else if ((condition > (5 * dot_param)) && check[5]) {
    wttd("|---->             |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[5] = false;
  } else if ((condition > (4 * dot_param)) && check[4]) {
    wttd("|--->              |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[4] = false;
  } else if ((condition > (3 * dot_param)) && check[3]) {
    wttd("|-->               |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[3] = false;
  } else if ((condition > (2 * dot_param)) && check[2]) {
    wttd("|->                |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[2] = false;
  } else if ((condition > (1 * dot_param)) && check[1]) {
    wttd("|>                 |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[1] = false;
  } else if ((condition < (1 * dot_param)) && check[0]) {
    wttd("|                  |", 2, 0, "Press to cancel!", 3, centerX("Press to cancel!"));
    check[0] = false;
  }
}
