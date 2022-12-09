#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace linkedlist;

template <class T> //test
class Node {
  public:
    T item;
    Node<T>* next;

    Node();
    Node(T item) {
      this->item = item;
      this->next = nullptr;
    }

    ~Node() {
      this->next = nullptr;
    }
      
};

