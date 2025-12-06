/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/ 

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()
#include <cassert>

/*********************************************
 * VELOCITY : ADD
 *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
   dx = dx + (acceleration.getDDX() * time);
   dy = dy + (acceleration.getDDY() * time);
}


/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *********************************************/
double Velocity::getSpeed() const
{
   return sqrt(dx * dx + dy * dy);
}


/*********************************************
 * VELOCITY : SET
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    /speed
 *     | a /
 *     |  /
 *     | /
 * dy = speed cos a
 * dx = speed sin a
 *********************************************/
void Velocity::set(const Angle& angle, double magnitude)
{
   dx = magnitude * sin(angle.getRadians());
   dy = magnitude * cos(angle.getRadians());
}


/************************************************
 * Velocity :: GET ANGLE
 * Determine the direction things are going
 * where 0 is up. This returns angle (clockwise) in radians
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    /
 *     | a /
 *     |  /
 *     | /
 ************************************************/
Angle Velocity::getAngle() const
{
   Angle angle;
   angle.setRadians(atan2(dx, dy));
   return angle;
}
Angle VelocityDummy::getAngle() const
{
   assert(false); 
   return Angle();
}

