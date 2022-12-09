# CSE 109 - Systems Software - Fall 2022

# Homework 6

**Due Date: 10/24/2022 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per function.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

There are two parts to this assignment. In Part 1, you will convert you linked list data structure that you implemented in Homework 4 from C to C++. In Part 2, you will implement a hash set in C++.

## Part 1 - Linked List Conversion

Convert your linked list data structure from Homework 4 to a C++ class. If you didn't successfully complete Homework 4, you can use the [posted solution](https://gitlab.com/lehigh-cse-109/spring-2021/assignments/homework-4/-/tree/solutions) as the basis for this part of the assignment. Your linked list class should be a template class so that it can hold items of any type. You should also convert your Node struct to a Node template class.

The Node class should have the following methods:

```c++
template <class T>
class Node {
  public:
    T item
    linkedlist::Node<T>* next;
    Node();
    ~Node();
};
```

You can add any other methods and fields necessary to make your Node work. You can implement these functions in a header file called `llnode.h` inside of the `lib` directory. Make sure they exist wihtin the `LinkedList` namespace though.

The Linked List class should have the following methods:

```c++
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
};
```

You can add any other methods and fields necessary to make your LinkedList work. You can write all of this code in a header file called `linkedlist.h` inside of the lib directory. You should add some template implementations for common types, like `int`, `char`, etc. Write a Makefile inside of this directory that has the following directives:

- static - build a static library `liblinkedlist.a`, put it in `lib/build/lib/release`. Put object files in `lib/build/objects`
- shared - build a shared library `liblinkedlist.so`, put it in `lib/build/lib/release`. Put object files in `lib/build/objects`
- debug - build a shared library with debug symbols, put it in `lib/build/lib/debug`. Put object files in `lib/build/objects`
- clean - remove all build artifacts.

## Part 2 - Hash Set

In this part you will implement a hash set data structure in C++. The core of the hashset is an array of linked list pointers. The type of the table is a `LinkedList<T>**`. The first star indicates it's a pointer to an array, the second star indicates each array element holds a List pointer. The Hashset also holds its size, and the current load factor. The load factor will be recalculated on each insert, and if the value exceeds a threshold (70% filled buckets) then the underlying table array will be resized. This will involve allocating a new, larger array, rehashing all of the elements into this new array, then freeing the old array and its constituent linked lists.

The Hashset struct is declared in `hashset.h`, along with a number of functions you will need to implement.

```c++

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
    // Initialize an empty hash set, where size is the number of buckets in the array
    HashSet(size_t size);

    // Free all memory allocated by the hash set
    ~HashSet();

    // Hash an unsigned long into an index that fits into a hash set
    unsigned long hash(T item);

    // Insert item in the set. Return true if the item was inserted, false if it wasn't (i.e. it was already in the set)
    // Recalculate the load factor after each successful insert (round to nearest whole number).
    // If the load factor exceeds 70 after insert, resize the table to hold twice the number of buckets.
    bool insert(T item);

    // Remove an item from the set. Return true if it was removed, false if it wasn't (i.e. it wasn't in the set to begin with)
    bool remove(T item);

    // Return true if the item exists in the set, false otherwise
    bool contains(T item);

    // Resize the underlying table to the given size. Recalculate the load factor after resize
    void resize(size_t new_size);

    // Returns the number of items in the hash set
    size_t len();

    // Returns the number of buckets that can be filled before reallocating
    size_t capacity();

    // Print Table. You can do this in a way that helps you implement your hash set.
    void print();

};
```

You should add some template implementations for common types, like `int`, `char`, etc. Write a Makefile inside of the project root that has the following directives:

- static - build a static library `libhashset.a`, put it in `build/lib/release`. Put object files in `build/objects`
- shared - build a shared library `libhashset.so`, put it in `build/lib/release`. Put object files in `build/objects`
- debug - build a shared library with debug symbols, put it in `build/lib/debug`. Put object files in `build/objects`
- clean - remove all build artifacts.
- install - move the shared library to `/usr/lib`

## Build Instructions

Write build instructions here. Explain to the user all the steps necessary to build this project including:

- What software (including versions) are needed?
- What system architectures and operating systems are supported?
- What commands need to be entered to build the project?

BUILD INSTRUCTIONS
- Hello, welcome to Kevin's LinkedList/HashSet program! 
- Warning: This program was made on MacOS 12.6 and thus will have MacOS specficiations for utilizing the program.
- The software you need to run this program includes:
-   GNU(version 12.2)
-   C++(version C++20)
-   HomeBrew(version 3.6.7)
-   XCode(version 10.13.6 or higher) 
- The supporting operating system is MacOS 12.6 or higher
- The supporting system architecture is arm64 
- These are the commands that need to be inputted in the terminal to build this project:
-   make static
-   make shared
-   make debug 
-   make install
- To reset the project, input "make clean" 

## Usage

Write usage instructions here. Explain to the user how they can integrate your library into their project. Usage instructions might include:

- What the user should #include into their project and where.
- An example command of how the user might build their project to link to your library.
- How to create a hash set using your library.
- How to use the hash set.
- How to clean up the hash set to avoid leaking memory.

