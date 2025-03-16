#include "HTTPServer.h"

bool checkNumberArgs(int args, char *argv[]){

	if (!args || args > 2){
		printf("Error:\nUsage: %s <port=3000>\n", argv[0]);
		printf("\nProgramm terminated...\n");
		return false;
	}
	return true;
}

unsigned long int checkPortNumber(char *port){

	char *endptr;
	errno = 0;

	unsigned long int portNumber = strtoul(port, &endptr, 10);

	if ((errno == ERANGE && (portNumber >= ULONG_MAX || portNumber == 0)) || \
	(errno != 0 && portNumber == 0) || portNumber > MAX_PORT_NUMBER){
		if (portNumber > MAX_PORT_NUMBER)
			printf("Max port range is %d\n", MAX_PORT_NUMBER);
			return 0;
		perror("strtoul");
		return 0;
	}


	return (portNumber);
}