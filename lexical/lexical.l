%{
    #include "./lexical.h"
    #include "../syntax/syntax.tab.h"
    
%}
UPPERCASE [A-Z]
LOWERCASE [a-z]
LETTER {UPPERCASE}|{LOWERCASE}
Digit [0-9]
Digit_NZ [1-9]
LOGIC_OP LT|EQ|NE|GT|LE|GE
INTEGER [+-]?({Digit_NZ}{Digit}*|0)
FLOAT {INTEGER}"."{Digit}*
CHAR \'.\'
STRING \"[^\"\n]+\"

TYPE (INTEGER)|(FLOAT)|(CHAR)|(STRING)

IDF {UPPERCASE}({LETTER}|{Digit}){0,19}

ARTH_OP [+-/*]

SPACES [ \t]+
EOI ";"
NL (\r\n)|(\n)
COMMENTS $[^$]*$

WRONG_CHAR_LONG \'[^\']+\'
WRONG_CHAR_EMPTY \'\'
WRONG_STR_NL \"(\n|[^\"])+\"
WRONG_STR_EMPTY \"\"
WRONG_STR_not_closed \"[^\"]+
ERROR .
%%
"," {LineHandle(yytext); return SEPARATOR;}
"[" {LineHandle(yytext); return BRACKETS_B;}
"]" {LineHandle(yytext); return BRACKETS_E;}
"{" {LineHandle(yytext); return C_BRACKETS_B;}
"}" {LineHandle(yytext); return C_BRACKETS_E;}
"(" {LineHandle(yytext); return PARENTHESIS_B;}
")" {LineHandle(yytext); return PARENTHESIS_E;}

{ARTH_OP} {LineHandle(yytext); return ARTH_OP;}
":=" {LineHandle(yytext); return AFFECT;}
{LOGIC_OP} {LineHandle(yytext); return LOGIC_OP;}

{TYPE} {Insert(yytext,2); return TYPE;}
"CONST" {Insert(yytext,2); return CONST;}

"PROD" {Insert(yytext,2); return PROD;}
"WHEN" {Insert(yytext,2); return WHEN;}
"OTHERWISE" {Insert(yytext,2); return OTHERWISE;}
"WHILE" {Insert(yytext,2); return WHILE;}
"EXECUTE" {Insert(yytext,2); return EXECUTE;}
"DO" {Insert(yytext,2); return DO;}

"CODE" {Insert(yytext,2); return CODE;}
"START" {Insert(yytext,2); return START;}
"END\." {Insert(yytext,2); return END;}

{IDF} {Insert(yytext,0); return IDF;}

{INTEGER} {    
    if(strlen(yytext)>8) printf("Unexpected INTEGER overflow %s",yytext);
    else {
        Insert(yytext,1);
        return INTEGER;
    }
}
{FLOAT} {
    if(strlen(yytext)>8) printf("Unexpected FLOAT overflow %s",yytext);
    else {
        Insert(yytext,1);
        return FLOAT;
    }
}
{CHAR} {Insert(yytext,1); return CHAR;}
{STRING} {Insert(yytext,1); return STRING;}

{EOI} {LineHandle(yytext); return EOI;}

{SPACES} {LineHandle(yytext);}
{NL} {
    position.line+=1; 
    printf("\n%d:\t",position.line);
    free(Line);
    };
{COMMENTS} {Insert(yytext,4);}

{WRONG_CHAR_LONG} {printf("CHAR has more than a character");}
{WRONG_CHAR_EMPTY} {printf("CHAR is Empty");}
{WRONG_STR_NL} {printf("String has New line");}
{WRONG_STR_EMPTY} {printf("String Empty");}
{WRONG_STR_not_closed} {printf("String not closed");}
{ERROR} {printf("Unexpected token %s",yytext);}
