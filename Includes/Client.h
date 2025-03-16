#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include "Server.h"

typedef struct s_client {

	struct sockaddr_in client_addr;
	int *client_fd;
	socklen_t client_addr_len;

} Client;


void 		GetClientConnections(Server *server);
void 		*handleClient(void  *arg);

const char 	*getMimeType(const char *file_ext);
char 		*getRequest(int *client_fd);


#endif