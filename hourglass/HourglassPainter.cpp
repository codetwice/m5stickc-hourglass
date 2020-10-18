#include <M5StickC.h>
#include "HourglassPainter.h"
#include "images.h"

HourglassPainter::HourglassPainter(ImagePainter *painter) {
  this->painter = painter;
  this->initializeSandPixels();
}

void HourglassPainter::drawHourglass(int topSand, int bottomSand) {
  int topRows = this->calculateSandRows(true, topSand);
  int bottomRows = this->calculateSandRows(false, bottomSand);

  this->drawHourglassInternal(topRows, bottomRows); 
  if (flowing) {
    // adjust the bottom rows so that at least one sand row is considered (otherwise the sand would flow out of hte hourglass)
    if (bottomRows == 0) {
      bottomRows = this->calculateSandRows(false, 1);
    }
    
    this->drawSandFlow(bottomRows);
  }
}

void HourglassPainter::setUpsideDown(bool upsideDown) {
  if (upsideDown != this->upsideDown) {
    // force a complete redraw
    this->requestRedraw();
    this->upsideDown = upsideDown;
  }
}

void HourglassPainter::initializeSandPixels() {
  int pixelCount;
  for (int y = 0; y < sandImage.height; y++) {
    pixelCount = 0;
    for (int x = 0; x < sandImage.width; x++) {
      if (sandImage.data[y * sandImage.width + x] != TRANSPARENT_COLOR) {
        pixelCount++;
      }
    }

    this->sandPixels[y] = pixelCount;
  }
}

int HourglassPainter::calculateSandRows(bool top, int pixels) {
  int sum = 0;
  int rows = 0;
  
  if (top) {
    for (int i=LCD_HEIGHT/2-1; i >= 0 && sum < pixels ; i--) {
      rows++;
      sum += this->sandPixels[i];
    }
  } else {
    for (int i=LCD_HEIGHT-1; i >= LCD_HEIGHT/2 && sum < pixels ; i--) {
      rows++;
      sum += this->sandPixels[i];
    }
  }

  return rows;
}

void HourglassPainter::drawHourglassInternal(int topRows, int bottomRows) {
  int diff;
  int startRow;
  
  if (this->lastTopRows == -1 || this->lastBottomRows == -1 || needsRedraw) {
    this->drawHourglassFull(topRows, bottomRows);
    this->lastTopRows = topRows;
    this->lastBottomRows = bottomRows;
    this->needsRedraw = false;    
    return;
  }
  
  // the number of top rows changed
  diff = topRows - this->lastTopRows;

  if (diff == 0) {
    // do nothing
  } else if (upsideDown) {
    startRow = min(LCD_HEIGHT/2 + this->lastTopRows, LCD_HEIGHT/2 + topRows);
    painter->drawImageSlice(diff > 0 ? &sandImage : &hourglassImage, 0, startRow, startRow, abs(diff));
  } else {
    startRow = min(LCD_HEIGHT/2-topRows, LCD_HEIGHT/2-this->lastTopRows);
    painter->drawImageSlice(diff > 0 ? &sandImage : &hourglassImage, 0, startRow, startRow, abs(diff));
  }

  // the number of bottom rows changed
  diff = bottomRows - this->lastBottomRows;
  if (diff == 0) {
    // do nothing
  } else if (upsideDown) {
    startRow = min(this->lastBottomRows, bottomRows);
    painter->drawImageSlice(diff > 0 ? &sandImage : &hourglassImage, 0, startRow, startRow, abs(diff));    
  } else {
    startRow = min(LCD_HEIGHT-bottomRows, LCD_HEIGHT-this->lastBottomRows);
    painter->drawImageSlice(diff > 0 ? &sandImage : &hourglassImage, 0, startRow, startRow, abs(diff));    
  }
  
  this->lastTopRows = topRows;
  this->lastBottomRows = bottomRows;
}

void HourglassPainter::drawHourglassFull(int topRows, int bottomRows) {
  painter->drawImage(&hourglassImage, 0, 0);

  if (upsideDown) {
    painter->drawImageSlice(&sandImage, 0, 0, 0, bottomRows);
    painter->drawImageSlice(&sandImage, 0, LCD_HEIGHT/2, LCD_HEIGHT/2, topRows);
  } else {
    painter->drawImageSlice(&sandImage, 0, LCD_HEIGHT/2-topRows, LCD_HEIGHT/2-topRows, topRows);
    painter->drawImageSlice(&sandImage, 0, LCD_HEIGHT-bottomRows, LCD_HEIGHT-bottomRows, bottomRows);
  }    
}

void HourglassPainter::drawSandFlow(int bottomRows) {
  int height = LCD_HEIGHT / 2 - bottomRows;
  if (upsideDown) {
    painter->drawImageSlice(&sandFlowImage, (LCD_WIDTH - sandFlowImage.width)/2, bottomRows, sandFlowPosition, height);
    sandFlowPosition += 2;
    if (sandFlowPosition > sandFlowImage.height / 2) {
      sandFlowPosition -= sandFlowImage.height / 2;
    }
  } else {
    painter->drawImageSlice(&sandFlowImage, (LCD_WIDTH - sandFlowImage.width)/2, LCD_HEIGHT / 2, sandFlowPosition, height);
    sandFlowPosition -= 2;
    if (sandFlowPosition < 0) {
      sandFlowPosition = sandFlowPosition + sandFlowImage.height / 2;
    }
  }
}

void HourglassPainter::setFlowing(bool flowing) {
  if (flowing != this->flowing) {
    this->flowing = flowing;
    this->requestRedraw();
  }
}

void HourglassPainter::requestRedraw() {
  this->needsRedraw = true;
}

void HourglassPainter::setSandColor(uint16_t color) {
  int size = sandImage.width * sandImage.height;
  
  for (int i; i < size; i++) {
    if (sandImage.data[i] != TRANSPARENT_COLOR) {
      sandImage.data[i] = color;
    }
  }

  this->requestRedraw();
}
