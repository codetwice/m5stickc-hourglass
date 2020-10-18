#include "InputController.h"

InputController::InputController() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < ORIENTATION_WAIT; j++) {
      this->accelerationHistory[i][j] = 0;
    }
  }
}

void InputController::loop() {
  this->handleButton(M5_BUTTON_HOME, homeButtonClickHandler);
  this->handleButton(M5_BUTTON_RST, resetButtonClickHandler);
  this->handleOrientation();
}

void InputController::handleButton(int buttonPin, ButtonHandler handler) {
  bool buttonState = digitalRead(buttonPin);
  if (buttonState != this->buttonStates[buttonPin]) {
    if (buttonState == LOW && handler != NULL) {
      handler();
    }
    
    this->buttonStates[buttonPin] = buttonState;
  }
}


void InputController::handleOrientation() {
  float values[3];
  M5.IMU.getAccelData(&values[0], &values[1], &values[2]);

  // calculate the moving average
  for (int i = 0; i < 3; i++) {
    this->accelerationHistorySum[i] = this->accelerationHistorySum[i] + values[i]- this->accelerationHistory[i][this->accelerationHistoryIndex];
    this->accelerationHistory[i][this->accelerationHistoryIndex] = values[i];
  }

  this->accelerationHistoryIndex = (this->accelerationHistoryIndex+1)%ORIENTATION_WAIT;
  this->orientationChangeHandler(this->accelerationHistorySum[0] / ORIENTATION_WAIT, this->accelerationHistorySum[1] / ORIENTATION_WAIT, this->accelerationHistorySum[2] / ORIENTATION_WAIT);
}

void InputController::setHomeButtonClickHandler(ButtonHandler handler) {
  this->homeButtonClickHandler = handler;
}

void InputController::setResetButtonClickHandler(ButtonHandler handler) {
  this->resetButtonClickHandler = handler;
}

void InputController::setOrientationChangeHandler(OrientationHandler handler) {
  this->orientationChangeHandler = handler;
}
