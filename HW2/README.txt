HW2 - Parent and Child Processes
Nikolas Torraca

Questions:
1.  Fork() returns 0 to the child process and the process ID of the child process to the parent process. 
2.  A Fork() call could fail if the system-imposed limit on total number of processes under execution would be exceeded. It could also fail if there is insufficient 
    space for the new process.
3.  WEXITSTATUS returns 8 bits.
4.  #include <sys/wait.h>
5.  In this program, we are using sequential processing because only one child process is running at a time. The child process finishes and the wait command finishes executing in 
    the parent process before we execute the next fork() command.
6.  Yes it is possible to have anomalies in the ouput from child process and the output from parent process. The child process can have a new program loaded into it.

Output from running ./Generator input.txt:
[Generator 2312714]: Waiting for the child process 2312715
[Lucas 2312715]: The sum of the first 3 numbers of the Lucas series is 6
[Lucas 2312715]: The nth number in the lucas series is 3
[Generator 2312714]: Child process 2312715 returned 6
[Generator 2312714]: Waiting for the child process 2312716
[HexagonalSeries 2312716]: The sum of the first 6 numbers of the Hexagonal series is 161
[HexagonalSeries 2312716]: The nth number in the Hexagonal series is 66
[Generator 2312714]: Child process 2312716 returned 6
[Generator 2312714]: Waiting for the child process 2312717
[HarmonicSeries 2312717]: The sum of the first 6 numbers of the Harmonic series is 2.450000
[HarmonicSeries 2312717]: The nth number in the Harmonic series is 0.166667
[Generator 2312714]: Child process 2312717 returned 2
[Generator 2312714]: The lucas child process returned 6
[Generator 2312714]: The Hexagonal child process is 6
[Generator 2312714]: The sum of the first n Harmonic numbers is 2
[Generator 2312714]: Waiting for the child process 2312718
[Lucas 2312718]: The sum of the first 10 numbers of the Lucas series is 198
[Lucas 2312718]: The nth number in the lucas series is 76
[Generator 2312714]: Child process 2312718 returned 10
[Generator 2312714]: Waiting for the child process 2312719
[HexagonalSeries 2312719]: The sum of the first 10 numbers of the Hexagonal series is 715
[HexagonalSeries 2312719]: The nth number in the Hexagonal series is 190
[Generator 2312714]: Child process 2312719 returned 10
[Generator 2312714]: Waiting for the child process 2312720
[HarmonicSeries 2312720]: The sum of the first 10 numbers of the Harmonic series is 2.928968
[HarmonicSeries 2312720]: The nth number in the Harmonic series is 0.100000
[Generator 2312714]: Child process 2312720 returned 2
[Generator 2312714]: The lucas child process returned 10
[Generator 2312714]: The Hexagonal child process is 10
[Generator 2312714]: The sum of the first n Harmonic numbers is 2