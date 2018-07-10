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
	PackOut();
	~PackOut();

	ssize_t Send( HTTP::Header msg );
	void responseRcv();

	std::vector< HTTP::Header > responsesRcv;
};

#endif // PACKOUT_H