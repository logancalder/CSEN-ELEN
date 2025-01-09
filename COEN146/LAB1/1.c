// Name: Logan Calder
// Date: 01/06/2025
// Title: Lab1 – Steps 3
// Description: This program copies a file from a source file to a destination file using functions and syscalls.
// 				It then compares the runtime of each method.

// COEN 146L : Lab 1 - template to use for file transfer (steps 3, 4, and 5)
// You need to adapt this template according to the requirements of each of the steps

#include <stdio.h>    // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>   // malloc(), free()
#include <pthread.h>  // pthread_create()
#include <unistd.h>   // read(), write()
#include <fcntl.h>    // open(), close()
#include <errno.h>    // errno
#include <time.h>     // clock()
#include <sys/mman.h> // mmap()

#define BUF_SIZE 2048       // buffer size
FILE *src, *dst;            // file pointers for source and destination files
int src_fd, dst_fd, b_read; // file descriptors for source and destination files
char *buf;                  // buffer to store read data

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char *src_filename, char *dst_filename)
{

    src = fopen(src_filename, "r"); // opens a file for reading
    if (src == NULL)
    { // fopen() error checking
        fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
        exit(0);
    }
    dst = fopen(dst_filename, "w"); // opens a file for writing; erases old file/creates a new file
    if (dst == NULL)
    { // fopen() error checking
        fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
        exit(0);
    }

    buf = malloc((size_t)BUF_SIZE); // allocate a buffer to store read data
    // reads content of file is loop iterations until end of file
    while ((b_read = fread(buf, 1, BUF_SIZE, src)) > 0)
    {
        fwrite(buf, 1, b_read, dst);
    }
    // closes src file pointer
    fclose(src);
    // closes dst file pointer
    fclose(dst);
    // frees memory used for buf
    free(buf);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    { // check correct usage
        fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
        exit(1);
    }
    // get the source and destination files from the command line arguments
    // call the check copy times function
    func_copy(argv[1], argv[2]);
    return 0;
}