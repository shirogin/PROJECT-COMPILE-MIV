#include "../lib.h"
//-------------------------------QUAD Def-------------------------------------------

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

void QuadInit();

Quad *createQuad();

quad_node *createQuadNode(Symbol *op1, Symbol *op2, Symbol *op3, Symbol *op4);

void appendQuad(Symbol *op1, Symbol *op2, Symbol *op3, Symbol *op4);

void pushQuad(Symbol *op1, Symbol *op2, Symbol *op3, Symbol *op4);

void printQuadList();
void freeQuads();
//-----------------------------------Quad Settings ------------------------------
const int QuadNodeSize = sizeof(quad_node);
const int QuadSize = sizeof(Quad);
Quad *quads;
void QuadInit()
{
    quads = createQuad();
}
Quad *createQuad()
{
    Quad *quad = (Quad *)calloc(1, QuadSize);
    quad->head = NULL;
    quad->tail = NULL;
    quad->length = 0;
    return quad;
}
quad_node *createQuadNode(Symbol *op1, Symbol *op2, Symbol *op3, Symbol *op4)
{
    quad_node *quad = (quad_node *)calloc(1, QuadNodeSize);
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

void appendQuad(Symbol *op1, Symbol *op2, Symbol *op3, Symbol *op4)
{
    quad_node *newNode = createQuadNode(op1, op2, op3, op4);

    if (quads->length == 0)
    {
        quads->head = newNode;
        quads->tail = newNode;
    }
    else
    {
        quads->tail->prev = newNode;
        newNode->next = quads->head;
        quads->head = newNode;
    }
    quads->length++;
}

void pushQuad(Symbol *op1, Symbol *op2, Symbol *op3, Symbol *op4)
{
    quad_node *newNode = createQuadNode(op1, op2, op3, op4);

    if (quads->length == 0)
    {
        quads->head = newNode;
        quads->tail = newNode;
    }
    else
    {
        quads->tail->next = newNode;
        newNode->prev = quads->tail;
        quads->tail = newNode;
    }
    quads->length++;
}

void printQuadList()
{
    quad_node *head = quads->head;
    printf("\n------------------------------------------\n");
    int i = 1;
    while (head != NULL)
    {
        printf("%d- | %s | %s | %s | %s |", i, head->op1->entity, head->op2->entity, head->op3->entity, head->op4->entity);
        head = head->next;
        i++;
        printf("\n------------------------------------------\n");
    }
}

void freeQuads()
{
    quad_node *next = quads->head, *last = NULL;
    while (next != NULL)
    {
        last = next;
        next = next->next;
        free(last);
    }
    quads->head = NULL;
    quads->tail = NULL;
}