#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Symbol Symbol;
typedef union TS TS;

union TS
{
    char Char;
    char *String;
    int Integer;
    float Float;
};

struct Symbol
{
    char *entity;
    char declared; // 0 null 1 variable 2 const
    TS value;
    Symbol *next;
};

struct Symbols
{
    short type;
    Symbol *head;
};

Symbol *createSymbol(char *entity)
{
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->entity = strdup(entity);
    symbol->declared = 'F';
    symbol->next = NULL;
    return symbol;
}

void addSymbol(Symbol **ahead, char *entity)
{
    if ((*ahead) == NULL)
        (*ahead) = createSymbol(entity);
    else
    {
        Symbol *head = *ahead;
        while (head->next != NULL)
            head = head->next;
        head->next = createSymbol(entity);
    }
}