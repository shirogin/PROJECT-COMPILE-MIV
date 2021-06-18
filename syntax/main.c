#include "quad.h"

int main()
{
    Symbol *head = NULL;
    TV tv;
    tv.Integer = 10;

    push(&head, "mouha", 'U');
    push(&head, "youcef", 'U');
    push(&head, "abdou1", 'U');
    push(&head, "abdou2", 'U');
    push(&head, "abdou3", 'U');
    push(&head, "abdou4", 'U');
    push(&head, "abdou5", 'U');

    printList(head);

    Quad *quad = createQuad();
    pushQuad(&quad, head, head->next, head->next->next, head->next->next->next);
    pushQuad(&quad, head->next->next->next, head->next->next, head->next, head);

    printQuadList(quad);
    return 0;
}