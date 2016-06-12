
#include "mvc/FileDisplayDevice.h"
#include "mvc/ColorManager.h"

void main()
{

   FileDisplayDevice* fdd;
   ColorManager cm;

   fdd = new FileDisplayDevice(&cm,"TIFF",100,100);

   cm.initColors();
   fdd->clear();
   fdd->setForeground("blue");
   fdd->drawLine(0,0,80,80);

   fdd->setForeground("red");
   fdd->drawLine(40,10,0,70);

   fdd->drawLine(50,10,10,70);

   fdd->write("jamie.tif");
}