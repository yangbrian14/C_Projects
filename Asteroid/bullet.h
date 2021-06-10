#ifndef BULLET_H
#define BULLET_H
using namespace std;
#include "flyingObject.h"

class Bullet : public Flying
{
   int frames;
  public:
   Bullet();
   void draw();
   void fire(Point, float, Velocity);
};

#endif