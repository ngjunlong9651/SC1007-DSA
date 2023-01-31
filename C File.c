#include <stdio.h>
#include <stdlib.h>

typedef struct mystruct {
    int item;
    struct node *next;

} ListNode;

int main() {
    ListNode *head = NULL, *temp;
    int i =0;
    while (i != -1)
    {
        if (head == NULL) 
        {
            head = malloc(sizeof(ListNode));
            temp = head;
        }
        else
        {
            temp -> next = malloc(sizeof(ListNode));
            temp = temp -> next;
        }
        temp -> item = i;
        scanf("%d", &i);
    }
    temp -> next = NULL;
    
}