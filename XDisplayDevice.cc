
#include <stdio.h>
#include "mvc/XDisplayDevice.h"
#include "mvc/MVCUtils.h"
#include <X11/Xutil.h>
#include <X11/cursorfont.h>

Pixel XDisplayDevice::getPixel(unsigned char red, 
                               unsigned char green,
                               unsigned char blue)
{
   XColor thecolor;
   XColor defs[256];
   int num_colors;
   int mindist,dist;
   int reddist,greendist,bluedist;
   int i;
   Pixel bestcolor;
   bool found;


   thecolor.red = red * 257;
   thecolor.green = green * 257;
   thecolor.blue = blue * 257;
   thecolor.flags = DoRed | DoGreen | DoBlue;
   if (XAllocColor(mydisplay,mycolormap,&thecolor) == 0)
     {
        // Find the best match in the colormap.

        num_colors = DisplayCells(mydisplay,DefaultScreen(mydisplay));
        for (i = 0; i < num_colors; i++)
           defs[i].pixel = i;
        XQueryColors(mydisplay,mycolormap,defs,num_colors);

        mindist = 256 * 256 * 3;
        bestcolor = thecolor.pixel;
        i = 0; 
        found = false;
        while ((!found) && (i < num_colors))
           {
               reddist = ((int)(defs[i].red >> 8) -
                          (int)(thecolor.red >> 8));
               greendist = ((int)(defs[i].green >> 8) -
                            (int)(thecolor.green >> 8));
               bluedist = ((int)(defs[i].blue >> 8) -
                           (int)(thecolor.blue >> 8));
               dist = (reddist * reddist) +
                      (greendist * greendist) +
                      (bluedist * bluedist);
               if (dist < mindist)
                  {
                     mindist = dist;
                     bestcolor = defs[i].pixel;
                     if (dist == 0)
                        {
                           found = true;
                        }
                  }
               i = i + 1;
           }
      }
   else
      bestcolor = thecolor.pixel;

   return bestcolor;
}

unsigned long XDisplayDevice::getPixelFromCookie(int cookie)
{
   // Returns the Pixel value corresponding to color id 'cookie'.

   unsigned char r,g,b;

   if (allocated[cookie])
      return(pixval[cookie]);

   // Otherwise, we have to allocate the color specified by cookie and
   // store its pixel value.

   r = mycm-> getRed(cookie);
   g = mycm -> getGreen(cookie);
   b = mycm -> getBlue(cookie);
   pixval[cookie] = getPixel(r,g,b);
   allocated[cookie] = true;

   return(pixval[cookie]);
   
}

XDisplayDevice::XDisplayDevice(ColorManager* cm, Display* disp, Window win)
{
   int i;
   int blackpixel, whitepixel;

   mycm = cm;
   mydisplay = disp;
   mywindow = win;
   _mydrawable = mywindow;
   mycolormap = DefaultColormap(mydisplay,DefaultScreen(mydisplay));

   // I'd like to set _buffer to NULL, but I'm not certain that NULL
   // will never be used as a pixmap ID. An example in the Xlib Programming
   // Manual compares the result of XCreatePixmap to False. So we'll
   // use that instead.  -- jamie
   _buffer = False;
   _drawtobuffer = false;

   maxcolors = mycm -> getMaxColors();
   allocated = new bool[maxcolors];
   pixval = new unsigned long[maxcolors];

   for (i = 0; i < maxcolors; i++)
     {
        allocated[i] = false;
        pixval[i] = 0;
      }

   backgroundGC = XCreateGC(mydisplay,mywindow,0,(XGCValues*)NULL);
   foregroundGC = XCreateGC(mydisplay,mywindow,0,(XGCValues*)NULL);
   drawGC = XCreateGC(mydisplay,mywindow,0,(XGCValues*)NULL);

   blackpixel = getPixelFromCookie(mycm->getColorCookie("black"));
   whitepixel = getPixelFromCookie(mycm->getColorCookie("white"));
   XSetForeground(mydisplay,backgroundGC,blackpixel);
   XSetForeground(mydisplay,foregroundGC,whitepixel);
   XSetForeground(mydisplay,drawGC,whitepixel);

   // Cursors

   _zoomcursor = XCreateFontCursor(mydisplay,XC_crosshair);
   _selectcursor = XCreateFontCursor(mydisplay,XC_hand2);
   _busycursor = XCreateFontCursor(mydisplay,XC_watch);
   _precisecursor = XCreateFontCursor(mydisplay,XC_dotbox);

   XDefineCursor(mydisplay,mywindow,_zoomcursor);
   _cursor = DISPDEV_ZOOM;
}

