# CSE109 - Systems Software - Homework 4

**Due Date: 9/19/2022 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You must make at least one commit per question.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

In this assignment we will explore the C GCC compilation pipeline. I've defined a simple C program in the project directory. Take a moment before starting to familiarize yourself with the files in the `src` and `include` directories. We are going to compile `main.c` into an executable `main`, and `lib1.c`/`lib2.c` into a library `libmylib.a`. The executable `main` will link to `libmylib.a`. You've done this several times already with the gcc command, but as we've learned in class, gcc is really a series of programs that are interconnected. In this assignment we will decompose the process into a number of different steps. Those steps are:

1. The C preprocessor - cpp
2. The C frontend - cc
3. The assembler - as
4. The linker - ld

As you go through this assignment you will generate a number of intermediate files. Usually I implore you not to commit compiler artifacts to your git repositories, but for this assignment the whole point is to generate and analyze these artifacts, so do commit them this time. They will have the extensions `.i`, `.s`, `.o`, and `.a`. In Part 1 will ask you to generate some files of the form `main.i.NNNt.*`. Save these to your repository as well. You should keep them all in the project root.

Here is a short reference of what the various file types mean:

- `.h` - C Header file
- `.c` - C Source
- `.i` - C preprocesor output
- `.s` - Assembly
- `.o` - Object Code
- `.a` - Object Archive

For this assignment, I ask you to make a number of observations about things we haven't covered in detail, and to form an inference from what you observe. Your objective for these questions is not to get the right answer (although it's fine if you do), but to form a well-reasoned response based on what we have studied. Getting the question wrong is fine as long as you do so thoughtfully. You will be graded on the clarity of your reasoning, and your ability to pull in knowledge from what we have studied in class.

### Part 1 - Exploring The C Preprocessor

The C preprocessor can be called directly by invoking the command `cpp` from the command line with a target input file. For example:

```bash
$ cpp main.c
```

Use the `cpp` command to preprocess `/src/bin/main.c`. You will have to use the `-I` flag in the usual way to tell the preprocessor where to find `mylib.h`. Save the result to a file in the project root directory called `main.i` (you can use the [`>` bash operator](https://www.linux.com/topic/desktop/understanding-angle-brackets-bash/) in the terminal to do this).

**Question 1:** How many bytes are in the source file?
    a) There are 8 bytes in the source file. This is because each int in C is 4 bytes. 

**Question 2:** How many bytes are in `main.i`? What happened in `cpp` to cause this difference?
    a) There are 16 bytes in main.i. This is because cpp had increased the storage space by adding filler characters to the file. This is due to how my cpu processes the size of the file as well. 

**Question 3:** List all the differences you see between `main.c` and `main.i`.
    a)  The primary difference I notice between 'main.c' and 'main.i' is that 'main.i' includes multiple #'s at the top of the file. I am unsure whether this is intentional or not, but my main.c files does not include these #'s. 

### Part 2 - Exploring The C Frontend

We can call the C frontend directly by invoking the command `cc` from the command line, with the target input file being the output we got from `main.i`. When you invoke `cc`, it transforms the input program into a number of internal states. We can take a look at some of these states with a collection of flags named `-fdump-*`.

The `cc` command will automatically invoke the assembler, which we can short-circuit with the `-S` flag to see the assembly output.

(you can do Questions 4-7 in one command)

**Question 4:** Use the `cc` command to compile `main.i`, into `main.s`, the contents of which is `main.c` represented in human-readable assembly language.
    a) Committed this. 

**Question 5:** Use the `-fdump-tree-gimple` flag to output the Gimple intermediate representation.
    a) Committed this file. 

**Question 6:** Use the `-fdump-tree-ssa` flag to output the SSA intermediate representation.
    a) Committed this file. 

**Question 7:** Use the `-fdump-rtl-expand` flag to output the first RTL intermediate representation.
    a) Committed this file. 
    
**Question 8:** Use the `-fdump-rtl-dfinish` flag to output the final RTL intermediate representation.
    a) Committed this file. 

**Question 9:** On my machine, the files generated are:

- main.i.004t.gimple
- main.i.018t.ssa
- main.i.192t.expand
- main.i.270t.dfinish

What do you think the number in the file names might indicate?
    a) I believe that the numbers indicate the number of bytes each file used. This is because dfinish is the largest file and also has the highest number attached to it. 

**Question 10:** Consider `main.i` and the Gimple intermediate representation. What has changed between these two files?
    a) What happened is that a new variable had been created in the gimple representation. Specifically the int D.1921 had been created and is returned instead of the 'x' used in main.c. 

