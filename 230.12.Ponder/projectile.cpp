/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 #include "physics.h"
 #include "cmath"
 using namespace std;


void Projectile::reset()
{
   mass = DEFAULT_PROJECTILE_WEIGHT;
   radius = DEFAULT_PROJECTILE_RADIUS;
   flightPath = {};
}

void Projectile::fire(const Position& pos, double simulationTime, double angle, double muzzleVelocity)
{
   Angle a_angle(angle);
   Velocity vel;
   vel.set(a_angle, muzzleVelocity);
   
   PositionVelocityTime pvt(simulationTime);
   pvt.pos = pos;

   pvt.v = vel;
   pvt.t = simulationTime;
   
   flightPath.push_back(pvt);
}

void Projectile::advance(double simulationTime) {
   if (flightPath.empty()) return;
   
   //otherwise
   PositionVelocityTime prevPvt = flightPath.back();
   PositionVelocityTime currPvt(simulationTime); // new flight path node
   
   double timeStep = simulationTime - prevPvt.t; // amount of time to move forward.

   // look up new values
   double gravity = gravityFromAltitude(prevPvt.pos.getMetersY());

   double airDensity = densityFromAltitude(prevPvt.pos.getMetersY());
   double speedOfSound = speedSoundFromAltitude(prevPvt.pos.getMetersY());
   double mach = prevPvt.v.getSpeed() / speedOfSound;
   double dragCoeff = dragFromMach(mach);

   double dragForce = forceFromDrag(airDensity, dragCoeff, radius, prevPvt.v.getSpeed());
   /*double dragForceX = forceFromDrag(airDensity, dragCoeff, radius, prevPvt.v.getDX());
   double dragForceY = forceFromDrag(airDensity, dragCoeff, radius, prevPvt.v.getDY());*/
   // drag acceleration
   double accDrag = accelerationFromForce(dragForce,mass);
   
   // acceleration components
   
   double angleRad = prevPvt.v.getAngle().getRadians();

   double accX = -sin(angleRad) * accDrag;
   double accY = -cos(angleRad) * accDrag - gravity;
   
   // time
   double hangTime = prevPvt.t;

   // velocity components (Don't need because they're already in currentPvt.v)
   ////dx = sin(rads) * velocity
   //velX = sin(angleRad) * velocity;
   ////dy = cos(rads) * velocity
   //velY = cos(angleRad) * currentPvt.;

   // new pos 
   // 
   // 
   /*
   s = s0 + v t + ½ a t2

      s = distance in meters(m)
      s0 = initial distance(m)
      v = velocity(m / s)
      t = time(s)
      a = acceleration(m / s2)
   */
   // x = x + velX*time + 0.5 * accX * time^2
   //double posX = prevPvt.pos.getMetersX() + ( prevPvt.v.getDX() * timeStep) + (0.5 * accX * (timeStep * timeStep) );
   double posX = positionFromAcceleration(prevPvt.pos.getMetersX(), prevPvt.v.getDX(), timeStep, accX);
   // y = y + velY*time + 0.5 * accY * time^2
   //double posY = prevPvt.pos.getMetersY() + ( prevPvt.v.getDY() * timeStep) + (0.5 * accY * (timeStep * timeStep) );
   double posY = positionFromAcceleration(prevPvt.pos.getMetersY(), prevPvt.v.getDY(), timeStep, accY);
   
   // new velocity components

   ////dx = dx + ddx * t // dx = velX, ddx = accX
   double velX = prevPvt.v.getDX() + velocityFromAcceleration(accX, timeStep); //prevPvt.v.getDX() + accX * simulationTime;
   ////dy = dy + ddy * t // dy = velY, ddy = accY
   double velY = prevPvt.v.getDY() + velocityFromAcceleration(accY, timeStep);
   
   //double velocity = sqrt((velX * velX) + (velY * velY)); // same as get_velocity
   Velocity velocity(velX,velY);
   
   //// new angle
   double newAngleRad = atan2(velX, velY); // get this through velocity.getAngle().getRadians()
   
   // hit ground
   if (posY < 0) {

      // (y - y0) / (t - t0) = (y1 - y0) / (t1 - t0)
      // set up variables
      double t_prev = hangTime - simulationTime;
      double t_curr = hangTime;
      double x_curr = posX;
      double y_curr = posY;
      double y_prev = prevPvt.pos.getMetersX();
      double x_prev = prevPvt.pos.getMetersY();

      // linear interpolation
      // Solve for t when y = 0
      //double t_hit = t_prev + (0 - y_prev) * (t_curr - t_prev) / (y_curr - y_prev);
      double t_hit = linearInterpolation(t_prev, y_prev, y_curr, 0, t_curr);
      //double x_hit = x_prev + (x_curr - x_prev) * ((t_hit - t_prev) / (t_curr - t_prev));
      double x_hit = linearInterpolation(x_prev, x_prev, t_curr, x_curr, t_hit);
      
      currPvt.pos = Position(x_hit,0); // the x distance at which y hit 0
      //posY = 0; // our interpolation ensures y should be 0
      hangTime = t_hit; // the adjusted time for when y=0
      
   }
   else {
      // if hasn't hit ground, update "prev" trackers.
      currPvt.pos = Position(posX,posY);
      hangTime += timeStep;
   };
   currPvt.t = hangTime;
   currPvt.v = velocity;
   
   flightPath.push_back(currPvt);
   
}
