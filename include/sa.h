#ifndef __SA_H__
#define __SA_H__

	#include "../src/lea.cpp"
	#include "../src/err.cpp"
	#include "../src/out_lea.cpp"

	class Poliz {
		Lex *p;
		int size;
		int free;
	public:
		Poliz (int max_size) {
			p = new Lex [size = max_size];
			free = 0;
		};
		~Poliz() {delete [] p;};

		void put_lex(Lex l) {p[free]=l; ++free;};
		void put_lex(Lex l, int place) {p[place]=l;};

		void blank() {++free;};

		int get_free() {return free;};

		Lex& operator[] (int index) {
			if (index > size)
				throw PolError("out of array");
			else
				if (index > free)
					throw PolError("indefinite element of array");
				else
					return p[index];
		};

		void print() {
			for (int i = 0; i < free; ++i) {
				cout << i << ' ';
				PrintLex(p[i]);
				cout << ' ';
				cout << p[i] << endl;
			}
		};
	};

	class Parser {
		Lex curr_lex;
		type_of_lex c_type;
		int c_val;
		Scanner scan;

		Stack <int, 100> st_int;
		Stack <type_of_lex, 100> st_lex;

		void B();
		void S();
		void E();
		void E1();
		void T();
		void F();

		void dec(type_of_lex type);
		void check_id();
		void check_op();
		void check_not();
		void eq_bool();
		void check_id_in_read();

		void gl() {
			curr_lex = scan.get_lex(); 
			c_type = curr_lex.get_type(); 
			c_val = curr_lex.get_value();
		}

	public:
		Poliz prog;

		Parser (const char *program): scan(program), prog(1000) {} 

		void analyze();
	};

#endif
//do not add anything here
