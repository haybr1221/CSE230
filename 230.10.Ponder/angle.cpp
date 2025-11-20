/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Hayley Branchflower & Graham McClure
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

/************************************
 * ANGLE : NORMALIZE
 ************************************/
double Angle::normalize(double radians) const
{
    if (radians < 0)
    {
        while (radians < 0)
            radians += (M_PI * 2);
    };

    if (radians > (M_PI * 2))
    {
        while (radians > (M_PI * 2))
            radians -= (M_PI * 2);
    };

    return radians;
}

