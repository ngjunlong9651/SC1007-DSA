#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node *next;
} ListNode;

int main(){
    ListNode *head, *firstnode, *secondnode;
    firstnode = malloc(sizeof(ListNode));
    secondnode = malloc(sizeof(ListNode));

    head = firstnode;
    firstnode -> next = secondnode;
    secondnode -> next = NULL;

}

