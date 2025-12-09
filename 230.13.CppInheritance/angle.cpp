/***********************************************************************
 * Source:
 *    Angle
 * Summary:
 *    Just call the Angle unit tests
 * Author:
 *    James Helfrich
 ************************************************************************/

#include <iostream>
#include <vector>
#include <sstream>
#include "angle.h"
#include "testAngleRadians.h"
using namespace std;


/************************************
 * MAIN
 * Simple driver
 ***********************************/
int main()
{
   TestAngle().run();
   TestAngleRadian().run();
   std::cout << "Tests Pass\n";
   
   return 0;
}
