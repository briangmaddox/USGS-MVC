#ifndef FILEDISPLAYDEVICE_H
#define FILEDISPLAYDEVICE_H

#include "mvc/DisplayDevice.h"
#include "mvc/ColorManager.h"


class FileDisplayDevice : public DisplayDevice
{

   // A DisplayDevice has an integer coordinate system whose origin
   // is located in the "upper left" corner. 'x' increases from
   // left to right. 'y' increases from top to bottom.

   private:

   protected:

      typedef enum {RGB,TIFF} FileType;

      ColorManager* _cm;
      int _width,_height;
      FileType _filetype;
      int _pixsize;
      unsigned char* _framebuf;
      int _foreground,_background;
      unsigned char* _pixval;
      int _numcolors;  // Number of colors in palette;
      int _palette[256];

      void addToPalette(int _foreground);

   public:

      FileDisplayDevice(ColorManager* acm, char* filetype,
                        int width, int height);
         // Where filetype is one of "RGB","TIFF"

      ~FileDisplayDevice(void);

      int     getWidth(void);
      int     getHeight(void);


      // Drawing

      void    clear(void);
      void    drawPoint(int x1, int y1);
      void    drawLine(int x1, int y1, int x2, int y2);

      // Attributes

      void    setForeground(char* colorname);
      void    setForeground(int colorcookie);
      void    setBackground(char* colorname);
      void    setBackground(int colorcookie);

      // FileDisplayDevice specific methods
 
      virtual void write(char* filename);
         // Causes entire framebuffer to be written to disk.
};

#endif // FILEDISPLAYDEVICE_H


