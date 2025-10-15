%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

int line_num = 1;

void yyerror(const char *s);
%}

identifier [a-zA-Z_][a-zA-Z0-9_]*
int_constant [0-9]+
float_constant [0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?
whitespace [ \t\r]+
newline \n

%%
{whitespace}  { /* skip whitespace */ }
{newline}     { line_num++; }

"if"          { return IF; }
"else"        { return ELSE; }
"int"         { return INT; }
"float"       { return FLOAT; }
"return"      { return RETURN; }

"{"           { return LBRACE; }
"}"           { return RBRACE; }
"("           { return LPAREN; }
")"           { return RPAREN; }
";"           { return SEMICOLON; }
"="           { return ASSIGN; }
"+"           { return PLUS; }
"-"           { return MINUS; }
"*"           { return MULTIPLY; }
"/"           { return DIVIDE; }

"=="          { return EQ; }
"!="          { return NE; }
">"           { return GT; }
"<"           { return LT; }
">="          { return GE; }
"<="          { return LE; }
"&&"          { return AND; }
"||"          { return OR; }
"!"           { return NOT; }

{int_constant}   { 
    yylval.int_val = atoi(yytext); 
    return INT_CONSTANT; 
}
{float_constant} { 
    yylval.float_val = atof(yytext); 
    return FLOAT_CONSTANT; 
}
{identifier}     { 
    yylval.string_val = strdup(yytext);
    return IDENTIFIER; 
}

.            { 
    fprintf(stderr, "LEXER ERROR: Invalid character '%c' at line %d\n", yytext[0], line_num);
    return ERROR; 
}

%%

int yywrap() {
    return 1;
}