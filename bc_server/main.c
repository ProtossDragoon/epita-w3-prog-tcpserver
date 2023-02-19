#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>

struct addrinfo get_server_hints()
{
    // Create the 'hints' structure.
    struct addrinfo hints;

    // Initialize all the fields to zero.
    memset(&hints, 0, sizeof(hints));

    // Specify the criteria
    hints.ai_family = AF_INET; // IPv4 
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE; // Server

    return hints;
}

int get_binded_socket(struct addrinfo *result)
{
    int sfd;
    int err;
    for (struct addrinfo *p = result; p != NULL; p = p->ai_next) {
        // Try to create a socket
        sfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        // If error, continue with the next iteration
        if (sfd == -1) {
            continue;
        }

        int optval = 1;
        err = setsockopt(
            sfd, SOL_SOCKET, SO_REUSEADDR,
            &optval, sizeof(int));
        if (err == -1) {
            close(sfd);
            continue;
        }

        // try to bind the socket
        err = bind(sfd, p->ai_addr, p->ai_addrlen);
        // If successful, break the loop (p != 0)
        if (err == 0) {
            break;
        }
        // If error, close the socket
        else {
            close(sfd);
        }
    }
    freeaddrinfo(result);
    return sfd;
}

void child_handler(int sig)
{
    wait(NULL);
}

int main(int argc, char** argv)
{
    // Keep the same structure of your echo server (fork_server.c).
    // Remove the echo() function (you no longer need it).
    // Your bc server should not display any messages. 
    // For instance, you must not print any line indicating 
    // a successful connection or the pid of a child process.
    // You must provide two files only:
    // - main.c
    // - Makefile
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage:\n"
            "Arg 1 = Port number (e.g. 2048)");
    
    struct addrinfo hints = get_server_hints();
    struct addrinfo *result;

    // Get the linked list
    int err = getaddrinfo(NULL, argv[1], &hints, &result);
    if (err == -1) {
        errx(EXIT_FAILURE, "getaddrinfo: %s", gai_strerror(err));
    }

    // Get a socket
    int sfd = get_binded_socket(result);
    // No socket has been open
    if (sfd == -1) {
        errx(EXIT_FAILURE, "socket()");
    }
    
    // Mark the socket as passive
    // The socket can now be used to accept 
    // incoming connection requests
    err = listen(sfd, 5);
    // Exit if error
    if (err == -1) {
        close(sfd);
        errx(EXIT_FAILURE, "listen()");
    }

    // Loop forever
    printf("Waiting for connections...\n");
    while (1) {
        // Accept an incoming connection
        int cfd = accept(sfd, NULL, NULL);
        // If error, close the socket
        if (cfd == -1) {
            close(sfd);
            errx(EXIT_FAILURE, "accept()");
        }
        // Create a new process
        pid_t pid = fork();
        // Child Process
        if (pid == 0) {
            printf("New connection (pid = %i)\n", getpid());
            close(sfd); 
            dup2(cfd, 0); // cfd: redirect to the bc STDIN
            dup2(cfd, 1); // cfd: redirect from the bc STDOUT
            dup2(cfd, 2); // cfd: redirect from the bc STDERR
            execlp("bc", "bc", NULL);
            close(cfd);
            exit(EXIT_SUCCESS);
        }
        // Parent Process
        else if (pid > 0) {
            // Close the connection socket.
            close(cfd);
            signal(SIGCHLD, child_handler);
            continue;
        }
        // Error: No Child Process is Created
        else {
            close(cfd);
            close(sfd);
            errx(EXIT_FAILURE, "fork()");
        }
    }
    close(sfd);
}
