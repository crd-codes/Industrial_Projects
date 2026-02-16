# 🗂️ Generalised Data Structure Library

## 📌 Project Overview

A **C++ template-based library** implementing common data structures with generic programming. Supports **Singly & Doubly Linked Lists (linear & circular), Stack, and Queue** with all basic operations. Designed for **learning, testing, and real-world applications**.

---
## 🛠️ Tech Stack

- **Language:** C++  
- **Concepts:** Object-Oriented Programming (OOP)
                Generic Programming using Templates
                Data Structures (Linked Lists, Stack, Queue)
                Dynamic Memory Management
---
## 🚀 Features

- **Singly Linear & Circular Linked List**  
  Insert, delete, and traverse at any position.
- **Doubly Linear & Circular Linked List**  
  Supports bidirectional traversal with insert/delete operations.
- **Stack**  
  Push, pop, peep, and display elements dynamically.
- **Queue**  
  Enqueue, dequeue, and display elements dynamically.
- **Generic Implementation**  
  Supports multiple data types (int, char, double, etc.) using templates.
- **Comprehensive Testing**  
  Sample `main()` demonstrates all operations for each data structure.
  
---



## 📂 Project Structure
```
Generalised-DS-Library/
│
├── Src/
│   ├── generalised_ds_library.h   → Header file with all data structure templates
│   └── main.cpp                   → Main file demonstrating usage
└── README.md
```
---

## ⚙️ Compilation & Execution

Linux / Ubuntu

g++ main.cpp -o myexe
./myexe

Windows (MinGW)

g++ main.cpp -o myexe
myexe

## 💻 Example Usage
```
#include <iostream>
#include "generalised_ds_library.h"
using namespace std;

int main() {
    // --- Singly Linear Linked List ---
    SinglyLLL<int> sll;
    sll.InsertFirst(11);
    sll.InsertFirst(21);
    sll.InsertLast(101);
    sll.InsertAtPos(105, 3);
    sll.Display();          // | 21 |->| 11 |->| 105 |->| 101 |->NULL
    cout << "Count: " << sll.Count() << endl;

    // --- Singly Circular Linked List ---
    SinglyCLL<int> scl;
    scl.InsertFirst(11); scl.InsertFirst(21); scl.InsertLast(101);
    scl.Display();          // | 21 | -> | 11 | -> | 101 | ->
    cout << "Count: " << scl.Count() << endl;

    // --- Doubly Linear Linked List ---
    DoublyLLL<char> dll;
    dll.InsertFirst('A'); dll.InsertFirst('B'); dll.InsertLast('X');
    dll.Display();          // NULL| B |<=>| A |<=>| X |<=>NuLL
    cout << "Count: " << dll.Count() << endl;

    // --- Stack ---
    Stack<char> st;
    st.push('a'); st.push('b'); st.push('c');
    st.Display();           // | c | | b | | a |
    cout << "Top element: " << st.peep() << endl;
    st.pop();
    st.Display();

    // --- Queue ---
    Queue<double> q;
    q.enqueue(11.5); q.enqueue(21.5); q.enqueue(51.5);
    q.Display();            // | 11.5| -| 21.5| -| 51.5| -
    cout << "Removed: " << q.dequeue() << endl;
    q.Display();

    return 0;
}
``` 

## 📈 Future Improvements

Implement Binary Search Tree (BST)

Add sorting and searching algorithms

---
## 👨‍💻 Author

CR Dugade
Aspiring Software Developer

* GitHub: https://github.com/crd-codes
* LinkedIn: https://linkedin.com/in/chakradhar-dugade
* Email : crofficialuse@gmail.com 

