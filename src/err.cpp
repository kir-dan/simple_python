#ifndef __ERR_H__
#define __ERR_H__

	#include "../include/lea.h"

	class Error {};

	class LexError: public Error {
		Lex lexeme;
	public:
		LexError(Lex l): lexeme(l) {}
		Lex getLex() {return lexeme;}
	};

	class SymError: public Error {
		int sym;
	public:
		SymError(int s): sym(s) {}
		int getSym() {return sym;}
	};

	class SemError: public Error {
		const char* buf;
	public:
		SemError(const char* b): buf(b) {}
		const char* getBuf() {return buf;}
	};

	class PolError: public Error {
		const char* buf;
	public:
		PolError(const char* b): buf(b) {}
		const char* getBuf() {return buf;}
	};

	class VarError: public SemError {
		char* name;
	public:
		VarError(const char* b, char* n): SemError(b), name(n) {}
		char* getName() {return name;}
	};

#endif
//do not add anything here
