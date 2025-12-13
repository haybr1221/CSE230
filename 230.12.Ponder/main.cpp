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
   gout << "Angle: " << pSim->howitzer.getElevation() << setprecision(1) << endl;     // angle the Howitzer is pointing
   
    //// INPUTS TO ADJUST ANGLE
   // space
   if (pUI->isSpace())
   {
      // fire bullet?
      cout << "Pressed Space. Fire" << endl;
      gout << "Altitude:    " << pSim->howitzer.getPosition().getPixelsY() << "m" << setprecision(1) << endl   // position y
      << "Speed:       " << pSim->howitzer.getMuzzleVelocity() << "m/s" << setprecision(1) << endl          // muzzle velocity
      << "Distance:    " << pSim->howitzer.getPosition().getPixelsX() << "m"   << setprecision(1) << endl   // position x
      << "Hang time:   " << 0.0 << "s"   << setprecision(1);                                   // timer starting when fired
   }
   
   double degrees = pSim->howitzer.getElevation().getDegrees();
   // right
   if (pUI->isRight()) 
   {
      cout << "Pressed Right." << endl;
      if (degrees < 90 || degrees > 270)
         pSim->howitzer.rotate(LEFTRIGHT_RADS); // radians for left/right
   }
   // left
   if (pUI->isLeft()) 
   {
      cout << "Pressed Left." << endl;
      if (degrees < 90 || degrees > 270)
         pSim->howitzer.rotate(-LEFTRIGHT_RADS); // radians for left/right
   }
   // up
   if (pUI->isUp())
   {
      cout << "Pressed Up." << endl;
      // negative UPDOWN_RADS (counterclockwise) if on the right side, else negative (clockwise on left)
      double dirRads = pSim->howitzer.getElevation().getRadians() < M_PI ? -UPDOWN_RADS : UPDOWN_RADS;
      pSim->howitzer.rotate(dirRads); // radians for left/right
   }
   // down
   if (pUI->isDown())
   {
      cout << "Pressed Down." << endl;
      // positive UPDOWN_RADS if on the right side, else negative
      double dirRads = pSim->howitzer.getElevation().getRadians() < M_PI ? UPDOWN_RADS : -UPDOWN_RADS;
      pSim->howitzer.rotate( dirRads ); // radians for left/right
   }

   
   // draw ground
   pSim->ground.draw(gout);
   pSim->howitzer.draw(gout,100); // temp 100 for testing
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
