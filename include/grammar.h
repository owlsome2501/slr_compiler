#ifndef GRAMMAR
#define GRAMMAR
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include "slr_grammar.h"
#include "sem.h"

class grammar
{
      public:
	struct grammar_unit;
	typedef std::shared_ptr<grammar_unit> gu_ptr;
	typedef std::shared_ptr<std::vector<gu_ptr>> gu_list;
	struct grammar_unit {
		sym type;
		su_ptr su;
	};

	static const size_t ternimal_length;
	static const size_t non_ternimal_length;
	static const size_t table_length;
	static const size_t grammar_size;
	static const int ACC;

      protected:
	static size_t *reduce_table;
	static const unsigned *goto_table;
	static const int *action_table;

      public:
	grammar();
	unsigned goto_state(unsigned state, gu_ptr non_terminal);
	int action(unsigned state, sym terminal);
	size_t get_reduce_size(int bnf_id);
	gu_ptr reduce(int bnf_id, gu_list gu_l);
	gu_ptr create_gu(sym type, const char *text);
};
#endif
