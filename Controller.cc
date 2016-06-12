#include "mvc/Controller.h"

Controller::Controller(void)
{
}

void Controller::setView(View2D* v)
{
   myview = v;
}

View2D* Controller::getView(void)
{
   return(myview);
}

void Controller::install(void)
{
}

void Controller::uninstall(void)
{
}

void Controller::reset(void)
{
}

void Controller::button1Release(int x, int y)
{
}

void Controller::button2Release(int x, int y)
{
}

void Controller::button3Release(int x, int y)
{
}

void Controller::pointerMotion(int x, int y)
{
   // Called when pointer moves. Pointer is now at
   // Device coordinates (x,y).
}

void Controller::button1Motion(int x, int y)
{
   // Called when pointer moves and Button1 is depressed.
}

void Controller::button2Motion(int x, int y)
{
   // Called when pointer moves and Button2 is depressed.
}

void Controller::button3Motion(int x, int y)
{
   // Called when pointer moves and Button3 is depressed.
}

void Controller::pointerEnter(int x, int y)
{
   // Called when pointer enters input area. (x,y) location
   // pointer entered.
}

void Controller::pointerLeave(int x, int y)
{
   // Called when pointer leaves input area. (x,y) location
   // pointer left.
}

void Controller::resize(int w, int h)
{
   // Called when input window resizes. w is new width, 
   // h is new height;

//   (myview->getProjection())->setDisplayDevWin(0,0,w,h);
//   (myview->getDisplayDevice())->deallocateBuffer();

   myview->reSize(w,h);
}

void Controller::expose(void)
{
   // Called when any portion of the input window is exposed.
   myview->reFresh();
}

void Controller::keyPressed(char* stringrep, int x, int y)
{
}
