## tml's Digital Hourglass for the M5StickC

This hourglass is a little program I wrote for my son so that he doesn't ask us every minute about when we're finally arrive somewhere. It is a digital version of the hourglass, running on an M5StickC.

It is using the LCD of the M5Stick to display the hourglass, it's using its acceleation sensors to determine the orientation and whether the sand is flowing or not (and in which direction). It also allows the selection of the time that should be counted down from by using a single side button which is pretty hard to be pushed for a little kid. 

The sand flowing down is colored by duration to serve as a visual hint about how long it is going to take. 

## Compilation

I created this program using the Arduino IDE (v1.8.13). It is written in C++ and should compile without any extra configuration needed. To compile it:

1. Follow the official M5StickC Arduino installation instructions (https://docs.m5stack.com/#/en/arduino/arduino_development)
2. Open hourglass/hourglass.ino from this project
3. Hit Upload in the IDE

That's all. It should compile and install right away, there are no external libraries (except of the M5StickC libraries installed in step 1 of course) needed. 

## Usage
Once running, you will see an hourglass on the screen. If you put down M5Stick down so that the hourglass is "standing", you will see the sand trickle down as you would expect from a real hourglass. If you turn it around, it will start flowing into the opposite direction. 

You can set the amount of sand (e.g. amount of time) by using top right side button (RST) of the M5StickC. This allows you to cycle through the duration options which are, by default, 1 minute to 10 minutes. 

## Configuration

There are a few settings you can configure. These are located in hourglass/const.h. The following settings are worth mentioning:

* LCD_BRIGHTNESS: The brightness of the LCD screen. Goes from 7 to 15. Set it lower to make the battery last longer. 
* ORIENTATION_X_MAX: Determines how much the stick has to be tilted sideways to stop the sand from flowing.
* ORIENTATION_Y_MIN: Determines how much the stick has to be tilted backwards (or forwards) to stop the sand from flowing.
* MS_PER_SAND: How milliseconds translate into pixels of sand. Set it higher => less sand will be drawn for the same amount of time.
* DURATION_OPTIONS: The durations the side button is cycling through.
* DEFAULT_DURATION: The default duration selected when the M5StickC is turned on.
* COLORMAP: Duration to color mapping. You can use this specify what color the sand should be at the different durations. 

## Image customization

The program reading the image of the hourglass and the sand from bitmaps. These bitmaps are defined in sand_data.h and  hourglass_data.h and attributed in images.h. The image data is an array of uint16_t storing raw RGB565 pixel colors (1 pixel => 1 uint16_t). 

In order to create these images I used a little PHP script I wrote which you can find in tools/gen.php. It can be used to create the RGB565 image data from a 32 bit PNG file. You should be able to use it to make a nicer hourglass. Or a differently shaped one. The hourglass program is quite clever, it is counting the pixels on the "sand" image so if you give it an hourglass of a different shape, it will most likely fill it up correctly.

In order to change the images used by the program, you can use my PNG to RGR565 tool: simply invoke it and pass in the filename of the PNG file as parameter, like this:

```
php gen.php glass.png
```

Executing this will dump the pixel data of glass.png into your console and you can then just copy paste it over to hourglass_data.h.
