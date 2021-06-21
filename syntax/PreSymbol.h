#include "./syntax.h"
//-----------------------------------PreSymbol Settings ------------------------------
const int PreSymbolSize = sizeof(PreSymbol);
PreSymbol *createPreSymbol(Symbol *symbol, char type)
{
    PreSymbol *preSymbol = (PreSymbol *)calloc(1, PreSymbolSize);
    preSymbol->next = NULL;
    preSymbol->ref = symbol;
    preSymbol->type = type;
    return preSymbol;
}

void pushPreSymbol(PreSymbol **head_ref, PreSymbol *new_node)
{
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    PreSymbol *last = *head_ref;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}
void appendPreSymbol(PreSymbol **head_ref, PreSymbol *new_node)
{
    new_node->next = *head_ref;
    *head_ref = new_node;
}
PreSymbol *poppPreSymbol(PreSymbol **head_ref)
{
    PreSymbol *temp = *head_ref;
    *head_ref = temp->next;
    temp->next = NULL;
    return temp;
}
//void postfixPreSymbol();
int preced(char ch)
{
    if (ch == '<' || ch == '=' || ch == '!' || ch == '>' || ch == 'l' || ch == 'g')
        return 1;
    else if (ch == '+' || ch == '-')
        return 2; //Precedence of + or - is 1
    else if (ch == '*' || ch == '/')
        return 3; //Precedence of * or / is 2
    else
        return 0;
}
char topPreSymbol(PreSymbol *head)
{
    while (head->next != NULL)
    {
        head = head->next;
    }
    return head->type;
}
PreSymbol *popPreSymbol(PreSymbol *head)
{
    PreSymbol *stalker = head;
    while (head->next != NULL)
    {
        stalker = head;
        head = head->next;
    }
    stalker->next = NULL;
    return head;
}
PreSymbol *inToPost(PreSymbol *head)
{
    PreSymbol *stk = createPreSymbol(NULL, '#'); //add some extra character to avoid underflow
    PreSymbol *postfix = NULL;                   //initially the postfix string is empty

    while (head != NULL)
    {
        if (head->type == 's')
            pushPreSymbol(&postfix, createPreSymbol(head->ref, head->type)); //add to postfix when character is letter or number
        else if (head->type == '(')
            pushPreSymbol(&stk, createPreSymbol(NULL, '('));
        else if (head->type == ')')
        {
            char top = topPreSymbol(stk);
            while (top != '#' && top != '(')
            {
                pushPreSymbol(&postfix, popPreSymbol(stk)); //store and pop until ( has found
                top = topPreSymbol(stk);
            }
            popPreSymbol(stk); //remove the '(' from stack
        }
        else
        {
            if (preced(head->type) > preced(topPreSymbol(stk)))
                pushPreSymbol(&stk, createPreSymbol(NULL, head->type)); //push if precedence is high
            else
            {
                char top = topPreSymbol(stk);
                while (top != '#' && preced(head->type) <= preced(top))
                {
                    pushPreSymbol(&postfix, popPreSymbol(stk)); //store and pop until higher precedence is found
                    top = topPreSymbol(stk);
                }
                pushPreSymbol(&stk, createPreSymbol(NULL, head->type));
            }
        }
        head = head->next;
    }
    char top = topPreSymbol(stk);
    while (top != '#')
    {
        pushPreSymbol(&postfix, popPreSymbol(stk)); //store and pop until stack is not empty.
        top = topPreSymbol(stk);
    }

    return postfix;
}
void printPreSymbol(PreSymbol *head)
{
    printf("\n-----------------------\n");
    while (head != NULL)
    {
        if (head->ref == NULL)
            printf("| Not IDF |  %c  |", head->type);
        else
        {
            printf("| %s |  %c  | <%c> |", head->ref->entity, head->type, head->ref->type);
            if (head->ref->type == 'i' || head->type == 'I')
                printf("    %d |", head->ref->value.Integer);
            else if (head->ref->type == 'f' || head->ref->type == 'F')
                printf("   %f  |", head->ref->value.Float);
            else if (head->ref->type == 'c' || head->ref->type == 'C')
                printf("   '%c'  |", head->ref->value.Char);
            else if (head->ref->type == 's' || head->ref->type == 'S')
                printf("   \"%s\"  |", head->ref->value.String);
        }
        head = head->next;
        printf("\n-----------------------\n");
    }
}