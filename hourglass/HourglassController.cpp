#include "HourglassController.h"
#include <Arduino.h>
#include <M5StickC.h>

HourglassController::HourglassController() {
  lastUpdate = millis();
}

void HourglassController::loop() {  
  unsigned long time = millis();
  if (isFlowing()) {
    elapsed = min(elapsed + time - lastUpdate, duration);
  }

  lastUpdate = time;
}

void HourglassController::flip() {  
  elapsed = duration - elapsed;
}

void HourglassController::setDuration(unsigned long duration) {  
  this->duration = duration;
  this->elapsed = 0;
}

unsigned long HourglassController::getTimeTop() {  
  return duration - elapsed;
}

unsigned long HourglassController::getTimeBottom() {  
  return elapsed;
}

void HourglassController::setVertical(bool vertical) {
  this->vertical = vertical;
}

bool HourglassController::isFlowing() {
  return vertical && elapsed < duration;
}
