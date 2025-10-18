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
#include <cmath> // for cos()

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
    // lander
    gout.drawLander(getPosition(), angle.getRadians());
    if (status == PLAYING)
        // thrust
        gout.drawLanderFlames(getPosition(), angle.getRadians(), thrust.isMain(),thrust.isCounter(), thrust.isClock());
    else 
        // thrust
        gout.drawLanderFlames(getPosition(), angle.getRadians(), false, false, false);
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{   
    //// adjust the angle according to thrust
    //double adjRad = thrust.rotation();
    //angle.add(adjRad);

    //// get acceleration from thrust, gravity, and angle
    //thrust.mainEngineThrust(); // get thrust for directional acceleration
    //// vertical component
    //double yComp = thrust.mainEngineThrust() * std::cos(angle.getRadians());
    //yComp += gravity;
    //// horizontal component
    //double xComp = thrust.mainEngineThrust() * std::sin(angle.getRadians());
    
    
    // Adjust the angle according to the thrust
    angle.add(thrust.rotation());
    
    double yComp = gravity;
    double xComp = 0;

   
     if (fuel > 0.0) {
        // fuel
        if (thrust.isClock() || thrust.isCounter())
           fuel -= 1; // adjust fuel for thrusters
        else if (thrust.isMain())
        {
           fuel -= 10; // adjust fuel for other
           yComp += cos(angle.getRadians()) * thrust.mainEngineThrust();
           xComp += -(std::sin(angle.getRadians())) * thrust.mainEngineThrust();
        }
     }
 
    // thrust: - sin(angle.radians) * 2.9795404
    return Acceleration(xComp, yComp);
}


double computeDistance(double velocity, double acceleration, double tTime)
{
    // distance equation
    //pos.x + velocity.dx * time + 0.5 * angle.ddx * time*time
    double addPosition = (velocity * tTime) + (1.0 / 2.0 * acceleration * pow(tTime, 2));
    return addPosition;
};



/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
    // adjust position
    pos.addX(computeDistance(velocity.getDX(), acceleration.getDDX(), time));
    pos.addY(computeDistance(velocity.getDY(), acceleration.getDDY(), time));
    // adjust velocity
    velocity.addDX(acceleration.getDDX() * time);
    velocity.addDY(acceleration.getDDY() * time);
}
