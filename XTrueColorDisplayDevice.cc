#include <stdio.h>
#include "mvc/XTrueColorDisplayDevice.h"
#include <X11/Xutil.h>
#include <X11/cursorfont.h>


XTrueColorDisplayDevice::XTrueColorDisplayDevice(ColorManager* cm, 
                                                 Display* disp, Window win)
                       :XDisplayDevice(cm,disp,win)
{
}

void XTrueColorDisplayDevice::drawRaster(unsigned char* theimage, 
                                         int width, int height, int x, int y)
{
   // image is a row major order, raw RGB (3 bytes / pixel) raster.
   // width and height are in pixels.

   XImage* newimage;

   newimage = XCreateImage(mydisplay,
                 DefaultVisual(mydisplay,DefaultScreen(mydisplay)),
                 24,ZPixmap,0,(char*)theimage,width,height,32,0);

   XPutImage(mydisplay,_mydrawable,
             DefaultGC(mydisplay,DefaultScreen(mydisplay)), 
             newimage,0,0,x,y,width,height);

   // Destroy the XImage struc, but not the client image data.
   newimage->data = (char*)NULL;
   XDestroyImage(newimage);

}


