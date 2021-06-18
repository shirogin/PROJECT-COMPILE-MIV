#include "../lexical/TS.h"

quad_node *createQuadNode(Symbol *op1, Symbol *op2, Symbol *op3, Symbol *op4)
{
    quad_node *quad = (quad_node *)calloc(1, sizeof(quad_node));
    if (quad == NULL)
        exit(-1);
    quad->op1 = op1;
    quad->op2 = op2;
    quad->op3 = op3;
    quad->op4 = op4;
    quad->next = NULL;
    quad->prev = NULL;
    return quad;
}

Quad *createQuad()
{
    Quad *quad = (Quad *)calloc(1, sizeof(Quad));
    quad->head = NULL;
    quad->tail = NULL;
    quad->length = 0;
    return quad;
}

void appendQuad(Quad **head_ref, Symbol *op1, Symbol *op2, Symbol *op3, Symbol *op4)
{
    quad_node *newNode = createQuadNode(op1, op2, op3, op4);

    if ((*head_ref)->length == 0)
    {
        (*head_ref)->head = newNode;
        (*head_ref)->tail = newNode;
    }
    else
    {
        (*head_ref)->tail->prev = newNode;
        newNode->next = (*head_ref)->head;
        (*head_ref)->head = newNode;
    }
    (*head_ref)->length++;
}

void pushQuad(Quad **head_ref, Symbol *op1, Symbol *op2, Symbol *op3, Symbol *op4)
{
    quad_node *newNode = createQuadNode(op1, op2, op3, op4);

    if ((*head_ref)->length == 0)
    {
        (*head_ref)->head = newNode;
        (*head_ref)->tail = newNode;
    }
    else
    {
        (*head_ref)->tail->next = newNode;
        newNode->prev = (*head_ref)->tail;
        (*head_ref)->tail = newNode;
    }
    (*head_ref)->length++;
}

void printQuadList(Quad *quad)
{
    printf("\n------------------------------------------\n");
    int i = 1;
    while (quad->head != NULL)
    {
        printf("%d- | %s | %s | %s | %s |", i, quad->head->op1->entity, quad->head->op2->entity, quad->head->op3->entity, quad->head->op4->entity);
        quad->head = quad->head->next;
        i++;
        printf("\n------------------------------------------\n");
    }
}

// void freeList(Symbol **head_ref)
// {
//     Symbol *next = *head_ref, *last = NULL;
//     while (next != NULL)
//     {
//         last = next;
//         next = next->next;
//         free(last);
//     }
// }