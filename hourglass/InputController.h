#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <M5StickC.h>
#include "const.h"

typedef void (*ButtonHandler)();
typedef void (*OrientationHandler)(float, float, float);

/**
 * Class handling all user input and firing callbacks
 */
class InputController {
  private:
  ButtonHandler homeButtonClickHandler = NULL;
  ButtonHandler resetButtonClickHandler = NULL;
  OrientationHandler orientationChangeHandler = NULL;

  /**
   * Array to hold the current states of the arduino pins
   */
  int buttonStates[40];

  /**
   * Acceleration history data, used for calculating the moving average
   */
  float accelerationHistory[3][ORIENTATION_WAIT];
  float accelerationHistorySum[3] = { 0, 0, 0 };
  int accelerationHistoryIndex = 0;
  
  public:
  InputController();

  /**
   * Main loop, called from the main application loop
   */
  void loop();

  /**
   * Sets the handler for the home button click
   * 
   * @param handler The handler to call when the home button is clicked
   */
  void setHomeButtonClickHandler(ButtonHandler handler);

  /**
   * Sets the handler for the side button click
   * 
   * @param handler The handler to call when the side button is clicked
   */
  void setResetButtonClickHandler(ButtonHandler handler);

  /**
   * Sets the handler for orientation changes
   * 
   * @param handler The handler to call when the orientation changes
   */
  void setOrientationChangeHandler(OrientationHandler handler);

  private:
  void handleButton(int buttonPin, ButtonHandler handler);
  void handleOrientation();
};

#endif
