 /**********************************************************************
 * Source File:
 *    Lab 12: M777 Howitzer
 * Author:
 *    <your name here>
 * Summary:
 *    Simulate firing the M777 howitzer 15mm artillery piece
 ************************************************************************/

#include <cassert>       // for ASSERT
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "uiInteract.h"  // for INTERFACE
#include "simulation.h"  // for SIMULATION
#include "position.h"    // for POSITION
#include "projectile.h"  // for PROJECTILE
#include "test.h"        // for the unit tests
#include "ground.h"
#include "howitzer.h"    // for HOWITZER
#include <iomanip>       // for SETPRECISION
using namespace std;

const double LEFTRIGHT_RADS = 0.05;
const double UPDOWN_RADS = 0.003;

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a simulator object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* pSim = (Simulator*)p;

   ogstream gout;
   Position pos(23000, 19000);
   
   // set stats
   gout = pos;
   gout << std::fixed << std::setprecision(1);
   
   if (!pSim->projectile.isProjectileActive())
   {
      gout << "Angle: " << pSim->howitzer.getElevation() << setprecision(1) << endl;     // angle the Howitzer is pointing
   }
   
   // howitzer angle in degrees
   double degrees = pSim->howitzer.getElevation().getDegrees();

   // display info
   if (pSim->projectile.isProjectileActive())
   {
      // Display projectile stats
      gout << "Altitude:    " << pSim->ground.getElevationMeters(pSim->projectile.getProjectilePosition()) << "m" << endl   // position y
         << "Speed:       " << pSim->projectile.getProjectileVelocity().getSpeed() << "m/s" << endl          // muzzle velocity
         << "Distance:    " << abs(pSim->projectile.getProjectilePosition().getMetersX()-pSim->howitzer.getPosition().getMetersX()) << "m" << endl   // position x
         << "Hang time:   " << pSim->projectile.getProjectileAge() << "s" << setprecision(1);                                   // timer starting when fired
      // handle collisions
      // hit target
      if (pSim->ground.onPlatform(pSim->projectile.getProjectilePosition())) {
         cout<< "Projectile hit the target!" << endl;
         // reset game
         pSim->projectile.reset();
         pSim->howitzer.generatePosition(pSim->upperRight);
         pSim->ground.reset(pSim->howitzer.getPosition());
      }
      // hit ground
      else if (pSim->ground.getElevationMeters(pSim->projectile.getProjectilePosition())<0) {
         pSim->projectile.reset();
         cout << "Projectile hit the ground." << endl;
         
      }
      // if outside X boundaries
      else if (pSim->projectile.getProjectilePosition().getPixelsX() < 0 || 
               pSim->projectile.getProjectilePosition().getPixelsX() > pSim->upperRight.getPixelsX())
      {
         pSim->projectile.reset();
         cout << "Projectile out of bounds." << endl;
      }
      else
      {
         // if not collided:
         pSim->projectile.advance(pSim->projectile.getProjectileAge()+pSim->simulationTime);
      }
      
      
   }
   else if (pUI->isSpace())
   {
      pSim->projectile.fire(pSim->howitzer.getPosition(), pSim->simulationTime, degrees, pSim->howitzer.getMuzzleVelocity());
      cout << "Pressed Space. Fired." << endl;
   }

   //// INPUTS TO ADJUST ANGLE

   // right (clockwise)
   if (pUI->isRight()) 
   {
      //cout << "Pressed Right." << endl;
      if (degrees < 90 || degrees > 180) // 180 so it won't get stuck just past 270
      {
         pSim->howitzer.rotate(LEFTRIGHT_RADS); // radians for left/right
         degrees = pSim->howitzer.getElevation().getDegrees();
      }
   }

   // left (counterclockwise)
   if (pUI->isLeft()) 
   {
      //cout << "Pressed Left." << endl;
      if (degrees < 180 || degrees > 270) // 180 to prevent sticking at just past 90
      {
         pSim->howitzer.rotate(-LEFTRIGHT_RADS); // radians for left/right
         degrees = pSim->howitzer.getElevation().getDegrees();
      }
   }

   // up
   if (pUI->isUp())
   {
      //cout << "Pressed Up." << endl;
      // counterclockwise ("left")
      if (degrees < 180) // 180 to prevent sticking at just past 90
      {
         pSim->howitzer.rotate(-UPDOWN_RADS); // radians for left/right
         degrees = pSim->howitzer.getElevation().getDegrees();
      }
      // clockwise ("right")
      else if (degrees > 180)
         pSim->howitzer.rotate(UPDOWN_RADS);
   }

   // down
   if (pUI->isDown())
   {
      //cout << "Pressed Down." << endl;
      // counterclockwise ("left")
      if (degrees > 270) // 180 to prevent sticking at just past 90
      {
         pSim->howitzer.rotate(-UPDOWN_RADS); // radians for left/right
         degrees = pSim->howitzer.getElevation().getDegrees();
      }
      // clockwise ("right")
      else if (degrees < 90)
      {
         pSim->howitzer.rotate(UPDOWN_RADS);
         degrees = pSim->howitzer.getElevation().getDegrees();
      }
   }
   if (pSim->projectile.isProjectileActive())
      pSim->projectile.draw(gout);
   // draw ground
   pSim->ground.draw(gout);
   double flightTime = pSim->projectile.isProjectileActive() ? pSim->projectile.getProjectileAge() : 100.0;
   pSim->howitzer.draw(gout,flightTime); // temp 100 for testing
   
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // unit tests
   testRunner();
  
   // Initialize OpenGL
   Position posUpperRight;
   posUpperRight.setZoom(40.0 /* 40 meters equals 1 pixel */);
   posUpperRight.setPixelsX(700.0);
   posUpperRight.setPixelsY(500.0);
   Interface ui("M777 Howitzer Simulation", posUpperRight);

   // Initialize the simulation.
   Simulator sim(posUpperRight);


   // set everything into action
   ui.run(callBack, (void *)&sim);

   return 0;
}