**Question 11:** Consider the Gimple and SSA intermediate representations. What has changed between these two files?
    a) Compared to Gimple, SSA seems to be more intricate. There are function at the top of the file that were not there in the gimple interpretation. Moreover, more variables had been created, like int_7 and sections such as <bb 2>: . 

**Question 12:** Consider the SSA and RTL-expand intermediate representations. Why do you think the RTL representation is so much larger than the SSA representation?
    a) I believe that the RTL is much larger compared to the SSA representation because it is attempting to be a more generic interpretation than the SSA representation. It also contains readable code for an indiviudal to understand the program's processes. In essence, it expands upon the other representations. 

**Question 13:** Now take a look at the assembly code in the `main.s` file. It's okay that you don't know what this does, that's a topic for CSE202. But as you look at this file, remember the [Rosetta Stone](https://en.wikipedia.org/wiki/Rosetta_Stone). The people who studied this stone were able to use their knowledge of Greek to decode the meaning behind the hieroglyphics by making connections between the two languages. Try to use your knowledge of C to decode the meaning behind some of the assembly in `main.s`. There are wrong answers here (this question will be graded on your reasoning, not on accuracy).
    a) I believe that the top section is noting the #'s at the top of main.i. After this, the "main:" section represents the "main" method in main.i. This area showcases how the variables are added to one another. After that, the LFE0 section is where the variable is returned. 


### Part 3 - Exploring the Assembler

The assembler can be called directly using the command `as`. The input to the assembler will be the assembly file from Part 2. The assembler will convert this assembly code into platform specific object code. Normally, `as` will call the linker `ld` after this step to generate an executable, but we can prevent that using the `-o` flag.

**Question 14:** Use `as` to turn `main.s` into `main.o`.
    a) Committed this file. 

**Question 15:** A `.o` file is known as an object file because it contains platform-specific object code. We can take a look at this code using the `hexdump` command with the `-C` flag. Do this in your console and reproduce the results below:

