#include "common.h"
#include "LightController.h"

LightController lc;

void setup() {
  Serial.begin(9600);
  printAplicationInfo();
  lc = LightController();
}

void loop() {
  lc.loop();
}