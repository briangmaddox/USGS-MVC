#include "mvc/Model2D.h"
#include "mvc/Global.h"
#include "mvc/LinkedList.h"
#include "mvc/View2D.h"

const int Model2D::maxviews = 100;
const int Model2D::maxcomp = 500000;

bool Model2D::findView(View2D* v)
{
   bool found;
   int i;

   found = false;
   i = 0;
   while ((!found) && (i < numviews))
      {
         if (viewlist[i] == v)
            found = true; 
         else
            i = i + 1;
      }
   return(found);
}

Model2D::Model2D()
{
   viewlist = NULL;
   numviews = 0;
   numcomp = 0;

   //viewlist = new View2D*[maxviews];
   //complist = new Component2D*[maxcomp];

   complist = new LinkedList();
}

void Model2D::addView(View2D* v)
{
   View2D** tmplist;
   int i;

   tmplist = new View2D*[numviews + 1];
   for (i = 0; i < numviews; i++)
      tmplist[i] = viewlist[i];

   tmplist[numviews] = v;
   numviews = numviews + 1;

   delete viewlist;
   viewlist = tmplist;      
}

void Model2D::deleteView(View2D* v)
{
   View2D** tmplist;
   int i,j;

   if (numviews == 0)
      return; 

   tmplist = new View2D*[numviews - 1];
   j = 0;
   for (i = 0; i < numviews; i++)
      {
         if (viewlist[i] != v)
            {
               tmplist[j] = viewlist[i];
               j = j + 1;
            }
      }

   numviews = numviews - 1;
   delete viewlist;
   viewlist = tmplist;
   
}

void Model2D::setEveryWorldSpaceWin(double x1, double y1, double x2, double y2)
{
   int i;
   Projection2D* proj;
   
   for (i = 0; i < numviews; i++)
      {
         proj = viewlist[i]->getProjection();
         if (proj != NULL)
            {
               proj->setWorldSpaceWin(x1,y1,x2,y2);
            }
      }
}


void Model2D::setEveryFullView(double x1, double y1, double x2, double y2)
{
   int i;
   Projection2D* proj;
   
   for (i = 0; i < numviews; i++)
      {
         proj = viewlist[i]->getProjection();
         if (proj != NULL)
            {
               proj->setFullView(x1,y1,x2,y2);
            }
      }
}

void Model2D::zoomEveryFullView(void)
{
   int i;
   Projection2D* proj;

   for (i = 0; i < numviews; i++)
      {
         proj = viewlist[i]->getProjection();
         proj->zoomFullView();
      }
}

void Model2D::update(void)
{
   int i;
   
   for (i = 0; i < numviews; i++)
      {
         viewlist[i]->reDraw();
      }
}

void Model2D::addComponent(Component2D* c)
{
   // Adds a component to the Model. 

   Component2D* p;
   bool found;
   
//   complist[numcomp] = c;
//   numcomp = numcomp + 1;

   // This insertion algorithm sucks. We really should be bucket sorting
   // the components. Maybe later... when I have more time. -- jamie

   p = (Component2D*) complist->getFirstElement();
   found = false;

   while ((p != NULL) && (!found))
      {
         if (p->getLayer() < c->getLayer())
            p = (Component2D*) p->getNext();
         else
            found = true;
      }

   if (p == NULL)
      complist->addElementLast(c);
   else
      complist->addElementBefore(p,c);
   
   numcomp = numcomp + 1;
}

void Model2D::deleteComponent(Component2D* c)
{
   // Deletes a component from the Model2D.

   Component2D* p;
   bool found;

   p = (Component2D*) complist->getFirstElement();
   found = false;

   while ((p != NULL) && (!found))
      {
         if (p == c)
            found = true;
         else
            p = (Component2D*) p->getNext();
      }

   if (found)
      {
         complist->deleteElement(p);
         numcomp = numcomp - 1;
      }
}
     
Component2D* Model2D::getComponent(long compid)
{
   // Returns pointer to component with id compid.
   return(NULL);
}

void Model2D::getRefreshList(Projection2D* p,
                             Component2D**& clist, int& nc)
{
   // Returns a list of Components visible in the World Space
   // Window defined by p.

   GlobalDebug.message("In Model2D::getRefreshList");


   Component2D** tmplist;
   Component2D* q;
   int i;
 
   tmplist = new Component2D*[numcomp];

//   for (i = 0; i < numcomp; i++)
//      tmplist[i] = complist[i];

   q = (Component2D*) complist->getFirstElement();
   i = 0;
   while (q != NULL)
      {
         if (q->isVisible())
            {
               tmplist[i] = q;
               i = i + 1;
            }
         q = (Component2D*) complist->getNextElement();
      }

   clist = tmplist;
   nc = i;

}

void Model2D::getModelBoundingBox(double& maxx, double& maxy,
                                  double& minx, double& miny)
{
   // Gets the maximum and minimum World Space x and y values 
   // over all the components in the Model.    

   Component2D* p;
   double x1,y1,x2,y2;

   maxx = 0.0;  
   maxy = 0.0;
   minx = 0.0;
   miny = 0.0;

   p = (Component2D*) complist->getFirstElement();

   while (p != NULL)
      {
         p->getBoundingBox(x1,y1,x2,y2);
         if (maxx < x1) maxx = x1;
         if (x1 < minx) minx = x1;
         if (maxx < x2) maxx = x2;
         if (x2 < minx) minx = x2;
         if (maxy < y1) maxy = y1;
         if (y1 < miny) miny = y1;
         if (maxy < y2) maxy = y2;
         if (y2 < miny) miny = y2;
         p = (Component2D*) complist->getNext();
      }
}

Component2D* Model2D::getNearestComponent(double x, double y, double maxdist)
{
         // Returns closest component within maxdist (World Coordinates)
         // of the point (x,y) or NULL or no component is found.
         // This method ignores components which are not selectable or
         // not visible.

   Component2D* closestcomp;
   Component2D* p;
   double dist;

   closestcomp = (Component2D*) complist->getFirstElement();
   dist = 1.0E15;
   p = closestcomp;
   while (p != NULL)
      {
         if ((p->isSelectable()) && (p->getDistance(x,y) < dist))
            {
               dist = p->getDistance(x,y);
               closestcomp = p;
            }
         p = (Component2D*) p->getNext();
      }

   if (dist <= maxdist)
      return closestcomp;

   return NULL;
            
}
