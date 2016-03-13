#include "sa.cpp"
#include "ex.cpp"
#include "out_lea.cpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " your_file" << endl;
		exit(1);
	}
	
	try {
		Interpretator I(argv[1]);
		I.interpretation();
		return 0;
	}
	catch (LexError l) {
		cout << "Traceback (most recent call last):" << endl;
		cout << "  File \"" << argv[1] << "\", line " << str_cnt << endl;
		cout << "    Bad lexeme: '";
		PrintLex(l.getLex());
		cout << "' in " << str_cnt << " row" << endl;
	}
	catch (SymError s) {
		cout << "Traceback (most recent call last):" << endl;
		cout << "  File \"" << argv[1] << "\", line " << str_cnt << endl;
		cout << "    Unexpected symbol '" << (char) s.getSym() << "'" << endl;
	}
	catch (VarError v) {
		cout << "Traceback (most recent call last):" << endl;
		cout << "  File \"" << argv[1] << "\", line " << str_cnt << endl;
		cout << "    " << v.getBuf() << ": " << v.getName() << endl;
	}
	catch (SemError s) {
		cout << "Traceback (most recent call last):" << endl;
		cout << "  File \"" << argv[1] << "\", line " << str_cnt << endl;
		cout << "    " << s.getBuf() << endl;
	}
	catch(PolError p) {
		cout << "Traceback (most recent call last):" << endl;
		cout << "  File \"" << argv[1] << "\"" << endl;
		cout << "    Poliz error: " << p.getBuf() << endl;
	}
}
