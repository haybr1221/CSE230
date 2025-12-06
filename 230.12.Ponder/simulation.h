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
   }

   Position upperRight;
   Ground ground;
   Howitzer howitzer;
};
