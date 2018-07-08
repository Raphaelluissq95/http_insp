#include<cstdlib>
#include<cstdio>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include "PackOut.h"

PackOut::PackOut() = default;

PackOut::~PackOut() = default;

ssize_t PackOut::Send(int rqstSocket, HTTP::Header msg){
	ssize_t sent = send(rqstSocket, msg.to_string().c_str(), msg.to_string().length(), 0);
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
	std::string message;
	do {
		char buffer[1024];
		valread = static_cast<int>(read(1, buffer, sizeof( buffer ) ));
		message += std::string(buffer, static_cast<unsigned long>(valread));
	} while (valread == 1024);
	if(valread > 0) {
		msgData md = msgData();
		// md.message = message;
		// md.addr_from = std::string( rqstSocket.addr.sin_addr );
		// md.port_from = ntohs( rqstSocket.addr.sin_port );
		// md.addr_to = "127.0.0.1";
		// md.port_to = "8228";
		responsesRcv.push_back(md);
		run = true;
	} else if( 0 == valread ) {
		printf("\nNão há requests para serem lidos\n");
		run = false;
	} else {
		printf( "\nFalha na leitura de dados\n" );
		run = false;
	}

	return run;
}