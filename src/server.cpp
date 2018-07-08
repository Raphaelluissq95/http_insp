#include <cstdlib>
#include <cstdio>
#include <memory>

#include "Server.h"
#include "Header.h"

Server::Server(int portNum) : running(true)
							, requestsRcv(packIn.requestsRcv)
							, responsesRcv(packOut.responsesRcv)
							, packIn( portNum )
							, packOut() {}

Server::~Server() = default;

bool Server::Init() {
	packIn.accConn();
	packIn.getRequests();

	if(!requestsRcv.empty())
		std::swap( requestsRcv, toSendRqst );

	if(!toSendRqst.empty()) {
		printf("\nEnviando %d request...\n"
			, (int) toSendRqst.size()
		);
		for (auto &i : toSendRqst) {
			printf("\nEnviando request..\n");
			printf("\nDe : %s:%d\n"
				, i.addr_from.c_str()
				, i.port_from
			);
			printf("\nPara : %s:%d\n"
				, i.addr_to
				, i.port_to
			);
			printf("\nRequest: \n\t%s\n"
				, i.message.c_str()
			);
			printf("Saí");
		}

		printf("Entrando no clear");
		toSendRqst.clear();
		printf("Saindo do clear");
	}

	printf("%s", (running)? "true":"false");
	running &= packOut.responseRcv();
	printf("%s", (running)? "true":"false");

	if(!responsesRcv.empty())
		std::swap(responsesRcv, toSendRsp);

	if(!toSendRsp.empty()) {
		printf("\nEnviando responses...\n");
		for(int i = 0;i < (int) toSendRsp.size();i++){
			printf("\nEnviando para \n"
			);
			printf("\n\n"
			);
		}

		toSendRsp.clear();
	}

	return running;
}