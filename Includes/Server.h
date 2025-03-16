#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

typedef struct server{

	int server_fd;
	struct sockaddr_in server_addr;
	
} Server;



bool initializeServer(unsigned long int port, Server *server);
bool RunServer(unsigned long int port);




#endif