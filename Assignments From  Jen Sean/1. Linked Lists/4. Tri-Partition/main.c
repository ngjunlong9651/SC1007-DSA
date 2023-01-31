#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode** head, int pivot);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	triPartition(&head, pivot);
	printList(head);
	deleteList(&head);

	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

void triPartition(ListNode** head, int pivot){
// Write your code here
	ListNode *new_head = NULL, *temp, *cur;
    cur = *head;

    while (cur != NULL) {
        if (cur->item < pivot) {
            if (new_head == NULL) {
                new_head = (ListNode*) malloc(sizeof(ListNode));
                temp = new_head;
            }
            else {
                temp->next = (ListNode*) malloc(sizeof(ListNode));
                temp = temp->next;
            }
            temp->item = cur->item;
        }
        cur = cur->next;
    }
    temp->next = NULL;
    //printList(new_head);

    cur = *head;

    while (cur != NULL) {
        if (cur->item == pivot) {
            if (new_head == NULL) {
                new_head = (ListNode*) malloc(sizeof(ListNode));
                temp = new_head;
            }
            else {
                temp->next = (ListNode*) malloc(sizeof(ListNode));
                temp = temp->next;
            }
            temp->item = cur->item;
        }
        cur = cur->next;
    }
    temp->next = NULL;
    //printList(new_head);

    cur = *head;
    while (cur != NULL) {
        if (cur->item > pivot) {
            if (new_head == NULL) {
                new_head = (ListNode*) malloc(sizeof(ListNode));
                temp = new_head;
            }
            else {
                temp->next = (ListNode*) malloc(sizeof(ListNode));
                temp = temp->next;
            }
            temp->item = cur->item;
        }
        cur = cur->next;
    }
    temp->next = NULL;
    //printList(new_head);
    deleteList(head);
    *head = new_head;
}
