###############################################################                                    
# Program:                                                                                         
#     Project 13, Asteroids                                                                        
#     Brother Alvey, CS165                                                                         
# Author:                                                                                          
#     Brian Yang                                                                                   
# Summary:                                                                                         
#     User control the ship on screen that is flying in space                                      
#     to shoot asteroids making sure they dont hit the ship                                        
#     and destroy the user.                                                                        
# Above and Beyond                                                                                 
#     Implementing a life system. Giving you 10 life so that                                       
#     the user can play a little longer.                                                           
###############################################################                                    


LFLAGS = -lglut -lGLU -lGL

###############################################################                                    
# Build the main game                                                                              
###############################################################                                    
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o roc\
ks.o
        g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.\
o rocks.o $(LFLAGS)

###############################################################                                    
# Individual files                                                                                 
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics                         
#    uiInteract.o   Handles input events                                                           
#    point.o        The position on the screen                                                     
#    game.o         Handles the game interaction                                                   
#    velocity.o     Velocity (speed and direction)                                                 
#    flyingObject.o Base class for all flying objects                                              
#    ship.o         The player's ship                                                              
#    bullet.o       The bullets fired from the ship                                                
#    rocks.o        Contains all of the Rock classes                                               
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
        g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
        g++ -c uiInteract.cpp

point.o: point.cpp point.h
        g++ -c point.cpp

driver.o: driver.cpp game.h
        g++ -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h rocks.h s\
hip.h
        g++ -c game.cpp

velocity.o: velocity.cpp velocity.h point.h
        g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
        g++ -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h
        g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
        g++ -c bullet.cpp

rocks.o: rocks.cpp rocks.h flyingObject.h point.h velocity.h uiDraw.h
        g++ -c rocks.cpp


###############################################################                                    
# General rules                                                                                    
###############################################################                                    
clean:
        rm a.out *.o