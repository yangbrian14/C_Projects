#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "flyingObject.h"
#include "uiDraw.h"

class Ship : public Flying
{
  private:
   int size;
   int rotateAmount;
   bool thrusting;
   int frames; // keeps track of how long the ship has been dead                                   
  public:
   Ship();
   void setThrusting(bool thrusting) { this->thrusting = thrusting; }
   int getFrames() { return frames; }
   void setFrames(int frames) { this->frames = frames; }
   void applyThrust();
   void rotateRight();
   void rotateLeft();
   void draw();
};

#endif /* ship_h */