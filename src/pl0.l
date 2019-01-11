%{
#include "slr_grammar.h"
#include <iostream>
using namespace std;
%}

%option c++
%option noyywrap

lbrace \{
rbrace \}
do do
while while
lpar \(
rpar \)
ends ;
identfier [_A-Za-z][A-Z_a-z0-9]*
assign (:=)
or \|\|
and &&
equ ==
nequ !=
gt >
lt <
ngt <=
nlt >=
plus \+
minus -
mul \*
div \/
constant [0-9]+
not !
whitespace [ \n\t]+
nul .
%%
{lbrace}    {   return 1+static_cast<int>(sym::LBRACE);    }
{rbrace}    {   return 1+static_cast<int>(sym::RBRACE);    }
{do}    {   return 1+static_cast<int>(sym::DO);    }
{while} {       return 1+static_cast<int>(sym::WHILE);     }
{lpar}  {   return 1+static_cast<int>(sym::LPAR); }
{rpar}  {   return 1+static_cast<int>(sym::RPAR); }
{ends}  {   return 1+static_cast<int>(sym::ENDS); }
{identfier} {   return 1+static_cast<int>(sym::IDENT); }
{assign} {   return 1+static_cast<int>(sym::ASSIGN); }
{or}    {   return 1+static_cast<int>(sym::OR); }
{and}   {   return 1+static_cast<int>(sym::AND); }
{equ}   {   return 1+static_cast<int>(sym::EQU); }
{nequ}  {   return 1+static_cast<int>(sym::NEQU); }
{gt}    {   return 1+static_cast<int>(sym::GT); }
{lt}    {   return 1+static_cast<int>(sym::LT); }
{ngt}   {   return 1+static_cast<int>(sym::NGT); }
{nlt}   {   return 1+static_cast<int>(sym::NLT); }
{plus}  {   return 1+static_cast<int>(sym::PLUS); }
{minus} {   return 1+static_cast<int>(sym::MINUS); }
{mul}   {   return 1+static_cast<int>(sym::MUL); }
{div}   {   return 1+static_cast<int>(sym::DIV); }
{constant}  {   return 1+static_cast<int>(sym::NUM); }
{not}   {   return 1+static_cast<int>(sym::NOT);    }
{whitespace} /* do    nothing*/
{nul}   {   return 1+static_cast<int>(sym::ERROR);  }
%%

/* int main() */
/* { */
/*     FlexLexer* lexer = new yyFlexLexer; */
/*     int type; */
/*     while(type = lexer->yylex()){ */
/*         cout << type << ": \"" << lexer->YYText() << "\"" << endl; */
/*     } */
/*     return 0; */
/* } */
