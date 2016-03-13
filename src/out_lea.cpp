#ifndef __OUT_LEA_CPP__
#define __OUT_LEA_CPP__

	#include "lea.cpp"

	void PrintLex(Lex cur_lex) {
		switch (cur_lex.get_type()) {
			case LEX_NULL:
				cout << "null";
			break;
			case LEX_FALSE:
				cout << "false";
			break;
			case LEX_TRUE:
				cout << "true";
			break;
			case LEX_AND:
				cout << "and";
			break;
			case LEX_OR:
				cout << "or";
			break;
			case LEX_NOT:
				cout << "not";
			break;
			case LEX_IF:
				cout << "if";
			break;
			case LEX_ELSE:
				cout << "else";
			break;
			case LEX_WHILE:
				cout << "while";
			break;
			case LEX_INPUTI:
				cout << "inputi";
			break;
			case LEX_INPUTB:
				cout << "inputb";
			break;
			case LEX_PRINT:
				cout << "print";
			break;
			case LEX_DEF:
				cout << "def";
			break;
			case LEX_INT:
				cout << "int";
			break;
			case LEX_BOOL:
				cout << "bool";
			break;
			case LEX_RETURN:
				cout << "return";
			break;

	//-------------------------------------

			case LEX_COMMA:
				cout << ",";
			break;
			case LEX_COLON:
				cout << ":";
			break;
			case LEX_ASSIGN:
				cout << "=";
			break;
			case LEX_LPAREN:
				cout << "(";
			break;
			case LEX_RPAREN:
				cout << ")";
			break;
			case LEX_LBRACE:
				cout << "{";
			break;
			case LEX_RBRACE:
				cout << "}";
			break;
			case LEX_EQ:
				cout << "==";
			break;
			case LEX_LSS:
				cout << "<";
			break;
			case LEX_GTR:
				cout << ">";
			break;
			case LEX_PLUS:
				cout << "+";
			break;
			case LEX_MINUS:
				cout << "-";
			break;
			case LEX_TIMES:
				cout << "*";
			break;
			case LEX_SLASH:
				cout << "/";
			break;
			case LEX_LEQ:
				cout << "<=";
			break;
			case LEX_NEQ:
				cout << "!=";
			break;
			case LEX_GEQ:
				cout << ">=";
			break;
			case LEX_NSTR:
				cout << "\\n";
			break;

	//-----------------------------		

			case LEX_NUM:
				cout << cur_lex.get_value();
			break;
			case LEX_ID:
				cout << TID[cur_lex.get_value()].get_name();
			break;
			case LEX_END:
				cout << "END";
			break;

	//-----------------------------

			case POLIZ_LABEL:
				cout << "PL";
			break;
			case POLIZ_ADDRESS:
				cout << TID[cur_lex.get_value()].get_name();
			break;
			case POLIZ_GO:
				cout << "PG";
			break;
			case POLIZ_FGO:
				cout << "PF";
			break;

			default:
				cout << "OTHER";
			break;
		}
	}

#endif
//do not add anything here
