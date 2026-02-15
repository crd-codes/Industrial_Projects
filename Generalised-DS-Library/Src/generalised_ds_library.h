#ifndef GENERALISED_DS_LIBRARY_H
#define GENERALISED_DS_LIBRARY_H

#include<iostream>

//////////////////////////////////////////////////////////////////////
//          Singly Linear LL using Generic Approach
//////////////////////////////////////////////////////////////////////

#pragma pack(1)
template <class T>
class SinglyLLLnode
{
    public:
        T data;
        SinglyLLLnode<T> *next;

        SinglyLLLnode(T no)
        {
            this->data = no;
            this->next = NULL;
        }
};

template <class T>
class SinglyLLL
{
    private :
        SinglyLLLnode<T> * first;
        int iCountNode;

    public:    
        SinglyLLL();
        void InsertFirst(T);  
        void InsertLast(T);
        void DeleteFirst();
        void DeleteLast();
        void Display();                 
        int Count();
        void InsertAtPos(T, int);
        void DeleteAtPos(int);
};


template <class T>
SinglyLLL<T> :: SinglyLLL()
{
    std::cout<<"Singly Linear LL gets created\n";
    this->first = NULL;
    this->iCountNode = 0;
}

//////////////////////////////////////////////////////////////////////
//
//  function Name :     InsertFirst
//  Input         :     Data of node
//  Output        :     Nothing
//  Description   :     Used to insert node at first postion
//  Author        :     Chakradhar Rawaji Dugade
//  Date          :     06/01/2026
//
//////////////////////////////////////////////////////////////////////
template <class T>
void SinglyLLL<T> :: InsertFirst(T no)    
{
    SinglyLLLnode<T> * newn = NULL;

    newn = new SinglyLLLnode<T>(no);

    newn->next = this->first;     
    this->first = newn;           

    this->iCountNode++;
}

template <class T>
void SinglyLLL<T> :: InsertLast(T no)
{
    SinglyLLLnode<T> * newn = NULL;
    SinglyLLLnode<T> * temp = NULL;

    newn = new SinglyLLLnode<T>(no);

    if(this->iCountNode == 0)           
    {
        this->first = newn;
    }
    else
    {
        temp = this->first;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newn;                
    }

    this->iCountNode++;
}

template <class T>
void SinglyLLL<T> :: DeleteFirst()
{
    SinglyLLLnode<T> * temp = NULL;

    if(this->first == NULL)
    {
        return;
    }
    else if(this->first->next == NULL)  
    {
        delete this->first;
        this->first = NULL;
    }
    else
    {
        temp = this->first;

        this->first = this->first->next;
        delete temp;
    }

    this->iCountNode--;
}

template <class T>
void SinglyLLL<T> :: DeleteLast()
{
    SinglyLLLnode<T> * temp = NULL;

    if(this->first == NULL)
    {
        return;
    }
    else if(this->first->next == NULL)  
    {
        delete this->first;
        this->first = NULL;
    }
    else
    {
        temp = this->first;

        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }
        delete temp->next;

        temp->next = NULL;
    }

    this->iCountNode--;
}

template <class T>
void SinglyLLL<T> :: Display()                  
{
    SinglyLLLnode<T> * temp = NULL;
    int iCnt = 0;

    temp = this->first;

    for(iCnt = 1; iCnt <= this->iCountNode; iCnt++)  
    {
        std::cout<<"| "<<temp->data<<" |->";
        temp = temp->next;
    }
    std::cout<<"NULL\n";            
}

template <class T>
int SinglyLLL<T> :: Count()
{
    return this->iCountNode;
}

