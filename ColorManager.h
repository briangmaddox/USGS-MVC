#ifndef COLORMANAGER_H
#define COLORMANAGER_H

class ColorManager
{
   // ColorManager class. 

   // Maintains a database of (colorname,<R,G,B>,cookie) tuples.
   // colorname is the text name of the color (eg. "yellow")
   // <R,G,B> is a vector describing the color in RGB space (eg. <255,255,0>)
   // cookie is a unique integer that is assigned by the ColorManager.
   // The cookie may be used to refer to the (colorname,<R,G,B>) pair.

   private:

   protected:

      static const int MaxColors;

      typedef struct {
         int red;
         int green;
         int blue;
       } rgbrec;

       char** colornames;
       rgbrec* colorvalues;
       int numcolors;
       int curcolor; // points to last entry found by colorExists.


   public:

      ColorManager(void);
      ~ColorManager(void);

      void    addColor(char* colorname, int red, int green, int blue);
         // Adds the pair (colorname,<red,green,blue>) to the 
         // color database.

      int     getColorCookie(char* colorname);
         // Returns the cookie for colorname.

      const char* getColorName(int cookie);
         // Returns the name of the color associated with cookie.

      bool    colorExists(char* colorname);
         // Returns 'true' if colorname is already in the database.

      int     getMaxColors(void);
         // Returns the maximum number of colors possible in the database.

      int     getRed(char* colorname);
      int     getRed(int cookie);

      int     getGreen(char* colorname);
      int     getGreen(int cookie);

      int     getBlue(char* colorname);
      int     getBlue(int cookie);

      void    initColors(void);
         // Clears ColorManager, and initializes it with the following
         // colors:
         //    "black"        0   0   0
         //    "white"      255 255 255
         //    "grey"       127 127 127
         //    "red"        255   0   0
         //    "green"        0 255   0
         //    "blue"         0   0 255
         //    "cyan"         0 255 255
         //    "magenta"    255   0 255
         //    "yellow"     255 255   0
         //    "orange"     255 165   0
         //    "pink"       255 192 203

};

#endif // COLORMANAGER_H
