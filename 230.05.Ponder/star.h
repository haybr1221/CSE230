/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
public:
   void reset(int width, int height)
   {
      pos.setX(random(0.0, static_cast<double>(width)));
      pos.setY(random(0.0, static_cast<double>(height)));
      phase = random(0, 255);
   }
   
   void draw(ogstream & gout)
   {
      gout.drawStar(pos, static_cast<unsigned char>(phase));
      phase = (phase + 1) % 256;
   }
   
private:
   Position pos;
   int phase;
};
