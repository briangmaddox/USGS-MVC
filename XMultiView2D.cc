
#include "mvc/XMultiView2D.h"
#include "mvc/RectProj2D.h"

void XMultiView2D::initstuff(void)
{
   _viewportprojs = NULL;
   _numviewports = 0;
   _px = NULL;
   _py = NULL;

   setSmartRefresh(true);

   // mydd -> drawToBuffer(true);  // Always need this.

   // We don't need the default projection.
   //delete myproj;
}   

XMultiView2D::XMultiView2D(ColorManager* cm, Widget wid, Window win)
             : XView2D(cm,wid,win)
{
   initstuff();
}

XMultiView2D::XMultiView2D(Widget wid, Window win)
             :XView2D(wid,win)
{
   initstuff();
}

XMultiView2D::XMultiView2D(void)
{
   initstuff();
}

XMultiView2D::~XMultiView2D(void)
{
   if (_viewportprojs != NULL)
      delete[] _viewportprojs;
}

void XMultiView2D::Draw(void)
{
   int i;
   int x1,y1,x2,y2;

   if (mydd == NULL) return;  // May not be attached yet.
 
   for (i = 0; i < _numviewports; i++)
      {
         myproj = &(_viewportprojs[i]);
         myproj -> getDisplayDevWin(&x1,&y1,&x2,&y2);
         mydd -> setViewport(x1,y1,x2,y2);
         View2D::Draw();
      }

   reFresh();
}

void XMultiView2D::reSize(int w, int h)
{
   if (mydd == NULL) return;  // May not be attached yet.

   mydd->deallocateBuffer();
   calcProjs();
}

void XMultiView2D::reFresh(void)
{

   // Most of this procedure is copied from View2D::reFresh, with
   // changes to accomodate multiple projections.

   Component2D** clist;
   DisplayDeviceCursorType tmpcursor;
   int numc; 
   int i,j;
   int x1,y1,x2,y2;

   if (mydd == NULL) return; // May not be attached yet.

   if (_smartrefresh && (mydd->supportsBuffer()) &&
       (mydd->bufferExists()))
      {
         mydd -> setViewport(0,0,mydd->getWidth()-1,mydd->getHeight()-1);
         tmpcursor = mydd->getCursor();
         mydd->setCursor(DISPDEV_BUSY);
         mydd->refreshFromBuffer();

         mymodel->getRefreshList(myproj,clist,numc);
         // Draw all positive layer objects.
         for (j = 0; j < _numviewports; j++)
            {
               myproj = &(_viewportprojs[j]);
               myproj -> getDisplayDevWin(&x1,&y1,&x2,&y2);
               mydd -> setViewport(x1,y1,x2,y2);
               for (i = 0; i < numc; i++)
                  {
                     if (clist[i]->getLayer() >= 0)
                        clist[i]->draw(myproj,mydd);
                  }
            }

         mydd -> setViewport(0,0,mydd->getWidth()-1,mydd->getHeight()-1);

         delete[] clist;
         //mydd->setSelectCursor();
         mydd->setCursor(tmpcursor);
      }
   else
      reDraw();
}


bool XMultiView2D::calcProjs(void)

