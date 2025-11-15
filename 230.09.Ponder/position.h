/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/


#pragma once

#include <iostream> 
#include <cmath>

class TestPosition;
class Acceleration;
class Velocity;
class TestGround;
class TestHowitzer;
class TestProjectile;


/*********************************************
 * Position
 * A single position on the field in Meters  
 *********************************************/
class Position
{
public:
   friend ::TestPosition;
   friend ::TestGround;
   friend ::TestHowitzer;
   friend ::TestProjectile;

   
   // constructors
   Position()            : x(0.0), y(0.0)  {}
   Position(double x, double y); // In meters
   Position(const Position & pt) : x(pt.x), y(pt.y) {}
   Position& operator = (const Position& pt);

   // getters
   double getMetersX()       const { return x; }
   double getMetersY()       const { return y; }
   double getPixelsX()       const { return x/metersFromPixels; }
   double getPixelsY()       const { return y/metersFromPixels; }
   double getZoom()          const { return metersFromPixels; }

   // setters
   void setZoom(double z)                { metersFromPixels = z; }
   void setMeters(double xMeters, double yMeters) { this->x = xMeters; this->y = yMeters; }
   void setMetersX(double xMeters)       { x = xMeters; }
   void setMetersY(double yMeters)       { y = yMeters; }
   void setPixelsX(double xPixels)       { x = (xPixels * metersFromPixels); }
   void setPixelsY(double yPixels)       { y = (yPixels * metersFromPixels); } // meters = pixels * metersFromPixels
   double addMetersX(double x)           { this->x += x; return this->x; }
   double addMetersY(double y)           { this->y += y; return this->y; }
   double addPixelsX(double x)           { this->x += x * metersFromPixels; return this->x; }
   double addPixelsY(double y)           { this->y += y * metersFromPixels; return this->y; }
   void add(const Acceleration& a, const Velocity& v, double t);
   void reverse() { }


private:
   double x;                 // horizontal position
   double y;                 // vertical position
   static double metersFromPixels;
};



// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Position& pt);
std::istream & operator >> (std::istream & in,        Position& pt);


/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
   double x;
   double y;
};


// prev position
//class Position
//{
//    friend TestPosition;    // for the unit tests
//    friend TestLander;      // for the unit tests
//
//public:
//    // constructors
//    Position() : x(0.0), y(0.0) {}
//    Position(const Position& pos) : x(pos.getX()), y(pos.getY()) {}
//    Position(double x, double y);
//
//    // getters
//    double getX() const { return x; }
//    double getY() const { return y; }
//    bool operator == (const Position& rhs) const
//    {
//        return (rhs.getX() == this->x) && (rhs.getY() == this->y);
//    }
//    bool operator != (const Position& rhs) const
//    {
//        return (rhs.getX() != x) || (rhs.getY() != y);
//    }
//
//    // setters
//    void setX(double x) { this->x = x; }
//    void setY(double y) { this->y = y; }
//    void addX(double x) { this->x += x; }
//    void addY(double y) { this->y += y; }
//    void add(const Acceleration& a, const Velocity& v, double t);
//    Position& operator = (const Position& rhs)
//    {
//        setX(rhs.getX());
//        setY(rhs.getY());
//        return *this;
//    }
//
//private:
//    double x;           // horizontal position
//    double y;           // vertical position
//};
//
