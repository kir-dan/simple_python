#include "lea.cpp"
#include "out_lea.cpp"

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " your_file output_format" << endl;
		exit(1);
	}
	
	Scanner prog(argv[1]);
	Lex cur_lex;

	try {
		while ((cur_lex = prog.get_lex()).get_type() != LEX_END) {
			if (!strcmp(argv[2], "0"))
				cout << cur_lex << endl;
			else if (!strcmp(argv[2], "1")) {
				PrintLex(cur_lex);
				cout << endl;
			}
			else {
				cout << "Error: output_format is 0 or 1" << endl;
				exit(1);
			}
		}
	}
	catch (int sym) {
		cout << "Error: unexpected symbol '" << (char) sym << "'" << endl;
	}
	catch (const char* buf) {
		if (!strcmp(buf, "!"))
			cout << "Error: unexpected symbol '!'" << endl;
	}
	return 0;
}