template <class T>
void SinglyLLL<T> :: InsertAtPos(T no, int pos)
{
    SinglyLLLnode<T> * temp = NULL;
    SinglyLLLnode<T> * newn = NULL;

    int iCnt = 0;

    if(pos < 1 || pos > this->iCountNode+1)
    {
        std::cout<<"Invalid Position\n";
        return;
    }

    if(pos == 1)
    {
        this->InsertFirst(no);
    }
    else if(pos == this->iCountNode+1)
    {
        this->InsertLast(no);
    }
    else
    {
        newn = new SinglyLLLnode<T>(no);

        temp = this->first;

        for(iCnt = 1; iCnt < pos-1; iCnt++)
        {
            temp = temp->next;
        }

        newn->next = temp->next;

        temp->next = newn;

        this->iCountNode++;
    }
}

template <class T>
void SinglyLLL<T> :: DeleteAtPos(int pos)
{
    SinglyLLLnode<T> * temp = NULL;
    SinglyLLLnode<T> * target = NULL;
    int iCnt = 0;

    if(pos < 1 || pos > this->iCountNode)
    {
        std::cout<<"Invalid position";
    }

    if(pos == 1)
    {
        this->DeleteFirst();
    }
    else if(pos == this->iCountNode)
    {
        this->DeleteLast();
    }
    else
    {
        temp = this->first;
        
        for(iCnt = 1; iCnt < pos-1; iCnt++)
        {
            temp = temp->next;
        }
        target = temp->next;

        temp->next = target->next;

        delete target;

        this->iCountNode--;
    }
}

//////////////////////////////////////////////////////////////////////
//          Singly Circular LL using Generic Approach
//////////////////////////////////////////////////////////////////////

#pragma pack(1)
template <class T>
struct SinglyCLLnode
{
    T data;
    struct SinglyCLLnode<T> *next;
};

template <class T>
class SinglyCLL
{
    private:
        struct SinglyCLLnode<T> * first;
        struct SinglyCLLnode<T> * last;
        int iCount;

    public:
        SinglyCLL();
        void InsertFirst(T no);
        void InsertLast(T no);
        void DeleteFirst();
        void DeleteLast();
        void Display();
        int Count();
        void DeleteAtPos(int pos);
        void InsertAtPos(T no, int pos);
};

template <class T>
SinglyCLL<T>::SinglyCLL()
{
    std::cout<<"Singly Circular LL gets created\n";

    this->first = NULL;
    this->last = NULL;
    this->iCount = 0;
}

template <class T>
void SinglyCLL<T>::InsertFirst(T no)
{
    struct SinglyCLLnode<T> * newn = NULL;

    newn = new struct SinglyCLLnode<T>;

    newn->data = no;
    newn->next = NULL;

    if(first == NULL && last == NULL)   // if(iCount == 0)
    {
        first = newn;
        last = newn;

        last->next = first;
    }
    else
    {
        newn->next = first;
        first = newn;

        last->next = first;
    }

    iCount++;
}

template <class T>
void SinglyCLL<T>::InsertLast(T no)
{
    struct SinglyCLLnode<T> * newn = NULL;

    newn = new struct SinglyCLLnode<T>;

    newn->data = no;
    newn->next = NULL;

    if(first == NULL && last == NULL)   // if(iCount == 0)
    {
        first = newn;
        last = newn;

        last->next = first;
    }
    else
    {
        last->next = newn;
        last = newn;

        last->next = first;
    }

    iCount++;
}

template <class T>
void SinglyCLL<T>::DeleteFirst()
{
    if(first == NULL && last == NULL)
    {
        return;
    }
    else if(first == last)
    {
        delete first;

        first = NULL;
        last = NULL;
    }
    else
    {
        first = first -> next;
        delete last->next;

        last->next = first;
    }
    iCount--;
}

template <class T>
void SinglyCLL<T>::DeleteLast()
{
    struct SinglyCLLnode<T> * temp = NULL;

    if(first == NULL && last == NULL)
    {
        return;
    }
    else if(first == last)
    {
        delete first;

        first = NULL;
        last = NULL;
    }
    else
    {
        temp = first;

        while(temp -> next != last)
        {
            temp = temp -> next;
        }

        delete last;
        last = temp;

        last->next = first;
    }
    iCount--;
}

