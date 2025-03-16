#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <regex.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "Checks.h"
#include "Server.h"
#include "Client.h"

#define MAX_PORT_NUMBER 65535 //Max port number to choose
#define DEFAULT_PORT 3000 //Default port if not specified
#define BUFFER_SIZE 5000
#define HEADER_BUFFER 250



#endif