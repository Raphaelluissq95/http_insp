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
		printf("\nEnviando %d request(s)...\n", (int) toSendRqst.size());

		for (auto &i : toSendRqst) {
			printf("\nEnviando request para %s:%s\n", i.host.c_str(), i.port.c_str());
			printf("\n%s\n", i.to_string().c_str());
			if(packOut.Send(i) == -1){
				printf("\nNão foi possível enivar request\n");
				exit(1);
			}
		}
		
		toSendRqst.clear();
	}
	
	running &= packOut.responseRcv();

	if(!responsesRcv.empty())
		std::swap(responsesRcv, toSendRsp);

	if(!toSendRsp.empty()) {
		printf("\nEnviando %d response(s)...\n", (int) toSendRsp.size());

		for(auto &i : toSendRsp) {
			printf("\nResponse: \n%s\n", i.to_string().c_str());
			if(packIn.Send(i) == -1){
				printf("\nNão foi possível enivar response\n");
				exit(1);
			}
		}

		toSendRsp.clear();
	}

	return running;
}