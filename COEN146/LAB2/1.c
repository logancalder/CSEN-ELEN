// Name: Logan Calder
// Date: 01/16/2025
// Title: Lab2 – Step 1
// Description: This program copies a file from a source file to a destination file using functions and syscalls.

#include <stdio.h>	  // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>	  // malloc(), free()
#include <pthread.h>  // pthread_create()
#include <unistd.h>	  // read(), write()
#include <fcntl.h>	  // open(), close()
#include <errno.h>	  // errno
#include <time.h>	  // clock()
#include <sys/mman.h> // mmap()

#define BUF_SIZE 2048

// Data structure to hold thread parameters
struct copy_struct
{
	int thread_id;
	char *src_filename;
	char *dst_filename;
};

// Copies a file from src_filename to dst_filename
int func_copy(char *src_filename, char *dst_filename)
{
	FILE *src, *dst;
	char *buf;
	int b_read;

	src = fopen(src_filename, "r");
	if (src == NULL)
	{
		fprintf(stderr, "Unable to open %s for reading: %i\n", src_filename, errno);
		return -1;
	}

	dst = fopen(dst_filename, "w");
	if (dst == NULL)
	{
		fprintf(stderr, "Unable to open/create %s for writing: %i\n", dst_filename, errno);
		fclose(src);
		return -1;
	}

	buf = malloc(BUF_SIZE);

	while ((b_read = fread(buf, 1, BUF_SIZE, src)) > 0)
	{
		fwrite(buf, 1, b_read, dst);
	}

	free(buf);
	fclose(src);
	fclose(dst);
	return 0;
}

// copies a files form src_filename to dst_filename using syscalls open(), read(), write(), close()
int syscall_copy(char *src_filename, char *dst_filename)
{
	FILE *src, *dst;			// file pointers for source and destination files
	int src_fd, dst_fd, b_read; // file descriptors for source and destination files
	char *buf;					// buffer to store read data

	src_fd = open(src_filename, O_RDONLY); // opens a file for reading

	if (src_fd < 0)
	{ // open() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		close(src_fd);
		exit(0);
	}
	// O_WRONLY - write only
	// O_CREAT - create file if it doesn't exist
	// O_TRUNC - truncates file to length 0 if it already exists (deletes existing file)
	// opens a file for writing; erases old file/creates a new file

	dst_fd = open(dst_filename, O_WRONLY | O_CREAT | O_TRUNC);
	if (dst_fd < 0)
	{ // open() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		close(dst_fd);
		exit(0);
	}

	// read/ write loop
	buf = malloc(BUF_SIZE);

	// reads up to BUF_SIZE bytes from src_filename
	// writes bytes_read to dst_filename
	while ((b_read = read(src_fd, buf, BUF_SIZE)) > 0)
	{
		// writes bytes_read to dst_filename
		write(dst_fd, buf, b_read);
	}

	close(src_fd);
	close(dst_fd);
	free(buf);

	return 0;
}

void check_copy_times(void *arg)
{
	struct copy_struct *params = (struct copy_struct *)arg;
	clock_t func_start, func_end, syscall_start, syscall_end;
	double func_time, syscall_time;

	// capture runtime of func_copy() using start clock, call the copy, end the clock
	printf("thread[%i] - copying using funcs %s to %s\n", params->thread_id, params->src_filename, params->dst_filename);
	func_start = clock();
	func_copy(params->src_filename, params->dst_filename);
	func_end = clock();

	// capture runtime of syscall_copy() using start clock, call the copy, end the clock
	printf("thread[%i] - copying using sys %s to %s\n", params->thread_id, params->src_filename, params->dst_filename);
	syscall_start = clock();
	syscall_copy(params->src_filename, params->dst_filename);
	syscall_end = clock();

	// calculate the runtime of each copy
	func_time = (double)(func_end - func_start) / CLOCKS_PER_SEC;
	syscall_time = (double)(syscall_end - syscall_start) / CLOCKS_PER_SEC;

	printf("time to copy using functions: %.7f\n", func_time);
	printf("time to copy using syscalls: %.7f\n", syscall_time);
}

int main(int argc, char *argv[])
{
	if (argc < 3 || (argc - 1) % 2 != 0)
	{
		fprintf(stderr, "Usage: %s <src_1> <dst_1> <src_2> <dst_2> ... <src_n> <dst_n>\n", argv[0]);
		exit(1);
	}

	int num_files = (argc - 1) / 2;
	pthread_t threads[num_files];
	struct copy_struct *thread_params = malloc(num_files * sizeof(struct copy_struct));

	if (thread_params == NULL)
	{
		fprintf(stderr, "Memory allocation for thread parameters failed\n");
		exit(1);
	}

	for (int i = 0; i < num_files; i++)
	{
		thread_params[i].thread_id = i;
		thread_params[i].src_filename = argv[1 + i];
		thread_params[i].dst_filename = argv[1 + num_files + i];

		if (pthread_create(&threads[i], NULL, check_copy_times, &thread_params[i]) != 0)
		{
			fprintf(stderr, "Error creating thread[%i]\n", i);
			free(thread_params);
			exit(1);
		}
	}

	for (int i = 0; i < num_files; i++)
	{
		pthread_join(threads[i], NULL);
	}

	free(thread_params);
	pthread_exit(NULL);
}
