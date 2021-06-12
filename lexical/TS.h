#include "../lib.h"

Symbol *createSymbol(char *entity, char t)
{
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));

    symbol->entity = strdup(entity);
    symbol->type = t;
    symbol->next = NULL;
    return symbol;
}

void append(Symbol **head_ref, char *entity, char type)
{
    Symbol *new_node = createSymbol(entity, type);

    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void push(Symbol **head_ref, char *entity, char type)
{
    Symbol *new_node = createSymbol(entity, type);

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    Symbol *last = *head_ref;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

Symbol *getSymbol(Symbol *head, char *entity)
{
    Symbol *current = head;
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

int assignVal(Symbol *head, char *entity, char type, TV value)
{
    Symbol *temp = getSymbol(head, entity);

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

int declareConst(Symbol *head, char *entity, char type, TV value)
{
    Symbol *temp = getSymbol(head, entity);

    if (temp != NULL && temp->type == 'U')
    {
        temp->type = type;
        switch (type)
        {
        case 'I':
            temp->value.Integer = value.Integer;
            break;
        case 'F':
            temp->value.Integer = value.Float;
            break;
        case 'C':
            temp->value.Char = value.Char;
            break;
        case 'S':
            temp->value.String = value.String;
            break;
        default:
            break;
        }
        return 1;
    }
    else
    {
        //printf("Can't declare, Symbol not found or already declared\n");
        return 0;
    }
}
int declareVariable(Symbol *head, char *entity, char type)
{
    Symbol *temp = getSymbol(head, entity);

    if (temp != NULL && temp->type == 'U')
    {
        temp->type = tolower(type);
        return 1;
    }
    else
    {
        //printf("Can't declare, Symbol not found or already declared\n");
        return 0;
    }
}

void printList(Symbol *head)
{
    printf("\n-----------------------\n");
    while (head != NULL)
    {
        printf("| %s |  %c  |", head->entity, head->type);
        if (head->type == 'i' || head->type == 'I')
            printf("    %d |", head->value.Integer);
        else if (head->type == 'f' || head->type == 'F')
            printf("|   %f  |", head->value.Float);
        else if (head->type == 'c' || head->type == 'C')
            printf("|   %c  |", head->value.Char);
        else if (head->type == 's' || head->type == 'S')
            printf("|   %s  |", head->value.String);
        else if (head->type == 'U' || head->type == '&' || head->type == 'K')
            printf(" ");
        head = head->next;
        printf("\n-----------------------\n");
    }
}
void freeList(Symbol **head_ref)
{
    Symbol *next = *head_ref, *last = NULL;
    while (next != NULL)
    {
        last = next;
        next = next->next;
        free(last);
    }
}