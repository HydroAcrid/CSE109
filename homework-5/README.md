# CSE109 - Systems Software - Fall 2022

# Homework 5

**Due Date: 9/27/2022 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per function.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

You will implement a linked list data structure in this assignment. The linked list will consist of a `head` pointer and a tail pointer. The head pointer will point to a `Node` struct, which will hold a data void pointer as well as a pointer to the next node in the list. The `tail` pointer will point to the final node in the linked list. The `next` pointer on the tail will point to `NULL`.


```
  ┌─────────┐    ┌─────────┐   ┌─────────┐    ┌─────────┐
  │     head│--->│  void*  │-->│  void*  │--->│  void*  │---> NULL
  │         │    └─────────┘   └─────────┘    └─────────┘
  │     tail│--------------------------------------^
  └─────────┘
```


The `List` and `Node` structs are declared in `linkedlist.h`, along with a number of functions you will need to implement.

```c
// Initialize an empty list. The head and tail pointers should point to NULL.
void initList(List* list_pointer);

// Create Node struct containing a void pointer to an item, return pointer to the newly created Node struct
Node* createNode(void* item);

// Insert new Node at the end of the list, containing a void pointer to item. The next pointer on this Node
// points to NULL. On success return 0. On failure, return 1.
int insertAtTail(List* list_pointer, void* item);

// Insert a Node at the head of the list, containing a void pointer to item. The next pointer on the
// newly created node points to the previous head of the list. On success return 0. On failure, return 1.
int insertAtHead(List* list_pointer, void* item);

// Insert a Node at the specified index, containing a void pointer to item. If the index is greater than
// the length of the list, the program should crash. On success return 0. On failure, return 1.
int insertAtIndex(List* list_pointer, int index, void* item);

// Remove Node from the end of list and return the void pointer it contains. The preceeding Node should
// point to NULL after this operation. On failure return a NULL pointer.
void* removeTail(List* list_pointer);

// Remove Node from start of list and return return the void pointer it contains. The following Node should 
// be the new head of the list. On failure return a NULL pointer.
void* removeHead(List* list_pointer);

// Insert Node item at a specified index and return return the void pointer it contains. The Node at the specified
// index before this function is called should be the next Node following the newly inserted Node.
// On failure return a NULL pointer.
void* removeAtIndex(List* list_pointer, int index);

// Return the pointer stored in the Node at the specified index. On failure return a NULL pointer. 
void* itemAtIndex(List* list_pointer, int index);
```

There is a print function that is already implemented for you. This will help you inspect the list as you write the above functions.

## Code Demo and Explanation

This is the oral portion of the homework. You will record an explanation for your data scructure demonstrating its usage and showing how you implemented it. You don't have to show your face but you do have to record your voice.

If you didn't finish the homework in is entirety, explain how you attempted to solve it and where you got stuck. This will get you at least some points. 

You can use Zoom to do this, [here is a link][3] to some instructions. You don't have to record your face, only your voice and the screen. Go through the answer and explain how you arrived there. Your goal with this question is to convince me you know what you are talking about, so I want you to do this without reading a script or written answer. Just go through line by line and explain what the program does. When you are done, upload your recording to your Lehigh Drive and add a link below. **IMPORTANT: Make sure you give me permission to view the file**.

Recording Link(s): https://drive.google.com/file/d/1wp6F9Np9I-htFxU-rHguCEhrQ0BQwJJh/view?usp=sharing
