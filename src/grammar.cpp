#include "grammar.h"

using namespace std;

grammar::grammar()
{
}

unsigned grammar::goto_state(unsigned state, gu_ptr non_terminal)
{
	int clo = static_cast<int>(non_terminal->type) - ternimal_length;
	return *(goto_table + state * non_ternimal_length + clo);
}

int grammar::action(unsigned state, sym terminal)
{
	return *(action_table + state * ternimal_length
		 + static_cast<int>(terminal));
}

size_t grammar::get_reduce_size(int bnf_id)
{
	// 不方便报告错误，因为0也是合法的
	// if (bnf_id > 0 && static_cast<size_t>(bnf_id) < grammar_size)
	return *(reduce_table + bnf_id);
}
