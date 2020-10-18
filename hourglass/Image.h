#ifndef IMAGE_H
#define IMAGE_H

/**
 * Image structure
 */
typedef struct image_t {
  unsigned int width;
  unsigned int height;
  uint16_t *data;
} Image;

#endif
