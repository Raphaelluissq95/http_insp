#include "lib.h"


Server::Server(int portNum) : PackIn(port), PackOut(port) {}

Server::~Server() {}

bool Server::Init(){
	PackIn.Accept();
	if(PackIn.msgReceived.size() > 0)
		print("\nForam enviados %d pacotes.\n",(int) PackIn.msgReceived.size());

	for(int i = 0;i < (int) PackIn.msgReceived.size();i++){
		HTTP::Header Header(PackIn.msgReceived[i].msg);;
		printf("\nMensagem\nDe: %s:%d\nPara: %s:%s\nMsg: %s\n"
			, PackIn.msgReceived[i].addr_from.c_str()
			, PackIn.msgReceived[i].port_num
			, header.host.c_str()
			, header.port.c_str()
			, header.to_string(false).c_str());
		PackOut.Send(PackIn.msgReceived[i].internConnId, header.host.c_str(), std::atoi(header.port.c_str()), PackIn.msgReceived[i].msg);
	}

	PackIn.msgReceived.clear();

	PackOut.Messages();
	if(PackOut.msgReceived.size() > 0)
		printf("\nForam recebidas %d pacotes.\n", (int) PackOut.msgReceived.size());

	for(int i = 0;i < (int) PackOut.msgReceived.size();i++){
		HTTP::Header Header(PackOut.msgReceived[i].msg);
		printf("\nMensagem\nDe: %s:%d\nPara: %s:%s\nMsg: %s\n"
			, PackOut.msgReceived[i].addr_from.c_str()
			, PackOut.msgReceived[i].port_num
			, header.host.c_str()
			, header.port.c_str()
			, header.to_string(false).c_str());
		PackIn.Send(PackOut.msgReceived[i].internConnId, PackOut.msgReceived[i].msg);
	}

	PackOut.msgReceived.clear();

	return true;
}