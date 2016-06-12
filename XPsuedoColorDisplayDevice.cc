
#include <stdio.h>
#include "mvc/XPsuedoColorDisplayDevice.h"
#include <X11/Xutil.h>
#include <X11/cursorfont.h>

void XPsuedoColorDisplayDevice::findColor(long rgbvals, Pixel& pixval, bool& found)
{
   // If the color corresponding to rgbvals is in the color table, set
   // pixval to the X Pixel value.

   long first,last,middle;
   static long old_rgbvals = -1;  // value from previous call to findColor.
   static Pixel old_pixval = 0;

   if (old_rgbvals == rgbvals)
      {
         pixval = old_pixval;
         found = true;
         return;
      }

   // binary search

   first = 0;
   last = num_colors - 1;
   found = false;

   while ((first <= last) && (!found))
      {
         middle = (first + last) / 2;
         if (rgbvals == colortable[middle].rgb_values)
            found = true;
         else if (rgbvals < colortable[middle].rgb_values)
            last = middle - 1;
         else 
            first = middle + 1;
      }

   if (found)
      {
         pixval = colortable[middle].pixel_value;
         old_rgbvals = rgbvals;
         old_pixval = pixval;
      }
}

void XPsuedoColorDisplayDevice::addColor(long rgbvals, Pixel pixval)
{
   // add the (rgbvals,pixval) tuple to the color table.

   int p,i;
   bool found;
   
   // insertion sort, ascending order on rgb_values.

   p = 0; 
   found = false;
   while ((p < num_colors) && (!found))
      {
         if (colortable[p].rgb_values < rgbvals)
            p = p + 1;
         else
            found = true;
      }

   if (found)
      {
         // Slide everything from p to end of list down one entry.
         for (i = num_colors - 1; i >= p; i--)
            {
               colortable[i+1] = colortable[i];
            }
         colortable[p].rgb_values = rgbvals;
         colortable[p].pixel_value = pixval;
         num_colors = num_colors + 1;
      }
   else
      {
         colortable[num_colors].rgb_values = rgbvals;
         colortable[num_colors].pixel_value = pixval;
         num_colors = num_colors + 1;
      }
}

Pixel XPsuedoColorDisplayDevice::getPixel(unsigned char red,
                                          unsigned char green,
                                          unsigned char blue)
{
   bool found;
   long rgbvals;
   Pixel pixval;

   // Convert seperate RGB values to a long.
   rgbvals = (blue << 16) + (green << 8) + red;

   // See if we've already allocated the color.
   findColor(rgbvals,pixval,found);
   if (found)
      return pixval;

   // Allocate the color and add it to the colortable.
   pixval = XDisplayDevice::getPixel(red,green,blue);
   addColor(rgbvals,pixval);
   return pixval;
}

XPsuedoColorDisplayDevice::XPsuedoColorDisplayDevice(ColorManager* cm,
                                                     Display* disp, Window win)
                          : XDisplayDevice(cm,disp,win)
{
   num_colors = 0;
}

void XPsuedoColorDisplayDevice::drawRaster(unsigned char* theimage, 
                                           int width, int height, int x, int y)
{
   // image is in row major order, 4 bytes / pixel, format: '0BGR'.
   // width and height are in pixels.

   XImage* newimage;
   unsigned char* tmpimage;
   Pixel thepix;
   int i;

   // Convert theimage from raw RGB to pseudocolor, allocating a color for 
   // each pixel.
   tmpimage = new unsigned char[width * height];
   for (i = 0; i < (width * height * 4); i = i + 4)
      {
         thepix = getPixel(theimage[i+3],theimage[i+2],theimage[i+1]);
         tmpimage[i/4] = (unsigned char) (thepix & 0x000000FF);
      }

   newimage = XCreateImage(mydisplay,
                 DefaultVisual(mydisplay,DefaultScreen(mydisplay)),
                 8,ZPixmap,0,(char*)tmpimage,width,height,8,0);

   XPutImage(mydisplay,_mydrawable,
             DefaultGC(mydisplay,DefaultScreen(mydisplay)), 
             newimage,0,0,x,y,width,height);

   // Destroy the XImage struc, but not the client image data.
   newimage->data = (char*)NULL;
   XDestroyImage(newimage);
   delete tmpimage;

}
