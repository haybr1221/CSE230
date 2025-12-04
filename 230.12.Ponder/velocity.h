/***********************************************************************
 * Header File:
 *    VELOCITY
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#pragma once

// for unit tests
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestProjectile;

// for add()
class Acceleration;
class Angle;

 /*********************************************
  * Velocity
  * I feel the need, the need for speed
  *********************************************/
class Velocity
{
   // for unit tests
   friend TestPosition;
   friend TestVelocity;
   friend TestProjectile;

   
public:
   // constructors
   Velocity()                     : dx(0.0), dy(0.0) { }
   Velocity(double dx, double dy) : dx(dx), dy(dy) { }

   // getters
   double getDX()       const { return dx; }
   double getDY()       const { return dy; }
   double getSpeed()    const;
   Angle  getAngle()    const;
   
   // setters
   void set(const Angle & angle, double magnitude);
   void setDX(double dx) { this->dx = dx; }
   void setDY(double dy) { this->dy = dy; }
   void addDX(double dx) { this->dx += dx; }
   void addDY(double dy) { this->dy += dy; }
   void add(const Acceleration & acceleration, double time);
   void add(const Velocity& rhs) { dx += rhs.dx; dy += rhs.dy; }
   void reverse() { dx *= -1; dy *= -1; }

private:
   double dx;           // horizontal velocity
   double dy;           // vertical velocity
};

#include <cassert>
/*********************************************
 * VelocityDummy
 * A Dummy double for velocity. This does nothing but assert.
 * Stubs will be derived from this for the purpose of making
 * isolated unit tests.
 *********************************************/
class VelocityDummy : public Velocity
{
public:
   // getters
   double    getDX()    const { assert(false); return 0.0;     }
   double    getDY()    const { assert(false); return 0.0;     }
   double    getSpeed() const { assert(false); return 0.0;     }
   Angle     getAngle() const;

   // setters
   void setDX(double dx)                          { assert(false); }
   void setDY(double dy)                          { assert(false); }
   void setDxDy(double dx, double dy)             { assert(false); }
   void setDirection(const Angle& direction)      { assert(false); }
   void setSpeed(double speed)                    { assert(false); }
   void set(const Angle& angle, double magnitude) { assert(false); }
   void add(const Acceleration& a, double t)      { assert(false); }
   void addDX(double dx)                          { assert(false); }
   void addDY(double dy)                          { assert(false); }
   void add(const Velocity& v)                    { assert(false); }
   void reverse()                                 { assert(false); }
};
