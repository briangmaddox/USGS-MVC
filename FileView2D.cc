
#include "mvc/FileView2D.h"
#include "mvc/FileDisplayDevice.h"
#include "mvc/ColorManager.h"
#include "mvc/RectProj2D.h"

FileView2D::FileView2D(ColorManager* cm, char* filetype, int width, int height)
{
   mydd = new FileDisplayDevice(cm,filetype,width,height);
   myproj = new RectProj2D();
   myproj -> setDisplayDevWin(0,0,mydd->getWidth()-1, mydd->getHeight()-1);
}

FileView2D::~FileView2D(void)
{
   if (mydd != NULL)
      delete mydd;

   if (myproj != NULL)
      delete myproj;
}

void FileView2D::write(char* filename)
{
   ((FileDisplayDevice*)mydd)->write(filename);
}
