/*********************************************************************          
 * File: game.cpp                                                               
 * Description: Contains the implementaiton of the game class                   
 *  methods.                                                                    
 *                                                                              
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...                      
#include <limits>
#include <algorithm>
#include <iostream>
#define OFF_SCREEN_BORDER_AMOUNT 5
#define CLOSE_ENOUGH 15
using namespace std;


Game::Game(Point topLeft, Point bottomRight)
{
   this->topLeft = topLeft;
   this->bottomRight = bottomRight;
   for (int i = 0; i < 5; i++)
      rocks.push_back(new bigRock());
   lives = 10;
}

Game::~Game()
{
   vector<Rock*>::iterator it = rocks.begin();
   while (it != rocks.end())
   {
      delete (*it);
      it++;
   }
}

void Game::handleInput(const Interface & ui)
{
   if (ui.isLeft() && ship.isAlive())
      ship.rotateLeft();
   if (ui.isRight() && ship.isAlive())
      ship.rotateRight();
   if (!ui.isDown() && ship.isAlive())
      ship.setThrusting(false);
   if (ui.isDown() && ship.isAlive())
      ship.applyThrust();
   if (ui.isSpace() && ship.isAlive())
   {
      Bullet bullet;
      bullet.fire(ship.getPoint(), ship.getAngle(), ship.getVelocity());
      bullets.push_back(bullet);
   }
}

void Game::advance()
{
   advanceBullets();
   advanceRocks();
   advanceShip();
   collisionDetect();
   freeMemory();
}

void Game::draw(const Interface & ui)
{
   vector<Rock*> ::iterator it = rocks.begin();
   while (it != rocks.end())
   {
      if (*it != NULL && (*it)->isAlive())
         (*it)->draw();
      it++;
   }
   if (ship.isAlive())
      ship.draw();
   if (!ship.isAlive())
   {
      ship.setFrames(ship.getFrames() + 1);
      if (ship.getFrames() == 15 && lives != 0)
      {
         ship.setAlive(true);
         Point defaultPoint;
         ship.setPoint(defaultPoint);
         ship.setFrames(0);
      }
   }
   Point textLocation(-200, 190);
   drawText(textLocation, "Lives: ");
   Point numLocation(-160, 199);
   drawNumber(numLocation, lives);
   if (lives == 0)
   {
      Point point(-40, 0);
      drawText(point, "Game Over!");
   }
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
         bullets[i].draw();
   }

}

void Game::advanceShip()
{
   ship.advance();
   ship.wrap();
}

void Game::advanceRocks()
{
   vector<Rock*> ::iterator it = rocks.begin();
   while (it != rocks.end())
   {
      (*it)->advance();
      (*it)->wrap();
      it++;
   }
}

void Game::advanceBullets()
{
   for (int i = 0; i < bullets.size(); i++)
   {
      bullets[i].advance();
      bullets[i].wrap();
   }
}

void Game::collisionDetect()
{
   for (int i = 0; i < bullets.size(); i++)
   {
      for (int j = 0; j < rocks.size(); j++)
      {
         if (bullets[i].isAlive())
         {
            if (rocks[i] != NULL && (rocks[j]->isAlive()))
            {
               if (getClosestDistance(*rocks[j], bullets[i]) < CLOSE_ENOUGH)
               {
                  cout << "hit!" << endl;
                  bullets[i].kill();
                  rocks[j]->hit(rocks, rocks[j]->getVelocity(), rocks[j]->getPo\
int());
               }
            }
         }
      }
   }
   for (int i = 0; i < rocks.size(); i++)
   {
      if (getClosestDistance(*rocks[i], ship) < CLOSE_ENOUGH)
      {
         cout << "ship destroyed!" << endl;
         if (ship.isAlive())
         {
            ship.kill();
            lives--;
         }
      }
   }
}

void Game::freeMemory()
{
   vector<Bullet> ::iterator it = bullets.begin();
   while (it != bullets.end())
   {
      if (!(*it).isAlive())
         it = bullets.erase(it);
      else
         it++;
   }

   vector<Rock*> ::iterator ri = rocks.begin();
   while (ri != rocks.end())
   {
      if (!(*ri)->isAlive())
      {
         delete (*ri);
         ri = rocks.erase(ri);
      }
      else
         ri++;
   }

}

bool Game::isOnScreen(Point & point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
           && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
           && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
           && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**********************************************************                                        
 * Function: getClosestDistance                                                                    
 * Description: Determine how close these two objects will                                         
 *   get in between the frames.                                                                    
 **********************************************************/

float Game :: getClosestDistance(Flying &obj1, Flying &obj2) const
{
   // find the maximum distance traveled                                                           
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.                    

   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                   obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                   obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();

      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);

      distMin = min(distMin, distSquared);
   }

   return sqrt(distMin);
}