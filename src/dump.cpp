#include "Dump.h"

Dump::Dump(){}

Dump::~Dump(){}

void Dump::DumpHTML( std::string body ){
	unsigned int start = static_cast<unsigned int>(body.find("<!DOCTYPE"));

	if(start == 0){
		FILE * fp =  fopen ( "dump/dump.html", "w+" );
		if( fp == NULL ) printf("\nArquivo não existe\n");
		else {
			fprintf( fp, body.c_str() );
			fclose( fp );
			printf("\nDump criado\n");
		}
	}
}