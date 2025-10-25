/**********************************************************************
 * LAB 06
 * Contributers: Graham McClure, Hayley Branchflower.
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <format>        // for FORMAT
#include <sstream>       // for combining vars and strings with precision
#include <iomanip>       // for SETPRECISION
#include <iostream>      // for COUT
#define TIME_INTERVAL 0.1
#define GRAVITY -1.625
using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : ground(posUpperRight)
   {
      for (int i = 0; i < numStars; i++)
        stars[i].reset((int)posUpperRight.getX(), (int)posUpperRight.getY());
      // initialize lander
      lander = Lander(posUpperRight);
      upperRight = Position(posUpperRight);
   }
   
   void draw(ogstream & gout)
   {
      for (int i = 0; i < numStars; i++)
         stars[i].draw(gout);
      
   }
   
   Ground ground;
   Lander lander;
   Thrust thrust;
   Position upperRight;
private:
   static const int numStars = 50;
   Star stars[numStars];
   
   
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator * pSimulator = (Simulator *)p;
   
   // reset simulator if dead and space is pressed.
   if (pUI->isSpace() && !pSimulator->lander.isFlying()) {
       //  reset simulator
       cout << "pressed space: Resetting\n";
       pSimulator->ground.reset();
       pSimulator->lander.reset(pSimulator->upperRight);
   };
   ogstream gout;

   // draw 50 stars
   pSimulator->draw(gout);

   // draw the ground
   pSimulator->ground.draw(gout);
   
   // draw the stats
   //// labels
   gout.setPosition(Position(10,380));
   gout.str("Fuel: \nAltitude:\nSpeed:");
   gout.setPosition(Position(70, 380));
   //// values
   stringstream statStream;
   statStream << pSimulator->lander.getFuel() << " lbs\n" << fixed << setprecision(0) << pSimulator->ground.getElevation(pSimulator->lander.getPosition()) << " meters\n" << setprecision(2) << pSimulator->lander.getSpeed() << " m/s";
   gout.str(statStream.str());
   gout.flush();
   
   if (pSimulator->lander.isFlying()) {

       // handle lander physics
       Acceleration acc = pSimulator->lander.input(pSimulator->thrust, GRAVITY);
       pSimulator->lander.coast(acc, TIME_INTERVAL);
       //pSimulator->
   }
   //// Lander
   pSimulator->thrust.set(pUI); // set the directions
       // draw lander
   pSimulator->lander.draw(pSimulator->thrust, gout);
   
   // if lander has landed
   if (pSimulator->ground.onPlatform(pSimulator->lander.getPosition(), pSimulator->lander.getWidth())) {
       // if moving too fast, crash
       if (pSimulator->lander.getSpeed() < pSimulator->lander.getMaxSpeed()) {
           pSimulator->lander.land();
       }
       else {
           pSimulator->lander.crash();
       }
   };

   // if lander has died
   if (pSimulator->ground.hitGround(pSimulator->lander.getPosition(), pSimulator->lander.getWidth())) {
       pSimulator->lander.crash();

   };
   // DEATH MESSAGE
   if (pSimulator->lander.isDead()) {
       // display crash text     
                            /// x = half the screen plus account for text width      ///  x = 5/6ths to the top
       gout.setPosition(Position(pSimulator->upperRight.getX() / 2 - 50, pSimulator->upperRight.getY() / 6 * 5));
       gout.str("Housten, we have a problem!\n\n(press SPACE to restart)");
       gout.flush();
   }
   // SUCCESS MESSAGE
   else if (pSimulator->lander.isLanded()) {
       gout.setPosition(Position(pSimulator->upperRight.getX() / 2 - 50, pSimulator->upperRight.getY() / 6 * 5));
       gout.str("The Eagle has landed!\n\n(press SPACE to restart)");
       gout.flush();
   };

}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();
   
   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void*)&simulator);

   return 0;
}
