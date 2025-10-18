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
    Angle() : radians(0) {}
    Angle(const Angle& rhs) : radians(rhs.radians) {}
    Angle(double degrees) : radians(degrees* (M_PI / 180)) {}

    // Getters
    double getDegrees() const { return radians * (180 / M_PI); }
    double getRadians() const { return radians; }


    // Setters
    void setDegrees(double degrees) { radians = convertToRadians(degrees); }
    void setRadians(double radians) { this->radians = normalize(radians); }
    void setUp() { radians = convertToRadians(0); }
    void setDown() { radians = convertToRadians(180); }
    void setRight() { radians = convertToRadians(90); }
    void setLeft() { radians = convertToRadians(270); }
    void reverse() { radians = normalize(radians + convertToRadians(180)); }
    Angle& add(double delta) { radians = normalize(radians + delta); return *this; }

private:
    double normalize(double radians) const;
    /* Takes a radians as a parameter and returns degrees. Does not utilize the
     class's attribute. Note that the results must be normalized. */
    double convertToDegrees(double radians)
    {
        double normRadians = normalize(radians);
        double degrees = normRadians * (180 / M_PI);

        return degrees;
    };

    /*  Takes a degrees as a parameter and returns radians. Does not utilize the
     class's attribute. Note that the results must be normalized. */
    double convertToRadians(double degrees)
    {
        double radians = degrees * (M_PI / 180);
        double normRadians = normalize(radians);
        return normRadians;
    };


    double radians;   // 360 degrees equals 2 PI radians
};

