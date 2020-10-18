#include <M5StickC.h>
#include "ImagePainter.h"
#include "const.h"

void ImagePainter::drawImage(Image *image, const int x, const int y) {
  M5.Lcd.drawBitmap(x, y, image->width, image->height, image->data, transparentColor);
};

/**
 * Draws a part of an image
 * 
 * @param image The image to draw
 * @param x Target X position on screen
 * @param y Target Y position on screen
 * @param startRow The row number to start drawing the image from
 * @param rows Number of rows to draw from the original image
 */
void ImagePainter::drawImageSlice(Image *image, const int x, const int y, const int startRow, const int rows) {
  M5.Lcd.drawBitmap(x, y, image->width, rows, image->data + (startRow * image->width), transparentColor);
};
