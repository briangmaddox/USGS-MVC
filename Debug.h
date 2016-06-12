#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

class Debug
{
   private:

   protected:

      bool _printmessages;

   public:

      Debug(void);

      virtual void messagesOn(void);
      virtual void messagesOff(void);

      virtual void message(char* themessage);
};

#endif // DEBUG_H
