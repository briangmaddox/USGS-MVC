
#include <stdio.h>
#include "ColorManager.h"

void main()
{
   ColorManager* bob;
   int c;
   int colorid;

   bob = new ColorManager();

   bob->addColor("yellow",255,255,0);
   bob->addColor("red",255,0,0);
   bob->addColor("blue",0,0,255);
   bob->addColor("green",0,255,0);


   printf("cookie=3, color='%s'\n",bob->getColorName(3));

   c = bob->getColorCookie("red");
   printf("'%s' <R,G,B>=<%d,%d,%d>\n",bob->getColorName(c),
          bob->getRed(c),bob->getGreen(c),
          bob->getBlue(c));

   bob->initColors();

   while (1 == 1)
     {
        scanf("%d",&colorid);
        printf("'%s' <R,G,B>=<%d,%d,%d>\n", bob->getColorName(colorid),
               bob->getRed(colorid),bob->getGreen(colorid),
               bob->getBlue(colorid));
      }

 }
