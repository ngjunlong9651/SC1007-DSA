#include <stdio.h>
#include <stdlib.h>

typedef struct mystruct {
    int items;
    struct node *next;
}ListNode;

int main(){
    ListNode *temp, *head = NULL;
    int i = 0;
    scanf("%d", &i);

    while(i!=-1){
        if (head == NULL){
            head = malloc(sizeof(ListNode)); // what happens if empty linked list
            temp = head;
        }
        else{
            temp -> next = malloc(sizeof(ListNode));
            temp = temp -> next;
        }
    // Create what happens for user to continuously enter integers as long as they are not -1
    temp -> items =i; // What does this do?
    scanf("%d", &i); 
    }
    // What happens when the user enters - 1
    temp -> next = NULL;
}
    