**main.o:**
```
00000000  7f 45 4c 46 02 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
00000010  01 00 3e 00 01 00 00 00  00 00 00 00 00 00 00 00  |..>.............|
00000020  00 00 00 00 00 00 00 00  d0 02 00 00 00 00 00 00  |................|
00000030  00 00 00 00 40 00 00 00  00 00 40 00 0d 00 0c 00  |....@.....@.....|
00000040  53 be 02 00 00 00 bf 01  00 00 00 31 c0 e8 00 00  |S..........1....|
00000050  00 00 be 04 00 00 00 bf  03 00 00 00 89 c3 31 c0  |..............1.|
00000060  e8 00 00 00 00 01 d8 5b  c3 00 47 43 43 3a 20 28  |.......[..GCC: (|
00000070  47 4e 55 29 20 31 30 2e  33 2e 30 00 00 00 00 00  |GNU) 10.3.0.....|
00000080  14 00 00 00 00 00 00 00  01 7a 52 00 01 78 10 01  |.........zR..x..|
00000090  1b 0c 07 08 90 01 00 00  1c 00 00 00 1c 00 00 00  |................|
000000a0  00 00 00 00 29 00 00 00  00 41 0e 10 83 02 67 0e  |....)....A....g.|
000000b0  08 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000000c0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000000d0  01 00 00 00 04 00 f1 ff  00 00 00 00 00 00 00 00  |................|
000000e0  00 00 00 00 00 00 00 00  00 00 00 00 03 00 01 00  |................|
000000f0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000100  00 00 00 00 03 00 02 00  00 00 00 00 00 00 00 00  |................|
00000110  00 00 00 00 00 00 00 00  00 00 00 00 03 00 03 00  |................|
00000120  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000130  00 00 00 00 03 00 04 00  00 00 00 00 00 00 00 00  |................|
00000140  00 00 00 00 00 00 00 00  00 00 00 00 03 00 07 00  |................|
00000150  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000160  00 00 00 00 03 00 08 00  00 00 00 00 00 00 00 00  |................|
00000170  00 00 00 00 00 00 00 00  00 00 00 00 03 00 06 00  |................|
00000180  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000190  08 00 00 00 12 00 04 00  00 00 00 00 00 00 00 00  |................|
000001a0  29 00 00 00 00 00 00 00  0d 00 00 00 10 00 00 00  |)...............|
000001b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001c0  23 00 00 00 10 00 00 00  00 00 00 00 00 00 00 00  |#...............|
000001d0  00 00 00 00 00 00 00 00  27 00 00 00 10 00 00 00  |........'.......|
000001e0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001f0  00 6d 61 69 6e 2e 63 00  6d 61 69 6e 00 5f 47 4c  |.main.c.main._GL|
00000200  4f 42 41 4c 5f 4f 46 46  53 45 54 5f 54 41 42 4c  |OBAL_OFFSET_TABL|
00000210  45 5f 00 61 64 64 00 73  75 62 00 00 00 00 00 00  |E_.add.sub......|
00000220  0e 00 00 00 00 00 00 00  04 00 00 00 0b 00 00 00  |................|
00000230  fc ff ff ff ff ff ff ff  21 00 00 00 00 00 00 00  |........!.......|
00000240  04 00 00 00 0c 00 00 00  fc ff ff ff ff ff ff ff  |................|
00000250  20 00 00 00 00 00 00 00  02 00 00 00 05 00 00 00  | ...............|
00000260  00 00 00 00 00 00 00 00  00 2e 73 79 6d 74 61 62  |..........symtab|
00000270  00 2e 73 74 72 74 61 62  00 2e 73 68 73 74 72 74  |..strtab..shstrt|
00000280  61 62 00 2e 74 65 78 74  00 2e 64 61 74 61 00 2e  |ab..text..data..|
00000290  62 73 73 00 2e 72 65 6c  61 2e 74 65 78 74 2e 73  |bss..rela.text.s|
000002a0  74 61 72 74 75 70 00 2e  63 6f 6d 6d 65 6e 74 00  |tartup..comment.|
000002b0  2e 6e 6f 74 65 2e 47 4e  55 2d 73 74 61 63 6b 00  |.note.GNU-stack.|
000002c0  2e 72 65 6c 61 2e 65 68  5f 66 72 61 6d 65 00 00  |.rela.eh_frame..|
000002d0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000310  1b 00 00 00 01 00 00 00  06 00 00 00 00 00 00 00  |................|
00000320  00 00 00 00 00 00 00 00  40 00 00 00 00 00 00 00  |........@.......|
00000330  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000340  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000350  21 00 00 00 01 00 00 00  03 00 00 00 00 00 00 00  |!...............|
00000360  00 00 00 00 00 00 00 00  40 00 00 00 00 00 00 00  |........@.......|
00000370  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000380  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000390  27 00 00 00 08 00 00 00  03 00 00 00 00 00 00 00  |'...............|
000003a0  00 00 00 00 00 00 00 00  40 00 00 00 00 00 00 00  |........@.......|
000003b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000003c0  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000003d0  31 00 00 00 01 00 00 00  06 00 00 00 00 00 00 00  |1...............|
000003e0  00 00 00 00 00 00 00 00  40 00 00 00 00 00 00 00  |........@.......|
000003f0  29 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |)...............|
00000400  10 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000410  2c 00 00 00 04 00 00 00  40 00 00 00 00 00 00 00  |,.......@.......|
00000420  00 00 00 00 00 00 00 00  20 02 00 00 00 00 00 00  |........ .......|
00000430  30 00 00 00 00 00 00 00  0a 00 00 00 04 00 00 00  |0...............|
00000440  08 00 00 00 00 00 00 00  18 00 00 00 00 00 00 00  |................|
00000450  3f 00 00 00 01 00 00 00  30 00 00 00 00 00 00 00  |?.......0.......|
00000460  00 00 00 00 00 00 00 00  69 00 00 00 00 00 00 00  |........i.......|
00000470  13 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000480  01 00 00 00 00 00 00 00  01 00 00 00 00 00 00 00  |................|
00000490  48 00 00 00 01 00 00 00  00 00 00 00 00 00 00 00  |H...............|
000004a0  00 00 00 00 00 00 00 00  7c 00 00 00 00 00 00 00  |........|.......|
000004b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000004c0  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000004d0  5d 00 00 00 01 00 00 00  02 00 00 00 00 00 00 00  |]...............|
000004e0  00 00 00 00 00 00 00 00  80 00 00 00 00 00 00 00  |................|
000004f0  38 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |8...............|
00000500  08 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000510  58 00 00 00 04 00 00 00  40 00 00 00 00 00 00 00  |X.......@.......|
00000520  00 00 00 00 00 00 00 00  50 02 00 00 00 00 00 00  |........P.......|
00000530  18 00 00 00 00 00 00 00  0a 00 00 00 08 00 00 00  |................|
00000540  08 00 00 00 00 00 00 00  18 00 00 00 00 00 00 00  |................|
00000550  01 00 00 00 02 00 00 00  00 00 00 00 00 00 00 00  |................|
00000560  00 00 00 00 00 00 00 00  b8 00 00 00 00 00 00 00  |................|
00000570  38 01 00 00 00 00 00 00  0b 00 00 00 09 00 00 00  |8...............|
00000580  08 00 00 00 00 00 00 00  18 00 00 00 00 00 00 00  |................|
00000590  09 00 00 00 03 00 00 00  00 00 00 00 00 00 00 00  |................|
000005a0  00 00 00 00 00 00 00 00  f0 01 00 00 00 00 00 00  |................|
000005b0  2b 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |+...............|
000005c0  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000005d0  11 00 00 00 03 00 00 00  00 00 00 00 00 00 00 00  |................|
000005e0  00 00 00 00 00 00 00 00  68 02 00 00 00 00 00 00  |........h.......|
000005f0  67 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |g...............|
00000600  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000610
Paste hexdump of main.o here
```

