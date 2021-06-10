#include "ship.h"
#include <cmath>

Ship::Ship()
{
   size = 10;
   rotateAmount = 6;
   thrusting = false;
   frames = 0;
}

void Ship::applyThrust()
{
   thrusting = true;

   float dx = 0.5 * (-cos(M_PI / 180 * (90 - angle)));
   float dy = 0.5 * (sin(M_PI / 180 * (90 - angle)));
   velocity.setDx(velocity.getDx() + dx);
   velocity.setDy(velocity.getDy() + dy);
}

void Ship::rotateRight()
{
   angle += -rotateAmount;
}

void Ship::rotateLeft()
{
   angle += rotateAmount;
}

void Ship::draw()
{
   if (angle >= 360)
      angle = 0;
   drawShip(point, angle, thrusting);
}