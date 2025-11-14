/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Hayley Branchflower
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

 // for the unit tests
class TestAngle;
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   public:
   // for the unit tests
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestHowitzer;
   friend TestProjectile;
   
   // Constructors
   Angle() : radians(0) {}
   Angle(const Angle& rhs) : radians(rhs.radians) {}
   Angle(double degrees) : radians(degrees* (M_PI / 180)) {}
   
   // Getters
   double getDegrees() const { return radians * (180 / M_PI); }
   double getRadians() const { return radians; }
   
   //         dx
   //    +-------/
   //    |      /
   // dy |     /
   //    |    / 1.0
   //    | a /
   //    |  /
   //    | /
   // dy = cos a
   // dx = sin a
   double getDx() const { return sin(radians); }
   double getDy() const { return cos(radians); }
   bool   isRight()          const { return (getDegrees() >= 0 && getDegrees() < 180); }
   bool   isLeft()           const { return (getDegrees() >= 180 && getDegrees() < 360); }

   // Setters
   void setDegrees(double degrees) { radians = convertToRadians(degrees); }
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setUp() { radians = convertToRadians(0); }
   void setDown() { radians = convertToRadians(180); }
   void setRight() { radians = convertToRadians(90); }
   void setLeft() { radians = convertToRadians(270); }
   void reverse() { radians = normalize(radians + convertToRadians(180)); }
   Angle& add(double delta) { radians = normalize(radians + delta); return *this; }

   // set based on the components
   //         dx
   //     +-------/
   //     |      /
   //  dy |     /
   //     |    /
   //     | a /
   //     |  /
   //     | /
   void setDxDy(double dx, double dy)  { radians = normalize(atan2(dx, dy)); }
   Angle operator+(double degrees) const { return Angle(); }

private:

   double normalize(double radians) const;

   double convertToDegrees(double radians)
   {
       double normRadians = normalize(radians);
       double degrees = normRadians * (180 / M_PI);

       return degrees;
   };

   double convertToRadians(double degrees)
   {
       double radians = degrees * (M_PI / 180);
       double normRadians = normalize(radians);
       return normRadians;
   };


   double radians;   // 360 degrees equals 2 PI radians
};

#include <iostream>

/*******************************************************
 * OUTPUT ANGLE
 * place output on the screen in degrees
 *******************************************************/
inline std::ostream& operator << (std::ostream& out, const Angle& rhs)
{
   out << rhs.getDegrees() << "degree";
   return out;
}