template <class T>
void SinglyCLL<T>::Display()
{
    if(first == NULL && last == NULL)
    {
        return;
    }

    struct SinglyCLLnode<T> * temp = first;

    do
    {
        std::cout<<"| "<<temp->data<<" | -> ";
        temp = temp -> next;
    } while (temp != last ->next);
    
    std::cout<<"\n";
}

template <class T>
int SinglyCLL<T>::Count()
{
    return iCount;
}

template <class T>
void SinglyCLL<T>::DeleteAtPos(int pos)
{
    struct SinglyCLLnode<T> * temp = NULL;
    struct SinglyCLLnode<T> * target = NULL;
    
    int i = 0;
    
    if(pos < 1 || pos > iCount)
    {
        std::cout<<"Invalid position\n";
        return;
    }

    if(pos == 1)
    {
        DeleteFirst();
    }
    else if(pos == iCount)
    {
        DeleteLast();
    }
    else
    {
        temp = first;

        for(i = 1; i < pos-1; i++)
        {
            temp = temp -> next;
        }

        target = temp -> next;

        temp->next = target->next;
        delete target;

        iCount--;
    }
}

template <class T>
void SinglyCLL<T>::InsertAtPos(T no, int pos)
{
    struct SinglyCLLnode<T> * temp = NULL;
    struct SinglyCLLnode<T> * newn = NULL;

    int i = 0;

    if(pos < 1 || pos > iCount+1)
    {
        std::cout<<"Invalid position\n";
        return;
    }

    if(pos == 1)
    {
        InsertFirst(no);
    }
    else if(pos == iCount+1)
    {
        InsertLast(no);
    }
    else
    {
        newn = new struct SinglyCLLnode<T>;

        newn->data = no;
        newn->next = NULL;

        temp = first;

        for(i = 1; i < pos -1; i++)
        {
            temp = temp -> next;
        }

        newn->next = temp -> next;
        temp->next = newn;

        iCount++;
    }
} 

//////////////////////////////////////////////////////////////////////
//          Doubly Linear LL using Generic Approach
//////////////////////////////////////////////////////////////////////

#pragma pack(1)
template<class T>
class DoublyLLLnode
{
    public:
        T data;
        DoublyLLLnode *next;
        DoublyLLLnode  *prev;

        DoublyLLLnode(T no)
        {
            this->data = no;
            this->next = NULL;
            this->prev = NULL;
        }
};

template<class T>
class DoublyLLL
{
    private:
        DoublyLLLnode<T> * first;
        int iCount;

    public:    
        DoublyLLL();

        void InsertFirst(T);
        void InsertLast(T);
        void InsertAtPos(T,int);

        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int);

        void Display();
        int Count();
};

template<class T>
DoublyLLL<T> :: DoublyLLL()
{
    std::cout<<"Doubly Linked LL gets created\n";

    this->first = NULL;
    this->iCount = 0;
}

template<class T>
void DoublyLLL<T> :: InsertFirst(T no)
{
    DoublyLLLnode<T> *newn = NULL;

    newn = new DoublyLLLnode<T>(no);

    if(this->first == NULL)
    {
        this->first = newn;
    }
    else
    {
        newn->next = this->first;
        this->first->prev = newn;
        this->first = newn;
    }
    this->iCount++;
}

template<class T>
void DoublyLLL<T> :: InsertLast(T no)
{
    DoublyLLLnode<T> *newn = NULL;
    DoublyLLLnode<T> *temp = NULL;

    newn = new DoublyLLLnode<T>(no);

    if(this->first == NULL)
    {
        this->first = newn;
    }
    else
    {
        temp = this->first;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newn;
        newn->prev = temp;
    }
    this->iCount++;
}

