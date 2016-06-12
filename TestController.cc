#include <stdio.h>
#include "mvc/TestController.h"

void TestController::button1Release(int x, int y)
{
   printf("TestController::button1Release  %d,%d\n",x,y);
}

void TestController::button2Release(int x, int y)
{
   printf("TestController::button2Release  %d,%d\n",x,y);
}

void TestController::button3Release(int x, int y)
{
   printf("TestController::button3Release  %d,%d\n",x,y);
}

void TestController::pointerMotion(int x, int y)
{
   // Called when pointer moves. Pointer is now at
   // Device coordinates (x,y).
   printf("TestController:pointerMotion! %d,%d\n",x,y);
}

void TestController::button1Motion(int x, int y)
{
   // Called when pointer moves and Button1 is depressed.
   printf("TestController:button1Motion  %d,%d\n",x,y);
}

void TestController::button2Motion(int x, int y)
{
   // Called when pointer moves and Button2 is depressed.
   printf("TestController:button2Motion  %d,%d\n",x,y);
}

void TestController::button3Motion(int x, int y)
{
   // Called when pointer moves and Button3 is depressed.
   printf("TestController:button3Motion  %d,%d\n",x,y);
}

void TestController::pointerEnter(int x, int y)
{
   // Called when pointer enters input area. (x,y) location
   // pointer entered.
   printf("TestController::pointerEnter: %d,%d\n",x,y);
}

void TestController::pointerLeave(int x, int y)
{
   // Called when pointer leaves input area. (x,y) location
   // pointer left.
   printf("TestController::pointerLeave: %d,%d\n",x,y);
}

void TestController::resize(int w, int h)
{
   // Called when input window resizes. w is new width, 
   // h is new height;

   printf("Window resized. New width, height = %d,%d\n",w,h);
}

void TestController::expose(void)
{
   // Called when any portion of the input window is exposed.
   printf("Window was exposed. Eeeeeek!! \n");
}
