#ifndef __LEA_CPP__
#define __LEA_CPP__

	#include "../include/lea.h"
	#include "err.cpp"

	//  ###                         
	// #   # #####   #    ###  #   #
	// #       #    # #  #   # #  # 
	//  ###    #   #   # #     ###  
	//     #   #   ##### #     # #  
	// #   #   #   #   # #   # #  # 
	//  ###    #   #   #  ###  #   #
	
	template <class T, int max_size > class Stack {
		T s[max_size];
		int top; 
	public:
		Stack() {top = 0;}

		void reset() {top = 0;}

		void push(T i);
		T pop();

		bool is_empty() {return top == 0;}
		bool is_full() {return top == max_size;}
	};
	
	template <class T, int max_size>
	
	void Stack <T, max_size >::push(T i) {
		if (!is_full()) {
			s[top] = i;
			++top; 
		}
		else
			throw SemError("Stack_is_full");
	}

	template <class T, int max_size>
	
	T Stack <T, max_size >::pop() {
		if (!is_empty()) {
			--top;
			return s[top];
		}
		else
			throw SemError("Stack_is_empty");
	}

	// #                
	// #     ##### #   #
	// #     #      # # 
	// #     ####    #  
	// #     #       #  
	// #     #      # # 
	// ##### ##### #   #

	Lex::Lex(type_of_lex t, int v) {
		t_lex = t;
		v_lex = v;
	}

	ostream& operator<<(ostream& s, Lex l) {
		s << "type_of_lex: " << l.t_lex << "; value_of_lex: " << l.v_lex;
		return s;
	}

	//                                                        
	// #####   #   ####  #           # ####  ##### #   # #####
	//   #    # #  #   # #           # #   # #     ##  #   #  
	//   #   #   # ####  #           # #   # ####  # # #   #  
	//   #   ##### #   # #           # #   # #     # # #   #  
	//   #   #   # #   # #           # #   # #     #  ##   #  
	//   #   #   # ####  ##### ##### # ####  ##### #   #   #  

	tabl_ident::tabl_ident(int max_size) {
		p = new Ident[size = max_size];
		top = 1;
	}

	int tabl_ident::put(const char* buf) {
		for (int i = 1; i < top; i++)
			if (!strcmp(buf, p[i].get_name()))
				return i;
		p[top].put_name(buf);
		top++;
		return top - 1;
	}

	//  ###                                     
	// #   #  ###    #   #   # #   # ##### #### 
	// #     #   #  # #  ##  # ##  # #     #   #
	//  ###  #     #   # # # # # # # ####  #   #
	//     # #     ##### # # # # # # #     #### 
	// #   # #   # #   # #  ## #  ## #     #  # 
	//  ###   ###  #   # #   # #   # ##### #   #

	const char* Scanner::TW[] = {
		"",				//0
		"false",		//1
		"true",			//2
		"and",			//3
		"or",			//4
		"not",			//5
		"if",			//6
		"else",			//7
		"while",		//8
		"inputi",		//9
		"inputb",		//10
		"print",		//11
		"def",			//12
		"return",		//13
		NULL
	};

	const char* Scanner:: TD[] = {
		"",				//0
		",",			//1
		":",			//2
		"=",			//3
		"(", 			//4
		")", 			//5
		"{",			//6
		"}",			//7
		"==",			//8
		"<",			//9
		">",			//10
		"+",			//11
		"-",			//12
		"*",			//13
		"/",			//14
		"<=",			//15
		"!=",			//16
		">=",			//17
		NULL
	};

	type_of_lex Scanner::words[] = {
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
		LEX_NULL		//16
	};

	type_of_lex Scanner::dlms[] = {
		LEX_NULL,		//0
		LEX_COMMA,		//1		,
		LEX_COLON,		//2		:
		LEX_ASSIGN,		//3		=
		LEX_LPAREN,		//4		(
		LEX_RPAREN,		//5		)
		LEX_LBRACE,		//6		{
		LEX_RBRACE,		//7		}
		LEX_EQ,			//8		==
		LEX_LSS,		//9		<
		LEX_GTR,		//10	>
		LEX_PLUS,		//11	+
		LEX_MINUS,		//12	-
		LEX_TIMES,		//13	*
		LEX_SLASH,		//14	/
		LEX_LEQ,		//15	<=
		LEX_NEQ,		//16	!=
		LEX_GEQ,		//17	>=
		LEX_NSTR,		//18	\n
		LEX_NULL		//19
	};

	tabl_ident TID(100);

	void Scanner::clear() {
		buf_top = 0;
		for (int i = 0; i < 80; i++)
			buf[i] = '\0';
	}

	int Scanner::look(const char* buf, const char** list) const {
		int i = 0;
		while (list[i]) {
			if (!strcmp(buf, list[i]))
				return i;
			++i;
		}
		return 0;
	}

	Scanner::Scanner(const char* program) {
		if (!(fp = fopen(program, "r"))) {
			cout << "Error: file not found!" << endl;
			exit(1);
		}
		cur_state = H;
		clear();
		sym = 0;
	}

	//                                          
	//  ###  ##### #####       #     ##### #   #
	// #   # #       #         #     #      # # 
	// #     ####    #         #     ####    #  
	// #  ## #       #         #     #       #  
	// #   # #       #         #     #      # # 
	//  ###  #####   #   ##### ##### ##### #   #

	Lex Scanner::get_lex() {
		int number, pos, cnt = 0;
		cur_state = H;
		do {
			gsym();
			switch (cur_state) {
			case H:
				if (sym == EOF)
					return Lex(LEX_END, 0);
				else if (sym == ' ' || sym == '\t')
					break;
				else if (sym == '\n') {
					clear();
					add();
					cur_state = NEWSTR;
				}
				else if (isalpha(sym) || sym == '_') {
					clear();
					add();
					cur_state = IDENT;
				}
				else if (isdigit(sym)) {
					number = sym - '0';
					cur_state = NUMB;
				}
				else if (sym == '#')
					cur_state = COM;
				else if (sym == '=' || sym == '!' || sym == '<' || sym == '>') {
					clear();
					add();
					cur_state = ALE;
				}
				else {
					ungetc(sym, fp);
					if (sym == '\n')
						str_cnt--;
					cur_state = DELIM;
				}
			break;
			case NEWSTR:
				if (sym != '\n') {
					ungetc(sym, fp);
					if (sym == '\n')
						str_cnt--;
					return Lex(LEX_NSTR, cnt);
				}
			break;
			case IDENT:
				if (isalpha(sym) || isdigit(sym) || sym == '_')
					add();
				else {
					ungetc(sym, fp);
					if (sym == '\n')
						str_cnt--;
					if ((pos = look(buf, TW)))
						return Lex(words[pos], pos); 
					else {
						pos = TID.put(buf);
						return Lex(LEX_ID, pos);
					}
				}
			break;
			case NUMB:
				if (isdigit(sym))
					number = number * 10 + (sym - '0');
				else {
					ungetc(sym, fp);
					if (sym == '\n')
						str_cnt--;
					return Lex(LEX_NUM, number);
				}
			break; 
			case COM:
				if (sym == '\n') {
					clear();
					cur_state = H;
				}
				else if (sym == EOF)
					return Lex(LEX_END, 0);
			break;
			case ALE:
				if (sym == '=') {
					add();
					pos = look(buf, TD);
					return Lex(dlms[pos], pos);
				}
				else {
					ungetc(sym, fp);
					if (sym == '\n')
						str_cnt--;
					if (!strcmp(buf, "!"))
						throw SymError('!');
					pos = look(buf, TD); 
					return Lex(dlms[pos], pos);
				}
			break;
			case DELIM:
				clear();
				add();
				if ((pos = look(buf, TD)))
					return Lex(dlms[pos], pos);
				else
					throw SymError(sym);
			break;
			}
		} while (true);
	}

#endif
//do not add anything here
