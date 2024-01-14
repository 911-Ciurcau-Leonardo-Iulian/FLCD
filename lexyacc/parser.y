%{
#include <stdio.h>
%}

%expect 8

%token letter digit nonZeroDigit

%%

program: statement program
       | /* empty */
       ;

declaration: type identifierList;

nextIdentifier: ',' identifier;

nextIdentifierChain: nextIdentifier nextIdentifierChain
                  | /* empty */
                  ;

identifierList: identifier nextIdentifierChain;

primitiveType: "bool"
            | "char"
            | "int"
            | "float"
            | "string"
            ;

typeNext: '[' positiveNumber ']'
        | /* empty */
        ;

type: primitiveType typeNext;

statement: declaration ';'
         | conditionalStructStatement
         | assignStatement ';'
         | inputOutputStatement ';'
         | returnStatement
         ;

returnStatement: "ret" expression;

assignStatement: identifier '=' expression;

inputOutputStatement: "read" '(' identifierList ')'
                   | "print" '(' expression ')'
                   ;

conditionalStructStatement: ifStatement
                        | whileStatement
                        ;

ifSimpleStatement: "if" '[' condition ']' ':' statement;

ifStatement: ifSimpleStatement elseStatementChain "end";

elseStatementChain: "else" statement elseStatementChain
                | /* empty */
                ;

whileStatement: "while" '[' condition ']' ':' statement "end";

condition: expression relation expression
         | '!' condition
         | /* empty */
         ;

relation: "<"
        | "<="
        | "=:"
        | "!="
        | ">="
        | ">"
        ;

expressionNumber: identifier
               | number
               ;

expression: charTerminal
          | mathExpression
          ;

mathExpression: expressionNumber
             | '(' mathExpression arithmeticOperator mathExpression ')'
             ;

arithmeticOperator: '+'
                 | '-'
                 | '*'
                 | '/'
                 ;

booleanOperator: "&&"
               | "||"
               ;

identifierStart: letter
              | '_'
              ;

identifierContent: letter identifierContent
                | digit identifierContent
                | '_' identifierContent
                | /* empty */
                ;

identifier: identifierStart identifierContent;

digitList: digit digitList
         | /* empty */
         ;

number: "0"
      | positiveNumber
      | '-' positiveNumber
      ;

positiveNumber: nonZeroDigit digitList;

charTerminal: '"' terminal '"';

terminal: letter
        | digit
        | arithmeticOperator
        | booleanOperator
        | relation
        | /* empty */
        ;

%%

int main() {
    yyparse();
    return 0;
}
