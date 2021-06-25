#include "TS.h"
char *Line;
Symbol *TS = NULL;
void printTS()
{
    printList(TS);
}
void freeTS()
{
    freeList(&TS);
}
struct position
{
    int line, column;
} position = {1, 1};

void LineHandle(char *Entity)
{
    if (Line == NULL)
    {
        Line = (char *)calloc(1, 500 * sizeof(char));
        strcpy(Line, Entity);
    }
    else
        strcat(Line, Entity);
    printf("%s", Entity);
}
void LexicalTreatment(char *Entity)
{
    position.column = position.column + strlen(Entity);
}
void Insert(char *Entity, char type)
{
    LineHandle(Entity);
    LexicalTreatment(Entity);
    if (getSymbol(TS, Entity) == NULL)
        push(&TS, Entity, type);
}
int printLexicalError(char *entity, char *msg)
{
    sprintf(errorMsg, "%s: Line %d column %d", msg, position.line, position.column);
    printf("\n\033[1;35mLexical Error: %s : %s \n\033[0m", errorMsg, yytext);
}