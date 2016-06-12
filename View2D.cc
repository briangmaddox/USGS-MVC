#include "mvc/View2D.h"
#include "mvc/Global.h"

void View2D::preDraw(void)
{
   _mycursor = mydd->getCursor();
   mydd->setCursor(DISPDEV_BUSY);

   if (_smartrefresh && (mydd->supportsBuffer()))
      mydd->drawToBuffer(true);

   mydd->clear();
}

void View2D::Draw(void)
{
   Component2D** clist;
   int numc; 
   int i;

   if (_smartrefresh && (mydd->supportsBuffer()))
      mydd->drawToBuffer(true);

   if ((mymodel != NULL) && (myproj != NULL))
      {
         GlobalDebug.message("In View2D::reDraw just before getRefreshList");
         mymodel->getRefreshList(myproj,clist,numc);

         // Scan for components on negative layers
         for (i = 0; i < numc; i++)
            {
               if (clist[i]->getLayer() < 0)
                  clist[i]->draw(myproj,mydd);
            }
         if (_smartrefresh && (mydd->supportsBuffer()))
            {
               mydd->drawToBuffer(false);
               mydd->refreshFromBuffer();
            }
         
         // Draw all other layers.
         for (i = 0; i < numc; i++)
            {
               if (clist[i]->getLayer() >= 0)
                  clist[i]->draw(myproj,mydd);
            }

         delete[] clist;

      }
}

void View2D::postDraw(void)
{
   mydd->setCursor(_mycursor);
}

View2D::View2D(void)
{
   mymodel = NULL;
   myproj = NULL;
   mydd = NULL;
   myinput = NULL;
   mycontroller = NULL;
   _smartrefresh = false;
}

View2D::~View2D(void)
{
   if (mymodel != NULL)
      mymodel->deleteView(this);
}

void View2D::reDraw(void)
{
   // Causes View to redraw itself

   preDraw();
   Draw();
   postDraw();

}

void View2D::reSize(int w, int h)
{
   // Message sent by the Controller class whenever the size of
   // this View's DisplayDevice changes. w,h are the new size.

   myproj->setDisplayDevWin(0,0,w,h);
   mydd->deallocateBuffer();
}

void View2D::reFresh(void)
{

   Component2D** clist;
   DisplayDeviceCursorType tmpcursor;
   int numc; 
   int i;

   if (_smartrefresh && (mydd->supportsBuffer()) &&
       (mydd->bufferExists()))
      {
         //mydd->setBusyCursor();
         tmpcursor = mydd->getCursor();
         mydd->setCursor(DISPDEV_BUSY);
         mydd->refreshFromBuffer();

         mymodel->getRefreshList(myproj,clist,numc);
         // Draw all positive layer objects.
         for (i = 0; i < numc; i++)
            {
               if (clist[i]->getLayer() >= 0)
                  clist[i]->draw(myproj,mydd);
            }

         delete[] clist;
         //mydd->setSelectCursor();
         mydd->setCursor(tmpcursor);
      }
   else
      reDraw();
}
 
void View2D::setSmartRefresh(bool flag)
{
   _smartrefresh = flag;
}

void View2D::setModel(Model2D* m)
{
   // Setting model to NULL deletes this view from the model it is currently
   // connected to.

   if (mymodel != NULL)
      mymodel->deleteView(this);

   mymodel = m;

   if (mymodel != NULL)
      mymodel->addView(this);
}

Model2D* View2D::getModel(void)
{
   return(mymodel);
}

void View2D::setProjection(Projection2D* p)
{
   myproj = p;
}

 
Projection2D* View2D::getProjection(void)
{
   return(myproj);
}


void View2D::setDisplayDevice(DisplayDevice* dd)
{
   mydd = dd;
}


DisplayDevice* View2D::getDisplayDevice(void)
{
   return(mydd);
}


void View2D::setInputDevice(InputDevice* theid)
{
   myinput = theid;
}


InputDevice* View2D::getInputDevice(void)
{
   return(myinput);
}

Controller* View2D::getController(void)
{
   return(mycontroller);
}

void View2D::setController(Controller* thecontroller)
{
   if (mycontroller != NULL)
      mycontroller->uninstall();

   mycontroller = thecontroller;

   mycontroller->install();
}


double View2D::getWorldSpaceX(int x, int y)
{
   return myproj -> getWorldSpaceX(x,y);
}

double View2D::getWorldSpaceY(int x, int y)
{
   return myproj -> getWorldSpaceY(x,y);
}

void View2D::pan(double newcenter_x, double newcenter_y)
{
   myproj -> pan(newcenter_x, newcenter_y);
   reDraw();
}

void View2D::zoomBy(double magfactor)
{
   myproj -> zoomBy(magfactor);
   reDraw();
}

void View2D::zoomTo(double x, double y, double magfactor)
{
   myproj -> zoomTo(x,y,magfactor);
   reDraw();
}

void View2D::zoomFullView(void)
{
   myproj -> zoomFullView();
   reDraw();
}
