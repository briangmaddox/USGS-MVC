
#include "List.h"

template<class T> List<T>::List(void)
{
   head = NULL;
   tail = NULL;
   current = NULL;
}
   
template<class T> T* List<T>::getFirst(void)
{
   if (head != NULL)
      return head->getData();
}

template<class T> T* List<T>::getNext(void)
{
}
template<class T> T* List<T>::getPrev(void)
{
}
template<class T> T* List<T>::getLast(void)
{
   if (tail != NULL)
      return tail->getData();
}
template<class T> bool List<T>::isFirst(void)
{
   if (current == head)
      return true;
   else
      return false;
}
template<class T> bool List<T>::isLast(void)
{
   if (current == tail)
      return true;
   else
      return false;
}
template<class T> bool List<T>::insertBefore(T* thedata)
{
   q = new ListNode();
   q->setData(thedata);

   if (current == NULL)
      {
         // First item in the list.
         head = p;
         tail = p;
         current = p;
      }
   else
      {
         p = current->getPrev();
         if (p == NULL)
            {
               // We're inserting before the head of the list.
               current->setPrev(q);
               q->setNext(current);
               head = q;
               current = q;
            }
         else
            {
               q->setNext(current);
               q->setPrev(p);
                              

}
template<class T> bool List<T>::insertAfter(T*)
{
}
template<class T> bool List<T>::deleteCurrent(T*)
{
}


