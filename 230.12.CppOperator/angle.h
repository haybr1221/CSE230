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
           out << convertToDegrees(radians) << "degrees";
       };
   
      inline Angle & operator=(const Angle & rhs)
      {
         radians = rhs.radians;
         return *this;
      }
   
      inline Angle operator-() const
      {
         double newAngle = convertToDegrees(radians) - 180;
         return Angle(newAngle);
      }
   
      inline bool operator==(const Angle & rhs)
      {
         return radians == rhs.radians;
      }
   
      inline bool operator!=(const Angle & rhs)
      {
         return radians != rhs.radians;
      }
   
      friend ostream & operator<<(ostream & out, const Angle & rhs)
      {
         out << rhs.radians;
         return out;
      }

      friend istream & operator>>(istream & in, Angle & rhs)
      {
         in >> rhs.radians;
         return in;
      }
   
      inline Angle & operator++()
      {
         radians++;
         return *this;
      }
   
      inline Angle operator++(int postfix)
      {
         Angle returnAngle(*this);
         radians++;
         return returnAngle;
      }
   
      inline Angle & operator--()
      {
         radians--;
         return *this;
      }
      
      inline Angle operator--(int postfix)
      {
         Angle returnAngle(*this);
         radians--;
         return returnAngle;
      }

      
   // Constructors
   Angle()                 : radians(0.0)  {}                           // Default constructor
   Angle(const Angle& rhs) : radians(rhs.radians)  {}                   // Copy constructor
   Angle(double degrees)   : radians(convertToRadians(degrees))  {}     // Non-default constructor

   };

