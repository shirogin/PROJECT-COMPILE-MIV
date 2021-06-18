#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct Symbol Symbol;
typedef union TV TV;
typedef struct quad_node quad_node;
typedef struct Quad Quad;

union TV
{
    char Char;
    char *String;
    int Integer;
    float Float;
};

struct Symbol
{
    char *entity;
    char type;
    /**
    *   K : keywords
    *   & : commenTV
    *   U : variables without types
    *   i : int 
    *   I : const int
    *   s : string
    *   S : const string
    *   c : char
    *   C : const char
    *   f : float
    *   F : const float
    */
    TV value;
    Symbol *next;
};

struct quad_node
{
    int num;
    Symbol *op1;
    Symbol *op2;
    Symbol *op3;
    Symbol *op4;
    struct quad_node *next;
    struct quad_node *prev;
};

struct Quad
{
    quad_node *head;
    quad_node *tail;
    int length;
};

Symbol *createSymbol(char *entity, char t);

void push(Symbol **head_ref, char *entity, char type);

Symbol *getSymbol(Symbol *head, char *entity);

int assignVal(Symbol *head, char *entity, char type, TV value);

int declareConst(Symbol *head, char *entity, char type, TV value);
int declareVariable(Symbol *head, char *entity, char type);

void printList(Symbol *head);
void freeList(Symbol **head_ref);
