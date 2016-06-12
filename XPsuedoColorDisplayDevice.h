#ifndef XPSUEDOCOLORDISPLAYDEVICE_H
#define XPSUEDOCOLORDISPLAYDEVICE_H

#include "mvc/XDisplayDevice.h"

class XPsuedoColorDisplayDevice : public XDisplayDevice
{
   // X Window DisplayDevice for 8 bit depth PsuedoColor visuals.

   private:

   protected:

      struct colortablerec
      {
         long rgb_values;     // RGB values of color.
         Pixel pixel_value;   // X Pixel value corresponding to color.
      };

      colortablerec colortable[1024];
      long num_colors;

      void findColor(long rgbvals, Pixel& pixval, bool& found);
         // If the color corresponding to rgbvals is in the color table, set
         // pixval to the X Pixel value.

      void addColor(long rgbvals, Pixel pixval);
         // add the (rgbvals,pixval) tuple to the color table.

      Pixel getPixel(unsigned char red, 
                     unsigned char green,
                     unsigned char blue);

   public:

      XPsuedoColorDisplayDevice(ColorManager* cm, Display* disp, Window win);

      void    drawRaster(unsigned char* theimage, int width, int height,
                         int x, int y);
         // image is a row major order, raw RGB (3 bytes / pixel) raster.
         // width and height are in pixels.

};

#endif // XPSUEDOCOLORDISPLAYDEVICE_H




