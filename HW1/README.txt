README
======

A. This package includes the following files:

|-- Description PDF of the assignment
|-- README.txt [This file]
|-- Executor.c 
    Contains the implementation of Executor. This file Creates the arrays and calculates the number of primes in the array.
|-- Executor.h
    Contains declarations of functions for Executor. This file also has descriptions of each function.
|-- Starter.c
    Contains main function.
|-- Makefile

B. Use your designed makefile 
To compile the code and build the executable using the command 

systemprompt>  make

To remove the  executable files use

systemprompt>  make clean

To run the program use (assuming seed is 3) 

systemprompt> ./Starter 3

which will run the program and generate the outputs.


C. Answer the following questions (1 point each, select/type the right answer).

  1. What is the main difference between Malloc() and Calloc()?
        The main difference between Malloc() and Calloc() is that when malloc allocates memory (in bytes), it does not initialize the allocated memory.
        Calloc initializes the bytes it allocates in memory to 0.
  2. What is the main advantage of using dynamic memory allocation?
        One major advantage of using dynamic memory allocation is that data structures can grow and shrink depending on what we need.
        We can allocate/de-allocate memory whenever we want. Dynamic allocation is also done at run tim.
  3. What happens if you attempt to free the memory already freed?
        This is undefined behavior. It's possible the memory that your stale pointer was pointing to was reallocated. This could cause loss of data, heap corruption, or more.
  4. What is the purpose of the headerfile Executor.h, and why is Starter.h not necessary?
        The header file contains the definitions of the functions used in Executor.c. Starter.c does not contain any functions besides main, so it does not need a header file.
  5. Describe the * and & operators in the context of pointers and references?
        You use * to declare/initialize a pointer variable. You also use * to access the data that a pointer is pointing to.
        Using '&' will give you the address of a pointer variable. '&' also denotes a reference veriable in C++ (there are no references in C)

VALGRIND OUTPUTS:
1. Completed code with no memory leaks:
  ==1372484== HEAP SUMMARY:
==1372484==     in use at exit: 0 bytes in 0 blocks
==1372484==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==1372484== 
==1372484== All heap blocks were freed -- no leaks are possible
==1372484== 
==1372484== For lists of detected and suppressed errors, rerun with: -s
==1372484== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

2. Code with memory leaks:
==1372786== HEAP SUMMARY:
==1372786==     in use at exit: 36,196 bytes in 72 blocks
==1372786==   total heap usage: 73 allocs, 1 frees, 37,220 bytes allocated
==1372786== 
==1372786== LEAK SUMMARY:
==1372786==    definitely lost: 36,196 bytes in 72 blocks
==1372786==    indirectly lost: 0 bytes in 0 blocks
==1372786==      possibly lost: 0 bytes in 0 blocks
==1372786==    still reachable: 0 bytes in 0 blocks
==1372786==         suppressed: 0 bytes in 0 blocks
==1372786== Rerun with --leak-check=full to see details of leaked memory
==1372786== 
==1372786== For lists of detected and suppressed errors, rerun with: -s
==1372786== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
