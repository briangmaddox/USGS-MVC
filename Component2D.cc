#include <stdio.h>
#include <math.h>
#include "Image/RGBPixel.h"
#include "Image/Image.h"
#include "mvc/Component2D.h"
#include "mvc/RectProj2D.h"
#include "mvc/Global.h"
#include "mvc/MVCUtils.h"

//
// Component2D class.
//

Component2D::Component2D(void)
{
   _layer = 0;
   _selectable = true;
   _drawselected = false;
   _visible = true;
   _linewidth = 0;
}

//
// Attributes
//
void Component2D::setLayer(long layernum)
{
   _layer = layernum;
}

long Component2D::getLayer(void)
{
   return _layer;
}

void Component2D::setSelectable(bool flag)
{
   _selectable = flag;
}

bool Component2D::isSelectable(void)
{
   return _selectable;
}

void Component2D::setDrawSelected(bool flag)
{
   _drawselected = flag;
}

void Component2D::setVisible(bool flag)
{
  _visible = flag;
}

bool Component2D::isVisible(void)
{
   return _visible;
}

void Component2D::setLineWidth(int width)
{
   _linewidth = width;
}

void Component2D::setLineColor(int colorcookie)
{
}

//
// Bounding Box
//
void Component2D::getBoundingBox(double& x1, double& y1,
                                 double& x2, double& y2)
{
   // Returns world coordinates for opposite corners of a 
   // minimum bounding box for the component.

   x1 = bb_x1;
   y1 = bb_y1;
   x2 = bb_x2;
   y2 = bb_y2;
}

void Component2D::computeBoundingBox(void)
{
   // Causes component to recompute its bounding box. Normally,
   // the component uses this method automatically whenever 
   // something changes that would affect the MBR. Subclasses
   // with methods that are not defined in the Component2D class
   // and that could affect the MBR should call this method.

   bb_x1 = 0.0;
   bb_y1 = 0.0;
   bb_x2 = 0.0;
   bb_y2 = 0.0;
}

bool Component2D::intersectsBox(double x1, double y1, double x2, double y2)
{
   // (x1,y1) (x2,y2) are opposite corners of a box. This method
   // returns 'true' if this component's bounding box is partially
   // or completely contained in the given box.

   canonicalRect(&x1,&y1,&x2,&y2);

   if ((bb_x1 >= x2) || (bb_x2 <= x1) || (bb_y1 <= y2) || (bb_y2 >= y1))
      return false;
   else
      return true;
        
}

//
// Misc.
//
double Component2D::getDistance(double x, double y)
{
   return 0.0;
}

void Component2D::draw(Projection2D* proj, DisplayDevice* dd)
{
         // Draw Component on Display Device dd using projection proj.
}

//
// Transformations
//
void Component2D::rotate(double x, double y, double theta)
{
         // Rotate Component by theta radians around point (x,y).
}

void Component2D::translate(double delta_x, double delta_y)
{
         // Translate Component.
}

void Component2D::moveTo(double x, double y)
{
   // Move component to (x,y).
}

void Component2D::scale(double sx, double sy)
{
	// Scale Component by sx in x and sy in y.
}


//
// PointComponent2D class.
//

PointComponent2D::PointComponent2D(double x, double y, int colorid)
{
   myx = x;
   myy = y;
   mycolorid = colorid;
}

void PointComponent2D::computeBoundingBox(void)
{
   bb_x1 = myx;
   bb_y1 = myy;
   bb_x2 = myx;
   bb_y2 = myy;
}

double PointComponent2D::getDistance(double x, double y)
{
   double result,dx,dy;

   dx = myx - x;
   dy = myy - y;

   result = sqrt(dx*dx + dy*dy);
}

void PointComponent2D::draw(Projection2D* proj, DisplayDevice* dd)
{
   int ix, iy;

   ix = proj->getDisplayDeviceX(myx,myy);
   iy = proj->getDisplayDeviceY(myx,myy);

   dd->setForeground(mycolorid);
   dd->drawPoint(ix,iy);
}

