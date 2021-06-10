#include "flyingObject.h"
using namespace std;


Flying::Flying()
{
   alive = true;
   angle = 0.00;
}

void Flying::advance()
{
   point.setX(velocity.getDx() + point.getX());
   point.setY(velocity.getDy() + point.getY());
}

void Flying::wrap()
{
   if (point.getX() > 205)
      (point.setX(-200));
   else if (point.getX() < -205)
      point.setX(200);
   else if (point.getY() > 205)
      point.setY(-200);
   else if (point.getY() < -205)
      point.setY(200);
}