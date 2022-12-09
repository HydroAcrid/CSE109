# CSE109 - Systems Software - Fall 2022

# Midterm Exam

Due by: 10/07/2022 by NOON

## Ethics Contract

**FIRST**: Please read the following carefully:

- I am the sole author of the content within this exam unless otherwise cited.
- I am not an uncredited author of any content in any other exam.
- I will not dicsuss the exam until after the submission deadline on Friday  10/7 at NOON (before recitation).
- All resources I used (including text books and online references and websites), are cited in this exam.
- I will not plagiarize someone else's work and turn it in as my own. If I use someone else's work in this exam, I will cite that work. Failure to cite work I used is plagiarism.
- I understand that acts of academic dishonesty may be penalized to the full extent allowed by the [Lehigh University Code of Conduct][0], including receiving a failing grade for the course. I recognize that I am responsible for understanding the provisions of the Lehigh University Code of Conduct as they relate to this academic exercise.

If you agree with the above, type your full name in the following space along with the date. Your exam **will not be graded** without this assent. When you are done, **make your first commit with the commit message: `I, <your full name here>, agree to the ethics contract`.**

Write your name and date between the lines below

---------------------------------------------
I, Kevin Dotel, agree to the ethics contract. 
---------------------------------------------

## Instructions 

**Read thoroughly before starting your exam:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per question.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Exam Prelude

There are two parts to this exam. Each question is weighted equally. This exam will test your ability to independently:

- Organize a programming project
- Use the basics of the C progamming language including structs and pointers
- Allocate memory on the heap and use it in a way that does not cause memory leaks
- Implement a library and use that library in an executable
- Write and use Makefiles to automate the build process

In Part 1 you're going to implement the `ls` program which lists directories and files in a target folder.

This repository is blank except for this README file. It's your job to create this program from scratch. You are going to lay out the directory structure, create a Makefile, create a header file, create library source files, implement your executable. You can use any libraries and functions you like to accomplish this.

Part 2 is the oral portion of the exam. I will ask you to pick a couple functions in your program and to record an explanation of your work along with your screen. For more info, see Part 2. **You will not be able to pass this exam without doing this portion.**

### Commit Policy

The exam is divided into discrete "questions", and you must make at least one commit per question to receieve full credit for the question. You can do the questions in any order, and you can go back to questions for which you have already made a commit. The commit message for each question should be "QUESTION N" where N is the number of the question.

### Resource Usage Policy

You are free to use any resource for this exam. This includes books, notes, lecture videos, documentation, the internet, Stack Overflow, etc. The only course resources off limits are me and your TAs. I am free to answer clarifying questions, but that's it. I can't help you debug or provide any technical support (this includes support with git. Knowing how to use git is part of this exam.)

If you use any resources from the internet or anywhere else, **YOU HAVE TO CITE THEM** in your exam. Failure to cite resources you used may lead to failure of the exam. If you use a resource, cite it every time you use it. A comment in code with a link and a brief explanation will suffice.

## ls

```
LS(1)                                                                                                                                               User Commands                                                                                                                                              LS(1)

NAME
       ls - list directory contents

SYNOPSIS
       ls [OPTION]... [FILE]...

DESCRIPTION
       List information about the FILEs (the current directory by default).  Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.

       Mandatory arguments to long options are mandatory for short options too.

       -a, --all
              do not ignore entries starting with .

       -l     use a long listing format

       --help display this help and exit

       --version
              output version information and exit

   Exit status:
       0      if OK,

       1      if any problems

AUTHOR
       Written by Richard M. Stallman and David MacKenzie.

REPORTING BUGS
       GNU coreutils online help: <https://www.gnu.org/software/coreutils/>
       Report ls translation bugs to <https://translationproject.org/team/>

COPYRIGHT
       Copyright © 2018 Free Software Foundation, Inc.  License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the extent permitted by law.

SEE ALSO
       Full documentation at: <https://www.gnu.org/software/coreutils/ls>
       or available locally via: info '(coreutils) ls invocation'

GNU coreutils 8.30
```


## Part 1

### Question 1

Lay out your directory structure. Create a `src` directory, an `include` directory, and a blank `Makefile` in the project root. 

- Inside the `src` directory create a `bin` directory. 
- Inside the `src/bin` directory create `main.c`.
- Inside the `src` directory create `lib.c`.
- Inside the `include` directory, create `myls.h`

!DONE!

### Question 2

Implement the Makefile to build your project. Your Makefile should have at least the following targets:

