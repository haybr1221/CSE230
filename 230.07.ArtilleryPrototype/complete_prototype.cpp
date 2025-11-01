// W07_prove_artillary_prototype.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define _USE_MATH_DEFINES // for M_PI
#include <iostream>
#include <cmath> // for SIN, COS, POW, and M_PI
using namespace std;

///********************
//* CALCULTATE POSITION ON AXIS
//* calculate new X or Y position
//*********/
//double computePositionOnAxis(double pos, double velocity, double time, double acceleration) {
//   // x = x + velX * time + 1/2 * accX * time^2
//   return pos + velocity * time + 1.0 / 2.0 * acceleration * pow(time, 2);
//};
//
///*******************************
// * COMPUTE HORIZONTAL COMPONENT
// * returns the horizontal component given the current speed and angle
// *******************************/
//double computeHorizontalComponent(double total_speed, double angle) {
//   // horizontal component (in meters/second) = total speed * sin(angle)
//   return total_speed * sin(angle);
//}
//
//double computeVerticalComponent(double total_speed, double angle) {
//   //vertical component (in meters/second) = total speed * cos(angle)
//   return total_speed * cos(angle);
//};
//
//double computeDistance(double distance, double velocity, double time, double acceleration) {
//   // s = s0 + velocity * time + 1/2 * accelelration * time^2
//   double newPos = distance + velocity * time + (1.0 / 2.0) * acceleration * pow(time, 2);
//   return newPos;
//};

///***************************
//* COMPUTE DRAG FORCE
//* returns drag force in newtons
//****************************/
//double computeDragForce(double dragCoef, double airDensity, double velocity, double area) {
//   // 1/2 * drag coefficient * air resistance * velocity^2 * area
//   double dragForce = 1.0 / 2.0 * dragCoef * airDensity * pow(velocity, 2) * area;
//   return dragForce;
//};
///********************
//* COMPUTE ACCELERATION VERTICAL
//* Returns a new acceleration for Y
//**********************/
//double computeAccelerationVertical(double angle, double acceleration, double gravity) {
//   double result = (-1 * cos(angle) * acceleration) - gravity;
//   return result;
//};
///********************
//* COMPUTE ACCELERATION HORIZONTAL
//* Returns a new acceleration for X
//**********************/
//double computeAccelerationHorizontal(double angle, double acceleration) {
//   return ((-1 * sin(angle)) * acceleration);
//};

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


int main()
{
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
   double angleDegrees = 75; // degrees
   double angleRadians = degreesToRadians(angleDegrees);
   double velocity = 827; // meters per second (from velX and velY)
   //double dragForce = 0; // just start at 0

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
   double distance = 0;
   
   // get speed
   /*velX = computeHorizontalComponent(velocity, angleRadians);
   velY = computeVerticalComponent(velocity, angleRadians);*/
   bool hitGround = false;
   // calculations
   while (!hitGround) {
      /* for (int i = 0; i < 20; i++) {*/
          // prepare values 
          //speedOfSound = lookupSoundSpeed(posY);
          
          //dragCoeff = lookupDragCoefficient(mach);

      //dragForce = 0.5 * dragCoeff * airDensity * (velocity * velocity) * area;
      



          //acceleration = dragForce / mass; // deceleration
          //cout << acceleration <<  "," << dragCoeff << endl; 
      // update gravity
      gravity = lookupGravity(posY);
      airDensity = lookupAirDensity(posY);
      speedOfSound = lookupSoundSpeed(posY);
      mach = velocity / speedOfSound;
      dragCoeff = lookupDragCoefficient(mach);

      // Calculate force
      double force = 1.0 / 2.0 * (dragCoeff) * (airDensity) * (velocity * velocity) * area;

      // Calculate drag (Newton's second law of motion)
      double drag = force / mass;

      //// Calculate angle
      //double angle = atan2(velX, velY);

      // Calculate ddx and ddy
      /*double accX = -drag * sin(angleRadians);
      double accY = -drag * cos(angleRadians);*/

      // acceleration components
    
      //ddx = -sin(rads) * acceleration
      accX = -sin(angleRadians) * drag;
      //ddy = -cos(rads) * acceleration - gravity
      accY = -cos(angleRadians) * drag - gravity;
      /*acceleration = sqrt((accX * accX) + (accY * accY));*/

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


      // position components

       // x = x + velX*time + 0.5 * accX * time^2
      //posX = posX + velX * timeStep + 0.5 * accX * timeStep * timeStep;
      // y = y + velY*time + 0.5 * accY * time^2
      //posY = posY + velY * timeStep + 0.5 * accY * timeStep * timeStep;

      // new velocity components

      ////dx = dx + ddx * t // dx = velX, ddx = accX
      velX = velX + accX * timeStep;
      ////dy = dy + ddy * t // dy = velY, ddy = accY
      velY = velY + accY * timeStep;
      velocity = sqrt((velX * velX) + (velY * velY));
      //



      //// new angle
      angleRadians = atan2(velX, velY);
      ////////////////
      //// check if hit ground

   // will only hit ground of either of the ys are 0
      if (posY < 0) {
         // if yes, linear interpolate
         hitGround = true;

         // (y - y0) / (t - t0) = (y1 - y0) / (t1 - t0)
         // Solve for t when y = 0
         double t_prev = hangTime - timeStep;
         double t_curr = hangTime;
         double x_curr = posX;
         double y_curr = posY;
         double y_prev = prevPosY;
         double x_prev = prevPosX;
         double t_hit = t_prev + (0 - y_prev) * (t_curr - t_prev) / (y_curr - y_prev);

         double x_hit = x_prev + (x_curr - x_prev) * ((t_hit - t_prev) / (t_curr - t_prev));

         posX = x_hit;
         hangTime = t_hit;
      }
      else {
         // if hasn't hit ground, update "prev" trackers.
         prevPosY = posY;
         prevPosX = posX;
      };
      //

      //// add to the total time
      hangTime += timeStep;     
      cout << "Distance: " << posX << "m      Altitude: " << posY << "m    Hang: " << hangTime << "s   Angle (radians): " << angleRadians << "   Hitground = " << hitGround << endl;

   };

};


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

