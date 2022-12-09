#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void printList(List* list) {
	Node* node;

  	// Handle an empty node. Just print a message.
	if(list->head == NULL) {
		printf("\nEmpty List");
		return;
	}
	
  	// Start with the head.
	node = (Node*) list->head;

	printf("\nList: \n\n\t"); 
	while(node != NULL) {
		printf("[ %x ]", node->item);

		// Move to the next node
		node = (Node*) node->next;

		if(node !=NULL) {
			printf("-->");
		}
	}
	printf("\n\n");
}
// Initialize an empty list
void initList(List* list_pointer) {
	list_pointer->head = NULL;
	list_pointer->tail = NULL;
}	

// Creates Node and allocates memory to it 
Node* createNode(void* item) {
	Node* node;
	node = (Node*)malloc(sizeof(Node));
	if(node == NULL) {
		return NULL; 
	}
	node->item = item;
	node -> next = NULL;
	return node; 
}

// Insert new item at the end of list.
int insertAtTail(List* list_pointer, void* item) {
	
	//Creates node at the end of the list
	Node* nodeEnd = createNode(item);
	if(nodeEnd == NULL) {
		return 1;
	}

	//
	if(list_pointer->head = NULL){
		list_pointer->head = nodeEnd;
		list_pointer->tail = nodeEnd;
		return 0;
	}

	//Adds the nodeEnd node to the end of tail node 
	list_pointer->tail->next = nodeEnd;
	list_pointer->tail = list_pointer->tail->next;

	return 0;
}

// Insert item at start of the list.
int insertAtHead(List* list_pointer, void* item) {
	//Creates node at the start of the list
	Node* nodeStart = createNode(item);
	if(nodeStart == NULL) {
		return 1;
	}

	//
	if(list_pointer->head = NULL){
		list_pointer->head = nodeStart;
		list_pointer->tail = nodeStart;
		return 0;
	}

	//Link the nod-e to the List. 
	nodeStart->next = list_pointer->head;

	//Inserts item to the head 
	list_pointer->head = nodeStart;
	
	return 0;
	
}

// Insert item at a specified index.
int insertAtIndex(List* list_pointer, int index, void* item) {
	//
	if (index == 0) {
		return insertAtHead(list_pointer, item);
	}

	//Creates node at the start of the list that will iterate 
	Node* nodeIndex = list_pointer->head; 
	Node* nodePrev = list_pointer->head;

	//New node that is being created 
	Node* nodeInsert = createNode(item);
	if(nodeInsert == NULL) {
		return 1;
	}
	
	//Iterates across the linked list "n" times 
	for(int i = 0; i < index; i++) {
		nodeIndex = nodeIndex->next;
	}

	//Nodeprev iterates until just before it reach nodeIndex node 
	while(nodePrev->next != nodeIndex) {
		nodePrev = nodePrev->next;
	}

	if (nodePrev == list_pointer->tail) {
		return insertAtTail(list_pointer, item);
	}

	//Connects nodePrev to nodeInsert 
	nodePrev->next = nodeInsert; 

	//Connects nodeInsert next to nodeIndex
	nodeInsert->next = nodeIndex; 

	return 0;

	
}

// Remove item from the end of list and return a reference to it
void* removeTail(List* list_pointer) {
	
	//Creates a node at the head and a reference point to the last node 
	Node* nodeTraverse = list_pointer->head;
	if(list_pointer->head = NULL){
		return NULL;
	}
	else if (list_pointer->head == list_pointer->tail) {
		void* t = list_pointer->head->item;
		list_pointer->head = NULL;
		list_pointer->tail = NULL;
		return t;
	}

	void* temp = list_pointer->tail->item;

	//Iterates through the list to reach the end and stops at the final node "next" 
	while(nodeTraverse->next != list_pointer->tail) {
		nodeTraverse = nodeTraverse->next;
	}

	//Makes the second to last node the new tail 
	list_pointer->tail = nodeTraverse; 

	//Makes this node return null
	nodeTraverse->next = NULL;

	//Returns reference point 
	return temp;
}

// Remove item from start of list and return a reference to it
void* removeHead(List* list_pointer) {
	//Created node that is the same value as head and makes a reference clone to the current head 
	Node* headRemove = list_pointer->head;
	if(list_pointer->head = NULL){
		return NULL;
	}
	else if (list_pointer->head == list_pointer->tail) {
		void* t = list_pointer->head->item;
		list_pointer->head = NULL;
		list_pointer->tail = NULL;
		return t;
	}

	void* temp = list_pointer->head->item;

	//Replaces the value of head with next node (null)  
	list_pointer->head = list_pointer->head->next;

	//Severs connection from original head to new head
	headRemove->next = NULL;

	return temp;
}

// Insert item at a specified index and return a reference to it
void* removeAtIndex(List* list_pointer, int index) {
	//Creates node that iterates across the linked list 
	Node* nodeNext = list_pointer->head; 
	Node* nodePrev = list_pointer->head; 

	if(list_pointer->head = NULL){
		return NULL;
	}

	//First Index 
	if(index == 0) {
		return removeHead(list_pointer);
	}

	//Iterates "n" times 
	for(int i = 0; i < index && nodeNext != NULL; i++) {
		nodeNext = nodeNext->next;
	}

	if (nodeNext == NULL) {
		return NULL;
	}
	
	//Nodeprev iterates until just before it reach nodenext node 
	while(nodePrev->next != nodeNext) {
		nodePrev = nodePrev->next;
	}

	if (nodePrev == list_pointer->tail) {
		return removeTail(list_pointer);
	}

	//NodePrev connects to the node after nodeNext 
	nodePrev->next = nodeNext->next;
	
	//Severs connection to node next to nodeNext
	nodeNext->next = NULL;

	//Returns reference item
	return nodeNext->item;

}

// Return item at index
void* itemAtIndex(List* list_pointer, int index) {
	//Creates node that iterates across the linked list 
	Node* nodeNext = list_pointer->head;
	if(list_pointer->head = NULL){
		return NULL;
	}

	//Iterates across index
	for(int i = 0; i < index; i++) {
		nodeNext = nodeNext->next;
	}

	//Returns reference point
	return nodeNext->item;
}


