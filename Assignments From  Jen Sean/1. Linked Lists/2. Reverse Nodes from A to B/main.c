#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode* head, int start, int end);

int main()
{
    ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E);

	while (scanf("%f", &f)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = f;
	}
	temp->next = NULL;

	head = reverseSegment(head,S,E);
	printList(head);
	deleteList(&head);
	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
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

ListNode *reverseSegment(ListNode* head, int start, int end)
{
// Write your code here
	// Count list first
	ListNode *cur;
	cur = head;
	int count = 0;
	while (cur != NULL) {
		count += 1;
		cur = cur->next;
	}

	ListNode *head_toReverse = NULL, *cur_toReverse;
	cur = head;
	if (start >= count-1 || start >= end || end > count-1 || start < 0 || end < 0) { // start and end is the same or start is larger than available index
		return(head);
	}
	else {
        count = 0; // use count as index now
		while (cur != NULL) {
            //printf("%d\n", count);
			if (count >= start && count <= end) {
				if (head_toReverse == NULL) { // first node
					head_toReverse = (ListNode*) malloc(sizeof(ListNode));
					cur_toReverse = head_toReverse;
				}
				else { // subsequent nodes
					cur_toReverse->next = (ListNode*) malloc(sizeof(ListNode));
					cur_toReverse = cur_toReverse->next;
				}
				cur_toReverse->item = cur->item;
			}
			else if (count > end) { // cursor is past the end alr
				break;
			}
			count++;
			cur = cur->next;
		}
		cur_toReverse->next = NULL;
	}

	// printList(head_toReverse);
	// Reverse linked list
	ListNode *nex, *pre;
	cur_toReverse = head_toReverse;
	nex = NULL;
	pre = NULL;

	while(cur_toReverse != NULL) {
		nex = cur_toReverse->next;
		cur_toReverse->next = pre;
		pre = cur_toReverse;
		cur_toReverse = nex;
	}
	head_toReverse = pre;

	// Replace the nodes with the reversed nodes
	count = 0;
	cur = head;
	cur_toReverse = head_toReverse;
	while (cur != NULL) {
		if (count >= start && count <= end) {
			cur->item = cur_toReverse->item;
			cur_toReverse = cur_toReverse->next;
		}
		cur = cur->next;
		if (count > end) {
			return(head);
		}
		count++;
	}
	return(head);
}