We'll learn more about this later in the course. For now, just looking at it, what observations do you make? Are you able to draw any connections between the hexdump and the C and assembly code?
    a) Yes, I notice specific lines that were in the C and assembly code and presented in the hexdump in various sections. It seems these areas store the C and assembly code. 

### Part 4 - Building a Library

Now that we've gone through the process of turning a source file into an object file, we need to link to the library code on which it depends. To do that, we need to repeat the build process for `mylib1.c` and `mylib2.c`.

**Question 16:** Go through the process of turning `mylib1.c`/`mylib2.c` into `mylib1.o`/`mylib2.o` by following the steps in parts 1 through 3. You'll need to build the following files (you can skip the Gimple/SSA/RTL intermediate representations):

- `mylib1.i`
- `mylib1.s`
- `mylib1.o`
- `mylib2.i`
- `mylib2.s`
- `mylib2.o`

**Question 17:** Use `hexdump -C` to take a look at the object code within `mylib1.o` and `mylib2.o`. Paste the output of each below:

**mylib1.o:**
```
mylib1.txt
Paste hexdump of mylib1.o here
```
x
**mylib2.o:**
```
mylib2.txt
Paste hexdump of mylib2.o here
```

**Question 18:** Using `ar`, package `mylib1.o` and `mylib2.o` into a static library called `libmylib.a`.

**Question 19:** Now use `hexdump -C` to inspect the contents of `libmylib.a`. Paste the output in the space below.

**libmylib.a:**
```
Paste hexdump of libmylib.a here
libmylib.txt
```

**Question 20:** Compare the hexdumps of `mylib1.o`, `mylib2.o`, and `libmylib.a`. What do you notice? How many bytes are in `mylib1.o`? How many are in `mylib2.o`? How many are in `libmylib.a`? Based on your comparison, what do you think the extra bytes are doing in `libmylib.a`?
- Bytes of mylib1.o are 532, mylib2.o are 532, and liubmylib.a are 1344.

### Part 5 - Building an Executable

We now have everything we need to build our executable. The `gcc` linker is a program called `ld`, and you can invoke the linker manually with the `ld` command in the terminal. But we won't use this command directly to build our executable, because doing so requires a number of arguments that are specific to the way your machine is configured. Therefore it's hard for me to provide generic instructions to do this as it might be different depending on your operating system and environment. Instead, we will invoke `gcc` which will call `ld` with the appropriate configuration options.

**Question 21:** Use `gcc` to combine `main.o` with `libmylib.a` to generate an executable named `main`.

**Question 22:** Use `hexdump -C` to take a look at hte object code within `main` and paste the output below:

```
Paste hexdump of main here
```

**Question 23:** Compare the output of `hexdump` for `main`, `main.o`, and `libmylib.a`. What do you notice? How many bytes are in `main.o`? How many are in `libmylib.a`? How many are in `main`? Based on your comparison, what do you think the extra bytes are doing in `main`?
- Bytes of main are 16865, main.o are 640, and libmylib.a are 1344.

**Question 24:** Write a `Makefile` that automates the build process without using `gcc` (except to invoke the linker in the last step). Your `Makefile` should have the following directives:

- all - build the executable from `main.o` and `libmylib.a`
- main.o - build `main.o` from `main.c`
- libmylib.a - build `libmylib.a` from `mylib1.c` and `mylib2.c`
- clean - remove all `*.i`, `*.s`, `*.a`, `*.o`, `main`, and intermediate representation files.
