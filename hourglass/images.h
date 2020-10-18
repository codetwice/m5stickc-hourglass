#ifndef IMAGES_H
#define IMAGES_H

#include "hourglass_data.h"
#include "sand_data.h"
#include "sandflow_data.h"
#include "Image.h"

extern Image hourglassImage = {
  80, 160, hourglassData
};

extern Image sandImage = {
  80, 160, sandData
};

extern Image sandFlowImage = {
  2, 320, sandFlowData
};

#endif
