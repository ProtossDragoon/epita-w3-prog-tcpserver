#include <stdlib.h>
#include <unistd.h>
#include <err.h>

#define BUFFER_SIZE 512

void rewrite(int fd, const void *buf, size_t count)
{
    size_t w = 0;
    size_t b_left = count - w;
    do {
        w = write(fd, buf, b_left);
        if (w == -1) {
            err(EXIT_FAILURE, "write()");
        }
        b_left = count - w;
        buf = buf + w;
    }
    while (b_left > 0);
}

void echo(int fd_in, int fd_out)
{
    // 1. ✅ Read some data from fd_in.
    // 2. ✅ Use the read(2) function to store this data into a buffer of characters 
    //    ✅ (the size of this buffer should be 512 characters).
    // 3. ✅ Store the return value of the read() function into the r variable.
    // 4. ✅ When all the data has been read (r = 0), 
    //    ✅ you must break the loop and return from the function.
    // 5. ✅ If an error occurs (r = -1), 
    //    ✅ you must exit the program with an error message.
    // 6. ✅ When some data is in the buffer, 
    //    ✅ you must send it to fd_out. To do so,
    //    ✅ use the rewrite() function from a previous practical.
    char buffer[BUFFER_SIZE];
    size_t r = 1;
    do {
        r = read(fd_in, buffer, BUFFER_SIZE);
        if (r == -1) {
            err(EXIT_FAILURE, "read()");
        }
        rewrite(fd_out, buffer, r);
    }
    while(r > 0);
}