void PointComponent2D::moveTo(double x, double y)
{
   myx = x;
   myy = y;
}

double PointComponent2D::getX(void)
{
   return myx;
}

double PointComponent2D::getY(void)
{
   return myy;
}

//
// SymbolComponent2D class.
//
SymbolComponent2D::SymbolComponent2D(double x, double y, int colorid)
                 : PointComponent2D(x,y,colorid)
{
   mysize = 8;
}

void SymbolComponent2D::setSize(int s)
{
   if (mysize > 0)
      mysize = s;
}

int SymbolComponent2D::getSize(void)
{
   return(mysize);
}

//
// PlusSymbolComponent2D class.
//
PlusSymbolComponent2D::PlusSymbolComponent2D(double x, double y, int colorid)
                      : SymbolComponent2D(x,y,colorid)
{
}

void PlusSymbolComponent2D::draw(Projection2D* proj, DisplayDevice* dd)
{
   // The world coordinates are for the center of the "plus".

   int ix,iy;

   if (_drawselected)
      dd->setXORMode(true);

   ix = proj->getDisplayDeviceX(myx, myy);
   iy = proj->getDisplayDeviceY(myx, myy);

   dd->setForeground(mycolorid);
   dd->setLineWidth(_linewidth);
   dd->drawLine(ix, iy - mysize, ix, iy + mysize);
   dd->drawLine(ix - mysize, iy, ix + mysize, iy);

   if (_drawselected)  // Draw a rectangle around it.
      {
         dd->drawLine(ix-mysize,iy+mysize,ix+mysize,iy+mysize);
         dd->drawLine(ix+mysize,iy+mysize,ix+mysize,iy-mysize);
         dd->drawLine(ix+mysize,iy-mysize,ix-mysize,iy-mysize);
         dd->drawLine(ix-mysize,iy-mysize,ix-mysize,iy+mysize);
      }

   if (_drawselected)
      dd->setXORMode(false);
}

//
// LineComponent2D class.
//

LineComponent2D::LineComponent2D(double x1, double y1, double x2, double y2,
                                 int colorid)
{
   lx1 = x1;
   ly1 = y1;
   lx2 = x2;
   ly2 = y2;

   mycolorid = colorid;

   computeBoundingBox();
}

void LineComponent2D::draw(Projection2D* proj, DisplayDevice* dd)
{
   // Draw Component on Display Device dd using projection proj.

   double tmpx1,tmpy1;
   double tmpx2,tmpy2;

   int tx1,ty1;
   int tx2,ty2;

   tmpx1 = lx1; tmpy1 = ly1;
   tmpx2 = lx2; tmpy2 = ly2;

   if (proj->clipLine(&tmpx1,&tmpy1,&tmpx2,&tmpy2))
      {
         tx1 = proj->getDisplayDeviceX(tmpx1,tmpy1);
         ty1 = proj->getDisplayDeviceY(tmpx1,tmpy1);

         tx2 = proj->getDisplayDeviceX(tmpx2,tmpy2);
         ty2 = proj->getDisplayDeviceY(tmpx2,tmpy2);

         dd->setForeground(mycolorid);
         dd->setLineWidth(_linewidth);
         dd->drawLine(tx1,ty1,tx2,ty2);
      }
}

void LineComponent2D::rotate(double x, double y, double theta)
{
   // Rotate Component by theta radians around point (x,y).
}

void LineComponent2D::translate(double delta_x, double delta_y)
{
   // Translate Component.
}

void LineComponent2D::scale(double sx, double sy)
{
   // Scale Component by sx in x and sy in y.
}

void LineComponent2D::computeBoundingBox(void)
{
   bb_x1 = lx1;
   bb_y1 = ly1;
   bb_x2 = lx2;
   bb_y2 = ly2;

   canonicalRect(&bb_x1,&bb_y1,&bb_x2,&bb_y2);
}

