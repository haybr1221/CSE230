/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{

    //Set the angle of the lander to straight up.
    angle.setDegrees(0.0);
    //Set the status of the lander to PLAYING.
    status = PLAYING;
    //Fill the fuel with 5000.0 units.
    fuel = 5000.0;
    //Set the horizontal velocity to a random value between - 4m / s and -10m / s.
    velocity.setDX(random(-10, -4));
    //Set the vertical velocity to a random value between - 2m / s and 2m / s.
    velocity.setDY(random(-2, 2));
    //Set the horizontal position to 1 pixel from the right of the screen.
    pos.setX(posUpperRight.getX() - 1);
    //Set the vertical position that is between 75 % and 95 % of the height of the screen.You will need to use the random() function to do that.
    double screenHeight = posUpperRight.getY();
    pos.setY(random((screenHeight * 0.75), (screenHeight * 0.95)));
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   pos.setX(-99.9);
   return Acceleration();
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   pos.setX(-99.9);
}
