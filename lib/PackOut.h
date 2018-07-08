#ifndef PACKOUT_H
#define PACKOUT_H

#include <string>
#include <vector>
#include <memory>

#include <unistd.h>

#include "Header.h"

class PackOut {
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

	typedef std::tuple< msgData, HTTP::Header > Response;

	PackOut();
	~PackOut();

	ssize_t Send( int rqstSocket, HTTP::Header msg );
	bool responseRcv(int svSocket);

	std::vector< msgData > responsesRcv;
private:
	int rqstedSocket;
};

#endif // PACKOUT_H