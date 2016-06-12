#ifndef MODEL2D_H
#define MODEL2D_H

#include "mvc/Component2D.h"
#include "mvc/Projection2D.h"

class View2D;

class Model2D
{
   private:

   protected:
      static const int maxviews;
      static const int maxcomp;

      View2D** viewlist;
      //Component2D** complist;
      LinkedList* complist;

      int numviews;
      int numcomp;

      virtual bool findView(View2D* v);

   public:

      Model2D();

      virtual void addView(View2D* v);
         // Adds a view to the Model.

      virtual void deleteView(View2D* v);
         // Deletes a view from the Model.

      virtual void setEveryWorldSpaceWin(double x1, double y1, double x2, double y2);

      virtual void setEveryFullView(double x1, double y1, double x2, double y2);
         // Tells every View registered with this model to set their full view
         // to the rectangle whose corners are the World Coordinates (x1,y1),
         // (x2,y2).

      virtual void zoomEveryFullView(void);
         // Causes all views registered with this model to zoom to their Full Views.

      virtual void update(void);
         // Message sent to the model to let it know that the contents have
         // changed in some way. This causes all views to be notified that the
         // model has changed.

      virtual void addComponent(Component2D* c);
         // Adds a component to the model. 

      virtual void deleteComponent(Component2D* c);
         // Deletes a component from the model.
     
      virtual Component2D* getComponent(long compid);
         // Returns pointer to component with id compid.

      virtual void getRefreshList(Projection2D* p,
                                  Component2D**& clist, int& nc);
         // Returns a list of Components visible in the World Space
         // Window defined by p.

      virtual void getModelBoundingBox(double& maxx, double& maxy,
                                       double& minx, double& miny);
         // Gets the maximum and minimum World Space x and y values 
         // over all the components in the Model. 


      //
      // Selection
      //

      virtual Component2D* getNearestComponent(double x, double y,
                                               double maxdist);
         // Returns closest component within maxdist (World Coordinates)
         // of the point (x,y) or NULL or no component is found.
         // This method ignores components which are not selectable or
         // not visible.



};

#endif // MODEL2D_H
