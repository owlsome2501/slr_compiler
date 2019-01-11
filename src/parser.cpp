#include "parser.h"

using namespace std;

typedef grammar::gu_ptr gu_ptr;
typedef grammar::grammar_unit gu;
typedef grammar::gu_list gu_list;

parser::parser()
{
	state_stack.push(0);
}

su_ptr parser::parse()
{
	int action = 0;
	lex.next();
	track();
	while (true) {
		action = gram.action(state_stack.top(), lex.top());
		// cout << "lex.top(): " << lex.top() << endl;
		// cout << "state: " << state_stack.top() << endl;
		// cout << "action: " << action << endl;
		if (action == gram.ACC) {
			// acc
			return gu_stack.top()->su;
		} else if (action < 0) {
			// reduce
			int true_action = -action;
			size_t packsize = gram.get_reduce_size(true_action);
			for (size_t i = 0; i != packsize; ++i)
				state_stack.pop();
			gu_ptr reduced =
				gram.reduce(-action, mv_to_pack(packsize));
			gu_stack.push(reduced);
			state_stack.push(gram.goto_state(state_stack.top(),
							 gu_stack.top()));
		} else if (action > 0) {
			// shift
			state_stack.push(static_cast<unsigned>(action));
			gu_stack.push(gram.create_gu(lex.top(), lex.text()));
			lex.next();
			track();
		} else if (lex.top() == sym::ERROR) {
			// error
			cout << "[Error] unknow symbol" << endl;
			show_tracked();
			return nullptr;
		} else if (action == 0) {
			// error
			cout << "[Error] syntax error" << endl;
			show_tracked();
			return nullptr;
		}
	}
	return nullptr;
}

gu_list parser::mv_to_pack(size_t length)
{
	gu_list gu_l = gu_list(new vector<gu_ptr>());
	// cout << "[DEBUG] mv_to_pack len >> " << length << endl;
	for (size_t i = 0; i != length; ++i) {
		// cout << "[DEBUG] mv_to_pack >> "
		//     << "times " << i << " value "
		//     << static_cast<int>(gu_stack.top()->type) << endl;
		gu_l->push_back(gu_stack.top());
		gu_stack.pop();
	}
	reverse(gu_l->begin(), gu_l->end());
	return gu_l;
}

void parser::track()
{
	tracker.push(string(lex.text()));
	if (tracker.size() > 10)
		tracker.pop();
}

void parser::show_tracked()
{
	cout << "ERROR occured at" << endl;
	cout << '\t';
	while (!tracker.empty()) {
		cout << tracker.front();
		tracker.pop();
	}
	cout << "  <=== ERROR" << endl;
}