void XDisplayDevice::setSize(int width, int height)
{
}

void XDisplayDevice::setWidth(int width)
{
   // Noop for now. Does it ever make sense for us to resize the window?
}

void XDisplayDevice::setHeight(int height)
{
   // Noop for now. Does it ever make sense for us to resize the window?
}

int  XDisplayDevice::getWidth(void)
{
   Window theroot;
   int x,y;
   unsigned int thewidth,theheight;
   unsigned int theborderwidth,thedepth;

   // We get the width each time (rather than storing it) because it
   // may have changed. We don't know. We aren't aware of resize events.

   XGetGeometry(mydisplay,mywindow,&theroot,&x,&y,&thewidth,&theheight,
                &theborderwidth,&thedepth);
   return(thewidth);
}

int  XDisplayDevice::getHeight(void)
{
   Window theroot;
   int x,y;
   unsigned int thewidth,theheight;
   unsigned int theborderwidth,thedepth;

   // We get the width each time (rather than storing it) because it
   // may have changed. We don't know. We aren't aware of resize events.

   XGetGeometry(mydisplay,mywindow,&theroot,&x,&y,&thewidth,&theheight,
                &theborderwidth,&thedepth);
   return(theheight);
}

// Drawing

void XDisplayDevice::clear(void)
{
   int w,h;

   w = getWidth();
   h = getHeight();

   XFillRectangle(mydisplay,_mydrawable,backgroundGC,0,0,w+1,h+1);
}

void XDisplayDevice::drawPoint(int x1, int y1)
{
   XDrawPoint(mydisplay,_mydrawable,foregroundGC,x1,y1);
}

void XDisplayDevice::drawLine(int x1, int y1, int x2, int y2)
{
   XDrawLine(mydisplay,_mydrawable,foregroundGC,x1,y1,x2,y2);
}

void XDisplayDevice::drawRect(int x1, int y1, int x2, int y2)
{
   canonicalRect(&x1,&y1,&x2,&y2);

   XDrawRectangle(mydisplay,_mydrawable,foregroundGC,
                  x1,y2,x2-x1,y1-y2);
}

void XDisplayDevice::drawFilledRect(int x1, int y1, int x2, int y2)
{
}

void XDisplayDevice::drawCircle(int center_x, int center_y, int radius)
{
}

void XDisplayDevice::drawFilledCircle(int center_x, int center_y, int radius)
{
}