//
// PolyLineComponent2D
//

PolyLineComponent2D::PolyLineComponent2D(void)
{
   _x = NULL;
   _y = NULL;
   _numpoints = 0;
}

PolyLineComponent2D::PolyLineComponent2D(double x[], double y[], 
                                         int numpoints, int colorid)
{
   _x = NULL;
   _y = NULL;
   _numpoints = 0;
   setPoints(x,y,numpoints);
   mycolorid = colorid;
}

PolyLineComponent2D::~PolyLineComponent2D(void)
{
   if (_x != NULL)
      delete [] _x;

   if (_y != NULL)
      delete [] _y;
}

void PolyLineComponent2D::draw(Projection2D* proj, DisplayDevice* dd)
{
   int i;
   double tmpx1,tmpy1,tmpx2,tmpy2;
   int tx1,ty1,tx2,ty2;

   if (_numpoints < 2)
      return;

   // Clip each line segment in the polyline against the projection. 

   dd->setForeground(mycolorid);
   dd->setLineWidth(_linewidth);

   for (i = 0; i < _numpoints - 1; i++)
      {
         tmpx1 = _x[i];   tmpy1 = _y[i];
         tmpx2 = _x[i+1]; tmpy2 = _y[i+1];

         if (proj->clipLine(&tmpx1,&tmpy1,&tmpx2,&tmpy2))
            {
               // At least part of the line is visible, so...
               tx1 = proj->getDisplayDeviceX(tmpx1,tmpy1);
               ty1 = proj->getDisplayDeviceY(tmpx1,tmpy1);

               tx2 = proj->getDisplayDeviceX(tmpx2,tmpy2);
               ty2 = proj->getDisplayDeviceY(tmpx2,tmpy2);

               dd->drawLine(tx1,ty1,tx2,ty2);
            }
      }
   
}

void PolyLineComponent2D::setPoints(double x[], double y[], int numpoints)
{
   int i;

   if (_x != NULL)
      delete [] _x;

   if (_y != NULL)
      delete [] _y;

   _x = new double[numpoints];
   _y = new double[numpoints];
   _numpoints = numpoints;

   for (i = 0; i < numpoints; i++)
      {
         _x[i] = x[i];
         _y[i] = y[i];
      }

   computeBoundingBox();
}

void PolyLineComponent2D::computeBoundingBox(void)
{
   int i;

   if (_numpoints == 0)
      return;

   bb_x1 = _x[0]; 
   bb_y1 = _y[0];
   bb_x2 = _x[0];
   bb_y2 = _y[0];
   for (i = 1; i < _numpoints; i++)
      {
         if (_x[i] < bb_x1) bb_x1 = _x[i];
         if (_x[i] > bb_x2) bb_x2 = _x[i];
         if (_y[i] > bb_y1) bb_y1 = _y[i];
         if (_y[i] < bb_y2) bb_y2 = _y[i];
      }

   canonicalRect(&bb_x1,&bb_y1,&bb_x2,&bb_y2);
}

//
// RasterComponent2D
//
RasterComponent2D::RasterComponent2D(Image* theimage, 
                   double xres, double yres,
                   double wx, double wy, int wx_offset, int wy_offset)
                  : Raster(theimage,xres,yres,wx,wy,wx_offset,wy_offset)
{
}

