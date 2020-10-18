#ifndef HOURGLASSCONTROLLER_H
#define HOURGLASSCONTROLLER_H

/**
 * Class controlling the hourglass mechanics
 */
class HourglassController {
  private:
  bool vertical = false;
  unsigned long duration = 0;
  unsigned long elapsed = 0;
  unsigned long lastUpdate = 0;
  
  public:
  /**
   * Default constructor
   */
  HourglassController();
  
  /**
   * Main loop, called periodically
   */
  void loop();

  /**
   * Flips the hourglass
   */
  void flip();

  /**
   * Sets the duration
   * 
   * @param duration The duration, in milliseconds
   */
  void setDuration(unsigned long duration);

  /**
   * Returns the time on the top (in milliseconds)
   * 
   * @return The time inms
   */
  unsigned long getTimeTop();

  /**
   * Returns the time on the bottom side of the hourglass (in milliseconds)
   * 
   * @return The time in ms
   */
  unsigned long getTimeBottom();

  /**
   * Sets whether the hourglass is in a vertical position (e.g. sand can flow)
   */
  void setVertical(bool vertical);

  /**
   * Returns whether the sand is flowing
   * 
   * @return True if the sand is flowing, false otherwise
   */
  bool isFlowing();
};

#endif
