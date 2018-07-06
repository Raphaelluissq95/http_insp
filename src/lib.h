#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define field std::tuple< std::string, std::string >

namespace Socket {

	typedef struct {
		std::string message;
		int internConnId;

		std::string addr_from;
		int port_from;

		std::string addr_to;
		int port_to;
	} msgData;
};

namespace Socket {

	class PckOut {
		public:
			PackOut( int port );
			~PackOut();
			
			ssize_t Send( int connectionIDofInternal, std::string addr, int port, std::string message );
			void Messages();

			std::vector< msgData > msgReceived;
		private:
			typedef struct {
				int socket;
				std::string addr;
				int port;
				struct sockaddr_in serv_addr;
				int connectionIDofInternal;
			} sckInfo;

			int port;
			std::vector< sckInfo > conn;
			fd_set active_fd_set;
			fd_set read_fd_set;
			struct timeval timeout;
	};
};

namespace Socket {

	class PckIn {
		public:
			PackIn(int port);
			~PackIn();
			
			void Accept();
			ssize_t Send( int connectionID, std::string message );

			std::vector< msgData > msgReceived;
		private:
			typedef struct {
				int socket;
				struct sockaddr_in address;
			} ConnectionData;

			typedef enum packInState : short {
				NEWBORN = 0,
				SOCKET_CREATED = 1 << 0,
				SOCKET_BINDED = 1 << 1,
				PACK_STARTED = 1 << 2,
				PACK_RUNNING = 1 << 3,
				SHUTTING_DOWN = 1 << 4
			} packInState;

			int port;
			int socketfd;
			short state;
			std::vector< ConnectionData > connections;
			fd_set active_fd_set;
			fd_set read_fd_set;
			struct timeval timeout;
			
			struct sockaddr_in address;
	};
};

namespace Socket {

	int socketError();
	int bindError();
	int listenError();
	int connectError();
	int selectError();
	int acceptError();
	int readError();
	int sendError();
	int closeError();
	int printErrno();
};

namespace HTTP {

	struct Header {
		Header( std::string& str );

		std::string to_string( bool includeBody = true );

		std::string firstLine;
		std::vector< field > fields;
		std::string body;

		std::string host;
		std::string port;
	};
};


class Server {
public:
	Server( int port );
	~Server();
	bool Init();
private:
	Socket::PckIn PackIn;
	Socket::PckOut PackOut;
};

#endif