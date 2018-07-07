#include <cstdlib>
#include <cstdio>
#include <memory>

#include "Server.h"
#include "Header.h"

Server::Server(int portNum) : requestsRcv(packIn.requestsRcv)
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
		printf("\nEnviando requests...\n");
		for(int i = 0;i < (int) toSendRqst.size();i++){
			printf("\nEnviando para\n"
			);
			printf("\n\n"
			);			
		}

		toSendRqst.clear();
	}

	packOut.responseRcv();

	if(packOut.responsesRcv.size() > 0)
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

	return true;
}