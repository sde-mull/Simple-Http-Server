#include "HTTPServer.h"

bool RunServer(unsigned long int port){
	
	Server server = {0};
	
	if (!initializeServer(port, &server))
		return false;

	GetClientConnections(&server);
	
	return true;

}

bool initializeServer(unsigned long int port, Server *server){

	printf("Initializing the server on port %lu...\n", port);

	//create server socket
	server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if ((server->server_fd < 0)){
		perror("socket failed\n");
		return false;
	}

	printf("Socket created successfully\n");

	//Configurate the socket

	server->server_addr.sin_family = AF_INET;
	server->server_addr.sin_addr.s_addr = INADDR_ANY;
	server->server_addr.sin_port = htons(port);
	
	if (bind(server->server_fd, (struct sockaddr *)&server->server_addr, sizeof(server->server_addr)) < 0){
		perror("Bind failed\n");
		close(server->server_fd);
		return false;
	}

	printf("Bind created successfully!\n");

	if (listen(server->server_fd, 10) < 0){
		perror("Listen failed");
		close(server->server_fd);
		return false;
	}

	printf("Server is listening on port %lu\n", port);

	return true;

}