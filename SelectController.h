
#include "mvc/Controller.h"

#ifndef SELECTCONTROLLER_H
#define SELECTCONTROLLER_H

class SelectController : public Controller
{

   // SelectController class. Allows user to select a component and move
   // it to a new location.

   private:

   protected:

      Component2D* thecomp;   // The selected component.

   public:

      SelectController(void);

      void install(void);

      void reset(void);
         // Deselects the selection (if any).

      void select(Component2D* c);
         // Forces component c to become the selected component. Deselects
         // any components already selected.

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

};

#endif // SELECTCONTROLLER_H
