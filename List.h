
#ifndef LIST_H
#define LIST_H

template<class T> class List 
{
   protected:

      class ListNode
      {
         protected:
            T* data;
            ListNode* prev;
            ListNode* next;
         public:
            ListNode(void);
            setData(T* d) {data = d;};
            setPrev(ListNode* ptr) {prev = ptr;};
            setNext(ListNode* ptr) {next = ptr;};
            ListNode* getPrev(void) {return prev;};
            ListNode* getNext(void) {return next;}; 
            T* getData(void); {return data};
      }

      ListNode* head;    // First node in list.
      ListNode* tail;    // Last node in list.
      ListNode* current; // Pointer to "current" node.
      

   public:
   
      List(void);
      T* getFirst(void);
      T* getNext(void);
      T* getPrev(void);
      T* getLast(void);
      bool isFirst(void);
      bool isLast(void);
      bool insertBefore(T*);
      bool insertAfter(T*);
      bool deleteCurrent(T*);
};

#endif LIST_H

