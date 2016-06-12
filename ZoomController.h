
#include "mvc/Projection2D.h"
#include "mvc/Controller.h"

#ifndef ZOOMCONTROLLER_H
#define ZOOMCONTROLLER_H

class ZoomController : public Controller
{

   private:

   protected:
      double _zoomfactor;
      bool _reportpos;

      // State variables for zoom area drag.
      bool drawingtobuffer;  // Whether or not DisplayDevice was drawing to its buffer
                             // when we started the drag. We need to restore this
                             // when we're finished with the XOR drawing.
      bool _zoomareadrag;  // Whether we are dragging a zoom area or not.
      bool _zoomareadrag_firsttime;  // To capture first point.
      bool _zad_aborted;  // If we start and area drag, and then cancel it, 
                          // this is true.
      double _zad_tolerance;
      double _zad_linewidth;
      int _zad_linecolor_cookie;

      long zad_x1,zad_y1; // Corners of area.
      long zad_x2,zad_y2;
      long old_zadx, old_zady;

   public:

      ZoomController();

      virtual void install(void);

      virtual void setZoomFactor(double f);
      virtual double getZoomFactor(void);

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

      void keyPressed(char* stringrep, int x, int y);

      // Zoom Area Drag
#if 0
      void setZoomAreaDragTolerance(double t);
         // The tolerance is the minimum distance the mouse has to be dragged before
         // zoom area selection actually begins. If the mouse button is released
         // before this minimum distance is reached, then a (sloppy) point click
         // has occured.
         // Default = 10.0  (screen pixels)

      void setZoomAreaDragLineWidth(int l);
         // Width of line to be used to draw the Zoom Area rectangle.
         // Default = 2

      void setZoomAreaDrawLineColor(int c);
#endif
};

#endif // ZOOMCONTROLLER_H
