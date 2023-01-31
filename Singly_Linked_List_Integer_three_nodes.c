#include <stdio.h>
#include <stdlib.h>

typedef struct mystruct{
    int number;
    struct node *next;
} ListNode;

int main(){
    ListNode *head, *firstnode, *secondnode, *thirdnode;

    firstnode = malloc(sizeof(ListNode));
    secondnode = malloc(sizeof(ListNode));
    thirdnode = malloc(sizeof(ListNode));

    head = firstnode;
    firstnode -> next = secondnode;
    secondnode -> next = thirdnode;
    thirdnode -> next = NULL;
}