- `static` will generate a static library (libmyls.a) and put it in `build/lib`.
- `shared` will generate a shared library (libmyls.so) and put it in `build/lib`.
- `bin` will generate an executable from `main.c` called `my_ls`, which statically links to `libmyls.a` (it should make that as well if it doesn't exist). Put the executable in `build/bin` and the library in `build/lib`. Put object files in `build/objects`.
- `all` will build the static and shared libraries as well as `my_ls`.
- `clean` will clean the project of all build directories and artifacts (*.so *.a *.o main)
- `install` will move the shared library to `/usr/lib`.

### Question 3

In `lib.c`, write a routine called `show_directory` that accepts a target directory as an argument and and prints to the screen the directory's visible contents (only files without a . prefix). 

You may want to use https://www.man7.org/linux/man-pages/man0/dirent.h.0p.html, which provides a handy struct that will help you in this task. You should format this output to print out as the basic `ls` command prints to the screen.

```
void show_directory(char* directory){}
```
You can add any helper functions you need to implement this question.

!DONE!

### Question 4

In lib.c, write a function that will list hidden files and folders (any filename prefixed with a dot, like .gitignore) are included in the output.

```
void show_directory_all(char* directory){}
```

!DONE!

You can add any helper functions you need to implement this question.

### Question 5

In lib.c, write functions that will list extra information about the contents of a given directory.

```
void show_directory_long(char* directory){}
void show_directory_long_all(char* directory){} // will show the hidden files as well
```

First: Print how many files and folders are in the directory
Then:
  List files/folders in the directory, one file/folder per row.

In each row:

- the name of the item, 
- if the item is an executable, put a star after its name

as well as one other piece of info. e.g.

- date created
- owner
- size

You can add any helper functions you need to implement this question.

### Question 6 

In `include/myls.h`

Put function stubs for the functions implemented in `lib.c`. For each one, add a comment in your own words about what it does.

```
void show_directory(char* directory);
void show_directory_all(char* directory);
void show_directory_long(char* directory);
void show_directory_long_all(char* directory);
```

### Question 7

In `main.c`, link to myls.h and use the functions provided by that library to implement the my_ls program. Start by printing the contents of the current directory if no arguments are supplied.

### Question 8

Handle printing a target directory supplied as a commandline input.

### Question 9

Handle the `-a` and `--all` flags

### Question 10

Handle the `-l` flag. Make sure you can handle `-al` and `-la`. Also make sure that the arguments are position independent.

### Question 11

Handle the `-v` and `--version` flags.

Print: "[your name] v.0.0.1"


### Question 12

Handle the `-h` and `--help` flags.

Prints a manual page for `my_ls` in your own words:

- describe program usage
- brief description of what the program does
- describe all flags and their usage (-a,-l,-h,-v)
- describe output values

## Part 2

This is the oral portion of the exam. You will record an explanation (minimum 5 mins.) for the `my_ls` program demonstrating its usage and showing how you implemented it. You don't have to show your face but you do have to record your voice.

If you didn't finish the exam in is entirety, explain how you attempted to solve it and where you got stuck. This will get you at least some points. 

First, demonstrate the program's core functions:
  - Demonstrate `my_ls`
  - Demonstrate `my_ls -a`
  - Demonstrate `my_ls -l`
  - Demonstrate `my_ls -al`
  - Demonstrate `my_ls -al /usr/bin` (or some other directory)

As part of your explaination, be sure to explain the following in detail:
  - How did you implement the Makefile?
  - How did you implement the `show_directory()` functions?
  - How did you implement handling input arguments?
  
You can use Zoom to do this, [here is a link][3] to some instructions. You only have to record your voice and the screen. Go through your exam and explain how you arrived at the submitted code. Your goal with this question is to convince me you know what you are talking about, so I want you to do this without reading a script or written answer. Just go through line by line and explain what the program does. When you are done, upload your recording to your Lehigh Drive and add a link below. **IMPORTANT: Make sure you give anyone with the link permission to view the file**.

Recording Link(s):

## Works Cited

Include a list of websites and resources you used to complete this exam. Make a numbered list, and at the place where you used this resource cite it using [reference style links in Markdown][1] (See this Readme's source for an example. It's invisible in the rendered document, but there are a number of links below this paragraph).

[0]: https://studentaffairs.lehigh.edu/content/code-conduct
[1]: https://www.markdownguide.org/basic-syntax#reference-style-links
[2]: http://crasseux.com/books/ctutorial/Building-a-library.html#Building%20a%20library
[3]: https://support.zoom.us/hc/en-us/articles/201362473-Local-recording

[4]:https://man7.org/linux/man-pages/man2/lstat.2.html 
[5]:https://iq.opengenus.org/ls-command-in-c/
[6]:https://man7.org/linux/man-pages/man3/readdir.3.html
[7]:https://randu.org/tutorials/c/libraries.php
[8]:https://man7.org/linux/man-pages/man2/lstat.2.html 

VIDEO: https://drive.google.com/file/d/1oonsL5_OISRDdjdYEn3MOiocVNGKYrt5/view?usp=sharing 