/*********************************************************************                             
 * File: game.h                                                                                    
 * Description: Defines the game class for Asteroids                                               
 *                                                                                                 
 *********************************************************************/

#ifndef GAME_H
#define GAME_H
#include "point.h"
#include "uiInteract.h"
#include "rocks.h"
#include "ship.h"
#include "bullet.h"
#include <vector>
class Game
{
  public:
   Game(Point, Point);
   ~Game();
   void handleInput(const Interface & ui);
   void advance();
   void draw(const Interface & ui);
  private:
   vector<Rock*> rocks;
   vector<Bullet> bullets;
   Ship ship;
   Point topLeft;
   Point bottomRight;
   int lives;
   void advanceShip();
   void advanceRocks();
   void advanceBullets();
   void collisionDetect();
   void freeMemory();
   bool isOnScreen(Point & point);
   float getClosestDistance(Flying &, Flying &) const;
};

#endif /* GAME_H */