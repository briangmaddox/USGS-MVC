
#include "mvc/Controller.h"

#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

class TestController : public Controller
{

   // Test Controller. Prints messages in response to each event type.
   // Useful (maybe) for testing, learning, etc. Good starting place
   // for developing new Controllers.

   private:

   protected:

   public:

      void button1Release(int x, int y);
         // Called when Button1 has been released. (x,y) represent
         // location of pointer when event occured.

      void button2Release(int x, int y);
         // Called when Button2 has been released. (x,y) represent
         // location of pointer when event occured.
 
      void button3Release(int x, int y);
         // Called when Button3 has been released. (x,y) represent
         // location of pointer when event occured.

      void pointerMotion(int x, int y);
         // Called when pointer moves. Pointer is now at
         // Device coordinates (x,y).

      void button1Motion(int x, int y);
         // Called when pointer moves and Button1 is depressed.

      void button2Motion(int x, int y);
         // Called when pointer moves and Button2 is depressed.

      void button3Motion(int x, int y);
         // Called when pointer moves and Button3 is depressed.

      void pointerEnter(int x, int y);
         // Called when pointer enters input area. (x,y) location
         // pointer entered.

      void pointerLeave(int x, int y);
         // Called when pointer leaves input area. (x,y) location
         // pointer left.

      void resize(int w, int h);
         // Called when input window resizes. w is new width, 
         // h is new height;

      void expose(void);
         // Called when any portion of the input window is exposed.

};

#endif // TESTCONTROLLER_H
