%{
#include <stdio.h>
%}

letter [A-Za-z]
digit [0-9]
non_zero_digit [1-9]

%%

[+-]|[*\/=<>]=?|[+\-*/]=|\+\+|--|&&|\|\||!|!=|%|=:   { printf("OPERATOR: %s\n", yytext); }
[][,:();']   { printf("SEPARATOR: %s\n", yytext); }
char|int|string|const|do|while|if|else|end|read|print|def|ret|main|for|true|false   { printf("RESERVED WORD: %s\n", yytext); }
{letter}({letter}|{digit})*   { printf("IDENTIFIER: %s\n", yytext); }
0|{non_zero_digit}{digit}*   { printf("INTEGER: %s\n", yytext); }
'[^']*'   { printf("STRING: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}
