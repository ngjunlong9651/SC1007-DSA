#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];
    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);
//    printf("Before remove nodes\n");
    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("END");
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}


void in2PreLL(char* infix, LinkedList *inExpLL)
{
  //Write your code here
    // 1. Reverse the infix expression into a linked list.

    LinkedList r_infix;
    r_infix.head = NULL;
    r_infix.size = 0;
    char number[SIZE];
    int i = 0;
    int length = strlen(infix);
    // 1. Reverse array into linked list
    while (*infix != NULL) {
        if (isdigit(*infix) != 0) { // is a number
            number[i] = *infix;
            i++;
        }
        else { // not a number
            number[i] = '\0';
            if (number[0] != '\0') {
                insertNode(&r_infix, atoi(number), OPERAND);
            }
            if (*infix == '(')
                insertNode(&r_infix, ')', OPT);
            else if (*infix == ')')
                insertNode(&r_infix, '(', OPT);
            else
                insertNode(&r_infix, *infix, OPT);
            i = 0;
        }
        if (*(infix+1) == '\0' && isdigit(*infix) != 0){ // last number
            number[i] = '\0';
            insertNode(&r_infix, atoi(number), OPERAND);
        }
        infix++;
    }

    // 2. Do "almost" postfix conversion

    ListNode *cur;
    cur = r_infix.head;

    Stack stack;
    stack.head = NULL;
    stack.size = 0;

    char prev;

    while (cur != NULL) {
        if (cur->type == OPERAND) { // element is an operand
            insertNode(inExpLL, cur->item, OPERAND);
        }

        else if (cur->type == OPT && cur->item == '(') {
            push(&stack, cur->item);
        }

        else if (cur->type == OPT && cur->item == ')') {
            while (peek(stack) != '(') {
                insertNode(inExpLL, peek(stack), OPT);
                pop(&stack);
            }
            pop(&stack); // pop the '('
        }

        else if (cur->type == OPT) {

            if (isEmptyStack(stack)) { // stack is empty
                push(&stack, cur->item);
            }

            else { // stack is not empty
                prev = peek(stack);

                if (prev == '(') // top of the stack is a '('
                    push(&stack, cur->item);

                else {
                    switch (cur->item) {

                    case '+':
                        if (prev == '+' || prev == '-') {
                            push(&stack, cur->item);
                        }
                        else if (prev == '*' || prev == '/') {
                            while (isEmptyStack(stack) == 0 && peek(stack) != '(' && (peek(stack) != '+' && peek(stack) != '-')) {
                                insertNode(inExpLL, peek(stack), OPT);
                                pop(&stack);
                            }
                            push(&stack, cur->item);
                        }
                        break;

                    case '-':
                        if (prev == '+' || prev == '-') {
                            push(&stack, cur->item);
                        }
                        else if (prev == '*' || prev == '/') {
                            while (isEmptyStack(stack) == 0 && peek(stack) != '(' && (peek(stack) != '+' && peek(stack) != '-')) {
                                insertNode(inExpLL, peek(stack), OPT);
                                pop(&stack);
                            }
                            push(&stack, cur->item);
                        }
                        break;

                    case '*':
                        push(&stack, cur->item);
                        break;

                    case '/':
                        push(&stack, cur->item);
                        break;
                    }
                }
            }
        }
        cur = cur->next;
    }
    while (isEmptyStack(stack) == 0) {
        insertNode(inExpLL, peek(stack), OPT);
        pop(&stack);
    }
}
