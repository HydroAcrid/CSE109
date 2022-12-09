# CSE109 - Systems Software - Fall 2022

# Homework 3

**Due Date: 9/12/2022 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per question.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

Answer the following questions about pointers in C. Make at least one commit per question. Each question is worth 1 point for a total of 5 points for the assignment. This will be scaled to 100% for your HW grade.

### Question 1

For each problem, write the English interpretation of the given line of C code. In the provided table, give the state of the memory after the line of code is executed. You can assume each block of memory can hold up to 32 bits of memory, and that pointers are 8 bits wide. Also assume that memory is aligned to 8 bit blocks (i.e. if a variable can be represented by fewer than 8 bits, it still occupies the entire block). You can start your memory range at memory address 0x42 for the purpose of this problem. Write the contents and memory address as an 8 bit big-endian hexadecimal number.

For instance:
```c
  // Example
  char foo = 10;
  // Interpretation: Declare an char called foo with the value 10
  // Memory:
  //         ┌──────────┬──────────┬──────────┬──────────┐
  //    label│foo       │          │          │          │
  //         ├──────────┼──────────┼──────────┼──────────┤
  //  address│0x42      │          │          │          │
  //         ├──────────┼──────────┼──────────┼──────────┤
  // contents│0x0A      │          │          │          │
  //         └──────────┴──────────┴──────────┴──────────┘
    char bar = 20;
  // Interpretation: Declare an integer called bar with the value 10
  // Memory:
  //         ┌──────────┬──────────┬──────────┬──────────┐
  //    label│foo       │bar       │          │          │
  //         ├──────────┼──────────┼──────────┼──────────┤
  //  address│0x42      │0x43      │          │          │
  //         ├──────────┼──────────┼──────────┼──────────┤
  // contents│0x0A      │0x14      │          │          │
  //         └──────────┴──────────┴──────────┴──────────┘
```

```c
int main() {
  // Problem 1
  char c = 163;
  // Interpretation: Declare an integer called c with the value of 163.
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │    c     │          │          │          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0x42   │          │          │          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0xA3   │          │          │          │
  // └──────────┴──────────┴──────────┴──────────┘
  
  
  // Problem 2
  char* b;
  char* a;
  // Interpretation: Declared two char* variables called b and a. 
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │    c     │    b     │    a     │          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0x42   │   0x43   │   0x44   │          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0xA3   │   0x0    │   0x0    │          │
  // └──────────┴──────────┴──────────┴──────────┘

  // Problem 3
  char d = 96;
  // Interpretation: Declare an integer called d with the value of 96.
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │     c    │    b     │    a     │    d     │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0x42   │   0x43   │   0x44   │   0x45   │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0xA3   │   0x0    │   0x0    │   0x60   │
  // └──────────┴──────────┴──────────┴──────────┘

  // Problem 4
  b = &c;
  a = &d;
  // Interpretation: Assigned b to the dereference of c. Assigned a to the dereference of d.
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │     c    │    b     │    a     │    d     │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0x42   │   0x43   │   0x44   │   0x45   │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0x0A3  │   0x42   │   0x45   │   0x60   │
  // └──────────┴──────────┴──────────┴──────────┘
  
  // Problem 5
  *a = 33;
  // Interpretation: Assigned *a to the value of 33. 
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │     c    │    b     │   a      │    d     │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0x42   │   0x43   │   0x44   │   0x45   │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0x0A3  │   0x42   │   0x45   │   0x21   │
  // └──────────┴──────────┴──────────┴──────────┘

  // Problem 6
  *b = *a + c;
  // Interpretation: Assigned *b to the sum of *a and c.  
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │     c    │    b     │   a      │    d     │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0x42   │   0x43   │   0x44   │   0x45   │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │   0xC4   │   0x42   │   0x45   │   0x21   │
  // └──────────┴──────────┴──────────┴──────────┘

  return 0;
}
```

### Question 2

In a the space below, write a function with the signature `void multiply_ptrs(int* x, int* y, int* z);`.

This function returns nothing. The body of the fuction should multiply the contents of `x` and `y` and store the result in `z`. For example, you could use it like this:

```c
int z;
int x = 5;
int y = 6;
multiply_ptrs(&x,&y,&z);
// z should be 30 after the above line is executed.
```

```c
void multiply_ptrs(int* x, int* y, int* z) {
    *z = *x * *y;
    printf("%d\n", *z);
}
```

Reproduce the above function in a file called `multiply_ptrs.c`, and include a `main()` function that demonstrates its usage. The main function should take in two numbers as input from the command line, and print out the result of `multiply_ptrs()` the terminal.

```
> ./multiply_ptrs 10 11
110
```

This will come in handy: https://www.cplusplus.com/reference/cstdlib/atoi/

### Question 3

