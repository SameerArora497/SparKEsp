#ifndef CONST_H
#define CONST_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <vector>
#include <errno.h>
#include <stdio.h>
#include <sys/un.h>

#define SOCKET_NAME "\0kuontol"
#define BACKLOG 8 //8 //32 //126 
#define PacketSize 4096 //1024 //2048 //4096 //8192 

#endif //CONST_H
