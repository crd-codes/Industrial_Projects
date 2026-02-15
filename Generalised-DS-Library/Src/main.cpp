//////////////////////////////////////////////////////////////////////
//               Generalised Data Structure Library
//////////////////////////////////////////////////////////////////////

/*
---------------------------------------------------------------------------------------------------
Type                    Name of class for node              Name of class for functionality
---------------------------------------------------------------------------------------------------
Singly Linear           SinglyLLLnode                       SinglyLLL               Done
Singly Circular         SinglyCLLnode                       SinglyCLL               Done
Doubly Linear           DoublyLLLnode                       DoublyLLL               Done
Doubly Circular         DoublyCLLnode                       DoublyCLL               Done
Stack                   Stacknode                           Stack                   Done
Queue                   Queuenode                           Queue                   Done
---------------------------------------------------------------------------------------------------
*/

#include<iostream>
#include"generalised_ds_library.h"

using namespace std;

int main()
{
    SinglyLLL<int> *obj = new SinglyLLL<int>();

    int iRet = 0;

    obj->InsertFirst(51);
    obj->InsertFirst(21);
    obj->InsertFirst(11);

    obj->Display();

    iRet = obj->Count();
    cout<<"Number of node are :"<<iRet<<"\n";

    obj->InsertLast(101);
    obj->InsertLast(111);
    obj->InsertLast(121);

    obj->Display();

    iRet = obj->Count();
    cout<<"Number of node are :"<<iRet<<"\n";

    obj->DeleteFirst();

    obj->Display();
    
    iRet = obj->Count();
    cout<<"Number of node are :"<<iRet<<"\n";

    obj->DeleteLast();

    obj->Display();

    iRet = obj->Count();
    cout<<"Number of node are :"<<iRet<<"\n";

    obj->InsertAtPos(105, 4);

    obj->Display();

    iRet = obj->Count();
    cout<<"Number of node are :"<<iRet<<"\n";

    obj->DeleteAtPos(4);

    obj->Display();

    iRet = obj->Count();
    cout<<"Number of node are :"<<iRet<<"\n";

    delete obj;

    printf("----------------------------------------------------------\n");

////////////////////////////////////////////////////////////////////////////////////////

    SinglyCLL<int> scobj;

    scobj.InsertFirst(51);
    scobj.InsertFirst(21);
    scobj.InsertFirst(11);
    
    scobj.InsertLast(101);
    scobj.InsertLast(111);
    scobj.InsertLast(121);
    
    scobj.InsertAtPos(105,5);

    scobj.Display();
    
    iRet = scobj.Count();

    cout<<"Number of elements are : "<<iRet<<"\n";

    scobj.DeleteAtPos(5);

    scobj.Display();
    
    iRet = scobj.Count();

    cout<<"Number of elements are : "<<iRet<<"\n";

    scobj.DeleteFirst();

    scobj.Display();
    
    iRet = scobj.Count();

    cout<<"Number of elements are : "<<iRet<<"\n";

    scobj.DeleteLast();

    scobj.Display();
    
    iRet = scobj.Count();

    cout<<"Number of elements are : "<<iRet<<"\n";

    printf("----------------------------------------------------------\n");
    
//////////////////////////////////////////////////////////////////////

    DoublyLLL<char> *dobj = new DoublyLLL<char>();

    dobj->InsertFirst('A');
    dobj->InsertFirst('B');
    dobj->InsertFirst('C');

    dobj->Display();
    
    cout<<"Number of elements are "<<dobj->Count()<<"\n";

    dobj->InsertLast('X');
    dobj->InsertLast('Y');
    dobj->InsertLast('Z');

    dobj->Display();
    
    cout<<"Number of elements are "<<dobj->Count()<<"\n";

    dobj->DeleteFirst();
    
    dobj->Display();
    
    cout<<"Number of elements are "<<dobj->Count()<<"\n";


    dobj->DeleteLast();

    dobj->Display();
    
    cout<<"Number of elements are "<<dobj->Count()<<"\n";

    dobj->InsertAtPos('$', 4);

    dobj->Display();
    
    cout<<"Number of elements are "<<dobj->Count()<<"\n";

    dobj->DeleteAtPos(4);

    dobj->Display();
    
    cout<<"Number of elements are "<<dobj->Count()<<"\n";

    delete dobj;

    printf("----------------------------------------------------------\n");

////////////////////////////////////////////////////////////////////////////////////////

    DoublyCLL<int> dcobj;

    dcobj.InsertFirst(51);
    dcobj.InsertFirst(21);
    dcobj.InsertFirst(11);
    
    dcobj.InsertLast(101);
    dcobj.InsertLast(111);
    dcobj.InsertLast(121);
    
    dcobj.InsertAtPos(105,5);

    dcobj.Display();
    
    iRet = dcobj.Count();

    cout<<"Number of elements are : "<<iRet<<"\n";

    dcobj.DeleteAtPos(5);

    dcobj.Display();
    
    iRet = dcobj.Count();

    cout<<"Number of elements are : "<<iRet<<"\n";

    dcobj.DeleteFirst();

    dcobj.Display();
    
    iRet = dcobj.Count();

    cout<<"Number of elements are : "<<iRet<<"\n";

    dcobj.DeleteLast();

    dcobj.Display();
    
    iRet = dcobj.Count();

    cout<<"Number of elements are : "<<iRet<<"\n";

    printf("----------------------------------------------------------\n");

/////////////////////////////////////////////////////////////////////////////////////

    Stack<char> *sobj = new Stack<char>();

    sobj->push('a');
    sobj->push('b');
    sobj->push('c');
    sobj->push('d');

    sobj->Display();
    cout<<"Number of elements in Stack are : "<<sobj->Count()<<"\n";

    cout<<"Return value of peep is : "<<sobj->peep()<<"\n";
    sobj->Display();
    cout<<"Number of elements in Stack are : "<<sobj->Count()<<"\n";

    cout<<"Poped element is : "<<sobj->pop()<<"\n";

    sobj->Display();
    cout<<"Number of elements in Stack are : "<<sobj->Count()<<"\n";

    cout<<"Poped element is : "<<sobj->pop()<<"\n";

    sobj->Display();
    cout<<"Number of elements in Stack are : "<<sobj->Count()<<"\n";

    sobj->push('e');
    sobj->Display();
    cout<<"Number of elements in Stack are : "<<sobj->Count()<<"\n";
    
    delete sobj;

    printf("----------------------------------------------------------\n");

////////////////////////////////////////////////////////////////////////////////////////

    Queue<double> *qobj = new Queue<double>();

    qobj->enqueue(11.56789);
    qobj->enqueue(21.56789);
    qobj->enqueue(51.56789);
    qobj->enqueue(101.56789);

    qobj->Display();
    cout<<"Number of elements in queue are : "<<qobj->Count()<<"\n";

    cout<<"Removed element is : "<<qobj->dequeue()<<"\n";

    qobj->Display();
    cout<<"Number of elements in queue are : "<<qobj->Count()<<"\n";

    cout<<"Removed element is : "<<qobj->dequeue()<<"\n";

    qobj->Display();
    cout<<"Number of elements in queue are : "<<qobj->Count()<<"\n";

    qobj->enqueue(121.56789);

    qobj->Display();
    cout<<"Number of elements in queue are : "<<qobj->Count()<<"\n";
    
    delete qobj;

    printf("----------------------------------------------------------\n");

    return 0;
}
