/**
 * @file packout.cpp
 * @brief Código responsável pelo manuseio do socket de saída do proxy
 *
 * Neste módulo, será feito a criação do socket do proxy e a linkagem com o servidor que deseja acessar para que seja possível interceptar o response.
 *
 * @author Raphael Queiroz
 * @author Felipe Brandão
*/
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

/**
 * @fn Send()
 * @brief Código responsável pela criação e envio do socket de saída do proxy
 *
 * @param msg - mensagem recebida da intercepção já no formato HTTP
 * @return sent - valor de checagem de mensagem enviada ou não (0 para mensagem enviada, c.c. mensagem não enviada)
*/
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

/**
 * @fn responsesRcv()
 * @brief Código responsável por receber os responses enviados pelo servidor
 *
 * @param
 * @return
*/
void PackOut::responseRcv(){
	int valread = 0;
	std::string message("");

	do {
		char buffer[1024];
		valread = static_cast<int>(read(outSocket, buffer, sizeof( buffer ) ));
		message += std::string(buffer, static_cast<unsigned long>(valread));
	} while (valread == 1024);

	if(valread > 0) {
		responsesRcv.push_back(HTTP::Header(message));
	} else {
		printf( "\nFalha na leitura de dados\n" );
		exit(1);
	}
}