#include <stdlib.h>
#include "mvc/LinkedList.h"

//
// ListElement class methods.
//
ListElement::ListElement(void)
{
   _prev = NULL;
   _next = NULL;
}

void ListElement::setPrev(ListElement* p)
{
   _prev = p;
}

ListElement* ListElement::getPrev(void)
{
   return _prev;
}


void ListElement::setNext(ListElement* p)
{
   _next = p;
}

ListElement* ListElement::getNext(void)
{
   return _next;
}



//
// LinkedList class methods.
//

LinkedList::LinkedList(void)
{
   _head = NULL;
   _tail = NULL;
   _curelement = NULL;
}


bool LinkedList::addElementFirst(ListElement* p)
{
   // Adds element p as the new first element in the list.

   p->setPrev(NULL);
   p->setNext(_head);

   if (_head != NULL)
      _head->setPrev(p);
   else
      _tail = p;
   _head = p;

   return true;
}

bool LinkedList::addElementLast(ListElement* p)
{
   // Adds element p as the new end of the list.

   p->setNext(NULL);
   p->setPrev(_tail);

   if (_tail != NULL)
      _tail->setNext(p);
   else
      _head = p;
   _tail = p;

   return true;
}

bool LinkedList::addElementBefore(ListElement* p, ListElement* q)
{
   // Adds q before element p

   if (p->getPrev() == NULL)
      _head = q;
   else
      (p->getPrev())->setNext(q);

   q->setPrev(p->getPrev());
   q->setNext(p);

   p->setPrev(q);
}

bool LinkedList::addElementAfter(ListElement* p, ListElement* q)
{
   // Adds q after element p

   if (p->getNext() == NULL)
      _tail = q;
   else
      (p->getNext())->setPrev(q);

   q->setNext(p->getNext());
   q->setPrev(p);

   p->setNext(q);
}

bool LinkedList::deleteElement(ListElement* p)
{
   // Delete the element pointed to by p.
   // We don't actually *delete* the object since we don't own it. We
   // just remove it from the list.

   if (p == NULL)
      return false;

   if (p->getPrev() == NULL)
      _head = p->getNext();
   else
      (p->getPrev())->setNext(p->getNext());

   if (p->getNext() == NULL)
      _tail = p->getPrev();
   else
      (p->getNext())->setPrev(p->getPrev());

   p->setPrev(NULL);
   p->setNext(NULL);         

}

ListElement* LinkedList::getFirstElement(void)
{
   _curelement = _head;
   return _head;
}

ListElement* LinkedList::getNextElement(void)
{
   if (_curelement != NULL)
      _curelement = _curelement->getNext();

   return _curelement;
}

