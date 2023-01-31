#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d",&K);

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


	reverseKNodes(&head, K);
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

void reverseKNodes(ListNode** head, int K){
//Write your code here

	ListNode *cur, *cur2;
	cur = *head;

	if (K <= 1) // size of K is 1 or less
		return;

	int size = 0;
	while (cur != NULL) {
		size++;
		cur = cur->next;
	}

	if (K >= size) // size of K is same size or bigger than linked list size
		return;

	int total_cycles = size / K;
	int num_cycles = 1, count = 1;
	int index = 0;

	ListNode *head_reverseTemp, *cur_reverseTemp, *next_reverseTemp, *pre_reverseTemp;

    cur = *head; // reset cursor

	while (num_cycles <= total_cycles) {
		// Create temp linked list;

		head_reverseTemp = NULL;

		while (count <= K) {
			if (head_reverseTemp == NULL) {
				head_reverseTemp = (ListNode*) malloc(sizeof(ListNode));
				cur_reverseTemp = head_reverseTemp;
			}
			else {
				cur_reverseTemp->next = (ListNode*) malloc(sizeof(ListNode));
				cur_reverseTemp = cur_reverseTemp->next;
			}

			cur_reverseTemp->item = cur->item;
			cur = cur->next;
			count++;
		}

		cur_reverseTemp->next = NULL;
		count = 1;

		// Reverse temp linked list
		cur_reverseTemp = head_reverseTemp;
		next_reverseTemp = NULL;
		pre_reverseTemp = NULL;

		while (cur_reverseTemp != NULL){
			next_reverseTemp = cur_reverseTemp->next;
			cur_reverseTemp->next = pre_reverseTemp;
			pre_reverseTemp = cur_reverseTemp;
			cur_reverseTemp = next_reverseTemp;
		}
		head_reverseTemp = pre_reverseTemp;

		cur2 = *head;
		while (index < (num_cycles-1) * K) {
            cur2 = cur2->next;
            index++;
		}

		index = 0;
        count = 1;
		while (count <= K) {
            cur2->item = head_reverseTemp->item;
            cur2 = cur2->next;
            head_reverseTemp = head_reverseTemp->next;
            count++;
		}
        count = 1;
        num_cycles++;
	}
}
