#ifndef PACKIN_H
#define PACKIN_H

#include <string>
#include <vector>
#include <memory>

#include <unistd.h>

#include "Header.h"
#include "Data.h"

class PackIn {
public:
	int svSocket = -1;

	typedef std::tuple< HTTP::Header > Request;

	explicit PackIn( int port );
	~PackIn();
	
	void accConn();
	void getRequests();
	ssize_t Send( HTTP::Header msg );

	std::vector< HTTP::Header > requestsRcv;
};

#endif // PACKIN_H