template<class T>
void DoublyLLL<T> :: InsertAtPos(T no,int pos)
{
    DoublyLLLnode<T> *temp = NULL;
    DoublyLLLnode<T> *newn = NULL;

    int iCnt = 0;

    if((pos < 1) || (pos > this->iCount+1))   
    {
        std::cout<<"Invalid Position\n";
        return;
    }

    if(pos == 1)
    {
        this->InsertFirst(no);
    }
    else if(pos == this->iCount+1)
    {
        this->InsertLast(no);
    }
    else
    {
        newn = new DoublyLLLnode<T>(no);

        temp = this->first;

        for(iCnt = 1; iCnt < pos-1; iCnt++)
        {
            temp = temp->next;
        }
        newn->next = temp->next;
        temp->next->prev = newn;
        
        temp->next = newn;
        newn->prev = temp;

        this->iCount++;
    }
}

template<class T>
void DoublyLLL<T> :: DeleteFirst()
{
   if(this->first == NULL)                  
   {
        return;
   }
   else if(this->first->next == NULL)       
   {
        delete this->first;
        this->first = NULL;
   }
   else                                    
   {
        this->first = this->first->next;
        delete this->first->prev;
        this->first->prev = NULL;
   } 
   this->iCount--;
}

template<class T>
void DoublyLLL<T> :: DeleteLast()
{
    DoublyLLLnode<T> * temp = NULL;

   if(this->first == NULL)                  
   {
        return;
   }
   else if(this->first->next == NULL)       
   {
        delete this->first;
        this->first = NULL;
   }
   else                                     
   {
        temp = this->first;

        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
   } 
   this->iCount--; 
}

template<class T>
void DoublyLLL<T> :: DeleteAtPos(int pos)
{
    DoublyLLLnode<T> *temp = NULL;
    DoublyLLLnode<T>* target = NULL;
    int iCnt = 0;

    if((pos < 1) || (pos > this->iCount))   
    {
        std::cout<<"Invalid Position\n";
        return;
    }

    if(pos == 1)
    {
        this->DeleteFirst();
    }
    else if(pos == this->iCount)
    {
        this->DeleteLast();
    }
    else
    {
        temp = this->first;

        for(iCnt = 1; iCnt < pos-1; iCnt++)
        {
            temp = temp->next;
        }
        target = temp->next;
        temp->next = target->next;
        target->next->prev = temp;
        delete target;
        
        this->iCount--;
    }
}

template<class T>
void DoublyLLL<T> :: Display()
{
    DoublyLLLnode<T> *temp = NULL;
    temp = this->first;

    std::cout<<"\nNULL";
    while(temp != NULL)
    {
        std::cout<<"| "<<temp->data<<" |<=>";
        temp = temp->next;
    }
    std::cout<<"NuLL\n";
}

template<class T>
int DoublyLLL<T> :: Count()
{
    return this->iCount;
}

//////////////////////////////////////////////////////////////////////
//          Doubly Circular LL using Generic Approach
//////////////////////////////////////////////////////////////////////

template <class T>
struct DoublyCLLnode
{
    T data;
    struct DoublyCLLnode<T> *next;
    struct DoublyCLLnode<T> *prev;
};

template <class T>
class DoublyCLL
{
    private:
        struct DoublyCLLnode<T> * first;
        struct DoublyCLLnode<T> * last;
        int iCount;

    public:
        DoublyCLL();
        void InsertFirst(T no);
        void InsertLast(T no);
        void DeleteFirst();
        void DeleteLast();
        void Display();
        int Count();
        void DeleteAtPos(int pos);
        void InsertAtPos(T no, int pos);
};

template <class T>
DoublyCLL<T>::DoublyCLL()
{
    std::cout<<"Doubly Circular LL gets created\n";

    this->first = NULL;
    this->last = NULL;
    this->iCount = 0;
}

template <class T>
void DoublyCLL<T>::InsertFirst(T no)
{
    struct DoublyCLLnode<T> * newn = NULL;

    newn = new struct DoublyCLLnode<T>;

    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;

    if(first == NULL && last == NULL)   // if(iCount == 0)
    {
        first = newn;
        last = newn;

        first->prev = last;
        last->next = first;
    }
    else
    {
        newn->next = first;
        newn->prev = last;
        
        first->prev = newn;
        last->next = newn;

        first = newn;   
    }

    iCount++;
}

