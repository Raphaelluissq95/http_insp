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
		printf("\nEnviando %d request...\n", (int) toSendRqst.size());

		for (auto &i : toSendRqst) {
			printf("\nRequest: \n%s\n", i.to_string(false).c_str());
			if(packOut.Send(packIn.svSocket, i) == -1){
				printf("\nNão foi possível enivar request\n");
				exit(1);
			}
		}
		
		toSendRqst.clear();
	}
	
	running &= packOut.responseRcv();
	printf("%s\n", (running)? "true":"false");

	if(!responsesRcv.empty())
		std::swap(responsesRcv, toSendRsp);

	if(!toSendRsp.empty()) {
		printf("\nEnviando %d responses...\n", (int) toSendRsp.size());

		for(auto &i : toSendRsp) {
			printf("\nResponse: \n%s\n", i.to_string(false).c_str());
			if(packIn.Send(i) == -1){
				printf("\nNão foi possível enivar response\n");
				exit(1);
			}
		}

		toSendRsp.clear();
	}

	return running;
}