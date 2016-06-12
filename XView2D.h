#ifndef XVIEW2D_H
#define XVIEW2D_H

#include "mvc/View2D.h"
#include "mvc/Model2D.h"
#include "mvc/Controller.h"
#include "mvc/Projection2D.h"
#include "mvc/XTrueColorDisplayDevice.h"
#include "mvc/XPsuedoColorDisplayDevice.h"
#include "mvc/InputDevice.h"
#include "mvc/ColorManager.h"
#include <X11/Intrinsic.h>

class XView2D : public View2D
{
   // X Window-specfic View.

   private:

      void initstuff(void);   // Stuff common to all ctors.
                                       

   protected:

      bool _attached;  // Whether or not we've been attached to the 
                       // Input and Output devices.

   public:

      XView2D(ColorManager* cm, Widget wid, Window win);
         // Needs a widget to attach event handlers to, and a window
         // to draw to. (A DrawingArea widget works well...)

      XView2D(Widget wid, Window win);
         // Uses the global variable 'theColorManager' which is included
         // in libmvc.a and defined in MVC.h.

      XView2D(void);
         // NOTE: This ctor incompletely initializes the XView2D object.
         // Since no widget or window is provided, the InputDevice and
         // XDisplayDevice objects are not created until the 'attach' method
         // is called.

      void attach(ColorManager* cm, Widget wid, Window win);
         // Attaches an instance of XView2D to the given widget and window.

      void reDraw(void);

      void setController(Controller* thecontroller);
};

#endif // XVIEW2D_H





