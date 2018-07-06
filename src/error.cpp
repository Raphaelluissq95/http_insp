#include "lib.h"

namespace Socket {

int socketError() {
	switch( errno ) {
		/* Linux error codes */
		case EACCES:
			printf( "\nEACCES: Permission to create a socket of the specified type and/or protocol is denied.\n" );
			break;
		case EAFNOSUPPORT:
			printf( "\nEAFNOSUPPORT: The implementation does not support the specified address family.\n" );
			break;
		case EINVAL:
			printf( "\nEINVAL: Unknown protocol, or protocol family not available; Or, Invalid flags in type.\n" );
			break;
		case EMFILE:
			printf( "\nEMFILE: The per-process limit on the number of open file descriptors has been reached.\n" );
			break;
		case ENFILE:
			printf( "\nENFILE: The system-wide limit on the total number of open file descriptors has been reached.\n" );
			break;
		case ENOBUFS:
		case ENOMEM:
			printf( "\nENOBUFS | ENOMEM: Insufficient memory is available. The socket cannot be created until sufficient resources are freed.\n" );
			break;
		case EPROTONOSUPPORT:
			printf( "\nEPROTONOSUPPORT: The protocol type or the specified protocol is not supported within this domain.\n" );
			break;
		/* Other */
		default:
			printf( "\nOTHER( %d ): Unknown error code.\n", errno );
			break;
	}
	int ret = errno;
	errno = 0;
	return ret;
}

int bindError() {
	switch( errno ) {
		/* Linux error codes */
		case EACCES:
			printf( "\nEACCES: The address is protected, and the user is not the superuser.\n" );
			break;
		case EADDRINUSE:
			printf( "\nEADDRINUSE: The given address is already in use; Or, The port number was specified as zero in the socket address structure, but, upon attempting to bind to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use.\n" );
			break;
		case EBADF:
			printf( "\nEBADF: sockfd is not a valid file descriptor.\n" );
			break;
		case EINVAL:
			printf( "\nEINVAL: The socket is already bound to an address; Or, addrlen is wrong, or addr is not a valid address for this socket's domain.\n" );
			break;
		case ENOTSOCK:
			printf( "\nENOTSOCK: The file descriptor sockfd does not refer to a socket.\n" );
			break;
		/* Extra POSIX error codes */
		case EADDRNOTAVAIL:
			printf( "\nEADDRNOTAVAIL: The specified address is not available from the local machine.\n" );
			break;
		case EAFNOSUPPORT:
			printf( "\nEAFNOSUPPORT: The specified address is not a valid address for the address family of the specified socket.\n" );
			break;
		case EALREADY:
			printf( "\nEALREADY: An assignment request is already in progress for the specified socket.\n" );
			break;
		case EINPROGRESS:
			printf( "\nEINPROGRESS: O_NONBLOCK is set for the file descriptor for the socket and the assignment cannot be immediately performed; the assignment shall be performed asynchronously.\n" );
			break;
		case ENOBUFS:
			printf( "\nENOBUFS: Insufficient resources were available to complete the call.\n" );
			break;
		case EOPNOTSUPP:
			printf( "\nEOPNOTSUPP: The socket type of the specified socket does not support binding to an address.\n" );
			break;
		/* Other */
		default:
			printf( "\nOTHER( %d ): Unknown error code.\n", errno );
			break;
	}
	int ret = errno;
	errno = 0;
	return ret;
}

int listenError() {
	switch( errno ) {
		/* Linux error codes */
		case EADDRINUSE:
			printf( "\nEADDRINUSE: Another socket is already listening on the same port; Or, The socket referred to by sockfd had not previously been bound to an address and, upon attempting to bind it to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use.\n" );
			break;
		case EBADF:
			printf( "\nEBADF: The argument sockfd is not a valid file descriptor.\n" );
			break;
		case ENOTSOCK:
			printf( "\nENOTSOCK: The file descriptor sockfd does not refer to a socket.\n" );
			break;
		case EOPNOTSUPP:
			printf( "\nEOPNOTSUPP: The socket is not of a type that supports the listen() operation.\n" );
			break;
		/* Extra POSIX error codes */
		case EDESTADDRREQ:
			printf( "\nEDESTADDRREQ: The socket is not bound to a local address, and the protocol does not support listening on an unbound socket.\n" );
			break;
		case EINVAL:
			printf( "\nEINVAL: The socket is already connected; Or, The socket has been shut down.\n" );
			break;
		case EACCES:
			printf( "\nEACCES: The calling process does not have appropriate privileges.\n" );
			break;
		case ENOBUFS:
			printf( "\nENOBUFS: Insufficient resources were available to complete the call.\n" );
			break;
		/* Other */
		default:
			printf( "\nOTHER( %d ): Unknown error code.\n", errno );
			break;
	}
	int ret = errno;
	errno = 0;
	return ret;
}

int connectError() {
	switch( errno ) {
		/* Linux error codes */
		case EACCES:
			printf( "\nEACCES: For UNIX domain sockets, which are identified by pathname: Write permission is denied on the socket file, or search permission is denied for one of the directories in the path prefix; Or, The user tried to connect to a broadcast address without having the socket broadcast flag enabled or the connection request failed because of a local firewall rule; Or, Search permission is denied for a component of the path prefix; or write access to the named socket is denied.\n" );
			break;
		case EPERM:
			printf( "\nEPERM: The user tried to connect to a broadcast address without having the socket broadcast flag enabled or the connection request failed because of a local firewall rule.\n" );
			break;
		case EADDRINUSE:
			printf( "\nEADDRINUSE: Local address is already in use; Or, Attempt to establish a connection that uses addresses that are already in use.\n" );
			break;
		case EADDRNOTAVAIL:
			printf( "\nEADDRNOTAVAIL: The socket referred to by sockfd had not previously been bound to an address and, upon attempting to bind it to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use; Or, The specified address is not available from the local machine.\n" );
			break;
		case EAFNOSUPPORT:
			printf( "\nEAFNOSUPPORT: The passed address didn't have the correct address family in its sa_family field; Or, The specified address is not a valid address for the address family of the specified socket.\n" );
			break;
		case EAGAIN:
			printf( "\nEAGAIN: Insufficient entries in the routing cache.\n" );
			break;
		case EALREADY:
			printf( "\nEALREADY: The socket is nonblocking and a previous connection attempt has not yet been completed; Or, A connection request is already in progress for the specified socket.\n" );
			break;
		case EBADF:
			printf( "\nEBADF: The argument sockfd is not a valid file descriptor.\n" );
			break;
		case ECONNREFUSED:
			printf( "\nECONNREFUSED: A connect() on a stream socket found no one listening on the remote address; Or, The target address was not listening for connections or refused the connection request.\n" );
			break;
		case EFAULT:
			printf( "\nEFAULT: The socket structure address is outside the user's address space.\n" );
			break;
		case EINPROGRESS:
			printf( "\nEINPROGRESS: The socket is nonblocking and the connection cannot be completed immediately; Or, O_NONBLOCK is set for the file descriptor for the socket and the connection cannot be immediately established; the connection shall be established asynchronously.\n" );
			break;
		case EINTR:
			printf( "\nEINTR: The system call was interrupted by a signal that was caught; Or, The attempt to establish a connection was interrupted by delivery of a signal that was caught; the connection shall be established asynchronously.\n" );
			break;
		case EISCONN:
			printf( "\nEISCONN: The socket is already connected; Or, The specified socket is connection-mode and is already connected.\n" );
			break;
		case ENETUNREACH:
			printf( "\nENETUNREACH: Network is unreachable; Or, No route to the network is present.\n" );
			break;
		case ENOTSOCK:
			printf( "\nENOTSOCK: The file descriptor sockfd does not refer to a socket.\n" );
			break;
		case EPROTOTYPE:
			printf( "\nEPROTOTYPE: The socket type does not support the requested communications protocol. This error can occur, for example, on an attempt to connect a UNIX domain datagram socket to a stream socket; Or, The specified address has a different type than the socket bound to the specified peer address.\n" );
			break;
		case ETIMEDOUT:
			printf( "\nETIMEDOUT: Timeout while attempting connection. The server may be too busy to accept new connections. Note that for IP sockets the timeout may be very long when syncookies are enabled on the server; Or, The attempt to connect timed out before a connection was made.\n" );
			break;
		/* Extra POSIX error codes */
		case ECONNRESET:
			printf( "\nECONNRESET: Remote host reset the connection request.\n" );
			break;
		case EHOSTUNREACH:
			printf( "\nEHOSTUNREACH: The destination host cannot be reached (probably because the host is down or a remote router cannot reach it).\n" );
			break;
		case EINVAL:
			printf( "\nEINVAL: The address_len argument is not a valid length for the address family; or invalid address family in the sockaddr structure.\n" );
			break;
		case ELOOP:
			printf( "\nELOOP: More than {SYMLOOP_MAX} symbolic links were encountered during resolution of the pathname in address.\n" );
			break;
		case ENAMETOOLONG:
			printf( "\nENAMETOOLONG: The length of a pathname exceeds {PATH_MAX}, or pathname resolution of a symbolic link produced an intermediate result with a length that exceeds {PATH_MAX}.\n" );
			break;
		case ENETDOWN:
			printf( "\nENETDOWN: The local network interface used to reach the destination is down.\n" );
			break;
		case ENOBUFS:
			printf( "\nENOBUFS: No buffer space is available.\n" );
			break;
		case EOPNOTSUPP:
			printf( "\nEOPNOTSUPP: The socket is listening and cannot be connected.\n" );
			break;
		/* Other */
		default:
			printf( "\nOTHER( %d ): Unknown error code.\n", errno );
			break;
	}
	int ret = errno;
	errno = 0;
	return ret;
}

int selectError() {
	switch( errno ) {
		/* Linux error codes */
		case EBADF:
			printf( "\nEBADF: An invalid file descriptor was given in one of the sets. (Perhaps a file descriptor that was already closed, or one on which an error has occurred.)\n" );
			break;
		case EINTR:
			printf( "\nEINTR: A signal was caught.\n" );
			break;
		case EINVAL:
			printf( "\nEINVAL: nfds is negative or exceeds the RLIMIT_NOFILE resource limit; Or, The value contained within timeout is invalid.\n" );
			break;
		case ENOMEM:
			printf( "\nENOMEM: Unable to allocate memory for internal tables.\n" );
			break;
		/* Other */
		default:
			printf( "\nOTHER( %d ): Unknown error code.\n", errno );
			break;
	}
	int ret = errno;
	errno = 0;
	return ret;
}

int acceptError() {
	switch( errno ) {
		/* Linux error codes */
		case EWOULDBLOCK:
			printf( "\nEWOULDBLOCK: The socket is marked nonblocking and no connections are present to be accepted.\n" );
			break;
		case EBADF:
			printf( "\nEBADF: sockfd is not an open file descriptor.\n" );
			break;
		case ECONNABORTED:
			printf( "\nECONNABORTED: A connection has been aborted.\n" );
			break;
		case EFAULT:
			printf( "\nEFAULT: The addr argument is not in a writable part of the user address space.\n" );
			break;
		case EINTR:
			printf( "\nEINTR: The system call was interrupted by a signal that was caught before a valid connection arrived.\n" );
			break;
		case EINVAL:
			printf( "\nEINVAL: Socket is not listening for connections, or addrlen is invalid; Or, invalid value in flags.\n" );
			break;
		case EMFILE:
			printf( "\nEMFILE: The per-process limit on the number of open file descriptors has been reached.\n" );
			break;
		case ENFILE:
			printf( "\nENFILE: The system-wide limit on the total number of open file descriptors has been reached.\n" );
			break;
		case ENOBUFS:
		case ENOMEM:
			printf( "\nENOBUFS | ENOMEM: Not enough free memory. This often means that the memory allocation is limited by the socket buffer limits, not by the system memory.\n" );
			break;
		case ENOTSOCK:
			printf( "\nENOTSOCK: The file descriptor sockfd does not refer to a socket.\n" );
			break;
		case EOPNOTSUPP:
			printf( "\nEOPNOTSUPP: The referenced socket is not of type SOCK_STREAM.\n" );
			break;
		case EPROTO:
			printf( "\nEPROTO: Protocol error.\n" );
			break;
		case EPERM:
			printf( "\nEPERM: Firewall rules forbid connection.\n" );
			break;
		/* Other */
		default:
			printf( "\nOTHER( %d ): Unknown error code.\n", errno );
			break;
	}
	int ret = errno;
	errno = 0;
	return ret;
}

int readError() {
	switch( errno ) {
		/* Linux error codes */
		case EWOULDBLOCK:
			printf( "\nEWOULDBLOCK: The file descriptor fd refers to a file other than a socket and has been marked nonblocking (O_NONBLOCK), and the read would block.\n" );
			break;
		case EBADF:
			printf( "\nEBADF: fd is not a valid file descriptor or is not open for reading.\n" );
			break;
		case EFAULT:
			printf( "\nEFAULT: buf is outside your accessible address space.\n" );
			break;
		case EINTR:
			printf( "\nEINTR: The call was interrupted by a signal before any data was read.\n" );
			break;
		case EINVAL:
			printf( "\nEINVAL: fd is attached to an object which is unsuitable for reading; or the file was opened with the O_DIRECT flag, and either the address specified in buf, the value specified in count, or the file offset is not suitably aligned; Or, fd was created via a call to timerfd_create() and the wrong size buffer was given to read(); Or, The STREAM or multiplexer referenced by fildes is linked (directly or indirectly) downstream from a multiplexer.\n" );
			break;
		case EIO:
			printf( "\nEIO: I/O error. This will happen for example when the process is in a background process group, tries to read from its controlling terminal, and either it is ignoring or blocking SIGTTIN or its process group is orphaned. It may also occur when there is a low-level I/O error while reading from a disk or tape. A further possible cause of EIO on networked filesystems is when an advisory lock had been taken out on the file descriptor and this lock has been lost; Or, The process is a member of a background process group attempting to read from its controlling terminal, and either the calling thread is blocking SIGTTIN or the process is ignoring SIGTTIN or the process group of the process is orphaned. This error may also be generated for implementation- defined reasons.\n" );
			break;
		case EISDIR:
			printf( "\nEISDIR: fd refers to a directory; Or, The fildes argument refers to a directory and the implementation does not allow the directory to be read using read() or pread(). The readdir() function should be used instead.\n" );
			break;
		/* Extra POSIX error codes */
		case EBADMSG:
			printf( "\nEBADMSG: The file is a STREAM file that is set to control-normal mode and the message waiting to be read includes a control part.\n" );
			break;
		case EOVERFLOW:
			printf( "\nEOVERFLOW: The file is a regular file, nbyte is greater than 0, the starting position is before the end-of-file, and the starting position is greater than or equal to the offset maximum established in the open file description associated with fildes.\n" );
			break;
		case ECONNRESET:
			printf( "\nECONNRESET: A read was attempted on a socket and the connection was forcibly closed by its peer.\n" );
			break;
		case ENOTCONN:
			printf( "\nENOTCONN: A read was attempted on a socket that is not connected.\n" );
			break;
		case ETIMEDOUT:
			printf( "\nETIMEDOUT: A read was attempted on a socket and a transmission timeout occurred.\n" );
			break;
		case ENOBUFS:
			printf( "\nENOBUFS: Insufficient resources were available in the system to perform the operation.\n" );
			break;
		case ENOMEM:
			printf( "\nENOMEM: Insufficient memory was available to fulfill the request.\n" );
			break;
		case ENXIO:
			printf( "\nENXIO: A request was made of a nonexistent device, or the request was outside the capabilities of the device.\n" );
			break;
		/* Other */
		default:
			printf( "\nOTHER( %d ): Unknown error code.\n", errno );
			break;
	}
	int ret = errno;
	errno = 0;
	return ret;
}

int sendError() {
	switch( errno ) {
		/* Linux error codes */
		case EACCES:
			printf( "\nEACCES: (For UNIX domain sockets, which are identified by pathname) Write permission is denied on the destination socket file, or search permission is denied for one of the directories the path prefix; Or, (For UDP sockets) An attempt was made to send to a network/broadcast address as though it was a unicast address.\n" );
			break;
		case EAGAIN:
			printf( "\nEAGAIN: The socket is marked nonblocking and the requested operation would block; Or, (Internet domain datagram sockets) The socket referred to by sockfd had not previously been bound to an address and, upon attempting to bind it to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use.\n" );
			break;
		case EALREADY:
			printf( "\nEALREADY: Another Fast Open is in progress.\n" );
			break;
		case EBADF:
			printf( "\nEBADF: sockfd is not a valid open file descriptor.\n" );
			break;
		case ECONNRESET:
			printf( "\nECONNRESET: Connection reset by peer.\n" );
			break;
		case EDESTADDRREQ:
			printf( "\nEDESTADDRREQ: The socket is not connection-mode, and no peer address is set.\n" );
			break;
		case EFAULT:
			printf( "\nEFAULT: An invalid user space address was specified for an argument.\n" );
			break;
		case EINTR:
			printf( "\nEINTR: A signal occurred before any data was transmitted.\n" );
			break;
		case EINVAL:
			printf( "\nEINVAL: Invalid argument passed.\n" );
			break;
		case EISCONN:
			printf( "\nEISCONN: The connection-mode socket was connected already but a recipient was specified. (Now either this error is returned, or the recipient specification is ignored.)\n" );
			break;
		case EMSGSIZE:
			printf( "\nEMSGSIZE: The socket type requires that message be sent atomically, and the size of the message to be sent made this impossible.\n" );
			break;
		case ENOBUFS:
			printf( "\nENOBUFS: The output queue for a network interface was full. This generally indicates that the interface has stopped sending, but may be caused by transient congestion. (Normally, this does not occur in Linux. Packets are just silently dropped when a device queue overflows.)\n" );
			break;
		case ENOMEM:
			printf( "\nENOMEM: No memory available.\n" );
			break;
		case ENOTCONN:
			printf( "\nENOTCONN: The socket is not connected, and no target has been given.\n" );
			break;
		case ENOTSOCK:
			printf( "\nENOTSOCK: The file descriptor sockfd does not refer to a socket.\n" );
			break;
		case EOPNOTSUPP:
			printf( "\nEOPNOTSUPP: Some bit in the flags argument is inappropriate for the socket type.\n" );
			break;
		case EPIPE:
			printf( "\nEPIPE: The local end has been shut down on a connection oriented socket. In this case, the process will also receive a SIGPIPE unless MSG_NOSIGNAL is set.\n" );
			break;
		/* Extra POSIX error codes */
		case EIO:
			printf( "\nEIO: An I/O error occurred while reading from or writing to the file system.\n" );
			break;
		case ENETDOWN:
			printf( "\nENETDOWN: The local network interface used to reach the destination is down.\n" );
			break;
		case ENETUNREACH:
			printf( "\nENETUNREACH: No route to the network is present.\n" );
			break;
		/* Other */
		default:
			printf( "\nOTHER( %d ): Unknown error code.\n", errno );
			break;
	}
	int ret = errno;
	errno = 0;
	return ret;
}

int closeError() {
	switch( errno ) {
		/* Linux error codes */
		case EBADF:
			printf( "\nEBADF: fd isn't a valid open file descriptor.\n" );
			break;
		case EINTR:
			printf( "\nEINTR: The close() call was interrupted by a signal.\n" );
			break;
		case EIO:
			printf( "\nEIO: An I/O error occurred.\n" );
			break;
		case ENOSPC:
			printf( "\nENOSPC: On NFS, these errors are not normally reported against the first write which exceeds the available storage space, but instead against a subsequent write(), fsync(), or close().\n" );
			break;
		/* Other */
		default:
			printf( "\nOTHER( %d ): Unknown error code.\n", errno );
			break;
	}
	int ret = errno;
	errno = 0;
	return ret;
}

};