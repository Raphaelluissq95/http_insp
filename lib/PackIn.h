#ifndef PACKIN_H
#define PACKIN_H

#include <string>
#include <vector>
#include <memory>

#include <unistd.h>

#include "Header.h"

class PackIn {
public:
	typedef struct {
		std::string message;

		std::string addr_from;
		int port_from;

		std::string addr_to;
		int port_to;

		int host;
		int port;
	} msgData;

	typedef std::tuple< msgData, HTTP::Header > Request;

	explicit PackIn( int port );
	~PackIn();
	
	void accConn();
	void getRequests();
	ssize_t Send( int rcvSocket, HTTP::Header msg );

	std::vector< msgData > requestsRcv;
};

#endif // PACKIN_H