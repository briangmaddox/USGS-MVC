#ifndef VIEW2D_H
#define VIEW2D_H

#include "mvc/Projection2D.h"
#include "mvc/DisplayDevice.h"

#ifndef MODEL2D_H
class Model2D;
#endif

#ifndef INPUTDEVICE_H
class InputDevice;
#endif

#ifndef CONTROLLER_H
class Controller;
#endif

class View2D
{
   private:

   protected:
      Model2D* mymodel;
      Projection2D* myproj;
      DisplayDevice* mydd;
      InputDevice* myinput;
      Controller* mycontroller;
      bool _smartrefresh;
      DisplayDeviceCursorType _mycursor;

      // The public reDraw method is implemented with the following methods.
      // Subclasses can override these to change the way reDraw works.
      virtual void preDraw(void);
      virtual void Draw(void);
      virtual void postDraw(void);

   public:

      View2D(void);
      ~View2D(void);

      virtual void reDraw(void);
         // Causes View to redraw itself; Usually called when the model
         // changes.

      virtual void reSize(int w, int h);
         // Message sent by the Controller class whenever the size of
         // this View's DisplayDevice changes. w,h are the new size.

      virtual void reFresh(void);
         // "Smart" redraw. If possible, the view attempts to optimize
         // the redraw because this method is only called when the 
         // DisplayDevice has changed. 

      virtual void setSmartRefresh(bool flag);
         // Setting this to true causes the view to attempt smart refreshes.
         // This means that if the DisplayDevice supports a graphics buffer,
         // draw components with negative layer numbers to this buffer.
         // The idea is to put graphics that are expensive to draw
         // (and that don't change very often) in negative layers. 
         // For example, an application might choose to put a RasterComponent
         // in layer -1, and editable LineComponents in layer 3. Since
         // the raster component is slow to redraw and will not be edited
         // it can go in the graphics buffer. The line components redraw
         // very quickley and will be changing, so they go in a positive
         // layer.
         // Default is false: draw everything directly to DisplayDevice.

      virtual void setModel(Model2D* m);
      virtual void setProjection(Projection2D* p);
      virtual void setDisplayDevice(DisplayDevice* dd);
      virtual void setInputDevice(InputDevice* theid);
      virtual void setController(Controller* thecontroller);

      virtual Model2D* getModel(void);
      virtual Projection2D* getProjection(void);
      virtual DisplayDevice* getDisplayDevice(void);
      virtual InputDevice* getInputDevice(void);
      virtual Controller* getController(void);


      virtual double getWorldSpaceX(int x, int y);
      virtual double getWorldSpaceY(int x, int y);
         // These two functions return either the World Space X or
         // World Space Y coordinate given a point in Device Space.

      virtual void pan(double newcenter_x, double newcenter_y);
         // Moves the center of the World Space Window to
         // (newcenter_x, newcenter_y) without changing its size.

      virtual void zoomBy(double magfactor);
         // Zooms current View by magfactor. Center of WSW
         // does not move. Positive magfactors make things "bigger" 
         // (World Space Window gets smaller). Negative magfactors
         // make things "smaller" (World Space Window get bigger).

      virtual void zoomTo(double x, double y, double magfactor);
         // A combination of 'pan' and 'zoomBy', this function magnifies the
         // current projection and centers it on (x,y);

      virtual void zoomFullView(void);

};

#include "mvc/Model2D.h"
#include "mvc/InputDevice.h"
#include "mvc/Controller.h"

#endif // VIEW2D_H


