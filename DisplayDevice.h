#ifndef DISPLAYDEVICE_H
#define DISPLAYDEVICE_H

typedef enum {DISPDEV_BUSY,
              DISPDEV_SELECT,
              DISPDEV_ZOOM,
              DISPDEV_PRECISE}
DisplayDeviceCursorType;

class DisplayDevice
{
   // Abstract DisplayDevice class.

   // A DisplayDevice has an integer coordinate system whose origin
   // is located in the "upper left" corner. 'x' increases from
   // left to right. 'y' increases from top to bottom.

   private:

   protected:

      DisplayDeviceCursorType _cursor;

   public:

      // Control

      virtual void    setSize(int width, int height);
      virtual void    setWidth(int width);
      virtual void    setHeight(int height);
      virtual int     getWidth(void);
      virtual int     getHeight(void);


      // Drawing

      virtual void    clear(void);
      virtual void    drawPoint(int x1, int y1);
      virtual void    drawLine(int x1, int y1, int x2, int y2);
      virtual void    drawRect(int x1, int y1, int x2, int y2);
      virtual void    drawFilledRect(int x1, int y1, int x2, int y2);
      virtual void    drawCircle(int center_x, int center_y, int radius);
      virtual void    drawFilledCircle(int center_x, int center_y, int radius);
      virtual void    drawRaster(unsigned char* theimage,
                                 int width, int height, int x, int y);
         // image is a row major order, raw RGB (3 bytes / pixel) raster.
         // width and height are in pixels. (x,y) is coordinate of
         // upperleft corner of image on the display.
      virtual void    setXORMode(bool flag);
         // When set to 'true', drawing is done to the display in XOR mode.
         // This means that whatever is drawn is exclusive-ORed pixel
         // by pixel with what is already on the display. This affects both
         // the display and the graphics buffer.
      virtual bool    setViewport(int x1, int y1, int x2, int y2);
         // A viewport is a rectangular area on a Display Device that output
         // should be restricted to. For DisplayDevices that support a viewport,
         // setting one ensures that no drawing is done outside the given area.
         // Returns true of the viewport is set, false if error.

      // Attributes

      virtual void    setForeground(char* colorname);
      virtual void    setForeground(int colorcookie);
      virtual void    setBackground(char* colorname);
      virtual void    setBackground(int colorcookie);
      virtual void    setLineColor(char* colorname);
      virtual void    setLineColor(int colorcookie);
      virtual void    setFillColor(char* colorname);
      virtual void    setFillColor(int colorcookie);
      virtual void    setLineWidth(int width);

      // Pointer control

      virtual void    setCursor(DisplayDeviceCursorType ct);
      virtual DisplayDeviceCursorType getCursor(void);

      // Buffer

      virtual bool    supportsBuffer(void);
         // Returns true if the DisplayDevice supports a drawing buffer.

      virtual bool    allocateBuffer(void);
         // This method causes the DisplayDevice to allocate space for
         // a buffer (if it supports one). 

      virtual bool    bufferExists(void);
         // Returns true if a drawing buffer exists. Used to determine if
         // the DisplayDevice is currently buffering graphics.

      virtual bool    deallocateBuffer(void);
         // Deallocates the drawing buffer (if one has been allocated).
         // Drawing to buffer is disabled.

      virtual bool    resizeBuffer(void);
         // Causes current drawing buffer to be deallocated, and a new
         // one allocated. Since a DisplayDevice cannot know when its
         // size has changed, this method must be called by the client.
         // If a buffer does not already exist, one is created.

      virtual bool    drawToBuffer(bool flag);
         // Enables / disables drawing to buffer. Returns true if 
         // operation was succesful. Drawing commands draw to either the
         // the actual output device or the buffer, but not to both at the
         // the same time. If DisplayDevice supports a buffer, and one is
         // not currently allocated, this method will allocate one.

      virtual bool    isDrawingToBuffer(void);
         // Returns true if DisplayDevice is drawing in the buffer, false
         // if output is going to actual output device.

      virtual bool    refreshFromBuffer(void);
         // Causes contents of buffer to be displayed on whatever device
         // display device is using for output. Does not alter contents
         // of buffer.

};

#endif // DEVICE_H
