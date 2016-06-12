#ifndef XTRUECOLORDISPLAYDEVICE_H
#define XTRUECOLORDISPLAYDEVICE_H

#include "mvc/XDisplayDevice.h"

class XTrueColorDisplayDevice : public XDisplayDevice
{
   // X Window DisplayDevice for 24 bit depth TrueColor visuals.

   private:

   protected:


   public:

      XTrueColorDisplayDevice(ColorManager* cm, Display* disp, Window win);


      // Drawing
      void    drawRaster(unsigned char* theimage, int width, int height,
                         int x, int y);
         // image is a row major order, raw RGB (3 bytes / pixel) raster.
         // width and height are in pixels.

};
#endif // XTRUECOLORDISPLAYDEVICE_H

