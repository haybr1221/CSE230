//
//  main.cpp
//  230.07.Prove
//
//  Created by Hayley Branchflower on 2025-10-30.
//

// Step 1-4

// Step 5-8

// Drag
// Implement the drag equation.

#include <cmath>

double drag(double v, double dx, double dy)
{
   // Define constants
   double dragCoefficient = 0.3;
   double airDensity = 0.6;
   
   // We know mass and diameter
   double m = 46.7; // Mass (kg)
   double d = 0.15489; // Diameter (m)
   
   // Calculate area of a circle
   double a = M_PI * ((d / 2) * (d / 2));
   
   // Calculate force
   double force = 1/2 * (dragCoefficient) * (airDensity) * (v * v) * a;
   
   // Calculate drag (Newton's second law of motion)
   double drag = force / m;
   
   // Calculate angle
   double angle = atan2(dx, dy);
   
   // Calculate ddx and ddy
   double ddx = -drag * sin(angle);
   double ddy = -drag * cos(angle);
   
   return {ddx, ddy};

}

double airDensity(double altitude)
{
   double d0 = 0.0;
   double r0 = 1.225;
   double d1 = 1000.0;
   double r1 = 1.112;
   
   // (r - r0) / (d - d0) = (r1 - r0) / (d1 - d0)
   return r0 + (r1 - r0) * ((altitude - d0) / (d1 - d0));
}

double dragCoeffecient(double mach)
{
   // Implement the drag coefficient linear interpolation function.
   // Implement the speed of sound linear interpolation function.
   // This will make a difference, but not as great as the air density change.
   double machTable[17] = {0.000, 0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980, 1.000, 1.020, 1.060, 1.240, 1.530, 1.990, 2.870, 2.890, 5.00};
   double dragTable[17] = {0.0000, 0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287, 0.4002, 0.4258, 0.4335, 0.4483, 0.4064, 0.3663, 0.2897, 0.2297, 0.2306, 0.2656};
   
   // Find the correct Mach range
   for (int i = 0; i < 17 - 1; i++)
   {
       if (mach >= machTable[i] && mach < machTable[i + 1])
       {
           double m0 = machTable[i];
           double m1 = machTable[i + 1];
           double d0 = dragTable[i];
           double d1 = dragTable[i + 1];

           // Linear interpolation
           return d0 + (d1 - d0) * ((mach - m0) / (m1 - m0));
       }
   }
   
   return dragTable[17 - 1];
}

double hitGround(double y_curr, double y_prev, double x_prev, double x_curr, double t_prev, double t_curr)
{
   // In our previous simulations, the final elevation is below the ground.
   // We need to compute the point of impact with the ground.
   // Perform linear interpolation to find the time and distance where we hit the ground.
   // Display the results to 1 decimal points of accuracy.
   
   // will only hit ground of either of the ys are 0
   if (y_prev > 0 and y_curr < 0)
   {
      // (y - y0) / (t - t0) = (y1 - y0) / (t1 - t0)
      // Solve for t when y = 0
      double t_hit = t_prev + (0 - y_prev) * (t_curr - t_prev) / (y_curr - y_prev);
      
      // Step 3: use that t_hit to find x_hit (the position at ground contact)
      double x_hit = x_prev + (x_curr - x_prev) * ((t_hit - t_prev) / (t_curr - t_prev));
      
      return x_hit, t_hit;
   }
   
   return -1;
}