{
   int wholelines;
   int lastline;
   int num_down;
   int width,height;
   int i,j;
   int curpoint;
   double delta_x, delta_y;
   double cur_x1, cur_y1;
   double cur_x2, cur_y2;
   RectProj2D* p;

   if (mydd == NULL) return true; // May not be attached yet.

   if (_numviewports == 0) return true;
   
   wholelines = (int) _numviewports / _num_across;
   lastline = _numviewports % _num_across;

   if (lastline > 0)
      num_down = wholelines + 1;
   else
      num_down = wholelines;

   width = mydd -> getWidth();
   height = mydd -> getHeight();
   delta_x = width / _num_across;
   delta_y = height / num_down;

   for (i = 0; i < wholelines; i++)
      {
         cur_y1 = i * delta_y;
         for (j = 0; j < _num_across; j++)
            {
               curpoint = (i * _num_across) + j;
               cur_x1 = j * delta_x;
               cur_x2 = cur_x1 + delta_x;
               cur_y2 = cur_y1 + delta_y;

               p = &(_viewportprojs[curpoint]);
               p -> setMaintainAspectRatio(true);
               p -> setDisplayDevWin((int)cur_x1+2,(int)cur_y1+2,
                                     (int)cur_x2-2,(int)cur_y2-2);
               p -> setWorldSpaceWin(0.0,0.0,2.0 * _radius,2.0 * _radius);
               p -> pan(_px[curpoint],_py[curpoint]);
            }
      }

   if (lastline > 0)
      {
         cur_y1 = wholelines * delta_y;
         cur_y2 = height - 1;
         delta_x = width / lastline;
         for (i = 0; i < lastline; i++)
            {
               cur_x1 = i * delta_x;
               cur_x2 = cur_x1 + delta_x;
               curpoint = (_num_across * wholelines) + i;
               p = &(_viewportprojs[curpoint]);
               p -> setMaintainAspectRatio(true);
               p -> setDisplayDevWin((int)cur_x1,(int)cur_y1,(int)cur_x2,(int)cur_y2);
               p -> setWorldSpaceWin(0.0,0.0,2.0 * _radius,2.0 * _radius);
               p -> pan(_px[curpoint],_py[curpoint]);
            }
      }
}


bool XMultiView2D::setPoints(double x[], double y[], int numpoints,
                             int num_across, double radius)
{
   // x[],y[] are coordinates for a list of points. The DisplayDevice
   // will be split into numpoints view ports; each centered on a point.
   // XMultiView2D will attempt to place num_across viewports across
   // the display device. If num_across does not divide numpoints evenly,
   // the remaining points will be equally spaced on the last row of
   // viewports. 'radius' is in WorldSpace coordinates and specifies a
   // minimum area around a point to be displayed. More area may be shown,
   // but it is guaranteed that the minimum area will be visible.

   int i;

   if (_px != NULL) delete [] _px;
   if (_py != NULL) delete [] _py;

   _px = new double[numpoints];
   _py = new double[numpoints];

   for (i = 0; i < numpoints; i++)
      {
         _px[i] = x[i];
         _py[i] = y[i];
      }

   if (_viewportprojs != NULL)
      delete[] _viewportprojs;

   _viewportprojs = new RectProj2D[numpoints];
   _numviewports = numpoints;
   _num_across = num_across;
   _radius = radius;

   return calcProjs();

}

double XMultiView2D::getWorldSpaceX(int x, int y)
{
   bool found;
   int i;

   found = false; 
   i = 0;
 
   while ((!found) && (i < _numviewports))
      {
         if (_viewportprojs[i].inDisplayDeviceWindow(x,y))
            found = true;
         else
            i = i + 1;
      }

   if (found)
      return _viewportprojs[i].getWorldSpaceX(x,y);
   else
      return 0.0;
}

double XMultiView2D::getWorldSpaceY(int x, int y)
{
   bool found;
   int i;

   found = false; 
   i = 0;
 
   while ((!found) && (i < _numviewports))
      {
         if (_viewportprojs[i].inDisplayDeviceWindow(x,y))
            found = true;
         else
            i = i + 1;
      }

   if (found)
      return _viewportprojs[i].getWorldSpaceY(x,y);
   else
      return 0.0;

}

void XMultiView2D::pan(double newcenter_x, double newcenter_y)
{
   // NOOP for now. We'll decide what this means for multiple 
   // viewports later. -- jamie 6/21/95
}

void XMultiView2D::zoomBy(double magfactor)
{
   int i;

   if (_numviewports > 0)
      {
         for (i = 0; i < _numviewports; i++)
            {
               _viewportprojs[i].zoomBy(magfactor);
            }
      }

   reDraw();

}

void XMultiView2D::zoomTo(double x, double y, double magfactor)
{
}


