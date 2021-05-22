#include "TS.h"
char *Line;
struct position
{
    int line, column;
} position = {1, 1};

void LineHandle(char *Entity)
{
    if (Line == NULL)
    {
        Line = (char *)malloc(500 * sizeof(char));
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
void Insert(char *Entity, short type)
{
    LineHandle(Entity);
    LexicalTreatment(Entity);
}