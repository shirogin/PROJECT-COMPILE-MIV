%{
    #include "../lib.h"
    extern struct position{
        int line,column;
    } position;
    extern void printTS();
    extern Symbol *TS ;
    extern char *yytext;
    extern void freeTS();
    extern char *Line;
    extern void exit(int status);
    TV val;
    int yylex();
    int yyerror(char* msg); 
    char T;
    FILE *yyin;

%}

%token CODE START END CONST EOI PROD
%token SEPARATOR BRACKETS_B BRACKETS_E C_BRACKETS_B C_BRACKETS_E PARENTHESIS_B PARENTHESIS_E
%token <mySTRING> TYPE STRING IDF

%token <myINT>INTEGER 
%token <myFLOAT>FLOAT 
%token <myCHAR>CHAR 
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
MTYPE : TYPE{
    T=$1[0];
};
DECLARATIONS: 
    | MTYPE IDF NASSIGN ListIDF EOI DECLARATIONS
    | CONST MTYPE CONSTIDF ListCONSTIDF EOI DECLARATIONS;
CONSTIDF: 
    IDF ASSIGN{
        declareConst(TS,$1,T,val);
    };
VALUE: INTEGER{ val.Integer=$1; } 
    | FLOAT { val.Float=$1; } 
    | STRING { val.String=$1; } 
    | CHAR{ val.Char=$1; } ;
ListIDF:  
    | SEPARATOR IDF NASSIGN ListIDF;
NASSIGN: 
    | ASSIGN;
ASSIGN: 
    AFFECT VALUE;
ListCONSTIDF: 
    | SEPARATOR CONSTIDF ListCONSTIDF;
INSTRACTIONS: 
    | IDF AFFECT VALIDFP EXPRESSIONS EOI INSTRACTIONS
    | WHILE CONDITION EXECUTE INSTRACTIONSSET INSTRACTIONS
    | WHENINSTRACTION INSTRACTIONS;
WHENINSTRACTION: 
    WHEN CONDITION DO INSTRACTIONSSET OTHERWISEINSTRACTIONS ;
OTHERWISEINSTRACTIONS: 
    | OTHERWISE OTHERWISEWHENINSTRACTIONS;
OTHERWISEWHENINSTRACTIONS: 
    WHENINSTRACTION INSTRACTIONSSET|INSTRACTIONSSET ;
INSTRACTIONSSET: 
    C_BRACKETS_B INSTRACTIONS C_BRACKETS_E;
CONDITION: 
    VALIDFP 
    | PARENTHESIS_B CONDITION PARENTHESIS_E
    | VALIDFP LOGIC_OP CONDITION;
EXPRESSIONS:  
    | ARTH_OP VALIDFP EXPRESSIONS;
VALIDFP: 
    IDF
    | VALUE
    | PROD PARENTHESIS_B PARAMETERS PARENTHESIS_E;
PARAMETERS: 
    VALIDFP PARAMETERSLIST;
PARAMETERSLIST: 
    | SEPARATOR PARAMETERS;
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
    printTS();
    freeTS();
    printf("\nProgram Ended\n");
    printf("\n");
    
    //print_TS();
    //fclose(F);
    //print_qdr(ListQdr);

    return 0;
}

int yywrap()
{}