void RasterComponent2D::draw(Projection2D* viewproj, DisplayDevice* dd)
{
   // Draw Component on Display Device dd using projection proj.
   // This will only work if we're using a Rectangular projection.

   double cx1, cy1; 
   double cx2, cy2;
   double wsw_x1, wsw_y1;
   double wsw_x2, wsw_y2;
   int dcx1, dcy1;
   int dcx2, dcy2;
   int outwidth, outheight;
   double xstep, ystep;
   unsigned char* outimage;
   double curx, cury;
   AbstractPixel* tmppix;
   RawRGBPixel rawpix;
   int ix,iy;
   int i,j;


   GlobalDebug.message("In RasterComponent2D draw method");

   //
   // Step 1. Clip image to World Space Window of view.      
   // 

   GlobalDebug.message("Before step 1.");

   // Set (cx1,cy1)(cx2,cy2) to be bounds of image in world space.
   myproj->getWorldSpaceWin(&cx1,&cy1,&cx2,&cy2);

   GlobalDebug.message("After call to myproj->getWorld...");

   // Set (wsw_x1,wsw_y1)(wsw_x2,wsw_y2) to be bounds of view's 
   // world space window.
   viewproj->getWorldSpaceWin(&wsw_x1,&wsw_y1,&wsw_x2,&wsw_y2);
  

   if ((cx1 >= wsw_x2) || (cx2 <= wsw_x1) ||
       (cy1 <= wsw_y2) || (cy2 >= wsw_y1))
      {
         // This RasterComponent is not visible in this view.
         return;
      }
   
   if (cx1 < wsw_x1) cx1 = wsw_x1;
   if (cx2 > wsw_x2) cx2 = wsw_x2;
   if (cy1 > wsw_y1) cy1 = wsw_y1;
   if (cy2 < wsw_y2) cy2 = wsw_y2;

   GlobalDebug.message("After step 1.");

   //
   // Step 2. Project visible region of image onto view.
   //

   GlobalDebug.message("Before step 2.");

   dcx1 = viewproj->getDisplayDeviceX(cx1,cy1);
   dcy1 = viewproj->getDisplayDeviceY(cx1,cy1);
   dcx2 = viewproj->getDisplayDeviceX(cx2,cy2);
   dcy2 = viewproj->getDisplayDeviceY(cx2,cy2);

   outwidth = dcx2 - dcx1 + 1;
   outheight = dcy2 - dcy1 + 1;

   GlobalDebug.message("After step 2.");

   //
   // Step 3. Sample visible region giving output image.
   // 

   GlobalDebug.message("Before step 3.");

   xstep = (cx2 - cx1) / outwidth;
   ystep = (cy1 - cy2) / outheight;

   outimage = (unsigned char*) new long[outwidth*outheight];  // raw RGB

   for (j = 0; j < outheight; j++)
      {
         cury = cy1 - (ystep * j);
         iy = myproj->getDisplayDeviceY(cx1,cury);
         for (i = 0; i < outwidth; i++)
            {
               curx = cx1 + (xstep * i);
               ix = myproj->getDisplayDeviceX(curx,cury);
               myimage->getRawRGBPixel(ix,iy,&rawpix);
               outimage[(j*outwidth*4)+(i*4)] = (unsigned char) 0;
               outimage[(j*outwidth*4)+(i*4)+1] = rawpix.Blue;
               outimage[(j*outwidth*4)+(i*4)+2] = rawpix.Green;
               outimage[(j*outwidth*4)+(i*4)+3] = rawpix.Red;
#if 0
               tmppix = myimage->getPixel(ix,iy);
               outimage[(j*outwidth*4)+(i*4)+3]=
                  (unsigned char) tmppix->getRed();
               outimage[(j*outwidth*4)+(i*4)+2] = 
                  (unsigned char) tmppix->getGreen();
               outimage[(j*outwidth*4)+(i*4)+1] =
                  (unsigned char) tmppix->getBlue();
               outimage[(j*outwidth*4)+(i*4)] = (unsigned char) 0;
               delete[] tmppix;
#endif
            }
      }

   GlobalDebug.message("After step 3.");

   GlobalDebug.message("Before call to drawRaster");
   dd->drawRaster(outimage,outwidth,outheight,dcx1,dcy1);
   GlobalDebug.message("After call to drawRaster");

   delete[] outimage;

}
