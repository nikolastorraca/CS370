HW3: Inter-Process Communications
Nikolas Torraca

Files:
-Starter.c: This file contains the main function. It takes a file name as input and sends the filename to Reader through a pipe. It then creates numerous child processes that
            perform additional operations on the data received back from Reader.c
-Reader.c: This file reads the filename via pipe and calculates a running sum of the data in the file.
-Lucas.c: This file calculates infomation based on it's input (from Starter.c) and the lucas sequence.
-HexagonalSeries.c: This file calculates infomation based on it's input (from Starter.c) and the hexagonal sequence.
-HarmonicSeries.c: This file calculates infomation based on it's input (from Starter.c) and the harmonic sequence.

Questions:
    1. 0 is the read end and 1 is the write end.
    2. The file descriptor is the write end of the pipe. This should be closed when reading from the pipe/after you have writen to the pipe.
    3. mmap is the function used to map file or devices to memory
    4. shm_open() is the name of the function used to open a shared memory object. It returns either a non-negative integer representing the lowest numbered unused file descriptor
       or -1 to indicate an error.