//double degreesToRadians(double degrees) {
//   // r / 2 π = d / 360
//   return degrees/360.0*2.0*M_PI;
//};
//
//
//
///*************************************************
//* LOOKUP SOUND SPEED
//* Returns the speed of sound for a given altitude
//**************************************************/
//double lookupSoundSpeed(double altitude) {
//   const int tableSize = 20;
//   double altitudeTable[tableSize] = {
//      0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
//      15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000
//   };
//   double speedTable[tableSize] = { 
//      340,336,332,328,324,320,316,312,308,303,
//      299,295,295,295,305,324,337,319,289,269
//   };
//
//   // ensure in range
//   if (!(altitude <= altitudeTable[tableSize - 1] && altitude >= altitudeTable[0])) {
//      cout << "ERROR: ALTITUDE OUT OF RANGE: " << altitude << endl;
//      return 0;
//   };
//   
//   int idxGreater = -1; // index of first value above given altitude
//   for (int i = 0; i < tableSize; i++) {
//
//      // if greater, we've found v1 and v2
//      if (altitudeTable[i] > altitude) {
//         idxGreater = i;
//         break;
//      };
//   };
//   // ensure is valid
//   if (idxGreater != -1) {
//      // linear interpolation
//      double v0 = altitudeTable[idxGreater - 1];
//      double v1 = altitudeTable[idxGreater];
//      double c0 = speedTable[idxGreater - 1];
//      double c1 = speedTable[idxGreater];
//      
//      // calculation
//      double result = c0 + ((altitude-v0) * (c1 - c0))/(v1-v0);
//      return result;
//
//   };
//}
//
///***************************************************
//* LOOKUP DRAG COEFFICIENT
//* Returns the drag coefficient for the given mach
//*************************/
//double lookupDragCoefficient(double mach) {
//
//
//   
//   const int tableSize = 17;
//   double machTable[tableSize] = { 
//      0.000, 0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980, 1.000, 
//      1.020, 1.060, 1.240, 1.530, 1.990, 2.870, 2.890, 5.000 
//   };
//   double dragCoeffTable[tableSize] = { 
//      0.0000, 0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287, 0.4002, 0.4258, 
//      0.4335, 0.4483, 0.4064, 0.3663, 0.2897, 0.2297, 0.2306, 0.2656 
//   };
//   // interpolate
//   // ensure in range
//   if (!(mach <= machTable[tableSize - 1] && mach >= machTable[0])) {
//      cout << "ERROR: MACH OUT OF RANGE: " << mach << endl;
//      return -1;
//   };
//
//   int idxGreater = -1; // index of first value above given altitude
//   for (int i = 0; i < tableSize; i++) {
//
//      // if greater, we've found v1 and v2
//      if (machTable[i] > mach) {
//         idxGreater = i;
//         break;
//      } // if exactly equal
//      else if (machTable[i] == mach) {
//         return dragCoeffTable[i];
//      };
//   };
//   // ensure is valid
//   if (idxGreater != -1) {
//      // linear interpolation
//      double v0 = machTable[idxGreater - 1];
//      double v1 = machTable[idxGreater];
//      double c0 = dragCoeffTable[idxGreater - 1];
//      double c1 = dragCoeffTable[idxGreater];
//
//      // calculation
//      double result = c0 + ((mach - v0) * (c1 - c0)) / (v1 - v0);
//      return result;
//
//   };
//   return -1;
//}
//
//int main()
//{
//   // Constants
//   float mass = 46.7;
//   double diameter = 0.15489;
//   double radius = diameter / 2;
//   double area = M_PI * (radius * radius);
//   double airDensity = 1.225;
//
//   double gravity = 9.807;
//   double timeStep = 0.01; // Use smaller time step for better accuracy
//
//   // Bullet Physics
//   double angleDegrees = 30;
//   double angleRadians = degreesToRadians(angleDegrees);
//   double initialVelocity = 827; // m/s
//
//   // Velocity components
//   double velX = cos(angleRadians) * initialVelocity; // x-component based on angle
//   double velY = sin(angleRadians) * initialVelocity; // y-component based on angle
//
//   // Position
//   double posX = 0;
//   double posY = 0;
//
//   // Simulation
//   for (int i = 0; i < 1000; i++) {
//      if (posY < 0) break; // Stop if hitting the ground
//
//      double speedOfSound = lookupSoundSpeed(posY);
//      double mach = std::sqrt(velX * velX + velY * velY) / speedOfSound;
//      double dragCoeff = lookupDragCoefficient(mach);
//      double dragForce = 0.5 * dragCoeff * airDensity * (velX * velX + velY * velY) * area;
//
//      double accelX = -dragForce * (velX / mass); // Drag deceleration in x
//      double accelY = -dragForce * (velY / mass) - gravity; // Drag deceleration in y and gravity
//
//      // Update positions
//      posX += velX * timeStep + 0.5 * accelX * timeStep * timeStep;
//      posY += velY * timeStep + 0.5 * accelY * timeStep * timeStep;
//
//      // Update velocities
//      velX += accelX * timeStep;
//      velY += accelY * timeStep;
//      std::cout << "position: (" << posX << ", " << posY << ")" << endl;
//   }
//
//   
//}