#include "ast_parser.h"

using namespace std;

const vector<string> ast_parser::sem_string{
	"",  "",  "",  ":=", "",   "",  "||", "&&", "==", "!=",
	"!", ">", "<", "<=", ">=", "+", "-",  "*",  "/"};
inline void ast_parser::print_qtuple(std::string op, std::string arg1,
				     std::string arg2, std::string res)
{
	cout << "( " << op << ", " << arg1 << ", " << arg2 << ", " << res
	     << " )" << endl;
}

inline string ast_parser::double_factor_parse(su_ptr ast_root)
{
	su_list args = ast_root->args;
	string arg1 = print((*args)[0]);
	string arg2 = print((*args)[1]);
	string res = T + to_string(temp_count++);
	print_qtuple(sem_string[static_cast<int>(ast_root->type)], arg1, arg2,
		     res);
	return res;
}

string ast_parser::print(su_ptr ast_root)
{
	su_list args = ast_root->args;
	switch (ast_root->type) {
	case sem::BLOCK: {
		cout << "{" << endl;
		for (su_ptr &sp : *(ast_root->args)) {
			print(sp);
		}
		cout << "}" << endl;
		break;
	}
	case sem::PART: {
		for (su_ptr &sp : *(ast_root->args)) {
			print(sp);
		}
		break;
	}
	case sem::DO_WHILE: {
		int loop_count_local = loop_count++;
		cout << "LOOP_" << loop_count_local << ":" << endl;
		print((*(ast_root->args))[0]);
		string cond = print((*(ast_root->args))[1]);
		cout << "if " << cond << " != 0 : goto LOOP_"
		     << loop_count_local << endl;
		break;
	}
	case sem::ASSIGN: {
		string arg1 = print((*args)[0]);
		string arg2 = print((*args)[1]);
		print_qtuple(":=", arg1, arg2, "-");
		break;
	}
	case sem::IDENT: {
		return ast_root->text;
		break;
	}
	case sem::NUM: {
		return to_string(ast_root->uint);
		break;
	}
	case sem::OR:
	case sem::AND:
	case sem::EQU:
	case sem::NEQU:
	case sem::GT:
	case sem::LT:
	case sem::NGT:
	case sem::NLT:
	case sem::PLUS:
	case sem::MUL:
	case sem::DIV: {
		return double_factor_parse(ast_root);
		break;
	}
	case sem::MINUS: {
		if ((*args).size() == 1) {
			string arg1 = print((*args)[0]);
			string res = T + to_string(temp_count++);
			print_qtuple("-", arg1, "-", res);
			return res;
		} else {
			return double_factor_parse(ast_root);
		}
		break;
	}
	case sem::NOT: {
		string arg1 = print((*args)[0]);
		string res = T + to_string(temp_count++);
		print_qtuple("!", arg1, "-", res);
		return res;
		break;
	}
	default:
		cout << "[ERROR] ast_parser" << endl;
		break;
	}
	return string();
}
