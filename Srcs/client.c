#include "HTTPServer.h"


const char *get_file_extension(const char *file_name) {
    const char *dot = strrchr(file_name, '.');
    if (!dot || dot == file_name) {
        return "";
    }
    return dot + 1;
}

char *buildResponse(const char *file_name){

	int 	file_fd = 0;
	char 	*response = NULL;
	char 	*header = NULL;
	size_t 	response_len = 0;
	const char *path = "../Contents/";
	char full_path[BUFFER_SIZE];

	
	header = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!header)
		return NULL;
	response = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!response)
		return NULL;
	
	if (file_name == NULL || strlen(file_name) == 0) {
		printf("Error: No file specified\n");
		snprintf(response, BUFFER_SIZE, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n400 Bad Request");
		return response;
	}

	const char *file_ext = get_file_extension(file_name);
	const char *mime_type = getMimeType(file_ext);

	snprintf((char *)header, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", mime_type);

	snprintf(full_path, BUFFER_SIZE, "%s%s", path, file_name);

	file_fd = open(full_path, O_RDONLY);
	if (file_fd == -1){
		snprintf(response, BUFFER_SIZE, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found");
		return response;
	}

	struct stat file_stat;
    fstat(file_fd, &file_stat);
    off_t file_size = file_stat.st_size;


	memcpy(response, header, strlen(header));

	response_len = strlen(header);

	ssize_t bytes_read;
    while ((bytes_read = read(file_fd, 
                            response + response_len, 
                            BUFFER_SIZE - response_len)) > 0) {
        response_len += bytes_read;
    }

	printf("%s\n", response);

	free(header);
    close(file_fd);
	return response;
}

void *handleClient(void  *arg){

	int 		client_fd = *(int *)arg;
	char 		file_ext[10];
	char 		*file_name = NULL;
	char		*response = NULL;

	file_name = getRequest(&client_fd);
	if (!file_name){
		free(file_name);
		return NULL;
	}


	response = buildResponse(file_name);


	send(client_fd, response, strlen(response), 0);

	free(file_name);
	free(arg);
	free(response);
	close(client_fd);

	return NULL;
}



const char *getMimeType(const char *file_ext) {
    if (strcasecmp(file_ext, "html") == 0 || strcasecmp(file_ext, "htm") == 0) {
        return "text/html";
    } else if (strcasecmp(file_ext, "txt") == 0) {
        return "text/plain";
    } else if (strcasecmp(file_ext, "js") == 0) {
        return "application/javascript";
    } else if (strcasecmp(file_ext, "css") == 0) {
        return "text/css";
    } else {
        return "application/octet-stream";
    }
}



void GetClientConnections(Server *server) {

	Client client = {0};
	
	while (1) {
		
		client.client_addr_len = sizeof(client.client_addr);
		client.client_fd = (int *)malloc(sizeof(int));
		if (!client.client_fd){
			perror("malloc failed\n");
			return ;
		}

		printf("Waiting to accept connection...\n");
	 	*client.client_fd = accept(server->server_fd, (struct sockaddr *)&client.client_addr, &client.client_addr_len);
		if (*client.client_fd < 0) {
			perror("Client Accept Failed\n");
			continue ;
		}

		printf("Connection Accepted: %d\n", *client.client_fd);

		pthread_t thread_id;
		pthread_create(&thread_id, NULL, handleClient, (void *)client.client_fd);
		pthread_detach(thread_id);
	}
}


char *getRequest(int *client_fd) {
	regex_t reegex;
	regmatch_t matches[2];
	

	char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer){
		perror("buffer malloc failed");
		return NULL;
	}
 
	ssize_t bytes_received = recv(*client_fd, buffer, BUFFER_SIZE, 0);
	if (bytes_received < 0)
		return NULL;
	
	buffer[bytes_received] = '\0';

	

	if (regcomp(&reegex, "^GET /([^ ]*) HTTP/1", REG_EXTENDED)){
		printf("Failed to compile regex\n");
		free(buffer);
		return NULL;	
	}

	if (regexec(&reegex, buffer, 2, matches, 0) != 0){
		printf("No match found\n");
		regfree(&reegex);
		free(buffer);
		return NULL;
	}
	
	int start = matches[1].rm_so;
	int end = matches[1].rm_eo;
	int length = end - start;

	char *file_name = (char *)malloc(length + 1);
	if (!file_name) {
		perror("malloc failed for file_name");
		regfree(&reegex);
		free(buffer);
		return NULL;
	}

	strncpy(file_name, buffer + start, length);
	file_name[length] = '\0';

	free(buffer);
	regfree(&reegex);

	return (file_name);
}