USAGE
Here is what you should #include in your project:
- For HashSet, include in your main file:
-   #include "hashset.h"
-   #include "stdbool.h"
-   #include <stdio.h>
-   #include <stdlib.h> 
- To create a HashSet, do this:
-   EX: HashSet<"var type"> hs("size"); 
- These are the HashSet functions you can use:
-   unsigned long hash(T item);
-   bool insert(T item);
-   bool remove(T item);
-   bool contains(T item);
-   void resize(size_t new_size);
-   size_t len();
-   size_t capacity();
-   void print();
- To clean the HashSet, you can use the remove(T item) function. To avoid leaking memory, you can also use the resize(size_t new_size) function. 



## Examples

Write two examples demonstrating how to use your hash set library. These example should be complete in the sense that the user can just copy and paste them into their code and everything should work as long as they follow the build and usage instructions you gave them.

EXAMPLE 1: 
#include "hashset.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>


int test(char* label, bool a, bool b) {
  printf("%s: ", label);
  if (a==b) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed. lhs=%x, rhs= %x\n",a,b);
    exit(1);
  }
}

int main() {

	HashSet<int> hs(10);

  int a = 0x12ab345;
  int b = 0xfeed425;
  int c = 0xabcd38;
  int d = 0x1235698;
  int e = 0x2c374;
  int f = 0xa0f8982;
  int g = 0x053eba;
  int h = 0x61c2f5e;
  int i = 0xe0295f2;
  int j = 0x5e700eaa;
  int k = 0xe75bf1;
  int l = 0x6baa9bb;
  int m = 0x8b1390a;
  int n = 0x59dd1;
  int o = 0xfc32;
  int p = 0xa9d89d8;
  int q = 0x5b2c9e;
  int r = 0x2431e3;
  int s = 0x1910a;
  int t = 0x72;

	hs.insert(a); // insert an item into the table

 	test("Test1", hs.contains(a), true); // find the item
  test("Test2", hs.insert(a), false); // can't insert the same item twice

  hs.insert(b);
  hs.insert(c);
  hs.insert(d);
  hs.insert(e);
  hs.insert(f);

  test("Test3", hs.contains(f), true);

  hs.insert(g);
  hs.insert(h); // 7 of 10 buckets should be filled on this insert, causing a resize to 20 buckets

  test("Test4", hs.capacity() == 13, true); // test that the table was resized, so it can hold 13 items before a resize is required

  hs.insert(i);
  hs.insert(j);
  hs.insert(k);
  hs.insert(l);
  hs.insert(m);
  hs.insert(n);
  hs.insert(o);
  hs.insert(p);
  hs.insert(q);
  hs.insert(r);
  hs.insert(s);
  hs.insert(t); // 14 of 20 buckets should be filled on this insert, causing another resize

  test("Test5", hs.capacity() == 27, true); // test that the table was resized again

  test("Test6", hs.remove(a), true); // test remove
  test("Test7", hs.contains(a), false); // the item should be gone
  test("Test8", hs.remove(a), false); // can't remove again
  test("Test9", hs.insert(a), true); // but we can add it back


  return 0;
}

EXAMPLE 2:
#include "hashset.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>


int test(char* label, bool a, bool b) {
  printf("%s: ", label);
  if (a==b) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed. lhs=%x, rhs= %x\n",a,b);
    exit(1);
  }
}

int main() {

	HashSet<char> hs(10);

  char a = 0x12ab345;
  char b = 0xfeed425;
  char c = 0xabcd38;
  char d = 0x1235698;
  char e = 0x2c374;
  char f = 0xa0f8982;
  char g = 0x053eba;
  char h = 0x61c2f5e;
  char i = 0xe0295f2;
  char j = 0x5e700eaa;
  char k = 0xe75bf1;
  char l = 0x6baa9bb;
  char m = 0x8b1390a;
  char n = 0x59dd1;
  char o = 0xfc32;
  char p = 0xa9d89d8;
  char q = 0x5b2c9e;
  char r = 0x2431e3;
  char s = 0x1910a;
  char t = 0x72;

	hs.insert(a); // insert an item into the table

 	test("Test1", hs.contains(a), true); // find the item
  test("Test2", hs.insert(a), false); // can't insert the same item twice

  hs.insert(b);
  hs.insert(c);
  hs.insert(d);
  hs.insert(e);
  hs.insert(f);

  test("Test3", hs.contains(f), true);

  hs.insert(g);
  hs.insert(h); // 7 of 10 buckets should be filled on this insert, causing a resize to 20 buckets

  test("Test4", hs.capacity() == 13, true); // test that the table was resized, so it can hold 13 items before a resize is required

  hs.insert(i);
  hs.insert(j);
  hs.insert(k);
  hs.insert(l);
  hs.insert(m);
  hs.insert(n);
  hs.insert(o);
  hs.insert(p);
  hs.insert(q);
  hs.insert(r);
  hs.insert(s);
  hs.insert(t); // 14 of 20 buckets should be filled on this insert, causing another resize

  test("Test5", hs.capacity() == 27, true); // test that the table was resized again

  test("Test6", hs.remove(a), true); // test remove
  test("Test7", hs.contains(a), false); // the item should be gone
  test("Test8", hs.remove(a), false); // can't remove again
  test("Test9", hs.insert(a), true); // but we can add it back


  return 0;
}

