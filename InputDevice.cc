#include <stdio.h>
#include "mvc/InputDevice.h"

void InputDevice::ButtonHandlerWrapper(Widget thewidget,
                                            XtPointer clientdata,
                                            XEvent* theevent)
{
   ((InputDevice*) clientdata) -> ButtonHandler(thewidget,theevent);
}

void InputDevice::ButtonHandler(Widget thewidget, XEvent* theevent)
{
   // Handles ButtonRelease Events.
   // ButtonPress events are not selected for, because selecting both
   // Press and Release causes a passive grab which causes us to lose
   // motion events.

   XButtonEvent* xbe;

   xbe = (XButtonEvent*) theevent;

   if (mycontroller == NULL)
      return;

   switch(xbe->button)
      {
         case(Button1): 
            mycontroller->button1Release(xbe->x,xbe->y);
            break;
         case(Button2):
            mycontroller->button2Release(xbe->x,xbe->y);
            break;
         case(Button3):
            mycontroller->button3Release(xbe->x,xbe->y);
            break;
         default:
            printf("InputDevice::ButtonHandler: Button not supported.\n");
            break;
      }
   
}

void InputDevice::PointerMotionHandlerWrapper(Widget thewidget,
                                              XtPointer clientdata,
                                              XEvent* theevent)
{
   ((InputDevice*) clientdata) -> PointerMotionHandler(thewidget,theevent);
}

void InputDevice::PointerMotionHandler(Widget thewidget, XEvent* theevent)
{
   // Handles Pointer Motion, with and without buttons pressed.

   XMotionEvent* xme;

   xme = (XMotionEvent*) theevent;

   if (mycontroller == NULL)
      return;

   if (xme->state == 0)  // No buttons or keys pressed.
      { mycontroller -> pointerMotion(xme->x, xme->y); return; }
 
   if (xme->state & Button1Mask)
      { mycontroller -> button1Motion(xme->x, xme->y); return; }

   if (xme->state & Button2Mask)
      { mycontroller -> button2Motion(xme->x, xme->y); return; }

   if (xme->state & Button3Mask)
      { mycontroller -> button3Motion(xme->x, xme->y); return; }

}

void InputDevice::ExposeHandlerWrapper(Widget thewidget,
                                       XtPointer clientdata,
                                       XEvent* theevent)
{
   ((InputDevice*) clientdata) -> ExposeHandler(thewidget,theevent);
}

void InputDevice::ExposeHandler(Widget thewidget, XEvent* theevent)
{
   XExposeEvent* xee;

   xee = (XExposeEvent*) theevent;

   if (myexposehandler_firsttime)
      {
         // Turn off bit gravity so we get resize events for shrinking 
         // and expanding windows.
         XSetWindowAttributes swa;
         swa.bit_gravity = ForgetGravity;
         XChangeWindowAttributes (xee->display, xee->window, 
                                  CWBitGravity, &swa);

         myexposehandler_firsttime = false;
      }

   if (mycontroller == NULL)
      return;

   // We don't care about any expose events except the last one 
   // in a given series.
   if (xee->count == 0)
      mycontroller -> expose();
}

void InputDevice::ResizeHandlerWrapper(Widget thewidget,
                                       XtPointer clientdata,
                                       XEvent* theevent)
{
   ((InputDevice*) clientdata) -> ResizeHandler(thewidget,theevent);
}

void InputDevice::ResizeHandler(Widget thewidget, XEvent* theevent)
{
   XConfigureEvent* xce;

   xce = (XConfigureEvent*) theevent;

   if (mycontroller == NULL)
      return;

   mycontroller -> resize(xce->width, xce->height);
}

void InputDevice::EnterLeaveHandlerWrapper(Widget thewidget,
                                           XtPointer clientdata,
                                           XEvent* theevent)
{
   ((InputDevice*) clientdata) -> EnterLeaveHandler(thewidget,theevent);
}

void InputDevice::EnterLeaveHandler(Widget thewidget, XEvent* theevent)
{
   XCrossingEvent* xce;

   xce = (XCrossingEvent*) theevent;

   if (mycontroller == NULL)
      return;

   if (xce->type == EnterNotify)
      mycontroller -> pointerEnter(xce->x, xce->y);
   else
      mycontroller -> pointerLeave(xce->x, xce->y);
}

void InputDevice::KeyPressHandlerWrapper(Widget thewidget,
                                         XtPointer clientdata,
                                         XEvent* theevent)
{
   ((InputDevice*) clientdata) -> KeyPressHandler(thewidget,theevent);
}

void InputDevice::KeyPressHandler(Widget thewidget, XEvent* theevent)
{
   XKeyPressedEvent* xkpe;
   char buffer[101];
   int charcount;
   KeySym key;

   xkpe = (XKeyPressedEvent*) theevent;

   if (mycontroller == NULL)
      return;

   // Get the string associated with the key that was pressed.
   charcount = XLookupString(xkpe,buffer,100,&key,NULL);
   buffer[charcount]='\0';

   mycontroller -> keyPressed(buffer,xkpe->x,xkpe->y);
}

InputDevice::InputDevice(Widget w)
{
   mywidget = w;
   mycontroller = NULL;
   myexposehandler_firsttime = true;

   // Set up event handlers for the various events.

   XtAddEventHandler(mywidget, ButtonReleaseMask, False,
                     (XtEventHandler)ButtonHandlerWrapper,
                     (XtPointer*)this);

   XtAddEventHandler(mywidget, PointerMotionMask | ButtonMotionMask, False,
                     (XtEventHandler)PointerMotionHandlerWrapper,
                     (XtPointer*)this);

   XtAddEventHandler(mywidget, ExposureMask, False,
                     (XtEventHandler)ExposeHandlerWrapper,
                     (XtPointer*)this);

   XtAddEventHandler(mywidget, StructureNotifyMask, False,
                     (XtEventHandler)ResizeHandlerWrapper,
                     (XtPointer*)this);

   XtAddEventHandler(mywidget, EnterWindowMask | LeaveWindowMask, False,
                     (XtEventHandler)EnterLeaveHandlerWrapper,
                     (XtPointer*)this);

   XtAddEventHandler(mywidget, KeyPressMask, False,
                     (XtEventHandler)KeyPressHandlerWrapper,
                     (XtPointer*)this);
}

void InputDevice::setController(Controller* c)
{
   mycontroller = c;
}

