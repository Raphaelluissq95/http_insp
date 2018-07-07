#include <cstdio>
#include <cstdlib>
#include "Server.h"

#define PORT_NUM 8228

int main() {
	int port = PORT_NUM;
	printf("Iniciando conexão com porta #%d\n",port);

	Server server(port);

	while(server.Init());

	return 0;
}