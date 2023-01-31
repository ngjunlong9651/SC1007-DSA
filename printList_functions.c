#include <stdio.h>
#include <stdlib.h>

void printList(ListNode *head)

typedef struct mystruct{
    int items;
    struct mystruct *next;	
} ListNode;

void printList(ListNode *head){
    if (head == NULL){
        return;
    }
    while (head != NULL){
        printf("%d", head -> items );
        head = head ->next;
    }
    printf("\n");
}