Using pointer arithmatic and what you know about c-strings, implement the function `int strlen(char *str);` in the space below. This function takes a c-string and returns the number of characters in the string. For example:

```c
int strln(char* str) {
  int length = 0;
  for(int i = 0; str[i]!= '\0'; i++) {
    length++;
  }
  printf("%d\n", length);

  return length;
}
```

Reproduce the above function in a file called `strlen.c`, and include a `main()` function that demonstrates its usage. The main function should take in a string as input from the command line, and print out the result of `strlen()` to the terminal. For example:

```
> ./strlen Hello
5
```

### Question 4

In Homework 2 we used the `char** argv` argument vector to modify the behavior of a program depending on how it's called. Let's say we have a program called `a.out`, and we call it as follows:

```bash
$ ./a.out one two three
```

Conceptually we know that a double pointer like `argv` can be thought of as a 2D table. But we also know that memory only has one dimension. So what exactly does `argv` look like in memory? How can we encode a 2D table in one dimension? In the space below, write a program that will print out the memory locations of the entire `argv` datastructure. *i.e.*:

```
argv
argv[0]
argv[1]
argv[2]
argv[3]
argv[0][0]
argv[0][1]
etc...
```

Start by considering specifically the example I gave above (you can hardcode numbers since you know the size of all the arguments), but then try to generalize it for any `argv`. Write your program below:

```c
int main(int argc, char** argv) {

   printf("%p\n", &argv);
   for(int i = 0; i < argc; i++) {
       printf("%p\n", &argv[i]);

   } 

   for(int i = 0; i < argc; i++) {

       for(int k = 0; argv[i][k] != '\0'; k++) {
            printf("%p\n", &argv[i][k]);
       }

   } 
  // Implement me
  return 0;
}
```

Reproduce the above function in a file called `argv.c`, which takes in any number of command line arguments, and prints the memory layout of the `argv` datastructure.

Explain below in words how `argv` is laid out. Fill out a table in the style of Question 1 with actual memory addresses and values from one of your test runs. If the memory isn't contiguous, you can use different tables to represent different regions of memory. You can also add more columns

```
Write explanation here...

// Interpretation: argv pointer is initialized.   
// Memory:
┌──────────┬────────────────┬───────────────┬────────────────┐
│ label    │argv            │               │                │
├──────────┼────────────────┼───────────────┼────────────────┤
│ address  |0x16b107510     │               │                │
├──────────┼────────────────┼───────────────┼────────────────┤
│ contents │0x16b107510     │               │                │
└──────────┴────────────────┴───────────────┴────────────────┘

// Interpretation: "one" was inputted. the four loop iterates to argv[1]. Argv[0] was also passed.
// Memory:
┌──────────┬────────────────┬───────────────┬────────────────┐
│ label    │argv[0]         │argv[1]        │                │
├──────────┼────────────────┼───────────────┼────────────────┤
│ address  |0x16b107510     │0x16b107518    │                │
├──────────┼────────────────┼───────────────┼────────────────┤
│ contents │0x16b107510     │0x16b107518    │                │
└──────────┴────────────────┴───────────────┴────────────────┘

// Interpretation: "one" was inputted. the four loop iterates to argv[2][0]. 
// Memory:
┌──────────┬────────────────┬───────────────┬────────────────┐
│ label    │argv[0]         │argv[1]        │argv[2][0]      │
├──────────┼────────────────┼───────────────┼────────────────┤
│ address  |0x16b107510     │0x16b107518    │0x16b1076b7     │
├──────────┼────────────────┼───────────────┼────────────────┤
│ contents │0x16b107510     │0x16b107518    │0x16b1076b7     │
└──────────┴────────────────┴───────────────┴────────────────┘

```

## Question 5

Modify your Homework 2 solution in the following ways:

1. Take `file_exists()` out of `main.c`, and put it into a file called `my_which_lib.c`
2. Create a header file called `my_which.h`, and write a function signature for `file_exists()` inside. It's just 1 line of code.
3. Make sure you include `my_which.h` inside of `main.c`
4. Move all source files (main.c, my_which.h, and my_which_lib.c) into a folder called `src`.
5. Create a makefile called `Makefile` in the project root. Inside of the makefile, write the following directives:
    - static: compiles `my_which_lib.c` into a static library called `libmy_which.a`. Move this file into a subdirectory called `build/bin`. Move any intermediate objects into `build/objects`. This directive should make those directories if they don't exist.
    - shared: compiles `my_which_lib.c` into a shared library called `libmy_which.so`. Move this file into a subdirectory called `build/bin`. Move any intermediate objects into `build/objects`. This directive should make those directories if they don't exist.
    - all: compiles main.c into the `my_which` executable. It should statically link to `libmy_which.a`. Move the finished executable into `build/bin`. Move any intermediate objects into `build/objects`. This directive should make those directories if they don't exist.
    - clean: removes all build artifacts including the build directories.
