#ifndef _WINGLIGHT_H
#define _WINGLIGHT_H

#include <Arduino.h>



class WingLight {
public:
  WingLight(){};
  WingLight(int outputPin);
  void loop(unsigned long dT);
  void printStatus();
private:
  unsigned int m_pin;
  unsigned int m_lightValue = 0;
  void setLight(int value);
  constexpr static float m_filter = 0.05;
};


WingLight::WingLight(int outputPin) {
  m_pin = outputPin;
  pinMode(m_pin, OUTPUT);
}

void WingLight::loop(int unsigned long dT) {
  int mapValue = map(dT, 1085, 1930, 0, 255);
  if (mapValue > 255)
    mapValue = 255;
  if (mapValue < 0)
    mapValue = 0;


  unsigned int smoothedLight = (mapValue * m_filter) + (m_lightValue * (1 - m_filter));
  m_lightValue = smoothedLight;
  setLight(smoothedLight);
}

void WingLight::printStatus() {
  Serial.print("Wing value: ");
  Serial.println(m_lightValue);
}

void WingLight::setLight(int value) {
  m_lightValue = value;

  if (m_lightValue > 255) {
    m_lightValue = 255;
  }

  analogWrite(m_pin, m_lightValue);
}

#endif