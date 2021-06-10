#include <cmath>
#include "uiDraw.h"
#include "bullet.h"

using namespace std;

Bullet::Bullet()
{

   frames = 0;
}

void Bullet::draw()
{
   drawDot(point);

   frames++;

   if (frames == 40)
      alive = false;
   else
      ;
}

void Bullet::fire(Point rectPoint, float angle, Velocity shipSpeed)
{
   point.setX(rectPoint.getX());
   point.setY(rectPoint.getY());
   float dx = 10 * (-cos(M_PI / 180.0 * (90 - angle)));
   float dy = 10 * (sin(M_PI / 180 * (90 - angle)));
   velocity.setDx(shipSpeed.getDx() + dx);
   velocity.setDy(shipSpeed.getDy() + dy);
}
