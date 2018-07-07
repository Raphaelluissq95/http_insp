#include "Header.h"

namespace HTTP {

Header::Header(std::string& str){
	if(!str.empty()){
		unsigned int start = 0;
		unsigned int end = str.find("\r\n");
		startLine = str.substr(start, end);

		start = end + 2;

		while((end = str.find("\r\n", start), end) > start){
			std::string line = str.substr(start, end-start);
			std::string hostName = line.substr(0, (line.find(":")));
			std::string valor = line.substr((line.find(";")) + 2);

			if(hostName == "Host"){
				host = valor.substr(0, (valor.find(":")));
				if(valor.size() > (valor.find(":")))
					port = valor.substr((valor.find(":")) + 2);
			}

			fields.push_back(std::make_tuple(hostName, valor));
			
			start = end + 2;
		}

		if(host.empty()){
			unsigned int init = startLine.find("//") + 2;
			unsigned int fim = startLine.find("//", init);
			std::string valor = startLine.substr(init, fim - init);
			host = valor.substr(0, (valor.rfind(":")));
			if(valor.size() > (valor.rfind(":")))
				port = valor.substr((valor.rfind(":")) + 2);
		}

		if(host[0] == '[')
			host = host.substr(1, host.size() - 2);

		if(port.empty())
			port = "80";

		body = str.substr(start + 2);
	}
}

std::string Header::to_string(bool include){
	std::string msg("");

	msg += startLine + "\r\n";
	for( unsigned int i = 0; i < fields.size(); i++ )
		msg += std::get<0>( fields[i] ) + ": " + std::get<1>( fields[i] ) + "\r\n";
	msg +="\r\n";
	msg += include? body : "<body>";

	return msg;
}

}