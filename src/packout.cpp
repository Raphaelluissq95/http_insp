#include<cstdlib>
#include<cstdio>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include <iostream>
#include <sstream>

#include "PackOut.h"

PackOut::PackOut() = default;

PackOut::~PackOut() = default;

int outSocket = -1;
struct addrinfo client_addr;
struct addrinfo *addr_c;

ssize_t PackOut::Send(HTTP::Header msg){
	client_addr.ai_family = AF_INET;
	client_addr.ai_socktype = INADDR_ANY;
	client_addr.ai_flags = 0;
	client_addr.ai_protocol = 0;

	int info = getaddrinfo( msg.host.c_str(), msg.port.c_str(), &client_addr, &addr_c);
	if(info == 0){
		outSocket = socket(AF_INET, SOCK_STREAM, 0);
		if(outSocket < 0){
			printf("\nErro ao criar out socket\n");
			exit(1);
		} 
		if(connect(outSocket, addr_c->ai_addr, addr_c->ai_addrlen) < 0){
			printf("\nErro na conexão do socket\n");
			exit(1);
		}
	}

	ssize_t sent = send(outSocket, msg.to_string().c_str(), msg.to_string().length(), 0);

	if(sent < 0){
		printf("\nNão foi possível enviar dado\n");
		exit(1);
	} else {
		return sent;
	}

	return -1;
}

bool PackOut::responseRcv(){
	bool run = true;
	
	int valread = 0;
	std::string message("");

	do {
		char buffer[1024];
		valread = static_cast<int>(read(outSocket, buffer, sizeof( buffer ) ));
		message += std::string(buffer, static_cast<unsigned long>(valread));
	} while (valread == 1024);

	if(valread > 0) {
		responsesRcv.push_back(HTTP::Header(message));
		run = true;
	} else if( 0 == valread ) {
		printf("\nNão há responses para serem lidos\n");
		run = false;
	} else {
		printf( "\nFalha na leitura de dados\n" );
		run = false;
	}

	return run;
}