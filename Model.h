#ifndef MODEL2D_H
#define MODEL2D_H

#include "mvc/View.h"
#include "mvc/Component2D.h"
#include "mvc/Projection2D.h"

class Model2D
{
   private:

   protected:

   public:

      Model2D();

      virtual void addView(View* v);
         // Adds a view to the Model.

      virtual void deleteView(View* v);
         // Deletes a view from the Model.

      virtual void addComponent(Component2D* c);
         // Adds a component to the model. 

      virtual void deleteComponent(Component2D* c);
         // Deletes a component from the model.
     
      virtual Component2D* getComponent(long compid);
         // Returns pointer to component with id compid.

      virtual void getRefreshList(Projection* p,
                                  Component2D** complist, int* numcomp);
         // Returns a list of Components visible in the World Space
         // Window defined by p.

};

#endif // MODEL2D_H
