
#include <string.h>
#include "mvc/ColorManager.h"

const int ColorManager::MaxColors = 500;

ColorManager::ColorManager(void)
{
   numcolors = 0;
   colornames = new char*[MaxColors];
   colorvalues = new rgbrec[MaxColors];
   initColors();
}

ColorManager::~ColorManager(void)
{
   int i;

   if (numcolors > 0)
      {
         for (i = 0; i < numcolors; i++)
            {
               delete [] colornames[i];
            }
      }
}

void  ColorManager::addColor(char* colorname, int red, int green, int blue)
{
   // Adds the pair (colorname,<red,green,blue>) to the 
   // color database.

   if (!colorExists(colorname))
      {
         // Add the color to the database.
         if (numcolors < MaxColors)
            {
               colornames[numcolors] = new char[strlen(colorname)+1]; 
               strcpy(colornames[numcolors],colorname);
               colorvalues[numcolors].red = red;
               colorvalues[numcolors].green = green;
               colorvalues[numcolors].blue = blue;
               numcolors = numcolors + 1;
	    }
      }        

}

int   ColorManager::getColorCookie(char* colorname)
{
   // Returns the cookie for colorname. 
   // The 'cookie' is really just the position of the color entry 
   // in the database.

   if (colorExists(colorname))
      return(curcolor);
   else
      return(-1);
}

const char* ColorManager::getColorName(int cookie)
{
   // Returns the name of the color associated with cookie.

   return((const char*) colornames[cookie]);
}


bool  ColorManager::colorExists(char* colorname)
{
   // Returns 'true' if colorname is already in the database.
   // Side Effect: Positions internal pointer 'curcolor' to the color
   //    if it exists.

   bool found;
   int i;

   found = false;
   i = 0;

   while ((found != true) && (i < numcolors))
      {
         if (strcmp(colornames[i],colorname) == 0)
	    {
               found = true;
               curcolor = i;
            }
         else
            i = i + 1;
      }

   return(found);
}

int ColorManager::getMaxColors(void)
{
   return(MaxColors);
 }

int   ColorManager::getRed(char* colorname)
{
   if (colorExists(colorname))
      return(colorvalues[curcolor].red);
   else
      return(0);
}

int   ColorManager::getRed(int cookie)
{
   return(colorvalues[cookie].red);
}

int   ColorManager::getGreen(char* colorname)
{
   if (colorExists(colorname))
      return(colorvalues[curcolor].green);
   else
      return(0);
}

int   ColorManager::getGreen(int cookie)
{
   return(colorvalues[cookie].green);
}

int   ColorManager::getBlue(char* colorname)
{
   if (colorExists(colorname))
      return(colorvalues[curcolor].blue);
   else
      return(0);
}

int   ColorManager::getBlue(int cookie)
{
   return(colorvalues[cookie].blue);
}

void ColorManager::initColors(void)
{
   // Clears ColorManager, and initializes with a small set of colors.

   int i;

   if (numcolors > 0)
      {
         for (i = 0; i < numcolors; i++)
            {
               delete [] colornames[i];
            }
      }
   numcolors = 0;

   addColor("black",0,0,0);
   addColor("white",255,255,255);
   addColor("grey",127,127,127);
   addColor("red",255,0,0);
   addColor("green",0,255,0);
   addColor("blue",0,0,255);
   addColor("cyan",0,255,255);
   addColor("magenta",255,0,255);
   addColor("yellow",255,255,0);
   addColor("orange",255,165,0);
   addColor("pink",255,192,203);

 }
