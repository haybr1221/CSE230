// W07_prove_artillary_prototype.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES // for M_PI
#include <iostream>
#include <cmath> // for SIN, COS, POW, and M_PI
using namespace std;

/********************
* CALCULTATE POSITION ON AXIS
* calculate either X or Y position
*********/
double computePositionOnAxis(double pos, double velocity, double time, double acceleration) {
   // x = x + velX * time + 1/2 * accX * time^2
   return pos + velocity * time + 1 / 2 * acceleration * pow(time, 2);
};
/*******************************
 * COMPUTE HORIZONTAL COMPONENT
 * returns the horizontal component given the current speed and angle
 *******************************/
double computeHorizontalComponent(double total_speed, double angle) {
   // horizontal component (in meters/second) = total speed * sin(angle)
   return total_speed * sin(angle);
}

double computeVerticalComponent(double total_speed, double angle) {
   //vertical component (in meters/second) = total speed * cos(angle)
   return total_speed * cos(angle);
};

double computeDistance(double distance, double velocity, double time, double acceleration) {
   // s = s0 + velocity * time + 1/2 * accelelration * time^2
   double newPos = distance + velocity * time + (1 / 2) * acceleration * pow(time, 2);
   return newPos;
};

/***************************
* COMPUTE DRAG FORCE
* returns drag force in newtons
****************************/
double computeDragForce(double dragCoef, double airDensity, double velocity, double area) {
   // 1/2 * drag coefficient * air resistance * velocity^2 * area
   double dragForce = 1 / 2 * dragCoef * airDensity * pow(velocity, 2) * area;
   return dragForce;
};

double degreesToRadians(double degrees) {
   // r / 2 π = d / 360
   return degrees/360*2*M_PI;
};

int main()
{
   double a;
   a = degreesToRadians(75);
   a = degreesToRadians(0);
   a = degreesToRadians(90);
   a = degreesToRadians(180);
   // 20 time units with zero acceleration, zero drag, and zero gravity.
   // constants
   float mass = 46.7;
   double diameter = 0.15489;
   double radius = diameter / 2;
   double area = M_PI * pow(radius, 2);
   
   float velocitySound = 340;

   // time
   int num_time_units = 20; // seconds
   double timeStep = 1;//0.01; // how long does each step take from the units?
   
   // bullet physics
   double angleDegrees = 75; // degrees
   double angleRadians = degreesToRadians(angleDegrees);
   double velocity = 827; // meters per second (from velX and velY)
   double dragForce = 0; // just start at 0
   double velX; // horizontal velocty component
   double velY; // vertical velocity component

   // forces
   double accX = 0;
   double accY = 0;
   double acceleration = dragForce * mass;
   double drag = 0; // altitude 0 = drag 0
   double gravity = -9.8; // temp const

   // location
   double posX = 0;
   double posY = 0;
   double distance = 0;
   

   // calculations
   for (int i = 0; i < 20; i++) {
      // position
      posX = computeDistance(posX, velX, timeStep, accX);
      posY = computeDistance(posY, velY, timeStep, accY);
      // speed
      velX = computeHorizontalComponent(velocity, angleRadians);
      velY = computeVerticalComponent(velocity, angleRadians);
      cout << "Distance: " << posX << "m    Altitude: " << posY << "m\n";
   };
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
