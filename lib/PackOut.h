#ifndef PACKOUT_H
#define PACKOUT_H

#include <string>
#include <vector>
#include <memory>

#include <unistd.h>

#include "Header.h"
#include "Data.h"

class PackOut {
public:
	typedef std::tuple< HTTP::Header > Response;

	PackOut();
	~PackOut();

	ssize_t Send( int rqstSocket, HTTP::Header msg );
	bool responseRcv();

	std::vector< HTTP::Header > responsesRcv;
private:
	int rqstedSocket;
};

#endif // PACKOUT_H