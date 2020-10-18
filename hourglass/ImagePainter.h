#ifndef IMAGEPAINTER_H
#define IMAGEPAINTER_H

#include <M5StickC.h>
#include "Image.h"
#include "const.h"

/**
 * Class used to drawimages onto the screen
 */
class ImagePainter {
  private:
  const int screenWidth = LCD_WIDTH;
  const int screenHeight = LCD_HEIGHT;
  const int transparentColor = TRANSPARENT_COLOR;
  
  public:
  /**
   * Draws an image to the given coordinates.
   * 
   * The top left pixel of the image will be drawn to the position specified by [x, y]
   * 
   * @param image The image to draw
   * @param x The target x coordinate
   * @param y The target y coordinate
   */
  void drawImage(Image *image, const int x, const int y);

  /**
   * Draws a horizontal slice of an image to the given coordinate
   * 
   * @param image The image to draw
   * @param x Target X position on screen
   * @param y Target Y position on screen
   * @param startRow The row number to start drawing the image from
   * @param rows Number of rows to draw from the original image
   */
  void drawImageSlice(Image *image, const int x, const int y, const int startRow, const int rows);
};

#endif
