
#include <stdio.h>
#include "RectProj2D.h"

void main()
{

   RectProj2D* myproj;
   double wx,wy;
   int dx,dy;

   myproj = new RectProj2D;

   myproj->setWorldSpaceWin(0,0,10,10);
   myproj->setDisplayDevWin(0,0,500,500);

   myproj->zoomBy(2.0);

   while (1==1)
      {
         scanf("%lf,%lf",&wx,&wy);
        
         dx = myproj->getDisplayDeviceX(wx,wy);
         dy = myproj->getDisplayDeviceY(wx,wy);
         printf("%lf,%lf ->  %d,%d\n",wx,wy,dx,dy);
      }

#if 0
   while (1==1)
      {
         scanf("%d,%d",&dx,&dy);
         wx = myproj->getWorldSpaceX(dx,dy);
         wy = myproj->getWorldSpaceY(dx,dy);
         printf("%d,%d -> %lf,%lf\n",dx,dy,wx,wy);
      }
#endif

   
}