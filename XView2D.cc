
#include "mvc/XView2D.h"
#include "mvc/MVC.h"
#include "mvc/RectProj2D.h"

// X Window-specfic View.

void XView2D::initstuff(void)
{
   myproj = new RectProj2D();
   mycontroller = NULL;
   myinput = NULL;
   mycontroller = NULL;
   _attached = false;
}   

XView2D::XView2D(ColorManager* cm, Widget wid, Window win)
{
   // Needs a widget to attach event handlers to, and a window
   // to draw to. (A DrawingArea widget works well...)

   initstuff();
   attach(cm,wid,win);
}

XView2D::XView2D(Widget wid, Window win)
{
   initstuff();
   attach(&theColorManager,wid,win);
}

XView2D::XView2D(void)
{
   initstuff();
}   

void XView2D::attach(ColorManager* cm, Widget wid, Window win)
{
   // Create a DisplayDevice for the correct visual.
   // NOTE: This is just a hack. We really should be more careful about 
   //    determining the visual, but this works for home and Work.

   int d;

   d = DefaultDepth(XtDisplay(wid),DefaultScreen(XtDisplay(wid)));
   if (d == 8)
      mydd = new XPsuedoColorDisplayDevice(cm,XtDisplay(wid),win);
   else
      mydd = new XTrueColorDisplayDevice(cm,XtDisplay(wid),win);

   myinput = new InputDevice(wid);

   myproj->setDisplayDevWin(0,0,mydd->getWidth()-1,mydd->getHeight()-1);

   if (mycontroller != NULL)
      {
         myinput->setController(mycontroller);
         mycontroller->install();
      }

   reSize(mydd->getWidth(), mydd->getHeight());

   _attached = true;
}


void XView2D::reDraw(void)
{
   View2D::reDraw();
}

void XView2D::setController(Controller* thecontroller)
{
   if (mycontroller != NULL)
      mycontroller->uninstall();

   mycontroller = thecontroller;
   mycontroller->setView(this);
   
   if (_attached)
      {
         myinput->setController(mycontroller);
         mycontroller->install();
      }
}





