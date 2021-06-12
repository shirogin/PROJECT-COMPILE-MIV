#include <stdio.h>
#include <string.h>
#include "TS.h"

int main()
{
    Symbol *head = NULL;
    TV tv;
    tv.Integer = 10;

    push(&head, "mouha", 'U');
    push(&head, "youcef", 'U');
    push(&head, "abdou", 'U');

    printList(head);

    declare(head, "youcef", 'i', tv);
    assignVal(head, "youcef", 'i', tv);
    printList(head);
    return 0;
}