template <class T>
void DoublyCLL<T>::InsertLast(T no)
{
    struct DoublyCLLnode<T> * newn = NULL;

    newn = new struct DoublyCLLnode<T>;

    newn->data = no;
    newn->next = NULL;
    newn->prev = NULL;

    if(first == NULL && last == NULL)   // if(iCount == 0)
    {
        first = newn;
        last = newn;

        first->prev = last;
        last->next = first;
    }
    else
    {
        newn->prev = last;
        newn->next = first;
        last->next = newn;
        first->prev = newn;

        last = newn;
    }

    iCount++;
}

template <class T>
void DoublyCLL<T>::DeleteFirst()
{
    struct DoublyCLLnode<T> *temp = NULL;

    if(first == NULL && last == NULL)
    {
        return;
    }
    else if(first == last)
    {
        delete first;

        first = NULL;
        last = NULL;
    }
    else
    {
        temp = first;

        first = first->next;
        first->prev = last;
        last->next = first;

        delete temp;
        
    }
    iCount--;
}

template <class T>
void DoublyCLL<T>::DeleteLast()
{
    struct DoublyCLLnode<T> * temp = NULL;

    if(first == NULL && last == NULL)
    {
        return;
    }
    else if(first == last)
    {
        delete first;

        first = NULL;
        last = NULL;
    }
    else
    {
        temp = last;

        last = last->prev;
        last->next = first;
        first->prev = last;

        delete temp;
    }
    iCount--;
}

template <class T>
void DoublyCLL<T>::Display()
{
    if(first == NULL && last == NULL)
    {
        return;
    }

    struct DoublyCLLnode<T> * temp = first;

    do
    {
        std::cout<<"| "<<temp->data<<" | -> ";
        temp = temp -> next;
    } while (temp != last -> next);
    
    std::cout<<"\n";
}

template <class T>
int DoublyCLL<T>::Count()
{
    return iCount;
}

template <class T>
void DoublyCLL<T>::DeleteAtPos(int pos)
{
    struct DoublyCLLnode<T> * temp = NULL;
    struct DoublyCLLnode<T> * target = NULL;
    
    int i = 0;
    
    if(pos < 1 || pos > iCount)
    {
        std::cout<<"Invalid position\n";
        return;
    }

    if(pos == 1)
    {
        DeleteFirst();
    }
    else if(pos == iCount)
    {
        DeleteLast();
    }
    else
    {
        temp = first;

        for(i = 1; i < pos-1; i++)
        {
            temp = temp -> next;
        }

        target = temp -> next;

        temp->next = target->next;
        target->next->prev = temp; 
        delete target;

        iCount--;
    }
}

template <class T>
void DoublyCLL<T>::InsertAtPos(T no, int pos)
{
    struct DoublyCLLnode<T> * temp = NULL;
    struct DoublyCLLnode<T> * newn = NULL;

    int i = 0;

    if(pos < 1 || pos > iCount+1)
    {
        std::cout<<"Invalid position\n";
        return;
    }

    if(pos == 1)
    {
        InsertFirst(no);
    }
    else if(pos == iCount+1)
    {
        InsertLast(no);
    }
    else
    {
        newn = new struct DoublyCLLnode<T>;

        newn->data = no;
        newn->next = NULL;
        newn->prev = NULL;

        temp = first;

        for(i = 1; i < pos -1; i++)
        {
            temp = temp -> next;
        }

        newn->next = temp->next;
        newn->prev = temp;
        temp->next->prev = newn;
        temp->next = newn;

        iCount++;
    }
} 

//////////////////////////////////////////////////////////////////////
//                  Stack using Generic Approach
//////////////////////////////////////////////////////////////////////

#pragma pack(1)
template<class T>
class Stacknode
{
    public:
        T data;
        Stacknode<T> *next;

