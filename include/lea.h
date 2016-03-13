#ifndef __LEA_H__
#define __LEA_H__

	#include <stdio.h>
	#include <ctype.h>
	#include <iostream>

	using namespace std;

	int str_cnt = 1;

	//                                                                  
	// ##### #   # ####  #####        ###  #####       #     ##### #   #
	//   #    # #  #   # #           #   # #           #     #      # # 
	//   #     #   #   # ####        #   # ####        #     ####    #  
	//   #     #   ####  #           #   # #           #     #       #  
	//   #     #   #     #           #   # #           #     #      # # 
	//   #     #   #     ##### #####  ###  #     ##### ##### ##### #   #

	enum type_of_lex {
		LEX_NULL,		//0
		LEX_FALSE,		//1
		LEX_TRUE,		//2
		LEX_AND,		//3
		LEX_OR,			//4
		LEX_NOT,		//5
		LEX_IF,			//6
		LEX_ELSE,		//7
		LEX_WHILE,		//8
		LEX_INPUTI,		//9
		LEX_INPUTB,		//10
		LEX_PRINT, 		//11
		LEX_DEF,		//12
		LEX_RETURN,		//13
		LEX_INT,		//14
		LEX_BOOL,		//15

		LEX_COMMA,		//16	,
		LEX_COLON,		//17	:
		LEX_ASSIGN,		//18	=
		LEX_LPAREN,		//19	(
		LEX_RPAREN,		//20	)
		LEX_LBRACE,		//21	{
		LEX_RBRACE,		//22	}
		LEX_EQ,			//23	==
		LEX_LSS,		//24	<
		LEX_GTR,		//25	>
		LEX_PLUS,		//26	+
		LEX_MINUS,		//27	-
		LEX_TIMES,		//28	*
		LEX_SLASH,		//29	/
		LEX_LEQ,		//30	<=
		LEX_NEQ,		//31	!=
		LEX_GEQ,		//32	>=
		LEX_NSTR,		//33	\n

		LEX_NUM,		//34
		LEX_ID,			//35

		LEX_END,		//36

		POLIZ_LABEL,	//37
		POLIZ_ADDRESS,	//38
		POLIZ_GO,		//39
		POLIZ_FGO		//40
	};

	// #                
	// #     ##### #   #
	// #     #      # # 
	// #     ####    #  
	// #     #       #  
	// #     #      # # 
	// ##### ##### #   #

	class Lex {
		type_of_lex		t_lex;
		int				v_lex;
	public:
		Lex(type_of_lex t = LEX_NULL, int v = 0);

		type_of_lex get_type() {return t_lex;}
		int get_value() {return v_lex;}

		friend ostream& operator<<(ostream& s, Lex l);
	};

	// ###                        
	//  #  ####  ##### #   # #####
	//  #  #   # #     ##  #   #  
	//  #  #   # ####  # # #   #  
	//  #  #   # #     # # #   #  
	//  #  #   # #     #  ##   #  
	// ### ####  ##### #   #   #  

	class Ident {
		char*		name;
		bool		declare;
		type_of_lex type;
		bool		assign;
		int			value;
	public:
		Ident() {
			declare = false;
			assign = false;
		}

		char* get_name() const {return name;}
		void put_name(const char* n) {
			name = new char[strlen(n) + 1];
			strcpy(name, n);
		}

		bool get_declare() {return declare;}
		void put_declare() {declare = true;}

		type_of_lex get_type() {return type;}
		void put_type(type_of_lex t) {type = t;}

		bool get_assign() {return assign;}
		void put_assign() {assign = true;}

		int get_value() const {return value;}
		void put_value(int v) {value = v;}
	};

	//                                                        
	// #####   #   ####  #           # ####  ##### #   # #####
	//   #    # #  #   # #           # #   # #     ##  #   #  
	//   #   #   # ####  #           # #   # ####  # # #   #  
	//   #   ##### #   # #           # #   # #     # # #   #  
	//   #   #   # #   # #           # #   # #     #  ##   #  
	//   #   #   # ####  ##### ##### # ####  ##### #   #   #  

	class tabl_ident {
		Ident*	p;
		int 	size;
		int 	top;
	public:
		tabl_ident(int max_size);
		~tabl_ident() {delete []p;}

		Ident& operator[](int k) {return p[k];}

		int put(const char* buf);
	};

	//  ###                                     
	// #   #  ###    #   #   # #   # ##### #### 
	// #     #   #  # #  ##  # ##  # #     #   #
	//  ###  #     #   # # # # # # # ####  #   #
	//     # #     ##### # # # # # # #     #### 
	// #   # #   # #   # #  ## #  ## #     #  # 
	//  ###   ###  #   # #   # #   # ##### #   #

	class Scanner {
		enum state {H, NEWSTR, IDENT, NUMB, COM, ALE, DELIM};

		static const char* 			TW[];
		static type_of_lex 		words[];
		static const char* 			TD[];
		static type_of_lex 		dlms[];
		
		state 		cur_state;
		FILE* 		fp;

		int 	sym;
		char	buf[80];
		int 	buf_top;

		void clear();
		void add() {buf[buf_top++] = sym;}
		void gsym() {sym = fgetc(fp); if (sym == '\n') str_cnt++;}

		int look(const char* buf, const char** list) const;
	public:
		Scanner(const char* program);

		Lex get_lex();
	};

#endif
//do not add anything here
