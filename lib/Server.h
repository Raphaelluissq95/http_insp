#ifndef SERVER_H
#define SERVER_H

#include <vector>

#include "PackOut.h"
#include "PackIn.h"
#include "Header.h"

class Server {
public:
	Server( int port );
	~Server();
	bool Init();
	
	bool running;
	std::vector< PackIn::msgData > &requestsRcv;
	std::vector< PackIn::msgData > toSendRqst;
	std::vector< PackOut::msgData > &responsesRcv;
	std::vector< PackOut::msgData > toSendRsp;
private:
	PackIn packIn;
	PackOut packOut;
};

#endif // SERVER_H