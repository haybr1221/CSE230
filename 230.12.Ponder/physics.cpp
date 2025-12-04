/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    Hayley Branchflower & Graham McClure
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/
  
 #include "physics.h"  // for the prototypes
 
 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
   if (domain <= mapping[0].domain)
      return mapping[0].range;
   
   if (domain >= mapping[numMapping-1].domain)
      return mapping[numMapping-1].range;
   
   for (int i = 0; i < numMapping - 1; i++)
   {
      double d0 = mapping[i].domain;
      double r0 = mapping[i].range;
      double d1 = mapping[i+1].domain;
      double r1 = mapping[i+1].range;
      
      if (domain == d0) return r0;
      if (domain == d1) return r1;
      
      if (domain > d0 && domain < d1)
      {
         return linearInterpolation(d0, r0, d1, r1, domain);
      }
   }
      
   return mapping[numMapping-1].range;
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
   const int tableSize = 20;
   const double altitudeTable[tableSize] = {
      0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,
      15000,20000,25000,30000,40000,50000,60000,70000,80000
   };
   const double gravityTable[tableSize] = {
      9.807,9.804,9.801,9.797,9.794,9.791,9.788,9.785,9.782,9.779,
      9.776,9.761,9.745,9.730,9.715,9.684,9.654,9.624,9.594,9.564
   };
   Mapping table[tableSize];

   for (int i = 0; i < tableSize; i++) {
      table[i].domain = altitudeTable[i];
      table[i].range = gravityTable[i];
   };
   // table, length, input_value
   double gravity = linearInterpolation(table, tableSize, altitude);
   return gravity;
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
   
   const int tableSize = 20;
   // altitude
   const double altitudeTable[tableSize] = {
      0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
      15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000
   };
   // density
   const double densityTable[tableSize]{
      1.2250000,1.1120000,1.0070000,0.9093000,0.8194000,0.7364000,0.6601000,0.5900000,0.5258000,0.4671000,
      0.4135000,0.1948000,0.0889100,0.0400800,0.0184100,0.0039960,0.0010270,0.0003097,0.0000828,0.0000185
   };

   Mapping table[tableSize];

   for (int i = 0; i < tableSize; i++) {
      table[i].domain = altitudeTable[i];
      table[i].range = densityTable[i];
   };
   // table, length, input_value
   double speedOfSound = linearInterpolation(table, tableSize, altitude);
   return speedOfSound;
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
   const int tableSize = 20;
   // altitude
   const double altitudeTable[tableSize] = { 0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,
                                             15000,20000,25000,30000,40000,50000,60000,70000,80000 };
   // speed of sound
   const double speedOfSoundTable[tableSize] = { 340,336,332,328,324,320,316,312,308,303,
                                                 299,295,295,295,305,324,337,319,289,269 };
   Mapping table[tableSize];

   for (int i = 0; i < tableSize; i++) {
      table[i].domain = altitudeTable[i];
      table[i].range = speedOfSoundTable[i];
   };
   // table, length, input_value
   double speedOfSound = linearInterpolation(table, tableSize, altitude);
   return speedOfSound;
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
   const int tableSize = 17;
   const double machTable[tableSize] = {
      0.000, 0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980, 1.000,
      1.020, 1.060, 1.240, 1.530, 1.990, 2.870, 2.890, 5.000
   };
   const double dragCoeffTable[tableSize] = {
      0.0000, 0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287, 0.4002, 0.4258,
      0.4335, 0.4483, 0.4064, 0.3663, 0.2897, 0.2297, 0.2306, 0.2656
   };

   Mapping table[tableSize];

   for (int i = 0; i < tableSize; i++) {
      table[i].domain = machTable[i];
      table[i].range = dragCoeffTable[i];
   };
   // table, length, input_value
   double drag = linearInterpolation(table, tableSize, speedMach);
   return drag;
}

