
#include "mvc/Component.h"

long Component::nextid = 0;

Component::Component()
{
   // Each component gets a unique ID number.

   myid = nextid;
   nextid = nextid + 1;
}

long Component::getID(void)
{
   return(myid);
}

