#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>

void catch(int sth) {
	wait(NULL);
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		errx(EXIT_FAILURE, "Usage:\nArg 1 = Port number (e.g. 2048)");
	}
	
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;	

	struct addrinfo* p_addrinfo = NULL;
	int err = getaddrinfo(NULL, argv[1], &hints, &p_addrinfo);
	if (err != 0) {
		errx(err, "getaddrinfo(): %s", gai_strerror(err));
	}

	int sfd = -1;
	for (struct addrinfo* p = p_addrinfo; p != NULL; p = p->ai_next) {
		sfd = socket(
			p->ai_family,
			p->ai_socktype,
			p->ai_protocol
		);
		if (sfd == -1) {
			continue;
		}
		int opt_val = 1;
		err = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val));
		if (err != 0) {
			errx(err, "setsockopt()");
		}
		if (bind(sfd, p->ai_addr, p->ai_addrlen) == 0) {
			break;	
		}
		close(sfd);
	}
	freeaddrinfo(p_addrinfo);
	if (sfd == -1) {
		errx(sfd, "socket(), bind()");
	}
	
	err = listen(sfd, 5);
       	if (err != 0) {
		errx(-1, "listen()");
	}

	signal(SIGCHLD, catch);
	while (1) {
		int accepted_sfd = accept(sfd, NULL, NULL);
		if (accepted_sfd == -1) {
			close(sfd);
			errx(-1, "accept()");
		}
		pid_t pid = fork();
		if (pid == 0) {
			close(sfd);
            		dup2(accepted_sfd, STDIN_FILENO);
           		dup2(accepted_sfd, STDOUT_FILENO);
            		dup2(accepted_sfd, STDERR_FILENO);
            		err = execlp("bc", "bc", NULL);
            		close(accepted_sfd);
            		if (err == -1) {
                		errx(-1, "exec()");
            		}
            		exit(0);
		} 
		else {
			close(accepted_sfd);
		}
	}
	close(sfd);
	return 0;
}
