#ifndef FILEVIEW2D_H
#define FILEVIEW2D_H

#include "mvc/View2D.h"
#include "mvc/ColorManager.h"

class FileView2D : public View2D
{
   private:

   protected:

   public:

      FileView2D(ColorManager* cm, char* filetype, int width, int height);
      ~FileView2D(void);

      // FileView2D specific methods
      void write(char* filename);

};

#endif // FILEVIEW2D_H


