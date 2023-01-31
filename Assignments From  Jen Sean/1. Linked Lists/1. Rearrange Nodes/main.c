#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList* llptr);

LinkedList rearrange (LinkedList ll);

int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll=rearrange(ll);

	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}

LinkedList rearrange (LinkedList ll){
// Write your code here
	// ListNode *cur;

	if (ll.size == 1)
        return(ll);
	int count = 1;
	LinkedList ll1, ll2;
	ll1.head = NULL;
    ll1.size = 0;
	ll2.head = NULL;
    ll2.size = 0;
	ListNode *temp1, *temp2, *cur;

	cur = ll.head;

	// REARRANGE 1
	// EVEN: First Half Nodes and Second Half Nodes
	// ODD: First Half Nodes and Second Half + 1 Nodes

	while (count <= ll.size){
		if (count <= ll.size/2) { // first half
			if (ll1.head == NULL){ // ll1 first node
				ll1.head = (ListNode*) malloc(sizeof(ListNode));
				temp1 = ll1.head;
			}
			else { // ll1 subsequent nodes
				temp1->next = (ListNode*) malloc(sizeof(ListNode));
				temp1 = temp1->next;
			}
			temp1->item = cur->item;
			ll1.size++;
		}
		else { // second half
			if (ll2.head == NULL){ // ll2 first node
				ll2.head = (ListNode*) malloc(sizeof(ListNode));
				temp2 = ll2.head;
			}
			else { // ll1 subsequent nodes
				temp2->next = (ListNode*) malloc(sizeof(ListNode));
				temp2 = temp2->next;
			}
			temp2->item = cur->item;
			ll2.size++;
		}
		cur = cur->next;
		count++;
	}
	temp1->next = NULL;
	temp2->next = NULL;

	// REARRANGE 2
	// R1->L1->R2->L2->R3...
	count = 1;
	LinkedList ll3;
	ll3.head = NULL;
    ll3.size = 0;
	ListNode *temp3;
	temp1 = ll1.head;
	temp2 = ll2.head;
	int size = ll.size;

	while (count <= size) {
		if(ll3.head == NULL) { // first node
			ll3.head = (ListNode*) malloc(sizeof(ListNode));
			temp3 = ll3.head;
		}
		else {
			temp3->next = (ListNode*) malloc(sizeof(ListNode));
			temp3 = temp3->next;
		}

		if (count % 2 == 1) {
			temp3->item = temp2->item;
			temp2 = temp2->next;
		}
		else {
			temp3->item = temp1->item;
			temp1 = temp1->next;
		}
		ll3.size++;
		count++;
	}
	temp3->next = NULL;

	// ARRANGE 3
	// SAME AS ARRANGE 1
	deleteList(&ll1); // I want to reuse ll1 and ll2 pointers
	deleteList(&ll2);

	count = 1;
	ll1.head = NULL;
    ll1.size = 0;
	ll2.head = NULL;
    ll2.size = 0;
	cur = ll3.head;

	while (count <= ll3.size){
		if (count <= ll3.size/2) { // first half
			if (ll1.head == NULL){ // ll1 first node
				ll1.head = (ListNode*) malloc(sizeof(ListNode));
				temp1 = ll1.head;
			}
			else { // ll1 subsequent nodes
				temp1->next = (ListNode*) malloc(sizeof(ListNode));
				temp1 = temp1->next;
			}
			temp1->item = cur->item;
			ll1.size++;
		}
		else { // second half
			if (ll2.head == NULL){ // ll2 first node
				ll2.head = (ListNode*) malloc(sizeof(ListNode));
				temp2 = ll2.head;
			}
			else { // ll1 subsequent nodes
				temp2->next = (ListNode*) malloc(sizeof(ListNode));
				temp2 = temp2->next;
			}
			temp2->item = cur->item;
			ll2.size++;
		}
		cur = cur->next;
		count++;
	}
	temp1->next = NULL;
	temp2->next = NULL;

	// ARRANGE 4
	// SAME AS ARRANGE 2
	deleteList(&ll3);

	count = 1;
	ll3.head = NULL;
    ll3.size = 0;
	temp1 = ll1.head;
	temp2 = ll2.head;
	temp3 = NULL;

	while (count <= size) {
		if(ll3.head == NULL) { // first node
			ll3.head = (ListNode*) malloc(sizeof(ListNode));
			temp3 = ll3.head;
		}
		else {
			temp3->next = (ListNode*) malloc(sizeof(ListNode));
			temp3 = temp3->next;
		}
        if (count == size){ // last node last position
            if (temp1 == NULL)
                temp3->item = temp2->item;
            else
                temp3-> item = temp1->item;
        }
		else if (count % 2 == 0) {
			temp3->item = temp2->item;
			temp2 = temp2->next;
		}
		else {
			temp3->item = temp1->item;
			temp1 = temp1->next;
		}
		ll3.size++;
		count++;
	}
	temp3->next = NULL;

	return(ll3);

}
