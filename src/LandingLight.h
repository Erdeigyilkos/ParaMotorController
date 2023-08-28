#ifndef _LANDINGLIGHT_H
#define _LANDINGLIGHT_H

#include <Arduino.h>

class LandingLight {
public:
  LandingLight(){};
  LandingLight(int outputPin);
  enum lightStates { OFF,
                     APPROACH,
                     LANDING
  };
  void loop();
  lightStates lightState;
  void printStatus();

private:
  unsigned int lightValues[3] = { 0, 50, 240 };
  unsigned int m_lightValue = 0;
  unsigned int m_pin;
  constexpr static float m_filter = 0.10;
  constexpr static float m_filterFast = 0.40;
  void setLight(int value);
};

LandingLight::LandingLight(int outputPin) {
  m_pin = outputPin;
  pinMode(m_pin, OUTPUT);
}

void LandingLight::loop() {
  switch (lightState) {
    case OFF:
      m_lightValue = m_lightValue == lightValues[0] ? lightValues[0] : (lightValues[0] * m_filterFast) + (m_lightValue * (1 - m_filterFast));
      break;
    case APPROACH:
      m_lightValue = m_lightValue == lightValues[1] ? lightValues[1] : (lightValues[1] * m_filter) + (m_lightValue * (1 - m_filter));
      break;
    case LANDING:
      m_lightValue = m_lightValue == lightValues[2] ? lightValues[2] : (lightValues[2] * m_filter) + (m_lightValue * (1 - m_filter));
      break;
  }


  setLight(m_lightValue);
}

void LandingLight::printStatus() {
  Serial.print("LandingLight mode: ");
  switch (lightState) {
    case 0:
      Serial.println("OFF");
      break;
    case 1:
      Serial.println("APPROACH");
      break;
    case 2:
      Serial.println("LANDING");
      break;
  }
}

void LandingLight::setLight(int value) {
  m_lightValue = value;

  if (m_lightValue > 255) {
    m_lightValue = 255;
  }

  analogWrite(m_pin, m_lightValue);
}

#endif