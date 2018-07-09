#include <queue>
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <inttypes.h>
#include <string>

#include "Spider.h"

int spdSocket = -1;
int port;
struct sockaddr_in spd_addr;
struct sockaddr_in firstAddr;

Spider::Spider( std::string hostName) : download(false), hiperTextTree(hostName) {
	port = 80;

	spd_addr.sin_family = AF_INET;
	spd_addr.sin_addr.s_addr = htons(INADDR_ANY);
	spd_addr.sin_port = htons(static_cast<uint16_t>(port));

	spdSocket = socket(AF_INET, SOCK_STREAM, 0);

	if(spdSocket < 0) {
		printf("\nErro de criação de socket\n");
		exit(1);
	}

	if(bind(spdSocket, (struct sockaddr*)&spd_addr, sizeof(spd_addr)) < 0) {
		printf("\nErro no bind do socket\n");
		exit(1);
	}
	
	listen(spdSocket,10);

	std::queue< std::string > downloadCrawlerRsc;
	downloadCrawlerRsc.push( hostName );

	while( !downloadCrawlerRsc.empty()) {
		std::string request( "GET http://" );
		request += downloadCrawlerRsc.front();
		request += " HTTP/1.1\r\n";
		request += "Host: " + hostName + "\r\n";
		request += "Connection: keep-alive\r\n\r\n";

		ssize_t sent = send(spdSocket, request.c_str(), request.length(), 0);
		if( sent < 0 ){
			printf("\nNão foi possível enviar dado\n");
			exit(1);
		}

		int valread = 0;
		std::string message("");

		do {
			char buffer[1024];
			valread = static_cast<int>(read( spdSocket, buffer, sizeof( buffer )));
			message += std::string( buffer, static_cast<unsigned long>(valread));
		} while(valread == 1024);
		if(valread > 0) {
			rootTree.emplace_back( hostName, downloadCrawlerRsc.front(), message);
		} else if( 0 == valread ) {
			printf("\nNão há requests para serem lidos\n");
		} else {
			printf( "\nFalha na leitura de dados\n" );
		}

		downloadCrawlerRsc.pop();
	}

	download = true;
}

bool Spider::checkValidation() {
	return download;
}

long long int Spider::findRootPath( std::string rscName ){
	for(unsigned long int i = 0;i < rootTree.size();i++)
		if(rootTree[i].getName() == rscName ) return i;
	return -1;
}