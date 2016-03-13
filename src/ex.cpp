#ifndef __EX_CPP__
#define __EX_CPP__

	#include "sa.cpp"
	#include <stdlib.h>

	class Executer {
		Lex pc_el;
	public:
		void execute(Poliz& prog); 
	};

	void Executer::execute(Poliz& prog) {
		Stack <int, 100> args;
		int i, j, index = 0, size = prog.get_free();
		
		while (index < size) {
			pc_el = prog[index];
			switch(pc_el.get_type()) {
				case LEX_TRUE:
				case LEX_FALSE:
				case LEX_NUM:
				case POLIZ_ADDRESS:
				case POLIZ_LABEL:
					args.push(pc_el.get_value());
				break;
				case LEX_ID:
					i = pc_el.get_value();
					if (TID[i].get_assign()) {
						args.push (TID[i].get_value());
						break;
					}
					else
						throw PolError("indefinite identifier");
				case LEX_NOT:
					args.push(!args.pop());
				break;
				case LEX_OR:
					i = args.pop();
					args.push(args.pop() || i );
				break;
				case LEX_AND:
					i = args.pop();
					args.push(args.pop() && i );
				break;
				case POLIZ_GO:
					index = args.pop() - 1;
				break;
				case POLIZ_FGO:
					i = args.pop();
					if (!args.pop())
						index = i - 1;
				break;
				case LEX_PRINT:
					cout << args.pop() << endl;
				break;
				case LEX_INPUTI: {
					char str[1024];
					bool flag = false;

					int tmp = i = args.pop();

					while (!flag) {
						fgets(str, sizeof(str), stdin);
						if (!strcmp(str, "0\n")) {
							TID[tmp].put_value(0);
							TID[tmp].put_assign();
							flag = true;
						}
						else if (atoi(str)) {
							TID[tmp].put_value(atoi(str));
							TID[tmp].put_assign();
							flag = true;
						}
						else
							cout << "Wrong value(input number): ";
					}
					break;
				}
				case LEX_INPUTB: {
					char bstr[1024];
					bool flag = false;

					int tmp = i = args.pop();

					while (!flag) {
						fgets(bstr, sizeof(bstr), stdin);
						if (!strcmp(bstr, "true\n")) {
							TID[tmp].put_value(1);
							TID[tmp].put_assign();
							flag = true;
						}
						else if (!strcmp(bstr, "false\n")) {
							TID[tmp].put_value(0);
							TID[tmp].put_assign();
							flag = true;
						}
						else
							cout << "Wrong value(input \"true\" or \"false\"): ";
					}
					break;
				}
				case LEX_PLUS:
					args.push(args.pop() + args.pop());
				break;
				case LEX_TIMES:
					args.push(args.pop() * args.pop());
				break;
				case LEX_MINUS:
					i = args.pop();
					args.push(args.pop() - i);
				break;
				case LEX_SLASH:
					i = args.pop();
					if (i) {
						args.push(args.pop() / i);
						break;
					}
					else
						throw PolError("divide by zero");
				case LEX_EQ:
					args.push(args.pop() == args.pop());
				break;
				case LEX_LSS:
					i = args.pop();
					args.push(args.pop() < i);
				break;
				case LEX_GTR:
					i = args.pop();
					args.push(args.pop() > i);
				break;
				case LEX_LEQ:
					i = args.pop();
					args.push(args.pop() <= i);
				break;
				case LEX_GEQ:
					i = args.pop();
					args.push(args.pop() >= i);
				break;
				case LEX_NEQ:
					i = args.pop();
					args.push(args.pop() != i);
				break;
				case LEX_ASSIGN:
					i = args.pop();
					j = args.pop();
					TID[j].put_value(i);
					TID[j].put_assign();
				break;
				default:
					throw PolError("unexpected elem");
			}
			index++;
		};
	}

	class Interpretator {
		Parser pars;
		Executer E;
	public:
		Interpretator ( char* program ): pars (program) {};
		void interpretation ();
	};

	void Interpretator::interpretation () {
		pars.analyze();
		E.execute(pars.prog);
	}

#endif
//do not add anything here
