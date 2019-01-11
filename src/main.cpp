#include "parser.h"
#include "ast_parser.h"

using namespace std;
int main()
{
	parser pas;
	su_ptr res = pas.parse();
	ast_parser ap;
	if (res)
		ap.print(res);
	else
		cout << "[ERROR] main" << endl;
	return 0;
}
