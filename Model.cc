
#include "mvc/Model2D.h"

Model2D::Model2D()
{
}

void Model2D::addView(View* v)
{
   // Adds a view to the Model2D.
}

void Model2D::deleteView(View* v)
{
   // Deletes a view from the Model2D.
}

void Model2D::addComponent(Component2D* c)
{
   // Adds a component to the Model2D. 
}

void Model2D::deleteComponent(Component2D* c)
{
   // Deletes a component from the Model2D.
}
     
Component2D* Model2D::getComponent(long compid)
{
   // Returns pointer to component with id compid.
}

void Model2D::getRefreshList(Projection2D* p
                           Component2D** complist, int* numcomp)
{
   // Returns a list of Components visible in the World Space
   // Window defined by p.
}

