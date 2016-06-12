#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifndef VIEW2D_H
class View2D;
#endif

class Controller
{

   private:

   protected:
  
      View2D* myview;

   public:

      Controller();

      virtual void setView(View2D* v);

      virtual View2D* getView(void);

      virtual void install(void);
         // Called by View when controller is installed. Controllers
         // should use this method to set themselves up and do any
         // initializing required when becoming active.

      virtual void uninstall(void);
         // Called by View when deactivating a controller. Controllers
         // should use this method to gracefully save state and go to
         // sleep until the next time they are installed.

      virtual void reset(void);
         // Makes controller "forget" what it was doing and where it
         // was at. Resets the 'state' of the controller.

      //
      // Events.
      //
      virtual void button1Release(int x, int y);
         // Called when Button1 has been released. (x,y) represent
         // location of pointer when event occured.

      virtual void button2Release(int x, int y);
         // Called when Button2 has been released. (x,y) represent
         // location of pointer when event occured.

      virtual void button3Release(int x, int y);
         // Called when Button3 has been released. (x,y) represent
         // location of pointer when event occured.

      virtual void pointerMotion(int x, int y);
         // Called when pointer moves. Pointer is now at
         // Device coordinates (x,y).

      virtual void button1Motion(int x, int y);
         // Called when pointer moves and Button1 is depressed.

      virtual void button2Motion(int x, int y);
         // Called when pointer moves and Button2 is depressed.

      virtual void button3Motion(int x, int y);
         // Called when pointer moves and Button3 is depressed.

      virtual void pointerEnter(int x, int y);
         // Called when pointer enters input area. (x,y) location
         // pointer entered.

      virtual void pointerLeave(int x, int y);
         // Called when pointer leaves input area. (x,y) location
         // pointer left.

      virtual void resize(int w, int h);
         // Called when input window resizes. w is new width, 
         // h is new height;

      virtual void expose(void);
         // Called when any portion of the input window is exposed.

      virtual void keyPressed(char* stringrep, int x, int y);
         // stringrep is string representing key that was pressed.
         // (x,y) is location in window of pointer when key was pressed.
};

#include "View2D.h"

#endif // CONTROLLER_H