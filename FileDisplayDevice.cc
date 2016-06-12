
#include <stdio.h>
#include <string.h>
#include "mvc/FileDisplayDevice.h"
#include "Image/RGBPallette.h"
#include "Image/TIFFImageOFile.h"

#define FB(x,y) _framebuf[(y * _width * _pixsize) + (x * _pixsize)]

void FileDisplayDevice::addToPalette(int colorcookie)
{
   static int lastcolor = -1;
   bool found;
   int cur;

   if (colorcookie != lastcolor)
      {
         // search the pallete to see if we already have this color.
         found = false;
         cur = 0;
         while ((!found) && (cur < _numcolors))
            {
               if (_palette[cur] == colorcookie)
                  found = true;
               else
                  cur = cur + 1;
            }
         if (!found)
            {
               _palette[_numcolors] = colorcookie;
               _numcolors = _numcolors + 1;
            }
         lastcolor = colorcookie;
      }

}   

FileDisplayDevice::FileDisplayDevice(ColorManager* acm,
                                     char* filetype, 
                                     int width, int height)
{
   _cm = acm;
   _width = width;
   _height = height;
//   _foreground = _cm->getColorCookie("white");
//   _background = _cm->getColorCookie("black");

   _numcolors = 0;

   if (strcmp(filetype,"RGB") == 0)
      {
         _filetype = RGB;
         _pixsize = 3;
      }
   else if (strcmp(filetype,"TIFF") == 0)
      {
         _filetype = TIFF;
         _pixsize = 1;
      }
   else
      {
         printf("Unknown file type in FileDisplayDevice ctor.\n");
         exit(69);
      }
   _pixval = new unsigned char[_pixsize];

   setForeground(_cm->getColorCookie("white"));
   setBackground(_cm->getColorCookie("black"));

   // Allocate space for the frame buffer.

   _framebuf = new unsigned char[_width * _height * _pixsize];

}

FileDisplayDevice::~FileDisplayDevice(void)
{
   if (_framebuf != NULL)
      delete [] _framebuf;

   if (_pixval != NULL)
      delete [] _pixval;
}	

int FileDisplayDevice::getWidth(void)
{
   return _width;
}

int FileDisplayDevice::getHeight(void)
{
   return _height;
}

void FileDisplayDevice::clear(void)
{
   // Fill the frame buffer with the background color.

   // This is *really* inefficient, but I'm in a hurry... -- jamie

   int x,y;
   int tmp;

   tmp = _foreground;
   setForeground(_background);

   for (x = 0; x < _width; x++)
      { 
         for (y = 0; y < _height; y++)
            {
               drawPoint(x,y);
            }
      }

   setForeground(tmp);
}

void FileDisplayDevice::drawPoint(int x1, int y1)
{

   // Put a point in the frame buffer at location (x1,y1) of
   // the foreground color.

   memcpy((void*) &FB(x1,y1),(const void*)_pixval,_pixsize);

}

/* absolute value of a */
#define ABS(a)		(((a)<0) ? -(a) : (a))

/* take binary sign of a, either -1, or 1 if >= 0 */
#define SGN(a)		(((a)<0) ? -1 : 1)

void FileDisplayDevice::drawLine(int x1, int y1, int x2, int y2)
{

   // Adapted from:

/*
 * Digital Line Drawing
 * by Paul Heckbert
 * from "Graphics Gems", Academic Press, 1990
 */

/*
 * digline: draw digital line from (x1,y1) to (x2,y2),
 * calling a user-supplied procedure at each pixel.
 * Does no clipping.  Uses Bresenham's algorithm.
 *
 * Paul Heckbert	3 Sep 85
 */


    int d, x, y, ax, ay, sx, sy, dx, dy;

    dx = x2-x1;  ax = ABS(dx)<<1;  sx = SGN(dx);
    dy = y2-y1;  ay = ABS(dy)<<1;  sy = SGN(dy);

    x = x1;
    y = y1;
    if (ax>ay) {		/* x dominant */
	d = ay-(ax>>1);
	for (;;) {
	    drawPoint(x, y);
	    if (x==x2) return;
	    if (d>=0) {
		y += sy;
		d -= ax;
	    }
	    x += sx;
	    d += ay;
	}
    }
    else {			/* y dominant */
	d = ax-(ay>>1);
	for (;;) {
	    drawPoint(x, y);
	    if (y==y2) return;
	    if (d>=0) {
		x += sx;
		d -= ay;
	    }
	    y += sy;
	    d += ax;
	}
    }
}

void FileDisplayDevice::setForeground(char* colorname)
{
   setForeground(_cm -> getColorCookie(colorname));
}

void FileDisplayDevice::setForeground(int colorcookie)
{
   _foreground = colorcookie;

   if (_filetype == TIFF)
      {
         _pixval[0] = (unsigned char) _foreground;
         addToPalette(_foreground);
      }
   else
      if (_filetype == RGB)
         {
            _pixval[0] = (unsigned char) _cm->getRed(_foreground);
            _pixval[1] = (unsigned char) _cm->getGreen(_foreground);
            _pixval[2] = (unsigned char) _cm->getBlue(_foreground);
         }
}

void FileDisplayDevice::setBackground(char* colorname)
{
   setBackground(_cm -> getColorCookie(colorname));
}

void FileDisplayDevice::setBackground(int colorcookie)
{
   _background = colorcookie;

   if (_filetype == TIFF)
      {
         addToPalette(_background);
      }

}

void FileDisplayDevice::write(char* filename)
{
   int i;
   RGBPallette* pal;
   RGBPixel* tmppix;
   TIFFImageOFile* outTIFFimage;

   if (_filetype == TIFF)
      {
         // Create the palette object

         pal = new RGBPallette(255);
         for (i = 0; i < _numcolors; i++)
            {
               tmppix = new RGBPixel();
               tmppix->setRed(_cm->getRed(_palette[i]));
               tmppix->setGreen(_cm->getGreen(_palette[i]));
               tmppix->setBlue(_cm->getBlue(_palette[i]));
               pal->setEntry(_palette[i],tmppix);
               delete tmppix;
            }

         outTIFFimage = new TIFFImageOFile(filename,_width,_height);
         outTIFFimage->setPallette(pal);

         for (i = 0; i < _height; i++)
            {
               outTIFFimage->putRawScanline(&FB(0,i),i);
            }

         delete outTIFFimage;
         delete pal;
      }
}

