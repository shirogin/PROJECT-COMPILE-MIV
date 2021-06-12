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
CHAR \'[^']\'
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

{TYPE} {LineHandle(yytext); yylval.mySTRING=strdup(yytext); return TYPE;}
"CONST" {LineHandle(yytext); return CONST;}

"PROD" {LineHandle(yytext); return PROD;}
"WHEN" {LineHandle(yytext); return WHEN;}
"OTHERWISE" {LineHandle(yytext); return OTHERWISE;}
"WHILE" {LineHandle(yytext); return WHILE;}
"EXECUTE" {LineHandle(yytext); return EXECUTE;}
"DO" {LineHandle(yytext); return DO;}

"CODE" {LineHandle(yytext); return CODE;}
"START" {LineHandle(yytext); return START;}
"END\." {LineHandle(yytext); return END;}

{IDF} {Insert(yytext,'U'); yylval.mySTRING=strdup(yytext); return IDF;}

{INTEGER} {    
    if(strlen(yytext)>8) printf("Unexpected INTEGER overflow %s",yytext);
    else {
        LineHandle(yytext);
        sscanf(yytext,"%d",&yylval.myINT);
        return INTEGER;
    }
}
{FLOAT} {
    if(strlen(yytext)>8) printf("Unexpected FLOAT overflow %s",yytext);
    else {
        LineHandle(yytext);
        sscanf(yytext,"%f",&yylval.myFLOAT);
        return FLOAT;
    }
}
{CHAR} {LineHandle(yytext); yylval.myCHAR=yytext[1]; return CHAR;}
{STRING} {
    LineHandle(yytext); 
    yytext[strlen(yytext)-1]='\0';
    yylval.mySTRING=strdup(++yytext);
    
    return STRING;
    }

{EOI} {LineHandle(yytext); return EOI;}

{SPACES} {LineHandle(yytext);}
{NL} {
    position.line+=1; 
    printf("\n%d:\t",position.line);
    free(Line);
    };
{COMMENTS} {LineHandle(yytext);}

{WRONG_CHAR_LONG} {printf("CHAR has more than a character");}
{WRONG_CHAR_EMPTY} {printf("CHAR is Empty");}
{WRONG_STR_NL} {printf("String has New line");}
{WRONG_STR_EMPTY} {printf("String Empty");}
{WRONG_STR_not_closed} {printf("String not closed");}
{ERROR} {printf("Unexpected token %s",yytext);}
