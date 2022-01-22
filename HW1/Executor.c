/*
 * HW1: Dynamic Memory Allcoation
 * File: Executor.c
 * Developed by: Nik Torraca
 */

int random_in_range(int lower_bound, int upper_bound)
{
    return ((rand() % (upper_bound - lower_bound)) + lower_bound);
}
