do-while循环语句的翻译程序
===========================================================

一个简单的用SLR(1)分析方法实现的pl/0混合c语言的翻译程序。

注：**本版本因时间限制不含生成分析表的部分**, 若需实现也可简单扩充代码。


## 程序概览

本程序通过分析在编译前定制的SLR(1)分析表，执行相应的语义规则而实现将源代码翻译为抽象语法树。
之后通过将抽象语法树转换成四元式输出。
程序本身较为简单，感谢[flex++][]项目及[JSMachines][]。
词法分析部分由flex++生成，而SLR(1)分析表则由[JSMachines][]生成（分析表可采用其他方法）。

## 模块

在没实现自动生成SLR(1)分析表的前提下，为满足较高的可定制性，本程序分为定制部分与固定部分。
修改可变部分即可实现翻译程序的定制，固定部分可以复用。

### 词法分析

包含文件：
[pl0.l](./src/pl0.l)(**定制**)，[lexer.cpp](./src/lexer.cpp), [lexer.h](./include/lexer.h)

数据结构：

```cpp
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
```

主要分析部分在由pl0.l生成的词法分析程序及其中包含的yyFlexLexer类。
lexer.h与lexer.cpp中定义的lexer类封装yyFlexLexer,并提供lexer::top()及lexer::next()方法。
其中lexer::top()方法返回在slr_grammar.h中定义的枚举类型sym变量。

### 语法、语义分析

包含文件：
[parser.cpp](./src/parser.cpp), [parser.h](./include/parser.h),
[grammar.cpp](./src/grammar.cpp),  [grammar.h](./include/grammar.h),
[slr_grammar.cpp](./src/slr_grammar.cpp)(**定制**), [slr_grammar.h](./include/slr_grammar.h)(**定制**),
[sem.h](./include/sem.h), [sem_patch.h](./include/sem_patch.h)(**定制**)

数据结构：

```cpp
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

enum sym : int {
	LBRACE,
	RBRACE,
	DO,
	WHILE,
	LPAR,
	RPAR,
    /* ... skiped sym ... */
	E4,
	E5,
	E6,
	ERROR
};

struct sem_unit;
typedef std::shared_ptr<sem_unit> su_ptr;
typedef std::shared_ptr<std::vector<su_ptr>> su_list;
struct sem_unit {
	sem type;
	std::string text;
	unsigned uint;
	su_list args;
};

enum struct sem : int {
	PART,
	BLOCK,
	DO_WHILE,
	ASSIGN,
    /* ... skiped sem ... */
	MUL,
	DIV
};

```

#### parser

parser类中包含了主要的SLR(1)的分析代码，并包含符号栈grammar::gu_stack与状态栈grammar::state_stack。
parser::parse()方法提供分析的主要逻辑，
其根据分词的结果调用grammar::action(unsigned state, sym terminal)获取action表中的值，
并执行grammar::reduce(int bnf_id, gu_list gu_l)或者新建语法单元并更新状态栈、符号栈。
parser::track()和show_tracked()分别记录与输出最近输入的词法单元。

#### grammar

grammar类依据定制部分与固定部分分离的原则，被分散在4个文件中。

*  grammar.cpp

    实现grammar::goto_state(unsigned state, gu_ptr non_terminal)、
    grammar::action(unsigned state, sym terminal)、
    grammar::get_reduce_size(int bnf_id)这些固定的代码。

*  grammar.h

    定义grammar类。

*  slr_grammar.cpp(**定制**)

    根据已分析得到的分析表，初始化ternimal_length、 non_ternimal_length、
    table_length、 reduce_table、 goto_table、 action_table等分析表数据。
    在其中，还实现了与文法相关的grammar::create_gu(sym type, const char *text)
    和grammar::reduce(int bnf_id, gu_list gu_l),分别实现了创建语法单元与归约。
    在归约的过程中实现语义分析，构建抽象语法树。

*  slr_grammar.h(**定制**)

    在本文件中定义了enum sym, 其中的符号被同时用在词法分析部分中。

#### sem_unit

sem_unit用于定义抽象语法树的节点，由于本程序中不包含统一的符号表管理，符号的信息也被储存在节点中。
enum sem则定义了抽象语法树所需要的语义符号。

### 生成四元式

包含文件：
[ast_parser.cpp](./src/ast_parser.cpp)(**定制**), [ast_parser.h](./include/ast_parser.h)

简单的抽象语法树到四元式的翻译程序。





[flex++]: https://gitlab.com/fbb-git/flexcpp
[JSMachines]: https://sourceforge.net/projects/jsmachines/