        Stacknode(T no)
        {
            this->data = no;
            this->next = NULL;
        }
};

template<class T>
class Stack
{
    private:
        Stacknode<T> *first;
        int iCount;

    public:
        Stack();

        void push(T);     
        T pop();          
        T peep();         
        void Display();
        int Count();
};

template<class T>
Stack<T> :: Stack()
{
    std::cout<<"Stack gets created successfully\n";

    this->first = NULL;
    this->iCount = 0;
}

template<class T>
void Stack<T> :: push(T no)
{
    Stacknode<T> *newn = NULL;

    newn = new Stacknode<T>(no);

    newn->next = this->first;
    this->first = newn;

    this->iCount++;
}    

template<class T>
T Stack<T> :: pop()
{
    T Value = 0;
    Stacknode<T> *temp = this->first;

    if(this->first == NULL)
    {
        std::cout<<"Stack is empty\n";
        return -1;
    }

    Value = this->first->data;
    
    this->first = this->first->next;
    delete temp;

    this->iCount--;

    return Value;
}          

template<class T>
T Stack<T> :: peep()
{
    T Value = 0;

    if(this->first == NULL)
    {
        std::cout<<"Stack is empty\n";
        return -1;
    }

    Value = this->first->data;
        
    return Value;
}   
   
template<class T>
void Stack<T> :: Display()
{
    Stacknode<T> *temp = this->first;

    if(this->first == NULL)
    {
        std::cout<<"Stack is empty\n";
        return;
    }

    while(temp != NULL)
    {
        std::cout<<"|\t"<<temp->data<<"\t|\n";
        temp = temp->next;
    }
}

template<class T>
int Stack<T> :: Count()
{
    return this->iCount;
}

//////////////////////////////////////////////////////////////////////
//                  Queue using Generic Approach
//////////////////////////////////////////////////////////////////////

#pragma pack(1)
template <class T>
class Queuenode
{
    public:
        T data;
        Queuenode<T> *next;

        Queuenode(T no)
        {
            this->data = no;
            this->next = NULL;
        }
};

template <class T>
class Queue
{
    private:
        Queuenode<T> *first;
        Queuenode<T> *last;

        int iCount;

    public:
        Queue();
        void enqueue(T);      
        T dequeue();          
        void Display();
        int Count();
};

template <class T>
Queue<T> :: Queue()
{
    std::cout<<"Queue gets created successfully\n";

    this->first = NULL;
    this->last = NULL;

    this->iCount = 0;
}

template <class T>
void Queue<T> :: enqueue(T no)
{
    Queuenode<T> *newn = NULL;

    newn = new Queuenode<T>(no);

    if(this->first == NULL && this->last == NULL)
    {
        this->first = newn;
        this->last = newn;
    }
    else
    {
        this->last->next = newn;   
        this->last = this->last->next;    // or this->last = newn;
    }
    
    this->iCount++;
}    

template <class T>
T Queue<T> :: dequeue()
{
    T Value = 0;
    Queuenode<T> *temp = this->first;

    if(this->first == NULL && this->last == NULL)
    {
        std::cout<<"Queue is empty\n";
        return -1;
    }

    Value = this->first->data;
    
    this->first = this->first->next;
    delete temp;

    if(this->first == NULL)               // If after deletion queue becomes empty, update last pointer to NULL
    {
        this->last = NULL;
    }

    this->iCount--;

    return Value;
}            
 
template <class T>
void Queue<T> :: Display()
{
    Queuenode<T> *temp = this->first;

    if(this->first == NULL && this->last == NULL)
    {
        std::cout<<"Queue is empty\n";
        return;
    }

    while(temp != NULL)
    {
        std::cout<<"| "<<temp->data<<"| -";
        temp = temp->next;
    }
    std::cout<<"\n";
}

template <class T>
int Queue<T> :: Count()
{
    return this->iCount;
}

//////////////////////////////// End of Library//////////////////////////////////////

#endif
