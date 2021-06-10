#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "uiDraw.h"
#include "flyingObject.h"


class Rock : public Flying
{
  protected:
   int size;
   int rotateAmount;
  public:
   virtual void hit(vector<Rock*> &, Velocity parentVelocity, Point parentPoint) = 0;
   virtual void draw() = 0;
};

class bigRock : public Rock
{
  public:
   bigRock();
   void hit(vector<Rock*> & rocks, Velocity parentVelocity, Point parentPoint);
   void draw();
};

class mediumRock : public Rock
{
  public:
   mediumRock(Velocity parentVelocity, Point parentPoint, int vertical, int horizontal);
   void hit(vector<Rock*> & rocks, Velocity parentVelocity, Point parentPoint);
   void draw();
};

class smallRock : public Rock
{
  public:
   smallRock(Velocity parentVelocity, Point parentPoint, int vertical, int horizontal);
   void hit(vector<Rock*> & rocks, Velocity parentVelocity, Point parentPoint);
   void draw();
};


#endif /* rocks_h */