#include <M5StickC.h>
#include "const.h"
#include "ImagePainter.h"
#include "HourglassPainter.h"
#include "InputController.h"
#include "HourglassController.h"

static ImagePainter painter;
static HourglassPainter hourglassPainter(&painter);
static InputController inputController;
static HourglassController hourglassController;
bool lastUpsideDown = false;
int minutes = DEFAULT_DURATION;

/**
 * Setup code, executed on startup
 */
void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(LCD_BRIGHTNESS);
  M5.IMU.Init();
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);

  inputController.setResetButtonClickHandler(&onSideButtonClicked);
  inputController.setOrientationChangeHandler(&onOrientationChanged);
  setDuration(minutes);
}

/**
 * Main loop, executed repeatedly
 */
void loop() {
  unsigned int top, bottom;
  
  inputController.loop();
  hourglassController.loop();
  hourglassPainter.setFlowing(hourglassController.isFlowing());

  top = hourglassController.getTimeTop() / MS_PER_SAND;
  bottom = hourglassController.getTimeBottom() / MS_PER_SAND; 
  hourglassPainter.drawHourglass(top, bottom);
  
  delay(MS_PER_FRAME);
}

/**
 * Sets the duration of the hourglass, in minutes
 * 
 * This method configures the controller and also changes the color of the sand according to the config. 
 * 
 * @param minutes Duration in minutes
 */
void setDuration(int minutes) {
  hourglassController.setDuration(minutes * 60 * 1000);
  int colorMapCount = sizeof(COLORMAP) / sizeof(COLORMAP[0]);
  uint16_t color = 0xffff;
  for (int i=0; i < colorMapCount; i++) {
    if (minutes >= COLORMAP[i].minute) {
      color = COLORMAP[i].color;
    }
  }

  char str[50];
  M5.Lcd.setTextSize(1);
  sprintf(str, "%d min", minutes);
  M5.Lcd.drawCentreString(str, 40, 20, 2);
  delay(500);
  
  hourglassPainter.setSandColor(color);
}

/**
 * Side button click handler
 * 
 * Changes the duration of the hourglass.
 */
void onSideButtonClicked() {
  int c = sizeof(DURATION_OPTIONS) / sizeof(DURATION_OPTIONS[0]);
  int i;
  for (i = 0; i < c; i++) {
    if (minutes == DURATION_OPTIONS[i]) {
      break;
    }
  }
  
  minutes = DURATION_OPTIONS[(i+1)%c];
  setDuration(minutes);
}

/**
 * Orientation change handler
 * 
 * Starts/stops the sand flow and controls the orientation of the sand.
 * 
 */
void onOrientationChanged(float accX, float accY, float accZ) {
  bool upsideDown = accY < 0;

  // enable the controller flow
  hourglassController.setVertical(abs(accX) < ORIENTATION_X_MAX && abs(accY) > ORIENTATION_Y_MIN);

  // flip the hourglass if needed
  if (lastUpsideDown != upsideDown) {
    hourglassController.flip();
    lastUpsideDown = upsideDown;
  }
  
  // configure the renderer
  hourglassPainter.setUpsideDown(upsideDown);
}
