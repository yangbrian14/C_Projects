#include "rocks.h"

bigRock::bigRock()
{
   size = 16;
   rotateAmount = 2;
   point.setX(random(-200, 200));
   point.setY(random(-200, 200));
   velocity.setDx(random(-1, 1));
   if (velocity.getDx() == 0)
      velocity.setDx(1);
   velocity.setDy(random(-1, 1));
   if (velocity.getDy() == 0)
      velocity.setDy(1);
}

void bigRock::hit(vector<Rock*> & rocks, Velocity parentVelocity, Point parentPoint)
{
   rocks.push_back(new mediumRock(parentVelocity, parentPoint, 1, 0));
   rocks.push_back(new mediumRock(parentVelocity, parentPoint, -1, 0));
   rocks.push_back(new smallRock(parentVelocity, parentPoint, 0, 2));
   alive = false;
}

void bigRock::draw()
{
   angle += rotateAmount;
   if (angle >= 360)
      angle = 0;
   drawLargeAsteroid(point, angle);
}

mediumRock::mediumRock(Velocity parentVelocity, Point parentPoint, int vertical, int horizontal)
{
   size = 8;
   rotateAmount = 5;
   point = parentPoint;
   point.setX(point.getX() + 15);
   point.setY(point.getY() + 15);
   velocity = parentVelocity;
   velocity.setDx(velocity.getDx() + horizontal);
   velocity.setDy(velocity.getDy() + vertical);
}

void mediumRock::hit(vector<Rock*> & rocks, Velocity parentVelocity, Point parentPoint)
{
   rocks.push_back(new smallRock(parentVelocity, parentPoint, 0, 3));
   rocks.push_back(new smallRock(parentVelocity, parentPoint, 0, -3));
   alive = false;
}

void mediumRock::draw()
{
   angle += rotateAmount;
   if (angle >= 360)
      angle = 0;
   drawMediumAsteroid(point, angle);
}

smallRock::smallRock(Velocity parentVelocity, Point parentPoint, int vertical, int horizontal)
{
   size = 4;
   rotateAmount = 10;
   point = parentPoint;
   point.setX(point.getX() + 15);
   point.setY(point.getY() + 15);
   velocity = parentVelocity;
   velocity.setDx(velocity.getDx() + horizontal);
   velocity.setDy(velocity.getDy() + vertical);
}

void smallRock::hit(vector<Rock*> & rocks, Velocity parentVelocity, Point parentPoint)
{
   alive = false;
}

void smallRock::draw()
{
   angle += rotateAmount;
   if (angle >= 360)
      angle - 0;
   drawSmallAsteroid(point, angle);
}