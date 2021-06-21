#include "./PreSymbol.h"
//-----------------------------------Quad Settings ------------------------------
const int QuadNodeSize = sizeof(quad_node);
const int QuadSize = sizeof(Quad);
int resNum;
char resName[20];
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

quad_node *createQuadNode(PreSymbol *op1, PreSymbol *op2, PreSymbol *op3, PreSymbol *res)
{
    quad_node *quad = (quad_node *)calloc(1, QuadNodeSize);
    if (quad == NULL)
        exit(-1);
    quad->op1 = op1;
    quad->op2 = op2;
    quad->op3 = op3;
    quad->res = res;
    quad->next = NULL;
    quad->prev = NULL;
    return quad;
}

void appendQuad(PreSymbol *op1, PreSymbol *op2, PreSymbol *op3, PreSymbol *res)
{
    quad_node *newNode = createQuadNode(op1, op2, op3, res);

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

void quadPreSymbol(PreSymbol *postfix)
{

    //PreSymbol *p1 = b->next, *p2 = p1->next, *p3 = p2->next;
    //printf("%c %c %c", p1->type, p2->type, p3->type);
    PreSymbol *pile = NULL;
    while (postfix != NULL)
    {
        PreSymbol *op1 = poppPreSymbol(&postfix);

        if (op1->type == 's')
        {
            appendPreSymbol(&pile, op1);
        }
        else
        {

            PreSymbol *op2 = poppPreSymbol(&pile),
                      *op3 = NULL,
                      *res = NULL;
            switch (op1->type)
            {
            case ':':
            {
                char type = tolower(op2->ref->type);
                res = poppPreSymbol(&pile);
                if (type != tolower(res->ref->type))
                {
                    printf("semantic error : data type aren't the same");
                    exit(-1);
                }

                break;
            }
            default:
            {
                op3 = op2;
                op2 = poppPreSymbol(&pile);
                char type = tolower(op2->ref->type);
                if (type != tolower(op3->ref->type))
                {
                    printf("semantic error : data type aren't the same");
                    exit(-1);
                }
                sprintf(resName, "TEMP %d", resNum);
                resNum++;
                res = createPreSymbol(createSymbol(resName, type), 's');
                appendPreSymbol(&pile, res);
                break;
            }
            }
            pushQuad(op1, op2, op3, res);
        }
        //createQuad();
    }
}

void pushQuad(PreSymbol *op1, PreSymbol *op2, PreSymbol *op3, PreSymbol *res)
{
    quad_node *newNode = createQuadNode(op1, op2, op3, res);

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
        printf("%d- ( %c , %s , %s , %s )", i,
               head->op1->type,
               head->op2 == NULL ? "NULL" : head->op2->ref->entity,
               head->op3 == NULL ? "NULL" : head->op3->ref->entity,
               head->res == NULL ? "NULL" : head->res->ref->entity);
        head = head->next;
        i++;
        printf("\n------------------------------------------\n");
    }
}
quad_node *getIndex(int x)
{
    int i = 0;
    quad_node *head = quads->head;
    while (head != NULL && i < x)
    {
        head = head->next;
        i++;
    }
    return head;
}
int EvaluationArth(char type, Symbol *op2, Symbol *op3, Symbol *res)
{
    switch (type)
    {
    case '+':
    {
        switch (res->type)
        {
        case 'i':
            res->value.Integer = op2->value.Integer + op3->value.Integer;
            break;
        case 'f':
            res->value.Float = op2->value.Float + op3->value.Float;
            break;
        case 'c':
            res->value.Char = (char)((int)op2->value.Char + (int)op3->value.Char);
            break;
        case 's':
        {
            res->value.String = (char *)malloc(sizeof(char) * (strlen(op3->value.String) + strlen(op2->value.String)));
            strcpy(res->value.String, op2->value.String);
            strcat(res->value.String, op3->value.String);
            break;
        }
        default:
            printf("semantic error : unknown type");
        }
        return 1;
    }
    case '-':
    {
        switch (res->type)
        {
        case 'i':
            res->value.Integer = op2->value.Integer - op3->value.Integer;
            break;
        case 'f':
            res->value.Float = op2->value.Float - op3->value.Float;
            break;
        default:
        {
            printf("semantic error : This operation '-' can only be applied to int or floats");
            exit(-1);
        }
        }
        return 1;
    }
    case '*':
    {
        switch (res->type)
        {
        case 'i':
            res->value.Integer = op2->value.Integer * op3->value.Integer;
            break;
        case 'f':
            res->value.Float = op2->value.Float * op3->value.Float;
            break;
        default:
        {
            printf("semantic error : This operation '*' can only be applied to int or floats");
            exit(-1);
        }
        }
        return 1;
    }
    case '/':
    {
        switch (res->type)
        {
        case 'i':
        {
            if (op3->value.Integer == 0)
            {
                printf("semantic error : division by 0");
                exit(-1);
            }
            res->value.Integer = op2->value.Integer / op3->value.Integer;
            break;
        }
        case 'f':
        {
            if (op3->value.Float == 0)
            {
                printf("semantic error : division by 0");
                exit(-1);
            }
            res->value.Float = op2->value.Float / op3->value.Float;
            break;
        }
        default:
        {
            printf("semantic error : This operation '/' can only be applied to int or floats");
            exit(-1);
        }
        }
        return 1;
    }
    }
    return 0;
}
void EvaluateQuad()
{
    quad_node *head = quads->head;
    while (head != NULL)
    {
        PreSymbol *op1 = head->op1;
        Symbol *op2 = head->op2 == NULL ? NULL : head->op2->ref,
               *op3 = head->op3 == NULL ? NULL : head->op3->ref,
               *res = head->res == NULL ? NULL : head->res->ref;

        if (EvaluationArth(op1->type, op2, op3, res) == 0)
        {
            switch (op1->type)
            {
            case ':':
            {
                if (res->type == 'I' || res->type == 'F' || res->type == 'C' || res->type == 'S')
                {
                    printf("Semantic Error : you can't affect values to constants");
                    exit(-1);
                }
                res->value = op2->value;
                break;
            }
            case '<':
            {
                switch (res->type)
                {
                case 'i':
                {
                    res->value.Integer = (op2->value.Integer < op3->value.Integer) ? 1 : 0;

                    break;
                }
                case 'f':
                {
                    res->value.Float = (op2->value.Float < op3->value.Float) ? 1 : 0;

                    break;
                }
                default:
                {
                    printf("semantic error : This operation 'LT' can only be applied to int or floats");
                    exit(-1);
                }
                }

                break;
            }
            case '=':
            {
                switch (res->type)
                {
                case 'i':
                    res->value.Integer = (op2->value.Integer == op3->value.Integer) ? 1 : 0;
                    break;
                case 'f':
                    res->value.Float = (op2->value.Float == op3->value.Float) ? 1 : 0;
                    break;
                default:
                {
                    printf("semantic error : This operation 'EQ' can only be applied to int or floats");
                    exit(-1);
                }
                }
                break;
            }
            case '!':
            {
                switch (res->type)
                {
                case 'i':
                    res->value.Integer = (op2->value.Integer != op3->value.Integer) ? 1 : 0;
                    break;
                case 'f':
                    res->value.Float = (op2->value.Float != op3->value.Float) ? 1 : 0;
                    break;
                default:
                {
                    printf("semantic error : This operation 'NE' can only be applied to int or floats");
                    exit(-1);
                }
                }
                break;
            }
            case '>':
            {
                switch (res->type)
                {
                case 'i':
                    res->value.Integer = (op2->value.Integer > op3->value.Integer) ? 1 : 0;
                    break;
                case 'f':
                    res->value.Float = (op2->value.Float > op3->value.Float) ? 1 : 0;
                    break;
                default:
                {
                    printf("semantic error : This operation 'GT' can only be applied to int or floats");
                    exit(-1);
                }
                }
                break;
            }
            case 'l':
            {
                switch (res->type)
                {
                case 'i':
                    res->value.Integer = (op2->value.Integer <= op3->value.Integer) ? 1 : 0;
                    break;
                case 'f':
                    res->value.Float = (op2->value.Float <= op3->value.Float) ? 1 : 0;
                    break;
                default:
                {
                    printf("semantic error : This operation 'LE' can only be applied to int or floats");
                    exit(-1);
                }
                }
                break;
            }
            case 'g':
            {
                switch (res->type)
                {
                case 'i':
                    res->value.Integer = (op2->value.Integer >= op3->value.Integer) ? 1 : 0;
                    break;
                case 'f':
                    res->value.Float = (op2->value.Float >= op3->value.Float) ? 1 : 0;
                    break;
                default:
                {
                    printf("semantic error : This operation 'GE' can only be applied to int or floats");
                    exit(-1);
                }
                }
                break;
            }
            case 'J':
            {
                head = getIndex(op2->value.Integer - 1);
                break;
            }
            case 'F':
            {
                if ((op3->type == 'i' && op3->value.Integer == 0) || (op3->type == 'f' && op3->value.Float == 0))
                {
                    head = getIndex(op2->value.Integer - 1);
                }
                break;
            }
            case 'T':
            {
                if ((op3->type == 'i' && op3->value.Integer == 1) || (op3->type == 'f' && op3->value.Float == 1))
                {
                    head = getIndex(op2->value.Integer - 1);
                }
                break;
            }
            case 'P':
            {
                Symbol *Tol = res;
                head = head->next;
                while (head != NULL && head->op1->type != 'p')
                {
                    op1 = head->op1;
                    res = head->res == NULL ? NULL : head->res->ref;
                    if (op1->type != 'S')
                    {
                        printf("<%c>\n", head->op1->type);
                        op2 = head->op2 == NULL ? NULL : head->op2->ref;
                        op3 = head->op3 == NULL ? NULL : head->op3->ref;
                        EvaluationArth(op1->type, op2, op3, res);
                    }
                    else
                    {
                        if (res->type == 'i' && res->value.Integer > 0)
                        {
                            Tol->value.Integer++;
                        }
                        else if (res->type == 'f' && res->value.Float > 0)
                        {
                            Tol->value.Float++;
                        }
                    }
                    head = head->next;
                }

                break;
            }
            default:
                printf("Semantic error: Operation unknown");
                break;
            }
        }
        if (head)
            head = head->next;
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