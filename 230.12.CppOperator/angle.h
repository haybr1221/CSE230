/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Module
 *      ANGLE
 * 3. Assignment Description:
 *      A class to represent an angle
 **************************************************************/

#pragma once

using namespace std;
#include <iostream>
#include <cassert>
#define TWO_PI 6.28318530718

class TestAngle;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   friend TestAngle;
   
   private:
       // Set private attributes and methods
       double radians;

       double normalize(double radian) const
       {
           if (radian < 0)
           {
              while (radian < 0)
                   radian += TWO_PI;
           };

           if (radian > TWO_PI)
           {
               while (radian > TWO_PI)
                   radian -= TWO_PI;
           };

           return radian;
       };

       double convertToDegrees(double radians) const
       {
           double normRadians = normalize(radians);
           double degrees = normRadians * (180 / M_PI);

           return degrees;
       };

       double convertToRadians(double degrees) const
       {
           double radians = degrees * (M_PI / 180);
           double normRadians = normalize(radians);
           return normRadians;
       };

   public:
       double getDegrees() const { return convertToDegrees(radians); };
       double getRadians() const { return radians; };

       void setDegrees(double degrees)
       {
           // Convert to radians
           double newRadians = convertToRadians(degrees);
           radians = normalize(newRadians);
       };

       void setRadians(double newRadians)
       {
           radians = normalize(newRadians);
       };

       void display(ostream& out) const
       {
           out.precision(1);
           out.setf(ios::fixed);
           out << convertToDegrees(radians);
       };
   
      // Assignment
      inline Angle & operator=(const Angle & rhs)
      {
         radians = rhs.radians;
         return *this;
      }
   
      // Negative
      inline Angle operator-() const
      {
         double newAngle = convertToDegrees(radians) - 180;
         return Angle(newAngle);
      }
   
      // Equals
      inline bool operator==(const Angle & rhs)
      {
         return radians == rhs.radians;
      }
   
      // Not equals
      inline bool operator!=(const Angle & rhs)
      {
         return radians != rhs.radians;
      }
   
      // Insertion
      friend ostream & operator<<(ostream & out, const Angle & rhs)
      {
         out.precision(1);
         out.setf(ios::fixed);
         double deg = rhs.convertToDegrees(rhs.radians);
         out << deg;
         return out;
      }

      // Extraction
      friend istream & operator>>(istream & in, Angle & rhs)
      {
         double deg = rhs.convertToDegrees(rhs.radians);
         in >> deg;
         if (!in.fail()) {
             rhs.radians = rhs.convertToRadians(deg);
         }
         return in;
      }
   
      // Increment prefix (++x)
      inline Angle & operator++()
      {
         double deg = convertToDegrees(radians);
         deg += 1.0;
         radians = convertToRadians(deg);
         return *this;
      }
      
      // Increment postfix (x++)
      inline Angle operator++(int postfix)
      {
         Angle returnAngle(*this);
         double deg = convertToDegrees(radians);
         deg += 1.0;
         radians = convertToRadians(deg);
         return returnAngle;
      }
   
      // Decrement prefix (--x)
      inline Angle & operator--()
      {
         double deg = convertToDegrees(radians);
         deg -= 1.0;
         radians = convertToRadians(deg);
         return *this;
      }
      
      // Decrement postfix (x--)
      inline Angle operator--(int postfix)
      {
         Angle returnAngle(*this);
         double deg = convertToDegrees(radians);
         deg -= 1.0;
         radians = convertToRadians(deg);
         return returnAngle;
      }

      
   // Constructors
   Angle()                 : radians(0.0)  {}                           // Default constructor
   Angle(const Angle& rhs) : radians(rhs.radians)  {}                   // Copy constructor
   Angle(double degrees)   : radians(convertToRadians(degrees))  {}     // Non-default constructor

   };

