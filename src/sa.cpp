#ifndef __SA_CPP__
#define __SA_CPP__

	#include "../include/sa.h"

	//  ###                #  
	// #   # ##### #   #  # # 
	// #     #     ## ## #   #
	//  ###  ####  # # # #   #
	//     # #     #   # #####
	// #   # #     #   # #   #
	//  ###  ##### #   # #   #

	void Parser::dec(type_of_lex type) {
		int i;
		while (!st_int.is_empty()) {
			i = st_int.pop();
			TID[i].put_declare(); 
			TID[i].put_type(type);
		}
	}

	void Parser::check_id() {
		if (TID[c_val].get_declare())
			st_lex.push(TID[c_val].get_type());
		else
			throw VarError("Variable is not declared", TID[c_val].get_name());
	}

	void Parser::check_op() {
		type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;

		t2 = st_lex.pop();
		op = st_lex.pop();
		t1 = st_lex.pop();
		
		if (op == LEX_PLUS || op == LEX_MINUS || \
			op == LEX_TIMES || op == LEX_SLASH)
		{
			r = LEX_INT;
		}
		if (op == LEX_OR || op == LEX_AND)
			t = LEX_BOOL;
		if (t1 == t2 && t1 == t)
			st_lex.push(r);
		else
			throw SemError("Wrong types are in operation");

		prog.put_lex(Lex(op));
	}

	void Parser::check_not() {
		if (st_lex.pop() != LEX_BOOL)
			throw SemError("Wrong type is in not");
		else
			st_lex.push(LEX_BOOL);

		prog.put_lex(Lex(LEX_NOT));
	}

	void Parser::eq_bool() {
		if (st_lex.pop() != LEX_BOOL)
			throw SemError("Expression is not boolean");
	}

	//  ###    #  
	// #   #  # # 
	// #     #   #
	//  ###  #   #
	//     # #####
	// #   # #   #
	//  ###  #   #

	void Parser::analyze() {
		gl();
		while (c_type != LEX_END) {
			S();
			if (c_type != LEX_NSTR && c_type != LEX_END)
				throw LexError(curr_lex);
			if (c_type != LEX_END)
				gl();
		}
		//prog.print();
	}

	void Parser::B () {
		if (c_type == LEX_LBRACE) {
			gl();
			if (c_type == LEX_RBRACE) 
				gl();
			else {
				S();
				while (c_type == LEX_NSTR) {
					gl();
					S();
				}
				if (c_type == LEX_RBRACE) 
					gl();
				else
					throw LexError(curr_lex);
			}
		}
		else
			throw LexError(curr_lex);
	}

	void Parser::S () {
		type_of_lex r;
		int pl0, pl1, pl2, pl3;

		if (c_type == LEX_IF) {
			gl();
			E();
			eq_bool();

			pl2 = prog.get_free();
			prog.blank();
			prog.put_lex(Lex(POLIZ_FGO));

			if (c_type == LEX_COLON) {
				gl();
				if (c_type != LEX_NSTR)
					throw LexError(curr_lex);
				gl();
				S();

				pl3 = prog.get_free();
				prog.blank();
				prog.put_lex(Lex(POLIZ_GO));
				prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()),pl2);

				if (c_type != LEX_NSTR)
					throw LexError(curr_lex);
				gl();

				if (c_type == LEX_ELSE) {
					gl();
					if (c_type != LEX_NSTR)
						throw LexError(curr_lex);
					gl();
					S();

					prog.put_lex(Lex(POLIZ_LABEL,prog.get_free()),pl3);
				}
			}
			else
				throw LexError(curr_lex);
		}
		else if (c_type == LEX_WHILE) {
			pl0 = prog.get_free();

			gl();
			E();
			eq_bool();

			pl1 = prog.get_free();
			prog.blank();
			prog.put_lex(Lex(POLIZ_FGO));

			if (c_type == LEX_COLON) {
				gl();
				if (c_type != LEX_NSTR)
						throw LexError(curr_lex);
				gl();
				S();

				prog.put_lex(Lex(POLIZ_LABEL, pl0));
				prog.put_lex(Lex(POLIZ_GO));
				prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()),pl1);
			}
			else
				throw LexError(curr_lex);
		}
		else if (c_type == LEX_PRINT) {
			gl();
			if (c_type == LEX_LPAREN) {
				gl();
				E();
				if (c_type == LEX_RPAREN) {
					gl();
					prog.put_lex(Lex(LEX_PRINT));
				}
				else
					throw LexError(curr_lex);
			}
			else
				throw LexError(curr_lex);
		}
		else if (c_type == LEX_INPUTI) {
			gl();
			if (c_type == LEX_LPAREN) {
				gl();
				if (c_type == LEX_ID) {
					prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
					TID[c_val].put_declare(); 
					TID[c_val].put_type(LEX_INT);
					gl();
				}
				else
					throw curr_lex;
				if (c_type == LEX_RPAREN) {
					gl();
					prog.put_lex(Lex(LEX_INPUTI));
				}
				else
					throw curr_lex;
			}
			else
				throw curr_lex;
		}
		else if (c_type == LEX_INPUTB) {
			gl();
			if (c_type == LEX_LPAREN) {
				gl();
				if (c_type == LEX_ID) {
					prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
					TID[c_val].put_declare(); 
					TID[c_val].put_type(LEX_BOOL);
					gl();
				}
				else
					throw curr_lex;
				if (c_type == LEX_RPAREN) {
					gl();
					prog.put_lex(Lex(LEX_INPUTB));
				}
				else
					throw curr_lex;
			}
			else
				throw curr_lex;
		}
		else if (c_type == LEX_ID) {
			st_int.push(c_val);
			prog.put_lex(Lex(POLIZ_ADDRESS,c_val));
			gl();
			if (c_type == LEX_ASSIGN) {
				gl();
				E();
				r = st_lex.pop();
				dec(r);
				st_lex.push(r);
				prog.put_lex(Lex(LEX_ASSIGN));
			}
			else
				throw LexError(curr_lex);
		}
		else B();
	}


	void Parser::E() {
		E1();
		if (c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR ||
			c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ)
		{
			st_lex.push(c_type);
			gl();
			E1();
			check_op();
		}
	}

	void Parser::E1() {
		T();
		while (c_type==LEX_PLUS || c_type==LEX_MINUS || c_type==LEX_OR) {
			st_lex.push(c_type);
			gl();
			T();
			check_op();
		}
	}

	void Parser::T() {
		F();
		while (c_type==LEX_TIMES || c_type==LEX_SLASH || c_type==LEX_AND) {
			st_lex.push(c_type);
			gl();
			F();
			check_op();
		} 
	}

	void Parser::F() {
		if (c_type == LEX_ID) {
			check_id();
			prog.put_lex(Lex(LEX_ID, c_val));
			gl();
		}
		else if (c_type == LEX_NUM) {
			st_lex.push(LEX_INT);
			prog.put_lex(curr_lex);
			gl();
		}
		else if (c_type == LEX_TRUE) {
			st_lex.push(LEX_BOOL);
			prog.put_lex(curr_lex);
			gl();
		}
		else if (c_type == LEX_FALSE) {
			st_lex.push(LEX_BOOL);
			prog.put_lex(curr_lex);
			gl();
		}
		else if (c_type == LEX_NOT) {
			gl();
			F();
			check_not();
		}
		else if (c_type == LEX_LPAREN) {
			gl();
			E();
			if (c_type == LEX_RPAREN)
				gl();
			else
				throw LexError(curr_lex);
		}
		else
			throw LexError(curr_lex);
	}

#endif
//do not add anything here
