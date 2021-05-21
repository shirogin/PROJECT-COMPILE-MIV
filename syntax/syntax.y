%{
    #include <stdio.h>
    #include <string.h>
    extern struct position{
        int line,column;
    } position;
    extern char *yytext;
    extern char *Line;
    extern void exit(int status);
    int yylex();
    int yyerror(char* msg); 
    FILE *yyin;

%}

%token CODE START END CONST IDF EOI PROD
%token SEPARATOR BRACKETS_B BRACKETS_E C_BRACKETS_B C_BRACKETS_E PARENTHESIS_B PARENTHESIS_E
%token <myINT> TYPE
%token INTEGER FLOAT CHAR STRING
%token WHEN OTHERWISE WHILE EXECUTE DO
%token AFFECT ARTH_OP LOGIC_OP

%start PROGRAM

%union {
    int myINT;
    char myCHAR;
    char mySTRING[100];
    float myFLOAT;
}

%type <myCHAR> EOI

%%
PROGRAM: CODE DECLARATIONS START INSTRACTIONS END{
    printf("Program ended well");
};
DECLARATIONS: 
    | TYPE IDF NASSIGN ListIDF EOI DECLARATIONS
    | CONST TYPE CONSTIDF ListCONSTIDF EOI DECLARATIONS;
CONSTIDF: IDF ASSIGN;
VALUE: INTEGER 
    | FLOAT 
    | STRING 
    | CHAR;
ListIDF:  | SEPARATOR IDF NASSIGN ListIDF;
NASSIGN: | ASSIGN;
ASSIGN: AFFECT VALUE;
ListCONSTIDF: | SEPARATOR CONSTIDF ListCONSTIDF;
INSTRACTIONS: 
    | IDF AFFECT VALIDFP EXPRESSIONS EOI INSTRACTIONS
    | WHILE CONDITION EXECUTE C_BRACKETS_B INSTRACTIONS C_BRACKETS_E INSTRACTIONS;
    | WHEN CONDITION DO C_BRACKETS_B INSTRACTIONS C_BRACKETS_E OTHERWISE C_BRACKETS_B INSTRACTIONS C_BRACKETS_E INSTRACTIONS;
CONDITION: VALIDFP | PARENTHESIS_B CONDITION PARENTHESIS_E
    | VALIDFP LOGIC_OP CONDITION;
EXPRESSIONS:  | ARTH_OP VALIDFP EXPRESSIONS;
VALIDFP: IDF
    | VALUE
    | PROD PARENTHESIS_B PARAMETERS PARENTHESIS_E;
PARAMETERS: VALIDFP PARAMETERSLIST;
PARAMETERSLIST: | SEPARATOR PARAMETERS;
%%

int yyerror(char* msg){
    char s[100];
    
    sprintf(s,"Syntax Error %s on line %d colom %d : %s",msg, position.line,position.column-strlen(yytext),Line);
    printf("\033[1;31m%s\n",yytext);
    for(int i=0;i<(strlen(s)-strlen(yytext));i++){
        printf(" ");
    }
    printf("^\n\033[0m");
}

int main(int argc, char *argv[]){
    //F = fopen("Lexical.txt","w");
    //QuadF = fopen("Quadriples.txt","w");
    //DeclarationF=fopen("DeclarationF.txt","w");
    /*if( F== NULL)
        {printf("file couldn't be created");
        return (-1);}
    fprintf(F,"1-\t");*/
    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
        printf("File doesn't exist");
    else yyparse();
    printf("\nProgram Ended\n");
    printf("\n");
    //print_TS();
    //fclose(F);
    //print_qdr(ListQdr);

    return 0;
}

int yywrap()
{}