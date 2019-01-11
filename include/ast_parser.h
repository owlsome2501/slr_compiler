#ifndef AST_PARSER
#define AST_PARSER

#include <iostream>
#include <vector>
#include <string>
#include "sem.h"
#include "grammar.h"

class ast_parser
{
      private:
	int loop_count = 0;
	int temp_count = 0;
	std::string T = std::string("T");
	static const std::vector<std::string> sem_string;

      public:
	std::string print(su_ptr ast_root);
	void print_qtuple(std::string op, std::string arg1, std::string arg2,
			  std::string res);
	std::string double_factor_parse(su_ptr ast_root);
};

#endif
