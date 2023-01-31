
#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;


void printList(ListNode *cur);
ListNode * findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);

int removeNode(ListNode **ptrHead,int index);

int main()
{
    ListNode *head=NULL;
    int size =0;
    int item;
    int index;

    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        if(insertNode(&head,size, item)) size++;
    scanf("%*s");

    printList(head);

    while(1){
        printf("Enter the index of the node to be removed: ");
        scanf("%d",&index);

        if(removeNode(&head,index))
            size--;
        else{
            printf("The node cannot be removed.\n");
            break;
        }

        printf("After the removal operation,\n");
        printList(head);
    }

    printList(head);
    return 0;
}

void printList(ListNode *cur){
    printf("Current List: ");
    while (cur != NULL){
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

ListNode *findNode(ListNode* cur, int index)
{
   if (cur==NULL || index<0)
      return NULL;
   while(index>0){
      cur=cur->next;
      if (cur==NULL)
         return NULL;
      index--;
   }
   return cur;
}

int insertNode(ListNode **ptrHead, int index, int item){
    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = *ptrHead;
        *ptrHead = newNode;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode(*ptrHead, index-1)) != NULL){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        return 1;
    }
    return 0;
}

int removeNode(ListNode **ptrHead,int index)
{
/* Write your program code here */
    ListNode *currentNode, *previousNode;
    currentNode = *ptrHead;

    // Edge case: Checking if the list is empty
    if (currentNode == NULL)
        return -1; // if startNode is empty, this means that the LinkedList is empty, therefore return -1
    
    // Edge case: Checking if the index is 0 (i.e. first node is the node to be removed)
    if (index == 0)
    {
        *ptrHead = currentNode -> next; // if the first node is to be removed, set the ptrHead to point to the next node
        free(currentNode);
    }

    // Finding the node to be removed.
    for (int i =0; i <index; i ++)
    {

        // Iterates past the Linked List, with each iteration, node values are constantly swapped previous node -> current node. current node = current node -> next
        previousNode = currentNode;
        currentNode = currentNode -> next;

        // While iterating through the linked list, if an index is null, return -1
        if (currentNode == NULL)
        {
            return -1;
        }

    // Removing the node
    previousNode -> next = currentNode -> next; // Setting the previous pointer to point to the node infront of the current node (i.e. skipping past current Node)
    free(currentNode);
    return 0;
    }
}
