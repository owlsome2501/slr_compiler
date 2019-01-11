#include "grammar.h"
#include "slr_grammar.h"

using namespace std;

const int grammar::ACC = 99;
const size_t grammar::table_length = 58;
const size_t grammar::grammar_size = 30;

const size_t grammar::ternimal_length = 24;
const int *grammar::action_table = new int[table_length * ternimal_length]{
	3,   -2,  5,   0,   0,   0,   0,   6,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   -2,  0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   ACC, 3,   -2,  5,   0,   0,   0,   0,   6,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   -2,  3,   -2,  5,   0,   0,   0,   0,   6,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -2,  -4,  -4,
	-4,  -4,  0,   0,   0,   -4,  0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   -4,  3,   0,   5,   0,   0,   0,
	0,   6,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   10,  0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   -1,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   -1,  0,   11,  0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   12,  0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   20,  0,   0,   21,  0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   23,  0,   0,   22,  24,  0,   -3,  -3,
	-3,  -3,  0,   0,   0,   -3,  0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   -3,  0,   0,   0,   0,   25,  0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   26,  0,   0,   27,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   -8,  -8,  0,   0,   -8,  28,  0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   -10, -10, 0,   0,   -10, -10, 29,  30,  0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -13, -13, 0,
	0,   -13, -13, -13, -13, 31,  32,  33,  34,  0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   -18, -18, 0,   0,   -18, -18, -18,
	-18, -18, -18, -18, -18, 35,  36,  0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   -21, -21, 0,   0,   -21, -21, -21, -21, -21, -21, -21,
	-21, -21, -21, 37,  38,  0,   0,   0,   0,   0,   0,   0,   0,   -24,
	-24, 0,   0,   -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24,
	-24, 0,   0,   0,   0,   0,   0,   0,   20,  0,   0,   21,  0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   23,  0,   0,   22,  24,  0,
	0,   0,   0,   0,   0,   -26, -26, 0,   0,   -26, -26, -26, -26, -26,
	-26, -26, -26, -26, -26, -26, -26, 0,   0,   0,   0,   0,   0,   0,
	0,   -27, -27, 0,   0,   -27, -27, -27, -27, -27, -27, -27, -27, -27,
	-27, -27, -27, 0,   0,   0,   0,   0,   0,   0,   20,  0,   0,   21,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   23,  0,   0,   22,
	24,  0,   0,   0,   0,   0,   20,  0,   0,   21,  0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   23,  0,   0,   22,  24,  0,   0,   0,
	0,   0,   20,  0,   0,   21,  0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   23,  0,   0,   22,  24,  0,   -6,  -6,  -6,  -6,  0,   0,
	0,   -6,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   -6,  0,   0,   0,   0,   20,  0,   0,   21,  0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   23,  0,   0,   22,  24,  0,
	0,   0,   0,   0,   20,  0,   0,   21,  0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   23,  0,   0,   22,  24,  0,   0,   0,   0,   0,
	20,  0,   0,   21,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	23,  0,   0,   22,  24,  0,   0,   0,   0,   0,   20,  0,   0,   21,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   23,  0,   0,   22,
	24,  0,   0,   0,   0,   0,   20,  0,   0,   21,  0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   23,  0,   0,   22,  24,  0,   0,   0,
	0,   0,   20,  0,   0,   21,  0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   23,  0,   0,   22,  24,  0,   0,   0,   0,   0,   20,  0,
	0,   21,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   23,  0,
	0,   22,  24,  0,   0,   0,   0,   0,   20,  0,   0,   21,  0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   23,  0,   0,   22,  24,  0,
	0,   0,   0,   0,   20,  0,   0,   21,  0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   23,  0,   0,   22,  24,  0,   0,   0,   0,   0,
	20,  0,   0,   21,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	23,  0,   0,   22,  24,  0,   0,   0,   0,   0,   20,  0,   0,   21,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   23,  0,   0,   22,
	24,  0,   0,   0,   0,   0,   20,  0,   0,   21,  0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   23,  0,   0,   22,  24,  0,   0,   0,
	0,   0,   0,   55,  0,   0,   0,   27,  0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -28,
	-28, 0,   0,   -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28,
	-28, 0,   0,   0,   0,   0,   0,   0,   0,   -29, -29, 0,   0,   -29,
	-29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, 0,   0,   0,
	0,   0,   0,   0,   0,   56,  0,   0,   0,   27,  0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   -7,  -7,  0,   0,   -7,  28,  0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -9,  -9,  0,
	0,   -9,  -9,  29,  30,  0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   -11, -11, 0,   0,   -11, -11, -11,
	-11, 31,  32,  33,  34,  0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   -12, -12, 0,   0,   -12, -12, -12, -12, 31,  32,  33,
	34,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -14,
	-14, 0,   0,   -14, -14, -14, -14, -14, -14, -14, -14, 35,  36,  0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   -15, -15, 0,   0,   -15,
	-15, -15, -15, -15, -15, -15, -15, 35,  36,  0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   -16, -16, 0,   0,   -16, -16, -16, -16, -16,
	-16, -16, -16, 35,  36,  0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   -17, -17, 0,   0,   -17, -17, -17, -17, -17, -17, -17, -17, 35,
	36,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -19, -19, 0,
	0,   -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, 37,  38,  0,
	0,   0,   0,   0,   0,   0,   0,   -20, -20, 0,   0,   -20, -20, -20,
	-20, -20, -20, -20, -20, -20, -20, 37,  38,  0,   0,   0,   0,   0,
	0,   0,   0,   -22, -22, 0,   0,   -22, -22, -22, -22, -22, -22, -22,
	-22, -22, -22, -22, -22, 0,   0,   0,   0,   0,   0,   0,   0,   -23,
	-23, 0,   0,   -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23,
	-23, 0,   0,   0,   0,   0,   0,   0,   0,   -25, -25, 0,   0,   -25,
	-25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, 0,   0,   0,
	0,   0,   0,   0,   0,   0,   57,  0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   -5,  -5,  -5,  -5,
	0,   0,   0,   -5,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   -5};
