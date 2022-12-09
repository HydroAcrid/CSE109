#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "linkedlist.h"


template <class T>
class HashSet {
  private:
    // The backbone of the hash set. This is an array of Linked List pointers.
    LinkedList<T>** array;

    // The number of buckets in the array
    size_t size; 

    // Generate a prehash for an item with a given size
    unsigned long prehash(T item);

  public:
    HashSet(size_t size);
    ~HashSet();
    unsigned long hash(T item);
    bool insert(T item);
    bool remove(T item);
    bool contains(T item);
    void resize(size_t new_size);
    size_t len();
    size_t capacity();
    void print();
    };


    // Initialize an empty hash set, where size is the number of buckets in the array
    template<class T>
    HashSet<T>::HashSet(size_t size) {
        this->size = size; 
        this->array = new linkedlist::LinkedList<T>*[this->size];

        for(int i = 0; i < size; i++) {
            this->array[i] = new linkedlist::LinkedList<T>();
        }
    }

    // Free all memory allocated by the hash set
    template<class T>
    HashSet<T>::~HashSet() {
        delete(array);
    }

    // Modifies this prehash function to work with a template type T instead of a char*
    template<class T>
    unsigned long HashSet<T>::prehash(T item) {
        unsigned long h = 5381;
        int c;
            while (c = item++) { 
                h = ((h << 5) + h) + c;
            }
        return h;
    }

    // Hash an unsigned long into an index that fits into a hash set
    //The use of modulo allows the hash item to fit into the index
    template<class T>
    unsigned long HashSet<T>::hash(T item) {
        return item % size; 
    }

    // Insert item in the set. Return true if the item was inserted, false if it wasn't (i.e. it was already in the set)
    // Recalculate the load factor after each successful insert (round to nearest whole number).
    // If the load factor exceeds 70 after insert, resize the table to hold twice the number of buckets.
    template<class T>
    bool HashSet<T>::insert(T item) {
        //Identify if the hash item already exists
        size_t index = hash(item);
        if(contains(hash)) {
            return false;
        }
        
        //Inserts item into set 
        array[index]->insertAtTail(item);

        //Checks if the load factor is greater than 70%. If so, resizes it. 
        //Because capacity calcs. remaining spots open, subtracting size and 
        //dividng size by it gives the percentage
        int sizeCheck = (10* ((size-capacity())/(float)size));
        if(sizeCheck >= 7) {
            resize(size*2);
        }
        return true;
        
    }

    // Remove an item from the set. Return true if it was removed, false if it wasn't (i.e. it wasn't in the set to begin with)
    template<class T>
    bool HashSet<T>::remove(T item) {
        //Use of hash to get index. I use this to get the length of the L.L.
        int index = hash(item);
        int arrayLen = array[index]->length;

        for(int i = 0; i < arrayLen; i++) {
            //Finds the item and deletes it. If no item is found, returns false.
            if(array[index]->itemAtIndex(i) == item) {
                this->array[index] -> removeAtIndex(i);
                return true;
            }
        }
        return false;
        
    }

    // Return true if the item exists in the set, false otherwise
    template<class T>
    bool HashSet<T>::contains(T item) {
        //Use of hash to get index. I use this to get the length of the L.L.
        int index = hash(item);
        int arrayLen = array[index]->length;

        for(int i = 0; i < arrayLen; i++) {
             //Finds the item. If no item is found, returns false.
            if(array[index]->itemAtIndex(i) == item) {
                return true;
            }
        }
        return false;

    }

    // Resize the underlying table to the given size. Recalculate the load factor after resize
    template <class T>
    void HashSet<T>::resize(size_t new_size) {
        //changes the size and stores the old size 
        size_t prevSize = size;
        this->size = new_size;

        //Creates a new array 
        linkedlist::LinkedList<T>** newArray = malloc(sizeof(linkedlist::LinkedList<T>*) *size);
        
        //Fills the new array with L.L.
        for(int i = 0; i < size; i++) {
            newArray[i] = new linkedlist::LinkedList<T>(); 
        }

        //Copies all old hashset elements and places them into new hashset 
        for(int i = 0; i < prevSize; i++) {
            linkedlist::LinkedList<T>* nextArray = array[i];
            
            //If the head is null, fills the array with the old elements until no longer null 
            if(nextArray->head != nullptr) {
                linkedlist::Node<T>* tempNode = nextArray->head;
                while(tempNode != nullptr) {
                    size_t index = hash(tempNode->item);
                    newArray[index]->insertAtTail(tempNode->item);
                    tempNode = tempNode->next;
                }
            }
        }

        this->array = newArray;

    }

    // Returns the number of items in the hash set
    template<class T>
    size_t HashSet<T>::len() {
        size_t count = 0;
        //Goes through each array in the LinkedList
        for(int i = 0; i < size; i++) {
            //Goes through each item in the LinkedList. Increments count each time 
            for(int j = 0; j < array[i]; j++) {
                count++;

            }
        }

        return count;

    }

    // Returns the number of buckets that can be filled before reallocating
    template<class T>
    size_t HashSet<T>::capacity() {
        size_t count = 0;
        //Goes through each array in the LinkedList. Increments count when the item is null 
        for(int i = 0; i < size; i++) {
             
           if(array[i]->head == nullptr) {
               count++;
           }
        }

        return count;
    }

    // Print Table. You can do this in a way that helps you implement your hash set.
    template<class T>
    void HashSet<T>::print() {
        for(int i = 0; i < size; i++) {
            array[i]->printList(); 
            
        }
        printf("%s\n\n", "");
    }





