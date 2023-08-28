#ifndef _COMMON_H
#define _COMMON_H

#define VERSION "1.0.0"

static bool inRange(int value, int targerValue, int range) {
  if (value > targerValue - range && value < targerValue + range) {
    return true;
  }
  return false;
}


static void printAplicationInfo() {
  Serial.println("Starting ParaMotor Controller.");
  Serial.print("App Version:");
  Serial.println(VERSION);
}

#endif