#ifndef PASER
#define PASER
#include <iostream>
#include <stack>
#include <queue>
#include <memory>
#include <algorithm>
#include "lexer.h"
#include "grammar.h"
#include "slr_grammar.h"

class parser
{
      public:
	typedef grammar::gu_ptr gu_ptr;

      private:
	lexer lex;
	grammar gram;
	std::stack<gu_ptr> gu_stack;
	std::stack<unsigned> state_stack;
	std::queue<std::string> tracker;

      private:
	void track();
	void show_tracked();
	grammar::gu_list mv_to_pack(size_t length);

      public:
	parser();
	su_ptr parse();
};

#endif
