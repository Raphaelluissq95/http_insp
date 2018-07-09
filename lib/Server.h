#ifndef SERVER_H
#define SERVER_H

#include <vector>

#include "PackOut.h"
#include "PackIn.h"
#include "Header.h"
#include "Data.h"

class Server {
public:
	explicit Server( int port );
	~Server();
	bool Init();
	
	bool running;
	std::vector< HTTP::Header > &requestsRcv;
	std::vector< HTTP::Header > toSendRqst;
	std::vector< HTTP::Header > &responsesRcv;
	std::vector< HTTP::Header > toSendRsp;
private:
	PackIn packIn;
	PackOut packOut;
};

#endif // SERVER_H