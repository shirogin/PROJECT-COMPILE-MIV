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

//Table[0].type = 0;
//Table[0].head; //=list variable

Symbol *createSymbol(char *entity, char t)
{
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->entity = strdup(entity);
    symbol->type = t;
    symbol->next = NULL;
    return symbol;
}
// declare(symb,type)
// type(symb)
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

void append(struct Symbol **head_ref, char *entity, char type)
{
    struct Symbol *new_node = (struct Symbol *)malloc(sizeof(struct Symbol));

    new_node->entity = entity;
    new_node->type = type;

    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void push(struct Symbol **head_ref, char *entity, char type)
{
    struct Symbol *new_node = (struct Symbol *)malloc(sizeof(struct Symbol));

    struct Symbol *last = *head_ref;

    new_node->entity = entity;
    new_node->type = type;

    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

Symbol *getSymbol(struct Symbol *head, char *entity)
{
    struct Symbol *current = head;
    int found = 0;

    while (current != NULL && found == 0)
    {
        if (strcmp(current->entity, entity) == 0)
            found = 1;
        else
            current = current->next;
    }

    return current;
}

int assignVal(struct Symbol *head, char *entity, char type, TV value)
{
    struct Symbol *temp = getSymbol(head, entity);

    if (temp != NULL)
    {
        if (temp->type == type)
        {
            if (temp->type == 'i')
                temp->value.Integer = value.Integer;
            else if (temp->type == 'f')
                temp->value.Integer = value.Float;
            else if (temp->type == 'c')
                temp->value.Char = value.Char;
            else if (temp->type == 's')
                temp->value.String = value.String;
            else if (temp->type == 'I' || temp->type == 'F' || temp->type == 'C' || temp->type == 'S')
                printf("Can't assign value to a CONSTANT!!\n");
        }
        else
        {
            printf("Can't assign value, Uncompatible types\n");
            return 0;
        }
        return 1;
    }
    else
    {
        printf("Can't assign value, Symbol not found\n");
        return 0;
    }
}

int declare(struct Symbol *head, char *entity, char type, TV value)
{
    struct Symbol *temp = getSymbol(head, entity);

    if (temp != NULL && temp->type == 'U')
    {
        temp->type = type;
        if (temp->type == 'I')
            temp->value.Integer = value.Integer;
        else if (temp->type == 'F')
            temp->value.Integer = value.Float;
        else if (temp->type == 'C')
            temp->value.Char = value.Char;
        else if (temp->type == 'S')
            temp->value.String = value.String;
        return 1;
    }
    else
    {
        printf("Can't declare, Symbol not found or already declared\n");
        return 0;
    }
}

void printList(struct Symbol *head)
{
    while (head != NULL)
    {
        printf(" %s-%c", head->entity, head->type);
        if (head->type == 'i' || head->type == 'I')
            printf("-%d ", head->value.Integer);
        else if (head->type == 'f' || head->type == 'F')
            printf("-%f ", head->value.Float);
        else if (head->type == 'c' || head->type == 'C')
            printf("-%c ", head->value.Char);
        else if (head->type == 's' || head->type == 'S')
            printf("-%s ", head->value.String);
        else if (head->type == 'U' || head->type == '&' || head->type == 'K')
            printf(" ");
        head = head->next;
    }
    printf("\n");
}