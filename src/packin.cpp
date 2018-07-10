/**
 * @file packin.cpp
 * @brief Código responsável pelo manuseio do socket de entrada do proxy
 *
 * Neste módulo, será feito a criação do socket do proxy e a linkagem com o servidor que deseja acessar para que seja possível interceptar o request.
 *
 * @author Raphael Queiroz
 * @author Felipe Brandão
*/
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>

#include "PackIn.h"

int inSocket = -1;
int portNum;
struct sockaddr_in server_addr;
socklen_t size;

/**
 * @fn PackIn()
 * @brief Código responsável pela criação do socket de entrada do proxy
 *
 * @param port - número da porta recebida na hora de rodar o executável
 * @return
*/
PackIn::PackIn(int port) {
	portNum = port;
	inSocket = socket(AF_INET, SOCK_STREAM, 0);

	if(inSocket < 0) {
		printf("\nErro de criação de socket\n");
		exit(1);
	}

	printf("\nServer socket connection criado\n");
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(static_cast<uint16_t>(port));

	if(bind(inSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		printf("\nErro no bind do socket\n");
		exit(1);
	}

	printf("\nSocket binded\n");
	size = sizeof(server_addr);
	printf("\nProcurando cliente...\n");

	listen(inSocket,10);
}

PackIn::~PackIn() = default;

/**
 * @fn accCon()
 * @brief Código responsável pela aceitação do socket de entrada do proxy
 *
 * @param
 * @return
*/
void PackIn::accConn() {
	svSocket = accept(inSocket, nullptr, nullptr);
	if(svSocket < 0) {
		printf("\nErro na aceitação de conexão\n");
		exit(1);
	}
}

/**
 * @fn getRequests()
 * @brief Código responsável por receber os requests enviados no socket de entrada
 *
 * @param
 * @return
*/
void PackIn::getRequests() {
	int valread = 0;
	std::string message;

	do {
		char buffer[1024];
		valread = static_cast<int>(read(svSocket, buffer, sizeof( buffer ) ));
		message += std::string(buffer, static_cast<unsigned long>(valread));
	} while (valread == 1024);

	if(valread > 0) {
		requestsRcv.push_back(HTTP::Header(message));
	} else if( 0 == valread ) {
		printf("\nNão há requests para serem lidos\n");
	} else {
		printf( "\nFalha na leitura de dados\n" );
	}
}

/**
 * @fn Send()
 * @brief Código responsável por enviar a mensagem no socket de entrada para o cliente
 *
 * @param msg - mensagem recebida do servidor já no formato HTTP
 * @return sent - valor de checagem de mensagem enviada ou não (0 para mensagem enviada, c.c. mensagem não enviada)
*/
ssize_t PackIn::Send(HTTP::Header msg){
	ssize_t sent = send(svSocket, msg.to_string().c_str(), msg.to_string().length(), 0);
	if(sent < 0){
		printf("\nNão foi possível enviar dado\n");
		exit(1);
	} else {
		return sent;
	}
}