const size_t grammar::non_ternimal_length = 11;
const unsigned *grammar::goto_table =
	new unsigned[table_length * non_ternimal_length]{
		0,  1,  2,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  7,  2,  4,  0,  0,  0,  0,  0,  0,
		0,  0,  8,  2,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  9,  4,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  13, 14, 15, 16, 17, 18, 19, 0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		39, 14, 15, 16, 17, 18, 19, 0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  40, 0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  41, 0,  0,  0,  0,  42, 14, 15, 16, 17, 18, 19, 0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  43, 15,
		16, 17, 18, 19, 0,  0,  0,  0,  0,  0,  44, 16, 17, 18, 19, 0,
		0,  0,  0,  0,  0,  0,  45, 17, 18, 19, 0,  0,  0,  0,  0,  0,
		0,  46, 17, 18, 19, 0,  0,  0,  0,  0,  0,  0,  0,  47, 18, 19,
		0,  0,  0,  0,  0,  0,  0,  0,  48, 18, 19, 0,  0,  0,  0,  0,
		0,  0,  0,  49, 18, 19, 0,  0,  0,  0,  0,  0,  0,  0,  50, 18,
		19, 0,  0,  0,  0,  0,  0,  0,  0,  0,  51, 19, 0,  0,  0,  0,
		0,  0,  0,  0,  0,  52, 19, 0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  53, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  54, 0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
size_t *grammar::reduce_table =
	new size_t[grammar_size]{1, 2, 0, 3, 1, 7, 4, 3, 1, 3, 1, 3, 3, 1, 3,
				 3, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 1, 1, 2, 2};

grammar::gu_ptr grammar::create_gu(sym type, const char *text)
{
	if (type == sym::NUM) {
		unsigned uint = static_cast<unsigned>(atoi(text));
		// cout << "[DEBUG] create num >> " << uint << endl;
		return gu_ptr(new grammar_unit{
			type, su_ptr(new sem_unit{sem::NUM, string(), uint,
						  nullptr})});
	} else if (type == sym::IDENT) {
		// cout << "[DEBUG] create id >> " << text << endl;
		return gu_ptr(new grammar_unit{
			type, su_ptr(new sem_unit{sem::IDENT, string(text), 0,
						  nullptr})});
	} else {
		return gu_ptr(new grammar_unit{type, nullptr});
	}
}

grammar::gu_ptr grammar::reduce(int bnf_id, gu_list gu_l)
{
	const char *bnf[]{"program -> part",
			  "part -> block part",
			  "part -> ''",
			  "block -> { part }",
			  "block -> statement",
			  "statement -> do block while ( e ) ;",
			  "statement -> id := e ;",
			  "e -> e || e1",
			  "e -> e1",
			  "e1 -> e1 && e2",
			  "e1 -> e2",
			  "e2 -> e2 == e3",
			  "e2 -> e2 != e3",
			  "e2 -> e3",
			  "e3 -> e3 > e4",
			  "e3 -> e3 < e4",
			  "e3 -> e3 <= e4",
			  "e3 -> e3 >= e4",
			  "e3 -> e4",
			  "e4 -> e4 + e5",
			  "e4 -> e4 - e5",
			  "e4 -> e5",
			  "e5 -> e5 * e6",
			  "e5 -> e5 / e6",
			  "e5 -> e6",
			  "e6 -> ( e )",
			  "e6 -> id",
			  "e6 -> num",
			  "e6 -> - e6",
			  "e6 -> ! e6"};
	// cout << bnf[bnf_id] << endl;
	gu_ptr new_non_terminal = nullptr;
	// for (gu_ptr &t : (*gu_l)) {
	// 	cout << "[DEBUG] gu_l :" << static_cast<int>(t->type) << endl;
	// }
	switch (bnf_id) {
	case 0: {
		break;
	}
	case 1: {
		gu_ptr part = (*gu_l)[1];
		su_list args = part->su->args;
		args->insert(args->begin(), (*gu_l)[0]->su);
		new_non_terminal = part;
		break;
	}
	case 2: {
		su_list sl = su_list(new vector<su_ptr>());
		su_ptr sp = su_ptr(new sem_unit{sem::PART, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::PART, sp});
		break;
	}
	case 3: {

		gu_ptr gp = (*gu_l)[1];
		gp->type = sym::BLOCK;
		gp->su->type = sem::BLOCK;
		new_non_terminal = gp;
		break;
	}
	case 4: {
		gu_ptr gp = (*gu_l)[0];
		gp->type = sym::BLOCK;
		new_non_terminal = gp;
		break;
	}
	case 5: {
		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[1]->su, (*gu_l)[4]->su});
		su_ptr sp =
			su_ptr(new sem_unit{sem::DO_WHILE, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::STATEMENT, sp});
		break;
	}
	case 6: {
		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::ASSIGN, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::STATEMENT, sp});
		break;
	}
	case 7: {
		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::OR, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E, sp});
		break;
	}
	case 8: {
		gu_ptr gp = (*gu_l)[0];
		gp->type = sym::E;
		new_non_terminal = gp;
		break;
	}
	case 9: {
		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::AND, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E1, sp});
		break;
	}
	case 10: {

		gu_ptr gp = (*gu_l)[0];
		gp->type = sym::E1;
		new_non_terminal = gp;
		break;
	}
	case 11: {
		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::EQU, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E2, sp});
		break;
	}
	case 12: {

		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::NEQU, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E2, sp});
		break;
	}
	case 13: {

		gu_ptr gp = (*gu_l)[0];
		gp->type = sym::E2;
		new_non_terminal = gp;
		break;
	}
	case 14: {

		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::GT, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E3, sp});
		break;
	}
	case 15: {

		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::LT, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E3, sp});
		break;
	}
	case 16: {

		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::NGT, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E3, sp});
		break;
	}
	case 17: {

		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::NLT, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E3, sp});
		break;
	}
	case 18: {
		gu_ptr gp = (*gu_l)[0];
		gp->type = sym::E3;
		new_non_terminal = gp;
		break;
	}
	case 19: {

		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::PLUS, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E4, sp});
		break;
	}
	case 20: {

		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::MINUS, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E4, sp});
		break;
	}
	case 21: {
		gu_ptr gp = (*gu_l)[0];
		gp->type = sym::E4;
		new_non_terminal = gp;
		break;
	}
	case 22: {
		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::MUL, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E5, sp});
		break;
	}
	case 23: {
		su_list sl = su_list(
			new vector<su_ptr>{(*gu_l)[0]->su, (*gu_l)[2]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::DIV, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E5, sp});
		break;
	}
	case 24: {
		gu_ptr gp = (*gu_l)[0];
		gp->type = sym::E5;
		new_non_terminal = gp;
		break;
	}
	case 25: {
		gu_ptr gp = (*gu_l)[1];
		gp->type = sym::E6;
		new_non_terminal = gp;
		break;
	}
	case 26: {
		gu_ptr gp = (*gu_l)[0];
		gp->type = sym::E6;
		new_non_terminal = gp;
		break;
	}
	case 27: {
		gu_ptr gp = (*gu_l)[0];
		gp->type = sym::E6;
		new_non_terminal = gp;
		break;
	}
	case 28: {
		su_list sl = su_list(new vector<su_ptr>{(*gu_l)[0]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::MINUS, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E6, sp});
		break;
	}
	case 29: {
		su_list sl = su_list(new vector<su_ptr>{(*gu_l)[0]->su});
		su_ptr sp = su_ptr(new sem_unit{sem::NOT, string(), 0, sl});
		new_non_terminal = gu_ptr(new grammar_unit{sym::E6, sp});
		break;
	}
	default:
		cout << "[ERROR reduce]" << endl;
		break;
	}
	return new_non_terminal;
}
