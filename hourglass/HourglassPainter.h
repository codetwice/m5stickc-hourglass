#ifndef HOURGLASSPAINTER_H
#define HOURGLASSPAINTER_H
#include "ImagePainter.h"
#include "const.h"

class HourglassPainter {
  private:

  /**
   * The image painter to use
   */
  ImagePainter *painter;

  /**
   * The number of sand pixels in the rows of the screen
   */
  int sandPixels[LCD_HEIGHT];

  /**
   * Whether the device is upside down
   */
  bool upsideDown = false;

  /**
   * The previous top sand rows painted
   */
  int lastTopRows = -1;

  /**
   * The previous bottom sand rows painted
   */
  int lastBottomRows = -1;

  /**
   * The current position in the sandflow image
   */
  int sandFlowPosition = 0;

  /**
   * Whether the sand is flowing or not
   */
  bool flowing = false;

  /**
   * Whether the entire hourglass needs to be redrawn or not
   */
  bool needsRedraw = false;
  
  public:
  HourglassPainter(ImagePainter *painter);

  /**
   * Draws the hour glass with the given number of sand pixels on the top and on the bottom
   * 
   * @param topSand the number of sand pixels on the top
   * @param bottomSand the number of sand pixels on the bottom
   */  
  void drawHourglass(int topSand, int bottomSand);
  void setUpsideDown(bool upsideDown);
  void setFlowing(bool flowing);
  void setSandColor(uint16_t color);
  
  private:
  /**
   * Process the sand image and count the pixels per raw. 
   * 
   * The result is stored in the sandPixels array, indexed by the y coordinate of the row.
   */
  void initializeSandPixels();
  
  /**
   * Calculates how many rows of sand has to be filled to produce a given number of sand pixels
   * 
   * @param top When true, the number of rows on the top side of the hourglass is returned. 
   * @param pixels The number of sand pixels to get the rows for
   * @return The number of rows to fill
   */
  int calculateSandRows(bool top, int pixels);

  /**
   * Optimized version which only draws the difference between the previous hourglass and the new one
   * 
   * @param topSand the number of sand pixels on the top
   * @param bottomSand the number of sand pixels rows on the bottom
   */ 
  void drawHourglassInternal(int topRows, int bottomRows);

  /**
   * Draws the hourglass completely
   * 
   * @param topSand the number of sand pixels on the top
   * @param bottomSand the number of sand pixels rows on the bottom
   */
  void drawHourglassFull(int topRows, int bottomRows);

  /**
   * Draws the sandflow from the middle of the hourglass to the top of the bottom sand layer
   * 
   * @param bottomSand the number of sand pixels rows on the bottom
   */
  void drawSandFlow(int bottomRows);

  /**
   * Requests a complete redraw
   * 
   * The hourglass will be completely redrawn at the next draw loop
   */
  void requestRedraw();
};

#endif
