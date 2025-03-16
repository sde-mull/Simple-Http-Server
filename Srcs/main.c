#include "HTTPServer.h"

int main(int argc, char *argv[]){

	unsigned long int portNumber = 0;

	printf("Programm initialized...\n\n");

	// Check the number of arguments passed
	if (!checkNumberArgs(argc, argv))
		return (EXIT_FAILURE);

	// check port number
	if (argc == 2){		
		portNumber = checkPortNumber(argv[1]);
		
		if (!portNumber){
			printf("\nProgramm terminated...\n");
			return (EXIT_FAILURE);
		}
	}

	portNumber = (portNumber != 0) ? portNumber : DEFAULT_PORT;

	if (RunServer(portNumber))
		return (EXIT_FAILURE);


	printf("\nProgramm terminated...\n");
	return (0);
}