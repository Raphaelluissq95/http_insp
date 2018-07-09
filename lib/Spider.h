#ifndef SPIDER_H
#define SPIDER_H

#include<vector>

#include "Crawler.h"

class Spider {
public:
	Spider( std::string host );
	bool checkValidation();
private:
	long long int findRootPath( std::string rscName );
	bool download;
	std::string hiperTextTree;
	std::vector< Crawler > rootTree;
};

#endif //SPIDER_H