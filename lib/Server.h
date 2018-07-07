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
	
	std::vector< PackIn::Request > &requestsRcv;
	std::vector< PackIn::Request > toSendRqst;
	std::vector< PackOut::Response > &responsesRcv;
	std::vector< PackOut::Response > toSendRsp;
private:
	PackIn packIn;
	PackOut packOut;
};

#endif // SERVER_H