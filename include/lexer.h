#ifndef LEXER
#define LEXER
#include <FlexLexer.h>
#include "grammar.h"
#include "slr_grammar.h"

class lexer
{
      private:
	FlexLexer *flex;
	sym top_value;
	bool is_end;

      public:
	lexer();
	~lexer();
	sym top();
	bool next();
	const char *text();
};
#endif
