#ifndef XMULTIVIEW2D_H
#define XMULTIVIEW2D_H

#include "mvc/XView2D.h"
#include "mvc/RectProj2D.h"

class XMultiView2D : public XView2D
{

   protected:

      RectProj2D* _viewportprojs;
      int _numviewports;
      double *_px, *_py;  // Coordinates of the points the viewports are
                          // centered on.
      int _num_across;
      double _radius;

      void initstuff(void);
      void Draw(void);
      bool calcProjs(void);

   public:

      XMultiView2D(ColorManager* cm, Widget wid, Window win);

      XMultiView2D(Widget wid, Window win);
         // Uses the global variable 'theColorManager' which is included
         // in libmvc.a and defined in MVC.h.         

      XMultiView2D(void);
         // NOTE: This ctor incompletely initializes the XView2D object.
         // Since no widget or window is provided, the InputDevice and
         // XDisplayDevice objects are not created until the 'attach' method
         // is called.

     void reSize(int w, int h);

     void reFresh(void);

     ~XMultiView2D(void);

      virtual bool setPoints(double x[], double y[], int numpoints,
                             int num_across, double radius);
         // x[],y[] are coordinates for a list of points. The DisplayDevice
         // will be split into numpoints view ports; each centered on a point.
         // XMultiView2D will attempt to place num_across viewports across
         // the display device. If num_across does not divide numpoints evenly,
         // the remaining points will be equally spaced on the last row of
         // viewports. 'radius' is in WorldSpace coordinates and specifies a
         // minimum area around a point to be displayed. More area may be shown,
         // but it is guaranteed that the minimum area will be visible.


      double getWorldSpaceX(int x, int y);
      double getWorldSpaceY(int x, int y);
         // These two functions return either the World Space X or
         // World Space Y coordinate given a point in Device Space.

      void pan(double newcenter_x, double newcenter_y);
         // Moves the center of the World Space Window to
         // (newcenter_x, newcenter_y) without changing its size.

      void zoomBy(double magfactor);
         // Zooms current View by magfactor. Center of WSW
         // does not move. Positive magfactors make things "bigger" 
         // (World Space Window gets smaller). Negative magfactors
         // make things "smaller" (World Space Window get bigger).

      void zoomTo(double x, double y, double magfactor);
         // A combination of 'pan' and 'zoomBy', this function magnifies the
         // current projection and centers it on (x,y);

};

#endif // XMULTIVIEW2D_H

