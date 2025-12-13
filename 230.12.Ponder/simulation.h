/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "ground.h"
#include "howitzer.h"
#include "projectile.h"


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) {
      upperRight = Position(posUpperRight);
      howitzer.generatePosition(posUpperRight);
      ground = Ground(posUpperRight);
      ground.reset(howitzer.getPosition());
      projectile = Projectile();
      simulationTime = 0.5; // half a second
   }

   Position upperRight;
   Ground ground;
   Howitzer howitzer;
   Projectile projectile;
   double simulationTime;
};
