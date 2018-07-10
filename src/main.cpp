#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Server.h"

#define PORT_NUM 8228

int main(int argc, char * const argv[]) {
	long port;

	if (argc != 1) {
        if (argc != 3) {
            printf("\nO aplicativo deve ser usado da seguinte forma:\n# ./aracne [-p <port>[=8228]]\n");
            exit(EXIT_FAILURE);
        } else if (strcmp(argv[1], "-p") != 0) {
            printf("\nA unica opcao possivel eh [-p <port>[=8228]]\n");
            exit(EXIT_FAILURE);
        }

        port = strtol(argv[2], nullptr, 10); // convertendo a porta de string para long

        if (port < 1024 || port > 65535) {
            printf("\nO numero da porta deve estar no range valido de 1024 a 65535\n");
            exit(EXIT_FAILURE);
        }
    } else {
	    port = PORT_NUM;
	}

    printf("Iniciando conexão com porta #%ld\n", port);

	Server server((int) port);

    server.Init();

	return 0;
}