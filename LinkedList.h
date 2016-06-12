#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class ListElement
{
   protected:

      ListElement* _prev;
      ListElement* _next;

   public:

      ListElement(void);

      void setPrev(ListElement* p);
      ListElement* getPrev(void);

      void setNext(ListElement* p);
      ListElement* getNext(void);
};

class LinkedList : public ListElement
{
   protected:
      
      ListElement* _head;        // Points to first element in list.
      ListElement* _tail;        // Points to last element in list.
      ListElement* _curelement;

   public:

      LinkedList(void);

      bool addElementFirst(ListElement* p);
         // Adds element p as the new first element in the list.
      bool addElementLast(ListElement* p);
         // Adds element p as the new end of the list.
      bool addElementBefore(ListElement* p, ListElement* q);
         // Adds q before element p
      bool addElementAfter(ListElement* p, ListElement* q);
         // Adds q after element p
      bool deleteElement(ListElement* p);

      ListElement* getFirstElement(void);
      ListElement* getNextElement(void);
};

#endif // LINKEDLIST_H