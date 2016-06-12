#include <math.h>
#include "mvc/ZoomController.h"
#include "mvc/Global.h"

#define DIST(a,b,c,d) (sqrt((((a)-(c))*((a)-(c))) + (((b)-(d))*((b)-(d)))))

ZoomController::ZoomController()
{
   _zoomfactor = 2.0;
   _reportpos = false;
   _zoomareadrag = false;
   _zoomareadrag_firsttime = true;
   _zad_tolerance = 10.0;
   _zad_aborted = false;
}

void ZoomController::install(void)
{
   (myview->getDisplayDevice())->setCursor(DISPDEV_ZOOM);
}

void ZoomController::setZoomFactor(double f)
{
   _zoomfactor = f;
}

double ZoomController::getZoomFactor(void)
{
   return _zoomfactor;
}

void ZoomController::button1Release(int x, int y)
{
   double wx, wy;
   double wx1, wy1, wx2, wy2;
   Projection2D* tmpproj;
   DisplayDevice* dd;

   tmpproj = myview->getProjection();

   if (_zoomareadrag)
      {
         _zoomareadrag = false;
         zad_x2 = x;
         zad_y2 = y;
         dd = myview -> getDisplayDevice();
         dd->drawRect(zad_x1,zad_y1,old_zadx,old_zady);
         dd->setXORMode(false);
         dd -> drawToBuffer(drawingtobuffer);

         wx1 = tmpproj->getWorldSpaceX(zad_x1,zad_y1);
         wy1 = tmpproj->getWorldSpaceY(zad_x1,zad_y1);
         wx2 = tmpproj->getWorldSpaceX(zad_x2,zad_y2);
         wy2 = tmpproj->getWorldSpaceY(zad_x2,zad_y2);

         tmpproj->setWorldSpaceWin(wx1,wy1,wx2,wy2);
         myview->reDraw();
      }
   else 
      if (!_zad_aborted)  // (Potentially sloppy) point click.
      {
         wx = tmpproj->getWorldSpaceX(x,y);
         wy = tmpproj->getWorldSpaceY(x,y);
         tmpproj->zoomTo(wx,wy,_zoomfactor);
         myview->reDraw();
      }

   _zoomareadrag_firsttime = true;
   _zad_aborted = false;

}

void ZoomController::button2Release(int x, int y)
{
   Projection2D* tmpproj;

   tmpproj = myview->getProjection();
   tmpproj->zoomBy(-1.0 * _zoomfactor);
   myview->reDraw();
}

void ZoomController::button3Release(int x, int y)
{
   double wx,wy;
   Projection2D* tmpproj;

  // (myview->getProjection())->zoomFullView();

   tmpproj = myview -> getProjection();
   wx = tmpproj->getWorldSpaceX(x,y);
   wy = tmpproj->getWorldSpaceY(x,y);
   tmpproj->pan(wx,wy);
   myview->reDraw();
}

void ZoomController::pointerMotion(int x, int y)
{
   // Called when pointer moves. Pointer is now at
   // Device coordinates (x,y).

   double wx,wy;
   Projection2D* tmpproj;

   if (_reportpos)
      {
         tmpproj = myview->getProjection();
         wx = tmpproj->getWorldSpaceX(x,y);
         wy = tmpproj->getWorldSpaceY(x,y);
         printf("World Coordinates: (%lf,%lf)\n",wx,wy);
      }

}

void ZoomController::button1Motion(int x, int y)
{
   // Called when pointer moves and Button1 is depressed.
   DisplayDevice* dd;

   dd = myview -> getDisplayDevice();

   // If we're in here, we *might* be doing an area drag. It could just be a 
   // sloppy point click. Don't actually start the _zoomareadrag until the 
   // pointer moves at least '_zad_tolerance' pixels away from the start point.

   if (_zoomareadrag_firsttime)
      {
         _zoomareadrag_firsttime = false;
         zad_x1 = x;
         zad_y1 = y;
      }
   else
      {
         if (_zoomareadrag == false)
            {
               if (DIST(zad_x1,zad_y1,x,y) >= _zad_tolerance)
                  {
                     _zoomareadrag = true;
                     _zad_aborted = false;
                     drawingtobuffer = dd -> isDrawingToBuffer();
                     dd -> drawToBuffer(false);
                     dd -> setForeground("red");
                     dd -> setLineWidth(2);
                     dd -> setXORMode(true);
                     dd -> drawRect(zad_x1,zad_y1,x,y);
                     old_zadx = x;
                     old_zady = y;
                  }
            }
         else
            {         
               if (DIST(zad_x1,zad_y1,x,y) < _zad_tolerance)
                  {
                     // We're back to within '_zad_tolerance' distance of 
                     // where we started. Discontinue the zoom area drag until
                     // and unless the User drags the rectangle wider.
                     _zoomareadrag = false;
                     _zad_aborted = true;
                     dd->drawToBuffer(drawingtobuffer);
                     dd->drawRect(zad_x1,zad_y1,old_zadx,old_zady);
                     dd->setXORMode(false);
                  }
               else
                  {
                     dd -> drawRect(zad_x1,zad_y1,old_zadx,old_zady);
                     dd -> drawRect(zad_x1,zad_y1,x,y);
                     old_zadx = x;
                     old_zady = y;
                  }
            }
      }
}

void ZoomController::button2Motion(int x, int y)
{
   // Called when pointer moves and Button2 is depressed.
}

void ZoomController::button3Motion(int x, int y)
{
   // Called when pointer moves and Button3 is depressed.
}

void ZoomController::pointerEnter(int x, int y)
{
   // Called when pointer enters input area. (x,y) location
   // pointer entered.
}

void ZoomController::pointerLeave(int x, int y)
{
   // Called when pointer leaves input area. (x,y) location
   // pointer left.
}

void ZoomController::keyPressed(char* stringrep, int x, int y)
{
   char thechar;
   double wx, wy;
   Projection2D* tmpproj;
   int i; 
   unsigned char tmpc;
   double tmpzf;

   if (strlen(stringrep) > 1)
      return;

   thechar = stringrep[0];

   tmpproj = myview->getProjection();
   wx = tmpproj->getWorldSpaceX(x,y);
   wy = tmpproj->getWorldSpaceY(x,y);   

   switch(thechar)
      {
         case('d'): GlobalDebug.messagesOn(); break;
         case('D'): GlobalDebug.messagesOff(); break;
         case('q'): exit(0); break;
         case('p'): _reportpos = !_reportpos; break;
         case('h'): 
            // print list of key commands
            printf("\n\n");
            printf("q - Quit\n"); 
            printf("f - view entire image\n");
            printf("p - Toggle position reporting\n");
            printf("1 through 9 - Change zoom factor\n");
            printf("\n");
            break;
         case('f'):
            tmpproj->zoomFullView();
            myview->reDraw();
            break;
         case('1'):
         case('2'):
         case('3'):
         case('4'):
         case('5'):
         case('6'):
         case('7'):
         case('8'):
         case('9'):
            sscanf(stringrep,"%lf",&tmpzf);
            setZoomFactor(tmpzf);
            break;
      } // end switch;
}

#if 0
void ZoomController::setZoomAreaDragTolerance(double t)
{
   _zad_tolerance = t;
}

void ZoomController::setZoomAreaDragLineWidth(int l)
{
   _zad_linewidth = l;
}

void ZoomController::setZoomAreaDrawLineColor(int c)
{
   _zad_linecolor_cookie = c;
}
#endif