void XDisplayDevice::drawRaster(unsigned char* theimage, 
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

void XDisplayDevice::setXORMode(bool flag)
{
   if (flag == true)
      {
         XSetFunction(mydisplay,foregroundGC,GXxor);
      }
   else
      {
         XSetFunction(mydisplay,foregroundGC,GXcopy);
      }
}

bool XDisplayDevice::setViewport(int x1, int y1, int x2, int y2)
{
   XRectangle rectlist[1];

   canonicalRect(&x1,&y1,&x2,&y2);

   rectlist[0].x = x1;
   rectlist[0].y = y2;
   rectlist[0].width = x2 - x1;
   rectlist[0].height = y1 - y2;

   XSetClipRectangles(mydisplay,foregroundGC,0,0,rectlist,1,Unsorted);
}

// Attributes

void XDisplayDevice::setForeground(char* colorname)
{
   int thecookie;
   unsigned long thepixel;

   thecookie = mycm -> getColorCookie(colorname);
   thepixel = getPixelFromCookie(thecookie);
   XSetForeground(mydisplay,foregroundGC,thepixel);
}

void XDisplayDevice::setForeground(int colorcookie)
{
   // Note: We should probably remember the last color that was set, so
   //    that if the current color is the same, we can avoid the 
   //    call to XSetForeground.

   unsigned long thepixel;

   thepixel = getPixelFromCookie(colorcookie);
   XSetForeground(mydisplay,foregroundGC,thepixel);
}

void XDisplayDevice::setBackground(char* colorname)
{
   int thecookie;
   unsigned long thepixel;

   thecookie = mycm -> getColorCookie(colorname);
   thepixel = getPixelFromCookie(thecookie);
   XSetForeground(mydisplay,backgroundGC,thepixel);
}

void XDisplayDevice::setBackground(int colorcookie)
{
   unsigned long thepixel;

   thepixel = getPixelFromCookie(colorcookie);
   XSetForeground(mydisplay,backgroundGC,thepixel);
}

void XDisplayDevice::setLineColor(char* colorname)
{
}

void XDisplayDevice::setLineColor(int colorcookie)
{
}

void XDisplayDevice::setFillColor(char* colorname)
{
}

void XDisplayDevice::setFillColor(int colorcookie)
{
}

void XDisplayDevice::setLineWidth(int width)
{
   if (width >= 0)
      {
         XGCValues newvals;

         newvals.line_width = width;
         XChangeGC(mydisplay,foregroundGC,GCLineWidth,&newvals);
      }
}

void XDisplayDevice::setCursor(DisplayDeviceCursorType ct)
{
   Cursor tmp;

   switch(ct)
      {
         case DISPDEV_BUSY:    tmp = _busycursor;     break;
         case DISPDEV_SELECT:  tmp = _selectcursor;   break;
         case DISPDEV_ZOOM:    tmp = _zoomcursor;     break;
         case DISPDEV_PRECISE: tmp = _precisecursor;  break;
         default: printf("Cursor not supported in XDisplayDevice.\n");
                  return;
      }
   _cursor = ct;

   XUndefineCursor(mydisplay,mywindow);
   XDefineCursor(mydisplay,mywindow,tmp);
   XFlush(mydisplay);
}

// Buffer

bool XDisplayDevice::supportsBuffer(void)
{
   // Returns true if the DisplayDevice supports a drawing buffer.

   return true;
}

bool XDisplayDevice::allocateBuffer(void)
{
   // This method causes the DisplayDevice to allocate space for
   // a buffer (if it supports one). 

   if (_buffer == False)
      {
         _buffer_width = getWidth();
         _buffer_height = getHeight();
         _buffer = XCreatePixmap(mydisplay,mywindow,
                                 _buffer_width,_buffer_height,
                                 DefaultDepth(mydisplay,
                                              DefaultScreen(mydisplay)));
         return true;
      }
   else
      return false;
   
}

bool XDisplayDevice::bufferExists(void)
{
   // Returns true if a drawing buffer exists. Used to determine if
   // the DisplayDevice is currently buffering graphics.

   if (_buffer == False)
      return false;

   return true;
}

bool XDisplayDevice::deallocateBuffer(void)
{
   // Deallocates the drawing buffer (if one has been allocated).
   // Drawing to buffer is disabled.

   if (_buffer == False)
      return false;
   else
      {
         XFreePixmap(mydisplay,_buffer);
         _buffer = False;
      }

   return true;
}

bool XDisplayDevice::resizeBuffer(void)
{
   // Causes current drawing buffer to be deallocated, and a new
   // one allocated. Since a DisplayDevice cannot know when its
   // size has changed, this method must be called by the client.
   // If a buffer does not already exist, one is created.

   deallocateBuffer();
   allocateBuffer();
   if (_drawtobuffer)
      _mydrawable = _buffer;
}

bool XDisplayDevice::drawToBuffer(bool flag)
{
   // Enables / disables drawing to buffer. Returns true if 
   // operation was succesful. Drawing commands draw to either the
   // the actual output device or the buffer, but not to both at the
   // the same time.
 
   _drawtobuffer = flag;

   if (_drawtobuffer)
      {
         if (_buffer == False) // No buffer exists. Create one.
            allocateBuffer();
         _mydrawable = _buffer;
      }
   else
      _mydrawable = mywindow;

   return true;
}

bool XDisplayDevice::isDrawingToBuffer(void)
{
   return _drawtobuffer;
}

bool XDisplayDevice::refreshFromBuffer(void)
{
   // Causes contents of buffer to be displayed on whatever device
   // display device is using for output. Does not alter contents
   // of buffer.

   if (_buffer != False)
      {
         XCopyArea(mydisplay,_buffer,mywindow,foregroundGC,
                   0,0,_buffer_width,_buffer_height,0,0);
         return true;
      }
   else
      return false;
}











