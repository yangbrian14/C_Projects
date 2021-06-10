#ifndef flyingObject_h
#define flyingObject_h
#include "velocity.h"
#include "point.h"
#include <vector>
using namespace std;

class Flying
{
  protected:
   Point point;
   Velocity velocity;
   bool alive;
   float angle;
  public:
   Flying();
   Point getPoint() { return point; }
   Velocity getVelocity() { return velocity; }
   float getAngle() { return angle; }
   bool isAlive() { return alive; }
   void setAlive(bool alive) { this->alive = alive; }
   void setPoint(Point point) { this->point = point; }
   void setVelocity(Velocity velocity) { this->velocity = velocity; }
   void advance();
   void draw() {}
   void kill() { alive = false; }
   void wrap();
};


#endif /* flyingObject_h */