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
 using namespace std;


void Projectile::reset()
{
   mass = DEFAULT_PROJECTILE_WEIGHT;
   radius = DEFAULT_PROJECTILE_RADIUS;
   flightPath = {};
}

void Projectile::fire(const Position& pos, double simulationTime, double angle, double muzzleVelocity)
{
   double vx = muzzleVelocity * sin(angle);
   double vy = muzzleVelocity * cos(angle);
   
   PositionVelocityTime pvt(simulationTime);
   pvt.pos = pos;
   pvt.v = Velocity(vx, vy);
   pvt.t = simulationTime;
   
   flightPath.push_back(pvt);
}
