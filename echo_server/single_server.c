#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>
#include "echo.h"

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

int main(int argc, char** argv)
{
    // Your program will take one argument only: the port number.
    // The code of a server is similar to that of a client.
    // 1. ✅ First, you have to initialize an addrinfo structure. 
    //    ✅ Initialize all of its fields to zeros by using the memset(3) function 
    //    ✅ and set only the following fields:
    //    - ✅ ai_family should be equal to AF_INET (IPv4)
    //    - ✅ ai_socktype should be equal to SOCK_STREAM (TCP)
    //    - ✅ ai_flags should be equal to AI_PASSIVE (Server Mode)
    // 2. ✅ Use the getaddrinfo(3) function to get a linked list of addresses.
    // 3. Then, for each address:
    //    - ✅ Try to open a socket by using the socket(2) function. 
    //      ✅ If an error occurs, continue with the next address.
    //    - ✅ In order to reuse the same address immediately after closing a connection, 
    //      ✅ you have to set the SO_REUSEADDR to one. 
    //      ✅ To do so, use the setsockopt(2) function.
    //    - ✅ Try to bind the socket to the address by using the bind(2) function.
    //    - ✅ If no error occurs, break the loop.
    //    - ✅ If an error occurs, close the socket and continue with the next address.
    //    - ✅ Free the linked list.
    //    - ✅ If no socket has been open, exit the program with an error message.
    // 4. ✅ Specify that the socket can be used to accept incoming connections. 
    //    ✅ Use the listen(2) function (the value 5 for backlog will be enough). 
    //    ✅ If an error occurs, exit the program with an error message.
    // 5. ✅ Print a message saying that your server is waiting for connections.
    // 6. ✅ Wait for connections by using the accept(2) function. 
    //    ✅ A new connected socket is then created 
    //    ✅ and should be used to read from or write to the client. 
    //    ✅ If an error occurs, exit the program with an error message.
    // 7. ✅ Print any message showing that a connection is successful.
    // 8. ✅ Use the file descriptor of this new socket with your echo() function.
    // 9. Close the two sockets.
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

    printf("Waiting for connections...\n");
    // Accept an incoming connection
    int cfd = accept(sfd, NULL, NULL);
    // If error, close the socket
    if (cfd == -1) {
        close(sfd);
        errx(EXIT_FAILURE, "accept()");
    }
    printf("Connection successful!\n");
    // Read data from the client: read(cfd, ...)
    // Process the data
    echo(cfd, cfd);
    // Send the response: write(cfd, ...);
    // Close the connection socket.
    close(cfd);
    close(sfd);
}