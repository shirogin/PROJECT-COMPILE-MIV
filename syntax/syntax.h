#include "../lib.h"
//-------------------------------PreSymbol Def-------------------------------------------
typedef struct PreSymbol PreSymbol;
struct PreSymbol
{
    Symbol *ref;
    /**
     * A : AFFICATION
     * + / - * Arethmetic Operatopins
     * <|=|!|>|l|g LOGIC_OP
     * E Etiquet
     * W While
     * s Symbole
     * I IF
     * P Prods
     * & temp
     * J jump
     * T jump if trues
     * F jump if false
    */
    char type;
    PreSymbol *next;
};

//-------------------------------QUAD Def-------------------------------------------
typedef struct quad_node quad_node;
typedef struct Quad Quad;

struct quad_node
{
    int num;
    PreSymbol *op1;
    PreSymbol *op2;
    PreSymbol *op3;
    PreSymbol *res;
    struct quad_node *next;
    struct quad_node *prev;
};

struct Quad
{
    quad_node *head;
    quad_node *tail;
    int length;
};

void QuadInit();

Quad *createQuad();

quad_node *createQuadNode(PreSymbol *op1, PreSymbol *op2, PreSymbol *op3, PreSymbol *op4);

void appendQuad(PreSymbol *op1, PreSymbol *op2, PreSymbol *op3, PreSymbol *op4);

void pushQuad(PreSymbol *op1, PreSymbol *op2, PreSymbol *op3, PreSymbol *op4);

void printQuadList();
void freeQuads();
