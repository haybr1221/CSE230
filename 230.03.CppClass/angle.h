/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 03: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

#define _USE_MATH_DEFINES
#pragma once

#define TWO_PI 6.28318530718
#include <cmath>
#include <math.h>    // for floor()
#include <iostream>  // for cout
#include <cassert>   // for assert()
using namespace std;

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

    /* Takes a radian as a parameter and reduce it to between 0 and 2π. For
     example, 3π will become π (corresponding to 540° becoming 180°), π/2
     staying unchanged (corresponding to 90°), and -7π becoming π (corresponding
     to -1260° becoming 180°). */
    double normalize(double radian)
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

public:
    /* Takes no parameters and return the angle in degrees. */
    double getDegrees() { return convertToDegrees(radians); };

    /*  Takes no parameters and return the angle in radians. */
    double getRadians() { return radians; };

    /* Takes a degrees as a parameter and updates the attribute with the passed
     parameter. If the parameter is above 360 or below zero, then it will "unwrap"
     so the radians is between 0 and 2π. */
    void setDegrees(double degrees)
    {
        // Convert to radians
        double radians = convertToRadians(degrees);
        radians = normalize(radians);
    };

    /* Takes a radian as a parameter and updates the attribute with the passed
     parameter. If the parameter is above 2π or below zero, then it will "unwrap." */
    void setRadians(double radians)
    {
        radians = normalize(radians);
    };

    /* Takes a ostream & out as a parameter display the value, in degrees, to
     1 decimal place of accuracy. This out parameter can be treated exactly
     the same as cout. You can use it with a.display(cout) if a is the name
     of your object */
    void display(ostream& out)
    {
        out.precision(1);
        out.setf(ios::fixed);
        out << convertToDegrees(radians) << "degrees";
    };
};


