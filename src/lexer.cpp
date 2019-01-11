#include "lexer.h"

lexer::lexer()
{
	is_end = false;
	flex = new yyFlexLexer;
}

lexer::~lexer()
{
	delete flex;
}

bool lexer::next()
{
	if (is_end)
		return false;
	int tmp_sym = flex->yylex();
	if (tmp_sym == 0) {
		is_end = true;
		top_value = sym::EOS;
	} else {
		top_value = static_cast<sym>(tmp_sym - 1);
		//std::cout << "lexer: " << top_value << std::endl;
	}
	return true;
}

sym lexer::top()
{
	return top_value;
}

const char *lexer::text()
{
	return flex->YYText();
}
