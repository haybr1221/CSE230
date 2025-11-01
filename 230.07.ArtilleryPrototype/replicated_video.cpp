// Note: I just followed the video for this; it's all correct as of the very first iteration... 
// It doesn't seem to want to come *down* though; why isn't gravity working??

#define _USE_MATH_DEFINES // for M_PI
#include <iostream>
#include <cmath> // for SIN, COS, POW, and M_PI
using namespace std;


double degreesToRadians(double degrees) {
   // r / 2 π = d / 360
   return degrees/360.0*2.0*M_PI;
};



/*************************************************
* LOOKUP SOUND SPEED
* Returns the speed of sound for a given altitude
**************************************************/
double lookupSoundSpeed(double altitude) {
   const int tableSize = 20;
   double altitudeTable[tableSize] = {
      0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
      15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000
   };
   double speedTable[tableSize] = { 
      340,336,332,328,324,320,316,312,308,303,
      299,295,295,295,305,324,337,319,289,269
   };

   // ensure in range
   if (!(altitude <= altitudeTable[tableSize - 1] && altitude >= altitudeTable[0])) {
      cout << "ERROR: ALTITUDE OUT OF RANGE: " << altitude << endl;
      return 0;
   };
   
   int idxGreater = -1; // index of first value above given altitude
   for (int i = 0; i < tableSize; i++) {

      // if greater, we've found v1 and v2
      if (altitudeTable[i] > altitude) {
         idxGreater = i;
         break;
      };
   };
   // ensure is valid
   if (idxGreater != -1) {
      // linear interpolation
      double v0 = altitudeTable[idxGreater - 1];
      double v1 = altitudeTable[idxGreater];
      double c0 = speedTable[idxGreater - 1];
      double c1 = speedTable[idxGreater];
      
      // calculation
      double result = c0 + ((altitude-v0) * (c1 - c0))/(v1-v0);
      return result;

   };
}

/***************************************************
* LOOKUP DRAG COEFFICIENT
* Returns the drag coefficient for the given mach
*************************/
double lookupDragCoefficient(double mach) {


   
   const int tableSize = 17;
   double machTable[tableSize] = { 
      0.000, 0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980, 1.000, 
      1.020, 1.060, 1.240, 1.530, 1.990, 2.870, 2.890, 5.000 
   };
   double dragCoeffTable[tableSize] = { 
      0.0000, 0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287, 0.4002, 0.4258, 
      0.4335, 0.4483, 0.4064, 0.3663, 0.2897, 0.2297, 0.2306, 0.2656 
   };
   // interpolate
   // ensure in range
   if (!(mach <= machTable[tableSize - 1] && mach >= machTable[0])) {
      cout << "ERROR: MACH OUT OF RANGE: " << mach << endl;
      return -1;
   };

   int idxGreater = -1; // index of first value above given altitude
   for (int i = 0; i < tableSize; i++) {

      // if greater, we've found v1 and v2
      if (machTable[i] > mach) {
         idxGreater = i;
         break;
      } // if exactly equal
      else if (machTable[i] == mach) {
         return dragCoeffTable[i];
      };
   };
   // ensure is valid
   if (idxGreater != -1) {
      // linear interpolation
      double v0 = machTable[idxGreater - 1];
      double v1 = machTable[idxGreater];
      double c0 = dragCoeffTable[idxGreater - 1];
      double c1 = dragCoeffTable[idxGreater];

      // calculation
      double result = c0 + ((mach - v0) * (c1 - c0)) / (v1 - v0);
      return result;

   };
   return -1;
}

int main()
{
   // 20 time units with zero acceleration, zero drag, and zero gravity.
   // constants
   float mass = 46.7;
   double diameter = 0.15489; // meters
   double radius = diameter / 2;
   double area = M_PI * (radius * radius);
   
   // INTERPOLATE THESE
   double airDensity = 1.225; // for 0
   float velocitySound = 340;
   double gravity = 9.807; // temp const

   // time
   //int num_time_units = 20; // seconds
   double timeStep = 1;// seconds - how long does each step take from the units?
   
   // bullet physics
   double angleDegrees = 30; // degrees
   double angleRadians = degreesToRadians(angleDegrees);
   double velocity = 827; // meters per second (from velX and velY)
   //double dragForce = 0; // just start at 0
   
   double speedOfSound = 340; // meters/sec - default at 0m altitude
   double mach;
   double velX = 0; // horizontal velocty component
   double velY = 0; // vertical velocity component
   
   // forces
   double dragCoeff;
   double dragForce;
   
   double accX = 0;
   double accY = 0;
   double acceleration;
   
   // hang
   double hangTime = 0;

   // location
   double posX = 0;
   double posY = 0;
   double distance = 0;
   
   // get speed
   /*velX = computeHorizontalComponent(velocity, angleRadians);
   velY = computeVerticalComponent(velocity, angleRadians);*/
   bool hitGround = false;
   // calculations
   //while (!hitGround) {
   for (int i = 0; i < 1000; i++) {
      // prepare values 
      speedOfSound = lookupSoundSpeed(posY);
      mach = velocity / speedOfSound;
      dragCoeff = lookupDragCoefficient(mach);
      dragForce = 0.5 * dragCoeff * airDensity * (velocity * velocity) * area;
      acceleration = dragForce / mass; // deceleration
      cout << acceleration <<  "," << dragCoeff << endl; 

      // velocity components
      
      //dx = sin(rads) * velocity
      velX = sin(angleRadians) * velocity;
      //dy = cos(rads) * velocity
      velY = cos(angleRadians) * velocity;

      // acceleration components
      
      //ddx = -sin(rads) * acceleration
      accX = -sin(angleRadians) * acceleration;
      //ddy = -cos(rads) * acceleration - gravity
      accY = -cos(angleRadians) * acceleration - gravity;

      // position components
      
      // x = x + velX*time + 0.5 * accX * time^2
      posX = posX + velX * timeStep + 0.5 * accX * timeStep * timeStep;
      // y = y + velY*time + 0.5 * accY * time^2
      posY = posY + velY * timeStep + 0.5 * accY * timeStep * timeStep;

      // new velocity components
      
      //dx = dx + ddx * t // dx = velX, ddx = accX
      velX = velX + accX * timeStep;
      //dy = dy + ddy * t // dy = velY, ddy = accY
      velY = velY + accY * timeStep;
      //velocity = sqrt((velX * velX) + (velY * velY)); // where should velocity be updated??
      
      // new angle
      
      //////////////
      // check if hit ground
      if (posY < 0) {
         // if yes, linear interpolate
         hitGround = true;

      }
      

      // add to the total time
      hangTime += timeStep;

      cout << "Distance: " << posX << "m      Altitude: " << posY << "m\n";
   };
}