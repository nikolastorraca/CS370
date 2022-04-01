README
======

This package includes the following files.

|-- Coordinator.java - This file accepts the seed from the command line and generates a number of items. It then creates a buffer, and the Generator/Consumer threads. 
		Once the threads terminate, it prints out the sum of generated/consumed primes.

|-- Generator.java - The generater class produces random prime values and adds them to the buffer.

|-- Consumer.java - The consumer class consumes elements in the buffer.

|-- Buffer.java - Implementation of a FIFO circular buffer

|-- Makefile - make to compile, make clean to remove .class executables and make tar to package code into a tar file

|-- README.txt


Questions:

1. The problem of producer consumer is solved using Semaphores. - 1 point
	a. Mutex Locks
	b. Semaphores

2. What two functions defined in Java are used for synchronization between producer and consumers in your program? wait() and notifyAll(). - 2 points

3. In which function do you override the body to define the new body of a thread in java? We overrode public void run(). - 1 point

4. Which function is used to wait for a thread to finish and come back to calling program i.e. for a thread to die? join(). - 1 point

NOTE:

Lab systems by default use Java 11 which supports nanosecond timestamp. If after logging in and running 'java -version', it doesn't output version 11, use the following two commands:

	$ export PATH=/usr/lib/jvm/jre-11-openjdk/bin/:$PATH

	$ export LD_LIBRARY_PATH=/usr/lib/jvm/jre-11-openjdk/lib/:$LD_LIBRARY_PATH


