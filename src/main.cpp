/**
 * @mainpage HTTP Interceptor
 * @brief Programa que simula um interceptador de requisições e respostas do HTTP
 *
 * @section desc Descrição
 * @subsection obj Objetivo
 * Implementar um interceptador de HTTP e verificar os requests e responses com seus campos e valores7
 * @subsection intro Introdução
 * Este programa simula um interceptador de HTTP request e reply. Seu funcionamento depende de um proxy criado ao iniciar o programa para captura do HTTP.\n
 * Para essa captura, foi definida uma porta padrão para rodar o proxy e configurado o browser para rodar neste proxy definido. Os requests e replys irão ser interceptados pelo proxy
 * para que se possa ser avaliado a comunicação entre cliente-servidor.\n
 * O programa foi escrito em C++ e implementado sockets para a interceptação.
 *
 * @author Raphael Queiroz -- 13/0154989
 * @author Felipe Brandão -- 12/0044919
*/

/**
 * @file main.cpp
 * @brief Código responsável pelo início do programa
 *
 * Neste módulo, será o link entre os argumento do executável para a chamada do servidor proxy.
 *
 * @author Raphael Queiroz
 * @author Felipe Brandão
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Server.h"
// #include "Ui.h"

#define PORT_NUM 8228

/**
 * @fn main()
 * @brief Código principal para incício do programa. Recebe informação do executável para o início do servidor proxy.
 *
 * @param argc - inteiro que receberá a quantidade de argumentos colocar na hora da execução do executável
 * @param argv - vetor contendo os argumento colocados na execução
 * @return 0 - retorno padrão para main
 *
 * @author Raphael Queiroz
 * @author Felipe Brandão
*/
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

    // int stat = Ui::init_gtk(argc, argv);

    server.Init();

	return 0;
}