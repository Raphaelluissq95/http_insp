#include "Crawler.h"
#include "Header.h"

Crawler::Crawler(std::string hostName, std::string name, std::string HTTPResp) : hostName(hostName), name(name) {
	unsigned int init = name.find( hostName );
	infoName = name.replace( init, hostName.length() + 1, "" );

	HTTP::Header header( HTTPResp );
	headerData = header.body;
}

std::string Crawler::getName() {
	return name;
}

std::string Crawler::getInfoName() {
	return infoName;
}

std::vector< std::string > Crawler::getResources() {
	return refResources;
}

bool savePath( std::string path ){

}