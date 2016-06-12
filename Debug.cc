#include <stdio.h>
#include "mvc/Debug.h"


Debug::Debug(void)
{
   _printmessages = false;
}

void Debug::messagesOn(void)
{
   _printmessages = true;
}

void Debug::messagesOff(void)
{
   _printmessages = false;
}

void Debug::message(char* themessage)
{
   if (_printmessages)
      printf("%s\n",themessage);
}

