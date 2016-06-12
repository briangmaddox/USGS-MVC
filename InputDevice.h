#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <X11/X.h>
#include <X11/Intrinsic.h>

#ifndef CONTROLLER_H
class Controller;
#endif

class InputDevice
{
   private:

   protected:
      Widget mywidget;
      Controller* mycontroller;
      bool myexposehandler_firsttime;

      // Handlers

      virtual void ButtonHandler(Widget thewidget, XEvent* theevent);
         // Called by ButtonPressHandlerWrapper whenever a pointer
         // button is pressed.

      virtual void PointerMotionHandler(Widget thewidget, XEvent* theevent);


      virtual void ExposeHandler(Widget thewidget, XEvent* theevent);


      virtual void ResizeHandler(Widget thewidget, XEvent* theevent);


      virtual void EnterLeaveHandler(Widget thewidget, XEvent* theevent);

      virtual void KeyPressHandler(Widget thewidget, XEvent* theevent);

      // Wrappers (One for each Handler)

      static void ButtonHandlerWrapper(Widget thewidget,
                                       XtPointer clientdata,
                                       XEvent* theevent);
         // This method must be static because it is called as an
         // 'XtEventHandler' function. clientdata contains the this
         // pointer of the object that registered this wrapper. We
         // use that to call ButtonPressHandler for the correct object.

      static void PointerMotionHandlerWrapper(Widget thewidget,
                                              XtPointer clientdata,
                                              XEvent* theevent);

      static void ExposeHandlerWrapper(Widget thewidget,
                                       XtPointer clientdata,
                                       XEvent* theevent);

      static void ResizeHandlerWrapper(Widget thewidget,
                                       XtPointer clientdata,
                                       XEvent* theevent);

      static void EnterLeaveHandlerWrapper(Widget thewidget,
                                           XtPointer clientdata,
                                           XEvent* theevent);

      static void KeyPressHandlerWrapper(Widget thewidget,
                                         XtPointer clientdata,
                                         XEvent* theevent);

   public:

      InputDevice(Widget w);

      virtual void setController(Controller* c);

};

#include "mvc/Controller.h"

#endif // INPUTDEVICE_H

