#ifndef XDISPLAYDEVICE_H
#define XDISPLAYDEVICE_H

#include <X11/X.h>
#include <X11/Intrinsic.h>
#include "mvc/ColorManager.h"
#include "mvc/DisplayDevice.h"

class XDisplayDevice : public DisplayDevice
{
   // X Window DisplayDevice

   private:

   protected:

      ColorManager* mycm;
      Display* mydisplay;
      Colormap mycolormap;
      Drawable _mydrawable;
      Window mywindow;
      Pixmap _buffer;
      int _buffer_width;
      int _buffer_height;
      bool _drawtobuffer;
      GC backgroundGC;
      GC foregroundGC;
      GC drawGC;
      Cursor _zoomcursor;
      Cursor _selectcursor;
      Cursor _busycursor;
      Cursor _precisecursor;

      bool* allocated; 
         // allocated[i] is 'true' if a Pixel value
         // for color with cookie i has been allocated.
      unsigned long* pixval;  
         // pixval[i] is Pixel value for color cookie i
      int maxcolors; 
         // Maximum number of color cookie. get from ColorManager.

      virtual Pixel getPixel(unsigned char red, 
                             unsigned char green,
                             unsigned char blue);
         // Returns the X pixel value corresponding to the color (red,green,blue).

      unsigned long getPixelFromCookie(int cookie);
         // Returns the pixel value that corresponds to either:
         // The color specified by cookie or
         // Some default color (probably the closest color possible).

   public:

      XDisplayDevice(ColorManager* cm, Display* disp, Window win);

      // Control

      void    setSize(int width, int height);
      void    setWidth(int width);
      void    setHeight(int height);
      int     getWidth(void);
      int     getHeight(void);


      // Drawing

      void    clear(void);
      void    drawPoint(int x1, int y1);
      void    drawLine(int x1, int y1, int x2, int y2);
      void    drawRect(int x1, int y1, int x2, int y2);
      void    drawFilledRect(int x1, int y1, int x2, int y2);
      void    drawCircle(int center_x, int center_y, int radius);
      void    drawFilledCircle(int center_x, int center_y, int radius);
      void    drawRaster(unsigned char* theimage, int width, int height,
                         int x, int y);
         // image is a row major order, raw RGB (3 bytes / pixel) raster.
         // width and height are in pixels.
      void    setXORMode(bool flag);
      bool    setViewport(int x1, int y1, int x2, int y2);

      void    setForeground(char* colorname);
      void    setForeground(int colorcookie);
      void    setBackground(char* colorname);
      void    setBackground(int colorcookie);
      void    setLineColor(char* colorname);
      void    setLineColor(int colorcookie);
      void    setFillColor(char* colorname);
      void    setFillColor(int colorcookie);
      void    setLineWidth(int width);

      // Pointer control

      void    setCursor(DisplayDeviceCursorType ct);

      // Buffer

      bool    supportsBuffer(void);
         // Returns true if the DisplayDevice supports a drawing buffer.

      bool    allocateBuffer(void);
         // This method causes the DisplayDevice to allocate space for
         // a buffer (if it supports one). 

      bool    bufferExists(void);
         // Returns true if a drawing buffer exists. Used to determine if
         // the DisplayDevice is currently buffering graphics.

      bool    deallocateBuffer(void);
         // Deallocates the drawing buffer (if one has been allocated).
         // Drawing to buffer is disabled.

      bool    resizeBuffer(void);
         // Causes current drawing buffer to be deallocated, and a new
         // one allocated. Since a DisplayDevice cannot know when its
         // size has changed, this method must be called by the client.
         // If a buffer does not already exist, one is created.

      bool    drawToBuffer(bool flag);
         // Enables / disables drawing to buffer. Returns true if 
         // operation was succesful. Drawing commands draw to either the
         // the actual output device or the buffer, but not to both at the
         // the same time.

      bool   isDrawingToBuffer(void);
         // Returns true if DisplayDevice is drawing in the buffer, false
         // if output is going to actual output device.

      bool    refreshFromBuffer(void);
         // Causes contents of buffer to be displayed on whatever device
         // display device is using for output. Does not alter contents
         // of buffer.
};

#endif // XDISPLAYDEVICE_H

