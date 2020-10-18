#ifndef CONST_H
#define CONST_H

typedef struct colormap_entry_t {
  unsigned int minute;
  uint16_t color;
} ColorMapEntry;

// display settings
const int LCD_WIDTH = 80;             // Screen width
const int LCD_HEIGHT = 160;           // Screen height
const int LCD_BRIGHTNESS = 9;        // Screen backlight (7-15)
const int TRANSPARENT_COLOR = 0xF81F; // Transparent pixel color (used in images)

// Orientation settings
const int ORIENTATION_WAIT = 10;      // Number of samples to calculate the moving average of when determining the orientation
const float ORIENTATION_X_MAX = 0.25; // maximum X tilt allowed to keep the sand flowing (device on table => 0)
const float ORIENTATION_Y_MIN = 0.35; // minimum Y tilt required to keep the stand flowing (device standing => 1)

// Timer settings
const int MS_PER_FRAME = 30;          // speed of the main loop
const int MS_PER_SAND = 220;          // millisecond to sand pixel ratio, used for rendering

// Duration options
const int DURATION_OPTIONS[] = { 1, 2, 3, 5, 8, 10 };
const int DEFAULT_DURATION = 3;       // default duration

// Minute to color mapping
const ColorMapEntry COLORMAP[] = {
  { 0, 0x04D9 },
  { 2, 0xFB2C },
  { 3, 0xE601 },
  { 4, 0x8BA8 },
  { 5, 0x46C2 },
  { 6, 0x0DDC },
  { 7, 0xFC7E },
  { 8, 0xC638 },
  { 9, 0xFCC7 },
  { 10, 0xB01B }
};

#endif
