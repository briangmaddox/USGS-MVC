#include "mvc/DisplayDevice.h"

// Control

void DisplayDevice::setSize(int width, int height)
{
}

void DisplayDevice::setWidth(int width)
{
}

void DisplayDevice::setHeight(int height)
{
}

int DisplayDevice::getWidth(void)
{
   return(0);
}

int DisplayDevice::getHeight(void)
{
   return(0);
}

// Drawing

void DisplayDevice::clear(void)
{
}

void DisplayDevice::drawPoint(int x1, int y1)
{
}

void DisplayDevice::drawLine(int x1, int y1, int x2, int y2)
{
}

void DisplayDevice::drawRect(int x1, int y1, int x2, int y2)
{
}

void DisplayDevice::drawFilledRect(int x1, int y1, int x2, int y2)
{
}

void DisplayDevice::drawCircle(int center_x, int center_y, int radius)
{
}

void DisplayDevice::drawFilledCircle(int center_x, int center_y, int radius)
{
}

void DisplayDevice::drawRaster(unsigned char* theimage,
                                int width, int height, int x, int y)
{
}

void DisplayDevice::setXORMode(bool flag)
{
   // When set to 'true', drawing is done to the display in XOR mode.
   // This means that whatever is drawn is exclusive-ORed pixel
   // by pixel with what is already on the display. This affects both
   // the display and the graphics buffer.
}

bool DisplayDevice::setViewport(int x1, int y1, int x2, int y2)
{
   return false;
}

// Attributes

void DisplayDevice::setForeground(char* colorname)
{
}

void DisplayDevice::setForeground(int colorcookie)
{
}

void DisplayDevice::setBackground(char* colorname)
{
}

void DisplayDevice::setBackground(int colorcookie)
{
}

void DisplayDevice::setLineColor(char* colorname)
{
}

void DisplayDevice::setLineColor(int colorcookie)
{
}

void DisplayDevice::setFillColor(char* colorname)
{
}

void DisplayDevice::setFillColor(int colorcookie)
{
}

void DisplayDevice::setLineWidth(int width)
{
}

//
// Pointer Control
//

void DisplayDevice::setCursor(DisplayDeviceCursorType ct)
{
   _cursor = ct;
}

DisplayDeviceCursorType DisplayDevice::getCursor(void)
{
   return _cursor;
}

//
// Buffer
//
bool DisplayDevice::supportsBuffer(void)
{
   // Returns true if the DisplayDevice supports a drawing buffer.

   return false;
}

bool DisplayDevice::allocateBuffer(void)
{
   // This method causes the DisplayDevice to allocate space for
   // a buffer (if it supports one). 

   return false;
}

bool DisplayDevice::bufferExists(void)
{
   // Returns true if a drawing buffer exists. Used to determine if
   // the DisplayDevice is currently buffering graphics.

   return false;
}

bool DisplayDevice::deallocateBuffer(void)
{
   // Deallocates the drawing buffer (if one has been allocated).
   // Drawing to buffer is disabled.

   return false;
}

bool DisplayDevice::resizeBuffer(void)
{
   // Causes current drawing buffer to be deallocated, and a new
   // one allocated. Since a DisplayDevice cannot know when its
   // size has changed, this method must be called by the client.
   // If a buffer does not already exist, one is created.

   return false;
}

bool DisplayDevice::drawToBuffer(bool flag)
{
   // Enables / disables drawing to buffer. Returns true if 
   // operation was succesful. Drawing commands draw to either the
   // the actual output device or the buffer, but not to both at the
   // the same time.

   return false;
}

bool DisplayDevice::isDrawingToBuffer(void)
{
   return false;
}

bool DisplayDevice::refreshFromBuffer(void)
{
   // Causes contents of buffer to be displayed on whatever device
   // display device is using for output. Does not alter contents
   // of buffer.

   return false;
}
