#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#include "PackIn.h"

int inSocket,svSocket;
struct sockaddr_in server_addr;
socklen_t size;

PackIn::PackIn(int port){
	inSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(inSocket < 0){
		printf("\nErro de criação de socket\n");
		exit(1);
	}

	printf("\nServer socket connection criado\n");
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port);

	if(bind(inSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		printf("\nErro no bind do socket\n");
		exit(1);
	}

	printf("\nSocket binded\n");
	size = sizeof(server_addr);
	printf("\nProcurando cliente...\n");

	listen(inSocket,1);	
}

PackIn::~PackIn() {}

void PackIn::accConn() {
	svSocket = accept(inSocket, (struct sockaddr*)&server_addr, &size);
	if(svSocket < 0){
		printf("\nErro na aceitação de conexão\n");
		exit(1);
	}
}

void PackIn::getRequests() {
	int valread = 0;
	std::string message("");
	do {
		char buffer[1024];
		valread = read( svSocket, buffer, sizeof( buffer ) );
		message += std::string( buffer, valread );
	} while (valread == 1024);
	if(valread > 0) {
		msgData md;
		// md.message = message;
		// md.addr_from = std::string( svSocket.addr.sin_addr );
		// md.port_from = ntohs( svSocket.addr.sin_port );
		// md.addr_to = "127.0.0.1";
		// md.port_to = port;
		requestsRcv.push_back(std::make_tuple(md, HTTP::Header(message)));
	} else if( 0 == valread ) {
		printf("\nNão há requests para serem lidos\n");
	} else {
		printf( "\nFalha na leitura de dados\n" );
	}
}

ssize_t PackIn::Send(int rcvSocket, HTTP::Header msg){
	ssize_t sent = send(rcvSocket, msg.to_string().c_str(), msg.to_string().length(), 0);
	if(sent < 0){
		printf("\nNão foi possível enviar dado\n");
		exit(1);
	} else {
		return sent;
	}

	return -1;
}