#ifndef COMPONENT_H
#define COMPONENT_H

#include "mvc/LinkedList.h"

class Component : public ListElement
{
   // Abstract superclass for Component2D and Component3D.

   protected:

      static long nextid;
      long myid; // Instance id.

   public:

      Component();

      virtual long getID(void);

};

#endif // COMPONENT_H
