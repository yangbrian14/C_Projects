#include "velocity.h"
using namespace std;

Velocity::Velocity()
{
   Dx = 0;
   Dy = 0;
}

Velocity::Velocity(float Dx, float Dy)
{
   this->Dx = Dx;
   this->Dy = Dy;
}

void Velocity::setDx(float Dx)
{
   this->Dx = Dx;
}

void Velocity::setDy(float Dy)
{
   this->Dy = Dy;
}