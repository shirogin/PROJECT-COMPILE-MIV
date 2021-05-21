%{
    #include <stdio.h>
    #include <stdlib.h>
    struct position{
        int line,column;
    } position = {1,1};
    
%}
UPPERCASE [A-Z]
LOWERCASE [a-z]
LETTER {UPPERCASE}|{LOWERCASE}
Digit [0-9]
Digit_NZ [1-9]

INTEGER [+-]?({Digit_NZ}{Digit}*|0)
FLOAT {INTEGER}"."{Digit}*
CHAR \'.\'
STRING \"[^\"\n]+\"

TYPE (int)|(float)|(char)|(string)

BRACKETS_B "["
BRACKETS_E "]"
C_BRACKETS_B "{"
C_BRACKETS_E "}"
PARENTHESIS_B "("
PARENTHESIS_E ")"

IF "if"
ELSE "else"
FOR "for"
WHILE "while"
DO "do"
SWITCH "switch"
MAIN "main"
FUNCTION "function"

IDF ({LETTER}|"_")({LETTER}|{Digit}|"_")*

AFFECT "="
ARTH_OP [+-/*]
LOGIC_OP (==|(<|>)=?)

POINT "."

SPACES [ \t]+
EOI ";"
NL (\r\n)|(\n)
COMMENTS (\/\*(\*[^/]|[^*])*\*\/|(\/\/)[^\n]+)

WRONG_CHAR_LONG \'.+\'
WRONG_CHAR_EMPTY \'\'
WRONG_STR_NL \"(\n|[^\"])+\"
WRONG_STR_EMPTY \"\"
WRONG_STR_not_closed \"[^\"]+
ERROR .
%%
{INTEGER} {printf("INTEGER");}
{FLOAT} {printf("FLOAT");}
{CHAR} {printf("CHAR");}
{STRING} {printf("STRING");}

{TYPE} {printf("TYPE");}


{BRACKETS_B} {printf("%s",yytext);}
{BRACKETS_E} {printf("%s",yytext);}
{C_BRACKETS_B} {printf("%s",yytext);}
{C_BRACKETS_E} {printf("%s",yytext);}
{PARENTHESIS_B} {printf("%s",yytext);}
{PARENTHESIS_E} {printf("%s",yytext);}

{AFFECT} {printf("%s",yytext);}
{ARTH_OP} {printf("%s",yytext);}
{LOGIC_OP} {printf("%s",yytext);}

{IF} {printf("%s",yytext);}
{ELSE} {printf("%s",yytext);}
{FOR} {printf("%s",yytext);}
{WHILE} {printf("%s",yytext);}
{DO} {printf("%s",yytext);}
{SWITCH} {printf("%s",yytext);}
{FUNCTION} {printf("%s",yytext);}
{MAIN} {printf("%s",yytext);}

{IDF} {printf("IDF",yytext);}

{EOI} {printf("%s",yytext);}

{SPACES} {printf("%s",yytext);}
{NL} {
    position.line+=1; 
    printf("\n%d:\t",position.line);
    };
{COMMENTS} {printf("%s",yytext);}

{WRONG_CHAR_LONG} {printf("CHAR has more than a character");}
{WRONG_CHAR_EMPTY} {printf("CHAR is Empty");}
{WRONG_STR_NL} {printf("String has New line");}
{WRONG_STR_EMPTY} {printf("String Empty");}
{WRONG_STR_not_closed} {printf("String not closed");}
{ERROR} {printf("Unexpected token %s",yytext);}

%%
int main(int argc, char *argv[]){
    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
        printf("File doesn't exist");
    else {
        printf("1:\t");
        yylex();
        }
    printf("\n");

    return 0;
}