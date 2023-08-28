#ifndef _BEACONLIGHT_H
#define _BEACONLIGHT_H

#include <Arduino.h>


class BeaconLight {
public:
  BeaconLight(){};
  BeaconLight(int outputPin);
  enum lightStates { OFF,
                     SINGLE_BLICK,
                     DOUBLE_BLICK
  };
  void loop(unsigned long dT);
  void printStatus();
  lightStates lightState;


private:
  unsigned int m_maxBright = 255;
  unsigned long m_cycleStart = 0;
  constexpr static unsigned int m_cyclePause = 1500;
  constexpr static unsigned int m_cycleLightPulse = 50;
  constexpr static unsigned int m_cycleLightBetween = 150;
  unsigned int m_lightValue;
  unsigned int m_pin;
  void setLight(int value);
};


BeaconLight::BeaconLight(int outputPin) {
  lightState = OFF;
  m_pin = outputPin;
  pinMode(m_pin, OUTPUT);
}

void BeaconLight::loop(unsigned long dT) {
  switch (lightState) {
    case OFF:
      setLight(0);
      break;
    case SINGLE_BLICK:
      if (dT < m_cycleStart + m_cycleLightPulse) {
        setLight(m_maxBright);
        break;
      } else if (dT < m_cycleStart + m_cyclePause) {
        setLight(0);
      } else {
        m_cycleStart = dT;
      }
      break;

    case DOUBLE_BLICK:
      if (dT < m_cycleStart + m_cycleLightPulse) {
        setLight(m_maxBright);
        break;
      } else if (dT < m_cycleStart + m_cycleLightBetween) {
        setLight(0);
        break;
      } else if (dT < m_cycleStart + m_cycleLightBetween + m_cycleLightPulse) {
        setLight(m_maxBright);
        break;
      } else if (dT < m_cycleStart + m_cyclePause) {
        setLight(0);
        break;
      } else {
        m_cycleStart = dT;
      }
  }
}

void BeaconLight::printStatus() {
  Serial.print("BeaconLight mode: ");
  switch (lightState) {
    case 0:
      Serial.println("OFF");
      break;
    case 1:
      Serial.println("SINGLE BLICK");
      break;
    case 2:
      Serial.println("DOUBLE BLICK");
      break;
  }
}

void BeaconLight::setLight(int value) {
  m_lightValue = value;

  if (m_lightValue > 255) {
    m_lightValue = 255;
  }

  analogWrite(m_pin, m_lightValue);
}

#endif