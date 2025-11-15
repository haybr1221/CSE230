// W07_prove_artillary_prototype.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define _USE_MATH_DEFINES // for M_PI
#include <iostream> // for cout
#include <iomanip> // for setprecision
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
   const double altitudeTable[tableSize] = {
      0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
      15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000
   };
   const double speedTable[tableSize] = { 
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
   const double machTable[tableSize] = { 
      0.000, 0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980, 1.000, 
      1.020, 1.060, 1.240, 1.530, 1.990, 2.870, 2.890, 5.000 
   };
   const double dragCoeffTable[tableSize] = { 
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

/***************************************************
* LOOKUP GRAVITY
* Returns the gravity for the given altitude
*************************/
double lookupGravity(double altitude) {
   const int tableSize = 20;
   const double altiTable[tableSize] = {
      0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,
      15000,20000,25000,30000,40000,50000,60000,70000,80000
   };
   const double gravTable[tableSize] = {
      9.807,9.804,9.801,9.797,9.794,9.791,9.788,9.785,9.782,9.779,
      9.776,9.761,9.745,9.730,9.715,9.684,9.654,9.624,9.594,9.564
   };
   
   // interpolate
   // ensure in range
   if (!(altitude <= altiTable[tableSize - 1] && altitude >= altiTable[0])) {
      cout << "ERROR: MACH OUT OF RANGE: " << altitude << endl;
      return -1;
   };

   int idxGreater = -1; // index of first value above given altitude
   for (int i = 0; i < tableSize; i++) {

      // if greater, we've found v1 and v2
      if (altiTable[i] > altitude) {
         idxGreater = i;
         break;
      } // if exactly equal
      else if (altiTable[i] == altitude) {
         return gravTable[i];
      };
   };
   // ensure is valid
   if (idxGreater != -1) {
      // linear interpolation
      double v0 = altiTable[idxGreater - 1];
      double v1 = altiTable[idxGreater];
      double c0 = gravTable[idxGreater - 1];
      double c1 = gravTable[idxGreater];

      // calculation
      double result = c0 + ((altitude - v0) * (c1 - c0)) / (v1 - v0);
      return result;

   };
   return -1;
}

double lookupAirDensity(double altitude) {
   const int tableSize = 19;
   const double altiTable[] = {
      0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
      15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000
   };
   const double densiTable[]{
      1.2250000,1.1120000,1.0070000,0.9093000,0.8194000,0.7364000,0.6601000,0.5900000,0.5258000,0.4671000,
      0.4135000,0.1948000,0.0889100,0.0400800,0.0184100,0.0039960,0.0010270,0.0003097,0.0000828,0.0000185
   };
   // interpolate
   // ensure in range
   if (!(altitude <= altiTable[tableSize - 1] && altitude >= altiTable[0])) {
      cout << "ERROR: MACH OUT OF RANGE: " << altitude << endl;
      return -1;
   };

   int idxGreater = -1; // index of first value above given altitude
   for (int i = 0; i < tableSize; i++) {

      // if greater, we've found v1 and v2
      if (altiTable[i] > altitude) {
         idxGreater = i;
         break;
      } // if exactly equal
      else if (altiTable[i] == altitude) {
         return densiTable[i];
      };
   };
   // ensure is valid
   if (idxGreater != -1) {
      // linear interpolation
      double v0 = altiTable[idxGreater - 1];
      double v1 = altiTable[idxGreater];
      double c0 = densiTable[idxGreater - 1];
      double c1 = densiTable[idxGreater];

      // calculation
      double result = c0 + ((altitude - v0) * (c1 - c0)) / (v1 - v0);
      return result;

   };
   return -1;
};


/*************************************
* SIMULATE PROJECTILE
* Simulates the path taken by a M795 projectile from a M777 howitzer.
* ARGS:
* angleRadians : double - The angle at which the bullet is fired, in radians.
**************************************/
int simulateProjectile(double angleRadians) {
   
   // 20 time units with zero acceleration, zero drag, and zero gravity.
   // constants
   float mass = 46.7;
   double diameter = 0.15489; // meters
   double radius = diameter / 2;
   double area = M_PI * (radius * radius);

   // INTERPOLATE THESE
   double airDensity = 0.6;//1.225; // for 0
   float velocitySound = 340;
   double gravity = 9.8; // temp const
   // forces
   double dragCoeff = 0.3;
   double dragForce;

   // time
   //int num_time_units = 20; // seconds
   double timeStep = 0.01;// seconds - how long does each step take from the units?

   // bullet physics
   double velocity = 827; // meters per second (from velX and velY)

   double speedOfSound = 340; // meters/sec - default at 0m altitude
   double mach;
   double velX = 0;//computeHorizontalComponent(velocity, angleRadians); // horizontal velocty component
   double velY = 0;//computeVerticalComponent(velocity, angleRadians); // vertical velocity component

   double accX = 0;
   double accY = 0;
   double acceleration = 0;

   // hang
   double hangTime = 0;

   // location
   double posX = 0;
   double posY = 0;
   double prevPosX = 0;
   double prevPosY = 0;
   
   bool hitGround = false;
   // calculations
   while (!hitGround) {

      // look up new values
      gravity = lookupGravity(posY);
      airDensity = lookupAirDensity(posY);
      speedOfSound = lookupSoundSpeed(posY);
      mach = velocity / speedOfSound;
      dragCoeff = lookupDragCoefficient(mach);

      // Calculate force
      double force = 1.0 / 2.0 * (dragCoeff) * (airDensity) * (velocity * velocity) * area;

      // Calculate drag (Newton's second law of motion)
      double drag = force / mass;

      // acceleration components
    
      //ddx = -sin(rads) * drag acceleration
      accX = -sin(angleRadians) * drag;
      //ddy = -cos(rads) * drag acceleration - gravity
      accY = -cos(angleRadians) * drag - gravity;

      // velocity components

      //dx = sin(rads) * velocity
      velX = sin(angleRadians) * velocity;
      //dy = cos(rads) * velocity
      velY = cos(angleRadians) * velocity;

      // position components

     // x = x + velX*time + 0.5 * accX * time^2
      posX = posX + velX * timeStep + 0.5 * accX * timeStep * timeStep;
      // y = y + velY*time + 0.5 * accY * time^2
      posY = posY + velY * timeStep + 0.5 * accY * timeStep * timeStep;

      // new velocity components

      ////dx = dx + ddx * t // dx = velX, ddx = accX
      velX = velX + accX * timeStep;
      ////dy = dy + ddy * t // dy = velY, ddy = accY
      velY = velY + accY * timeStep;
      velocity = sqrt((velX * velX) + (velY * velY));

      //// new angle
      angleRadians = atan2(velX, velY);
      
      //// check if hit ground

      if (posY < 0) {
         
         hitGround = true;

         // (y - y0) / (t - t0) = (y1 - y0) / (t1 - t0)
         // set up variables
         double t_prev = hangTime - timeStep;
         double t_curr = hangTime;
         double x_curr = posX;
         double y_curr = posY;
         double y_prev = prevPosY;
         double x_prev = prevPosX;

         // linear interpolation
         // Solve for t when y = 0
         double t_hit = t_prev + (0 - y_prev) * (t_curr - t_prev) / (y_curr - y_prev);

         double x_hit = x_prev + (x_curr - x_prev) * ((t_hit - t_prev) / (t_curr - t_prev));

         posX = x_hit; // the x distance at which y hit 0
         posY = 0; // our interpolation ensures y should be 0
         hangTime = t_hit; // the adjusted time for when y=0
      }
      else {
         // if hasn't hit ground, update "prev" trackers.
         prevPosY = posY;
         prevPosX = posX;
      };
      //

      //// add to the total time
      hangTime += timeStep;     
   };
   //cout << fixed << setprecision(1) << "Distance: " << posX << "m      Altitude: " << posY << "m    Hang: " << hangTime << "s   Angle (radians): " << angleRadians << "   Hitground = " << hitGround << endl;
   cout << fixed << setprecision(1) << "Distance: " << posX << "m      Hang: " << hangTime << "s   Final Angle (radians): " << angleRadians << endl;
   return 0;
};

int main() {
   // run 4 times: once for each of the 4 tests
   for (int i = 0; i < 4; i++) {
      double angleDegrees; // degrees
      cout << "\nWhat is the angle (degrees)? >";
      cin >> angleDegrees;
      double angleRadians = degreesToRadians(angleDegrees);
      simulateProjectile(angleRadians);
   };
};