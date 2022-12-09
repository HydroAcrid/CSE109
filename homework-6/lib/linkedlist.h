#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "llnode.h"

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

namespace linkedlist {
template <class T>
class LinkedList {

  private:
    linkedlist::Node<T>* head;
    linkedlist::Node<T>* tail;

  public:
    size_t length;
    LinkedList();
    ~LinkedList();
    size_t insertAtTail(T item);
    size_t insertAtHead(T item);
    size_t insertAtIndex(size_t index, T item);
    T removeTail();
    T removeHead();
    T removeAtIndex(size_t index);
    T itemAtIndex(size_t index);
    void printList();

  };

}

template <class T>
linkedlist::LinkedList<T>::LinkedList() { //Constructor for linkedlist
  this->head = nullptr;
  this->tail = nullptr;
  this->length = 0;
  }

template <class T>
linkedlist::LinkedList<T>::~LinkedList() { //Destructor for linkedlist 
  Node<T>* tempNode = this->head;
  Node<T>* traverseNode; 

  while(tempNode != NULL) {
      traverseNode = tempNode;
      tempNode = tempNode->next;
      delete traverseNode;
    }
  }

template <class T>
size_t linkedlist::LinkedList<T>::insertAtTail(T item) {
  //Creates the Node for tail
    Node<T>* tempNode = new Node<T>(item); 
    if(tempNode == NULL) {
      return 1; 
    }

    //if list is empty.
    if(this->head == NULL) {
      this->head = tempNode;
      this->tail = tempNode;
    } else {
      this->tail->next = tempNode;
      this->tail = this->tail->next;
    }	
    return 0;	
  
  }

template <class T>
size_t linkedlist::LinkedList<T>::insertAtHead(T item) {
  //Creates the Node for head
  Node<T>* tempNode = new Node<T>(item); 
  if(tempNode == NULL) {
    return 1; 
  }

  //if list is empty.
  if(this->head == NULL) {
    this->head = tempNode;
    this->tail = tempNode;
  } else {
    tempNode->next = this->head;
    this->head = tempNode;
  }		
  return 0;
}

template <class T>
size_t linkedlist::LinkedList<T>::insertAtIndex(size_t index, T item) {
  //Creates the Node for inserting
  Node<T>* insrtNode = new Node<T>(item); 
  if(insrtNode == NULL) {
    return 0; 
  }

  int i = 0;
  Node<T>* prevNode = new Node<T>(item);
  Node<T>* tempNode = new Node<T>(item);
  tempNode->head = this->head;   

  while (tempNode != NULL) {
    if (i == index) {
      prevNode->next = insrtNode;
      insrtNode->next = tempNode;
      return 0;
    } else if (i > index) {
      return 0;
    } else {
      i++;
      prevNode = tempNode;
      tempNode = tempNode->next;
    }
  }	
  return	0; 
    }

template <class T>
T linkedlist::LinkedList<T>::removeTail() {
  Node<T>* tempNode = new Node<T>();
  int i = 0;

  if(this->tail == NULL) {	
    // List is Empty	
    return NULL;
  }
  else {
    tempNode = this->head;

  // Iterate to the end of the list
  while(tempNode->next != this->tail) { 
    tempNode = tempNode->next;
  }

  Node<T>* tailNode = this->tail;
  this->tail = tempNode;
  this->tail->next = NULL;	
  free(tailNode);	
  }	

  }

template <class T>
T linkedlist::LinkedList<T>::removeHead() {
  if(this->head == NULL) {	
    // List is Empty	
    return NULL;
  } else {
    Node<T>* headNode = this->head;
    this->head = this->head->next;	
    free(headNode);	
  }	

  }

template <class T>
T linkedlist::LinkedList<T>::removeAtIndex(size_t index) {
  int i = 0;
  Node<T>* prev = new Node<T>();
  Node<T>* node = this->head;
  while (node != NULL) {
    if (i == index) {
      prev->next = node->next;
      free(node);
    } else if (i > index) {
        // List is too short
    return NULL;
    } else {
      i++;
      prev = node;
      node = node->next;
    }
  }	
}

template <class T>
void linkedlist::LinkedList<T>::printList() {
    Node<T>* tempNode = new Node<T>();

    if(this->head == nullptr) {
      printf("\nEmpty List");
      return;
    }

    tempNode = this->head;
    printf("\nList: \n\n\t"); 
    while(node != NULL) {
      printf("[ %x ]", tempNode->item);

      // Move to the next node
      tempNode = tempNode->next;

      if(tempNode !=NULL) {
        printf("-->");
      }
    }
    printf("\n\n");


  }




#endif

