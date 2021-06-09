#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Symbol Symbol;
typedef union TV TV;

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
    char declared;
    /**
     *  
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

//Table[0].type = 0;
//Table[0].head; //=list variable

Symbol *createSymbol(char *entity, char t)
{
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->entity = strdup(entity);
    symbol->declared = t;
    symbol->next = NULL;
    return symbol;
}
// declare(symb,type)
// declared(symb)
//
void addSymbol(Symbol **ahead, char *entity, char t)
{
    if ((*ahead) == NULL)
        (*ahead) = createSymbol(entity, t);
    else
    {
        Symbol *head = *ahead;
        while (head->next != NULL)
            head = head->next;
        head->next = createSymbol(entity, t);
    }
}