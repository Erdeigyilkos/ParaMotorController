#ifndef _LIGHTCONTROLLER_H
#define _LIGHTCONTROLLER_H

#include "BeaconLight.h"
#include "WingLight.h"
#include "LandingLight.h"
#include "common.h"

class LightController {
public:
  LightController();
  void loop();
private:
  BeaconLight bl;
  WingLight wl;
  LandingLight ll;
  int m_tolerance = 20;
  unsigned Ch1Input = 2;
  unsigned Ch2Input = 3;
  unsigned long m_previousStatusPrint = 0;
  unsigned long m_statusPrintInterval = 10000;
};

LightController::LightController() {
  bl = BeaconLight(9);
  wl = WingLight(5);
  ll = LandingLight(6);
}

void LightController::loop() {
  unsigned long duration = pulseIn(Ch1Input, HIGH, 1000000);
  unsigned long ch2dur = pulseIn(Ch2Input, HIGH, 1000000);

  if (inRange(duration, 1036, m_tolerance) || inRange(duration, 1386, m_tolerance) || inRange(duration, 1735, m_tolerance)) {
    bl.lightState = BeaconLight::lightStates::OFF;
  } else if (inRange(duration, 1143, m_tolerance) || inRange(duration, 1490, m_tolerance) || inRange(duration, 1843, m_tolerance)) {
    bl.lightState = BeaconLight::lightStates::SINGLE_BLICK;
  } else if (inRange(duration, 1250, m_tolerance) || inRange(duration, 1598, m_tolerance) || inRange(duration, 1950, m_tolerance)) {
    bl.lightState = BeaconLight::lightStates::DOUBLE_BLICK;
  }

  if (inRange(duration, 1036, m_tolerance) || inRange(duration, 1143, m_tolerance) || inRange(duration, 1250, m_tolerance)) {
    ll.lightState = LandingLight::lightStates::OFF;
  } else if (inRange(duration, 1379, m_tolerance) || inRange(duration, 1492, m_tolerance) || inRange(duration, 1600, m_tolerance)) {
    ll.lightState = LandingLight::lightStates::APPROACH;
  } else if (inRange(duration, 1736, m_tolerance) || inRange(duration, 1843, m_tolerance) || inRange(duration, 1950, m_tolerance)) {
    ll.lightState = LandingLight::lightStates::LANDING;
  }

  if (millis() - m_previousStatusPrint >= m_statusPrintInterval) {
    m_previousStatusPrint = millis();
    bl.printStatus();
    ll.printStatus();
    wl.printStatus();
  }

  ll.loop();
  bl.loop(millis());
  wl.loop(ch2dur);
}

#endif