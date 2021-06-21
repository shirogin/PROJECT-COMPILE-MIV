%{
    #include "./quad.h"
    extern struct position{
        int line,column;
    } position;
    extern void printTS();
    extern Symbol *TS ;
    PreSymbol * TempS=NULL,*EtiqueL=NULL,*EtiqueE=NULL,*EtiqueELSE=NULL;
    Symbol *temp=NULL;
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
%token <mySTRING>AFFECT ARTH_OP LOGIC_OP

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
MTYPE : TYPE{ IT=$1[0]; };
DECLARATIONS: | MTYPE VARIDF ListIDF EOI DECLARATIONS
    | CONST MTYPE CONSTIDF ListCONSTIDF EOI DECLARATIONS;
CONSTIDF: 
    IDF ASSIGN{
        if(VT==IT){
            int x=declareConst(TS,$1,VT,val);
            if(x==0) printf("Can't declare, Const not found \n");
            else if(x==-1) printf("Can't declare, Const has been already declared\n");
        }else printf("Can't declare, Trying to declare Const with diffrent type of value\n");
    };
VARIDF: IDF NASSIGN{
        int x=declareVariable(TS,$1,IT);
        if(x==0) printf("Can't declare, Variable not found \n");
        else if(x==-1) printf("Can't declare, Variable has been already declared\n");
        else if(VT==IT ) {
            x=assignVal(TS,$1,tolower(VT),val);
            if(x==0) printf("Can't Assign, Variable not found \n");
            else if(x==-1) printf("Can't Assign, Trying to assign variable with diffrent type of value then the type declared with\n");
        }
        else if( VT!='U') printf("Can't Assign value, Trying to assign variable with diffrent type of value then the type declared with\n");
    };
VALUE: INTEGER{ VT='I'; val.Integer=$1; } 
    | FLOAT { VT='F'; val.Float=$1;} 
    | STRING { VT='S'; val.String=strdup($1);} 
    | CHAR{ VT='C'; val.Char=$1; } ;
ListIDF: | SEPARATOR VARIDF ListIDF;
NASSIGN: {VT='U';} | ASSIGN;
ASSIGN: AFFECT VALUE;
ListCONSTIDF:  | SEPARATOR CONSTIDF ListCONSTIDF;
INSTRACTIONS:  | AFFECTATION  EXPRESSIONS EOI{ 
        PreSymbol*t= inToPost(TempS);
        quadPreSymbol(t);
        TempS=NULL;
    } INSTRACTIONS
    | WHILE {
        Symbol *t=createSymbol("&", 'i');
        t->value.Integer=quads->length;
        appendPreSymbol( &EtiqueL,createPreSymbol(t, 'E'));
    } PARENTHESIS_B CONDITION PARENTHESIS_E EXECUTE{
        Symbol *t=createSymbol("&", 'i');
        PreSymbol *p=createPreSymbol(t, 'E');
        appendPreSymbol( &EtiqueE,p);
        pushQuad(createPreSymbol(NULL,'F'),p,quads->tail->res,NULL);
    }
        INSTRACTIONSSET { 
            PreSymbol *pp= poppPreSymbol(&EtiqueL);
            pushQuad(createPreSymbol(NULL,'J'),pp,NULL,NULL);
            pp= poppPreSymbol(&EtiqueE);
            pp->ref->value.Integer=quads->length;
        } INSTRACTIONS
    | WHENINSTRACTION INSTRACTIONS;
AFFECTATION: IDF {
        temp=getSymbol(TS,$1);
        if(temp==NULL) printf("IDF not found!!");
        else if(temp->type=='U') printf("Can't access IDF, IDF not declared");
        else pushPreSymbol(&TempS,createPreSymbol(temp,'s'));
    } AFFECT {
        pushPreSymbol(&TempS,createPreSymbol(NULL,':'));
    };
WHENINSTRACTION: WHEN PARENTHESIS_B CONDITION PARENTHESIS_E DO{ 
    Symbol *t=createSymbol("&", 'i');
    //create etique
    PreSymbol *p=createPreSymbol(t, 'E');
    //push etique to etique else
    appendPreSymbol( &EtiqueELSE,p);
    //create quadriple with etique JF
    pushQuad(createPreSymbol(NULL,'F'),p,quads->tail->res,NULL);
    //create etique end
    t=createSymbol("&", 'i');
    p=createPreSymbol(t, 'E');
    //push etique to etique E 
    appendPreSymbol( &EtiqueE,p);
} INSTRACTIONSSET {
    //create jump quad to etiqueE using top
    pushQuad(createPreSymbol(NULL,'J'),EtiqueE,NULL,NULL);
    
} OTHERWISEINSTRACTIONS ;
OTHERWISEINSTRACTIONS: { 
        //pop it out
        PreSymbol *p= poppPreSymbol(&EtiqueE);
        //assign val to etique E
        p->ref->value.Integer=quads->length; 
    }
    | OTHERWISE{
        //assign val to etiqueElse and pop it out
        PreSymbol *p= poppPreSymbol(&EtiqueELSE);
        p->ref->value.Integer=quads->length;        
    } OTHERWISEWHENINSTRACTIONS;
OTHERWISEWHENINSTRACTIONS: WHENINSTRACTION {
        //pop it out
        PreSymbol *p= poppPreSymbol(&EtiqueE);
        //assign val to etique E
        p->ref->value.Integer=quads->length;  
    }
    | INSTRACTIONSSET { 
        //pop it out
        PreSymbol *p= poppPreSymbol(&EtiqueE);
        //assign val to etique E
        p->ref->value.Integer=quads->length;
        pushQuad(createPreSymbol(NULL,'J'),p,NULL,NULL);
    };
INSTRACTIONSSET: C_BRACKETS_B INSTRACTIONS C_BRACKETS_E;
CONDITION: VALIDFP LOGIC_OP  { pushPreSymbol(&TempS,createPreSymbol(NULL,$2[0]));} 
    VALIDFP{
        PreSymbol*t= inToPost(TempS);
        quadPreSymbol(t);
        TempS=NULL;
    };
EXPRESSIONS: VALIDFP SUBEXPRESSIONS
    | PARENTHESIS_B {pushPreSymbol(&TempS,createPreSymbol(NULL,'('))} EXPRESSIONS 
        PARENTHESIS_E {pushPreSymbol(&TempS,createPreSymbol(NULL,')'))} SUBEXPRESSIONS ;
SUBEXPRESSIONS: | ARTH_OP { pushPreSymbol(&TempS,createPreSymbol(NULL,$1[0])); } EXPRESSIONS;
VALIDFP: IDF{
        temp=getSymbol(TS,$1);
        if(temp==NULL) printf("IDF not found!!");
        else if(temp->type=='U') printf("Can't access IDF, IDF not declared");    
        else pushPreSymbol(&TempS,createPreSymbol(temp,'s'));   
    }
    | VALUE{
        temp = createSymbol("#",tolower(VT));
        setVal(temp,tolower(VT),val);
        pushPreSymbol(&TempS,createPreSymbol(temp,'s'));
    }
    | PROD PARENTHESIS_B PARAMETERS PARENTHESIS_E;
PARAMETERS:  EXPRESSIONS PARAMETERSLIST;
PARAMETERSLIST: | SEPARATOR PARAMETERS;
%%

int yyerror(char* msg){
    char s[100];
    
    sprintf(s,"Syntax Error %s on line %d colom %d : %s",msg, position.line,(int)(position.column-strlen(yytext)),Line);
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
        
        printf("\n");
        printf("------QUADRIPULES TABLE----");
        printQuadList();
        EvaluateQuad();
        printf("------SYMBOL TABLE----");
        printTS();
        freeQuads();
        freeTS();
        printf("\nProgram Ended well\n");
    } 
    
    
    
    fclose(yyin);

    return 0;
}

int yywrap()
{}