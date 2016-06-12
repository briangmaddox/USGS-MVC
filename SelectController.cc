#include <stdio.h>
#include <math.h>
#include "mvc/Projection2D.h"
#include "mvc/Component2D.h"
#include "mvc/Model2D.h"
#include "mvc/DisplayDevice.h"
#include "mvc/SelectController.h"

SelectController::SelectController(void)
{
   thecomp = NULL;
}

void SelectController::install(void)
{
   (myview->getDisplayDevice())->setCursor(DISPDEV_SELECT);
}

void SelectController::reset(void)
{
   // Deselect the current selection. NOTE: This assumes the current
   // selection stil exists!

   if (thecomp != NULL)
      {
         thecomp->setDrawSelected(false);
         thecomp = NULL;
      }
}

void SelectController::select(Component2D* c)
{

   if (c == NULL)
      return;

   reset();  // Clear the currently selected object, if any.

   thecomp = c;
   thecomp->setDrawSelected(true);

}

void SelectController::button1Release(int x, int y)
{
}

void SelectController::button2Release(int x, int y)
{
   // We want select distance to be 10 DisplayDevice pixels. Figure
   // out what that is in World Coordinates.

   Projection2D* tmpproj;
   Component2D* tmpcomp;
   double t1,t2,wx,wy;

   tmpproj = myview->getProjection();

   t1 = tmpproj->getWorldSpaceX(0,0);
   t2 = tmpproj->getWorldSpaceX(10,0);

   wx = tmpproj->getWorldSpaceX(x,y);
   wy = tmpproj->getWorldSpaceY(x,y);

   tmpcomp = (myview->getModel())->getNearestComponent(wx,wy,fabs(t1-t2));

   if (thecomp != NULL)
      {
         thecomp->setDrawSelected(false);
         //thecomp->setVisible(true);
      }

   if (tmpcomp != NULL)
      {
         tmpcomp->setDrawSelected(true);
         //tmpcomp->setVisible(false);
      }

   if ((thecomp != NULL) || (tmpcomp != NULL))
      myview->reFresh();

   thecomp = tmpcomp;
}

void SelectController::button3Release(int x, int y)
{
}

void SelectController::pointerMotion(int x, int y)
{
   // Called when pointer moves. Pointer is now at
   // Device coordinates (x,y).
}

void SelectController::button1Motion(int x, int y)
{
   // Called when pointer moves and Button1 is depressed.

   Projection2D* proj;
   DisplayDevice* dd;
   double wx,wy;

   if (thecomp != NULL)
      {
         proj = myview->getProjection();
         dd = myview->getDisplayDevice();
         thecomp->draw(proj,dd);
         wx = proj->getWorldSpaceX(x,y);
         wy = proj->getWorldSpaceY(x,y);
         thecomp->moveTo(wx,wy);
         thecomp->draw(proj,dd);
      }
}

void SelectController::button2Motion(int x, int y)
{
   // Called when pointer moves and Button2 is depressed.
}

void SelectController::button3Motion(int x, int y)
{
   // Called when pointer moves and Button3 is depressed.
}

void SelectController::pointerEnter(int x, int y)
{
   // Called when pointer enters input area. (x,y) location
   // pointer entered.
}

void SelectController::pointerLeave(int x, int y)
{
   // Called when pointer leaves input area. (x,y) location
   // pointer left.
}

