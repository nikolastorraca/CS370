/*
 * HW1: Dynamic Memory Allocation
 * File: Executor.h
 * Developed by: Nik Torraca
 */

#ifndef FILE_INCLUDED
#define FILE_INCLUDED

//This function returns the ratio of prime #s to non-prime numbers in the arrays
//Input: None
//Output: Ratio of prime numbers
float get_running_ratio();

//Calculates a random number given an upper and lower bound
//Input: Upper and lower bounds
//Output: Random number
int random_in_range(int lower_bound, int upper_bound);

//Finds number of prime numbers in an array
//Input: Array
//       Length of array
//Output: Number of primes in array
int get_prime_count(int *array, int arraySize);


#endif // FILE_INCLUDED 
