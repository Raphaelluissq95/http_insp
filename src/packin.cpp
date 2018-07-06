#include "lib.h"

#define PACK_TIMEOUT_MS 25
#define QUEUESIZE 5

namespace Socket {

	PckIn::PackIn( int port ) : port( port ), socketfd( -1 ), state( 0 ) {
		errno = 0;
		socketfd = socket( AF_INET, SOCK_STREAM, 0 );
		if( socketfd < 0 ) {
			printf( "\nSocket creation error\n" );
			socketError();
		} else {
			state |= packInState::SOCKET_CREATED;
			address.sin_family = AF_INET;
			address.sin_addr.s_addr = htonl( INADDR_LOOPBACK );
			address.sin_port = htons( port );
			memset( &(address.sin_zero), 0, sizeof( address.sin_zero ) );
			if( bind( socketfd, (struct sockaddr *) &address, sizeof(address) ) < 0 ) {
				printf( "\nFailed to bind socket.\n" );
				bindError();
			} else {
				state |= packInState::SOCKET_BINDED;
				FD_ZERO( &active_fd_set );
				FD_SET( socketfd, &active_fd_set );
				if( listen( socketfd, QUEUESIZE ) < 0 ) {
					printf( "\nFailed to start listening.\n" );
					listenError();
				} else {
					state |= packInState::packIn_STARTED;
				}
			}
		}
	}

	PckIn::~PackIn() {
		state = packInState::SHUTTING_DOWN;
		for( int i = connections.size() - 1; i >= 0; i-- ) {
			if( close( connections[i].socket ) < 0 ) {
				closeError();
			}
			FD_CLR( connections[i].socket, &active_fd_set );
		}
		if( socketfd >= 0 ) {
			if( close( socketfd ) < 0 ) {
				closeError();
			}
			FD_CLR( socketfd, &active_fd_set );
		}
		state = 0;
	}

	void PckIn::Accept() {
		if( state & packInState::packIn_STARTED ) {
			state |= packInState::packIn_RUNNING;

			read_fd_set = active_fd_set;
			timeout.tv_sec = 0;
			timeout.tv_usec = PACK_TIMEOUT_MS;
			if( select( FD_SETSIZE, &read_fd_set, NULL, NULL, &timeout ) < 0 ) {
				printf( "\nCould not wait on select for sockets.\n" );
				selectError();
			}
			for( int i = 0; i < FD_SETSIZE; i++ ) {
				if( FD_ISSET(i, &read_fd_set ) ) {
					if( i == socketfd ) {
						// Accepting connections
						ConnectionData cd;
						socklen_t length = sizeof(struct sockaddr_in);
						cd.socket = accept( socketfd, (struct sockaddr*) &(cd.address), &length );
						if( -1 < cd.socket ) {
							connections.push_back( cd );
							FD_SET( cd.socket, &active_fd_set );
						} else {
							printf( "\nCould not accept socket.\n" );
							acceptError();
						}
					} else {
						// Receiving data
						int connectionID;
						for( connectionID = 0; connectionID < (int) connections.size(); connectionID++ ) {
							if( connections[connectionID].socket == i ) break;
						}
						int valread = 0;
						std::string message("");
						do {
							char buffer[1024];
							valread = read( i, buffer, sizeof( buffer ) );
							message += std::string( buffer, valread );
						} while (1024 == valread);
						if( 0 < valread) {
							MessageData md;
							md.message = message;
							md.internalConnectionID = connectionID;
							md.addr_from = std::string( inet_ntoa( connections[connectionID].address.sin_addr ) );
							md.port_from = ntohs( connections[connectionID].address.sin_port );
							md.addr_to = "127.0.0.1";
							md.port_to = port;
							messagesReceived.push_back( md );
						} else if( 0 == valread ) {
							if( close( i ) < 0 ) {
								closeError();
							}
							FD_CLR( i, &active_fd_set );
							connections.erase( connections.begin() + connectionID );
						} else {
							printf( "\nCould not read data.\n" );
							readError();
						}
					}
				}
			}
		}
	}

	ssize_t PckIn::Send( int connectionID, std::string message ) {
		if( state & packInState::packIn_RUNNING ) {
			if( connectionID < (int) connections.size() ) {
				ssize_t sent = send( connections[connectionID].socket , message.c_str(), message.length(), 0 );
				if( sent < 0 ) {
					printf( "\nCould not send data.\n" );
					sendError();
				} else {
					return sent;
				}
			} else {
				printf( "\nInvalid connectionID.\n" );
			}
		} else {
			printf( "\nCannot send message. Listener is not in a valid state for sending data.\n" );
		}
		return -1;
	}
};