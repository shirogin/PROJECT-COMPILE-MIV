#include "../lib.h"
const int SymbolSize = sizeof(Symbol);

Symbol *createSymbol(char *entity, char t)
{
    Symbol *symbol = (Symbol *)calloc(1, SymbolSize);
    if (symbol == NULL)
        exit(-1);
    // printf("%d", strlen(entity));
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
    pushSymbol(head_ref, createSymbol(entity, type));
}

void pushSymbol(Symbol **head_ref, Symbol *new_node)
{

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
int setVal(Symbol *temp, char type, TV value)
{
    if (temp != NULL)
    {
        if (temp->type == type)
        {
            if (temp->type == 'i')
                temp->value.Integer = value.Integer;
            else if (temp->type == 'f')
                temp->value.Float = value.Float;

            else if (temp->type == 'c')
                temp->value.Char = value.Char;
            else if (temp->type == 's')
                temp->value.String = value.String;
            else if (temp->type == 'I' || temp->type == 'F' || temp->type == 'C' || temp->type == 'S')
                printf("Can't assign value to a CONSTANT!!\n");
            return 1;
        }
        else
            //printf("Can't assign value, Uncompatible types\n");
            return -1;
    }
    else
        return 0;
}
int assignVal(Symbol *head, char *entity, char type, TV value)
{
    Symbol *temp = getSymbol(head, entity);
    return setVal(temp, type, value);
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
    else if (temp != NULL)
        return 0;
    else
        return -1;
}

int declareVariable(Symbol *head, char *entity, char type)
{
    Symbol *temp = getSymbol(head, entity);

    if (temp != NULL && temp->type == 'U')
    {
        temp->type = tolower(type);
        return 1;
    }
    else if (temp != NULL)
        return 0;
    else
        return -1;
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
            printf("   %f  |", head->value.Float);
        else if (head->type == 'c' || head->type == 'C')
            printf("   '%c'  |", head->value.Char);
        else if (head->type == 's' || head->type == 'S')
            printf("   \"%s\"  |", head->value.String);
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