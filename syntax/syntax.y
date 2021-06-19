%{
    #include "./quad.h"
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
    char IT,VT;
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
    char* mySTRING;
    float myFLOAT;
}

%type <myCHAR> EOI

%%
PROGRAM: CODE DECLARATIONS START INSTRACTIONS END;
MTYPE : TYPE{
    IT=$1[0];
};
DECLARATIONS: 
    | MTYPE VARIDF ListIDF EOI DECLARATIONS
    | CONST MTYPE CONSTIDF ListCONSTIDF EOI DECLARATIONS;
CONSTIDF: 
    IDF ASSIGN{
        if(VT==IT){
            int x=declareConst(TS,$1,VT,val);
            if(x==0)
                printf("Can't declare, Const not found \n");
            else if(x==-1)
                printf("Can't declare, Const has been already declared\n");
        }else printf("Can't declare, Trying to declare Const with diffrent type of value\n");
    };
VARIDF: IDF NASSIGN{
        int x=declareVariable(TS,$1,IT);
        if(x==0)
                printf("Can't declare, Variable not found \n");
        else if(x==-1)
            printf("Can't declare, Variable has been already declared\n");
        else if(VT==IT ) {
            x=assignVal(TS,$1,tolower(VT),val);
            if(x==0)
                printf("Can't Assign, Variable not found \n");
            else if(x==-1)
                printf("Can't Assign, Trying to assign variable with diffrent type of value then the type declared with\n");
        }
        else if( VT!='U') printf("Can't Assign value, Trying to assign variable with diffrent type of value then the type declared with\n");
    };
VALUE: INTEGER{ VT='I'; val.Integer=$1; } 
    | FLOAT { VT='F'; val.Float=$1;} 
    | STRING { VT='S'; val.String=strdup($1);} 
    | CHAR{ VT='C'; val.Char=$1; printf("%c",$1); } ;
ListIDF:  
    | SEPARATOR VARIDF ListIDF;
NASSIGN: {VT='U'}
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
    IDF{
        Symbol * temp=getSymbol(TS,$1);
        if(temp==NULL)
            printf("IDF not found!!");
        else if(temp->type=='U')
            printf("Can't access IDF, IDF not declared");
    }
    | VALUE
    | PROD PARENTHESIS_B PARAMETERS PARENTHESIS_E;
PARAMETERS: 
    VALIDFP EXPRESSIONS PARAMETERSLIST;
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
    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
        printf("File doesn't exist");
    else{
        QuadInit();
        yyparse();
        printf("\nProgram Ended\n");
        printf("\n");
        printTS();
        print
        freeQuads();
        freeTS();
    } 
    
    
    
    fclose(yyin);

    return 0;
}

int yywrap()
{}