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

Server::~Server() {}

bool Server::Init() {
	packIn.accConn();
	packIn.getRequests();

	if(requestsRcv.size() > 0)
		std::swap( requestsRcv, toSendRqst );

	if(toSendRqst.size() > 0){
		printf("\nEnviando %d request...\n"
			, (int) toSendRqst.size()
		);
		for(int i = 0;i < (int) toSendRqst.size();i++){
			printf("\nEnviando request..\n");
			printf("\nDe : %s:%d\n"
				, toSendRqst[i].addr_from.c_str()
				, toSendRqst[i].port_from
			);
			printf("\nPara : %s:%d\n"
				, toSendRqst[i].addr_to
				, toSendRqst[i].port_to
			);
			printf("\nRequest: \n\t%s\n"
				, toSendRqst[i].message.c_str()
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

	if(responsesRcv.size() > 0)
		std::swap(responsesRcv, toSendRsp);

	if(toSendRsp.size() > 0){
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