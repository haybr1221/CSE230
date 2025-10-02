/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestLander;
   
   // Constructors
   Angle()                 : radians(0)  {}
   Angle(const Angle& rhs) : radians(rhs.radians)  {}
   Angle(double degrees)   : radians(degrees * (M_PI / 180))  {}

   // Getters
   double getDegrees() const { return radians * (180 / M_PI); }
   double getRadians() const { return radians; }

   // Setters
   void setDegrees(double degrees) { radians = normalize(degrees * (M_PI / 180));}
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setUp()                    { radians = normalize(0 * (M_PI / 180));}
   void setDown()                  { radians = normalize(180 * (M_PI / 180));}
   void setRight()                 { radians = normalize(90 * (M_PI / 180)); }
   void setLeft()                  { radians = normalize(270 * (M_PI / 180)); }
   void reverse()                  { radians = normalize(radians + (180 * (M_PI/180))); }
   Angle& add(double delta)        { radians = normalize(radians + delta); return *this; }

private:
   double normalize(double radians) const;

   double radians;   // 360 degrees equals 2 PI radians
};

