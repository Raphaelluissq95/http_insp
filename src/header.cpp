#include "lib.h"

namespace HTTP {

Header::Header(std::string& str){
	if(!str.empty()){
		unsigned int first = 0;
		unsigned int last = str.find("\r\n");
		firstLine = str.substr(first,last);

		first = last + 2;
		while((last = str.find("\r\n", first), last) > first){
			std::string line = str.substr( first, last-first );
			unsigned int division = line.find( ":" );
			std::string property = line.substr( 0, division );
			std::string value = line.substr( division + 2 );

			if( "Host" == property ) {
				division = value.rfind( ":" );
				host = value.substr( 0, division );
				if( division < value.size() )
					port = value.substr( division + 1 );
				
			}

			fields.push_back( std::make_tuple( property, value ) );

			first = last + 2;
		}

		if( host.empty() ) {
			unsigned int begin = firstLine.find( "//" ) + 2;
			unsigned int end = firstLine.find( "/", begin );
			std::string value = firstLine.substr( begin, end-begin );
			unsigned int division = value.rfind( ":" );
			host = value.substr( 0, division );
			if( division < value.size() )
				port = value.substr( division + 1 );
		}
		if( '[' == host[0] ) {
			host = host.substr( 1, host.size()-2 );
		}
		if( port.empty() ) {
			port = "80";
		}

		body = str.substr( first + 2 );
	}
}

std::string Header::to_string( bool includeBody ) {
	std::string request( "" );

	request += firstLine + "\r\n";

	for( unsigned int i = 0; i < fields.size(); i++ ) {
		request += std::get<0>( fields[i] ) + ": " + std::get<1>( fields[i] ) + "\r\n";
	}

	request += "\r\n";
	request += includeBody ? body : "<body>";

	return request;
}

};