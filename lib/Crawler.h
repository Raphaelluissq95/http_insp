#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>
#include <vector>

struct Crawler {
public:
	Crawler( std::string hostName, std::string name, std::string HTTPResp);
	std::string getName();
	std::string getInfoName();
	std::vector< std::string > getResources();
	bool savePath( std::string path );
private:
	std::string hostName;
	std::string name;
	std::string infoName;
	std::string headerData;
	std::vector< std::string > refResources;
};

#endif //CRAWLER_H