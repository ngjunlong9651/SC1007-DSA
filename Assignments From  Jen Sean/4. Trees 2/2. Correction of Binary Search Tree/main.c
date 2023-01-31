#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queueNode{
	BTNode *data;
	struct _queueNode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

typedef struct _stackNode{
	BTNode *data;
	struct _stackNode *next;
}StackNode;

typedef struct _stack
{
    int size;
	StackNode *top;
}Stack;

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * data);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode* createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

//Prototypes of Interface functions for Stack structure
void push(Stack *sPtr, BTNode *data);
int pop(Stack *sPtr);
BTNode* peek(Stack s);
int isEmptyStack(Stack s);

void BSTCorrection(BTNode* root);

int main()
{
    BTNode* root = NULL;
    BTNode* temp = NULL;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int item;
    int flag=1;
    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
    {
        if(root==NULL)
        {
            if(item!=-1){
                root =createNode(item);
                enqueue(&q,root);
            }
        }
        else{
            while(!isEmptyQueue(q)){
                temp = getFront(q);
                if(flag){
                    if(item != -1){
                        temp->left = createNode(item);
                        enqueue(&q,temp->left);
                    }
                    flag = 0;
                    break;
                }
                else if(temp->right==NULL){
                    if(item!=-1){
                        temp->right = createNode(item);
                        enqueue(&q,temp->right);
                    }
                    dequeue(&q);
                    flag=1;
                    break;
                }
                else  dequeue(&q);
            }
        }
    }
    scanf("%*s");

    printf("The input binary search tree:\n");
    printBTNode(root,0,0);
    printf("\n");
    printf("The corrected binary search tree:\n");
    BSTCorrection(root);

    printBTNode(root,0,0);

    deleteTree(&root);

    return 0;
}
BTNode* createNode(int item)
{
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
	node->item = item;
	node->left = node->right = NULL;
	return node;
}

void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}
void enqueue(Queue *qPtr, BTNode *data){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->data;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}

void push(Stack *sPtr, BTNode *data){
    StackNode *newNode;
    newNode= (StackNode *)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = sPtr->top;
    sPtr->top = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr==NULL || sPtr->top==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->top;
       sPtr->top = sPtr->top->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode* peek(Stack s){
    return s.top->data;
}

int isEmptyStack(Stack s){
     if(s.size==0) return 1;
     else return 0;
}

void BSTCorrection(BTNode* root)
{
    // Write your code here
    // In Order Traversal - start
    Stack s1;
    s1.top = NULL;
    s1.size = 0;

    Queue q1;
    q1.head = NULL;
    q1.tail = NULL;
    q1.size = 0;

    BTNode *cursor;
    cursor = root;

    while (1) {
        if (cursor != NULL) { // push all the left nodes to stack
            push(&s1, cursor);
            cursor = cursor->left;
        }
        else {
            if (isEmptyStack(s1) == 1) {
                break;
            }
            cursor = peek(s1);
            pop(&s1);
                // do the operations here
//            printf("%d ", cursor->item);
            enqueue(&q1, cursor); // enqueue nodes to queue in in-order
            // do the operations here - end
            cursor = cursor->right;

        }
    }
//    printf("\n");
    // In Order Traversal - end



    QueueNode *curQ;
    curQ = q1.head;
    while (curQ != NULL) {
        push(&s1, curQ->data);
        curQ = curQ->next;
    }
//    printf("q1 size: %d\n", q1.size);
//    printf("s1 size: %d\n", s1.size);

    // Find first wrong value from the left (queue)
    int a, b;

    QueueNode *fromleft;
    fromleft = q1.head;
    while (fromleft != NULL) {
        if (fromleft->data->item > fromleft->next->data->item) {
            a = fromleft->data->item;
            break;
        }
        fromleft = fromleft->next;
    }
//    printf("a: %d\n", a);

    StackNode *fromright;
    fromright = s1.top;
    while (fromright != NULL) {
        if (fromright->data->item < fromright->next->data->item) {
            b = fromright->data->item;
            break;
        }
        fromright = fromright->next;
    }
//    printf("b: %d\n", b);


    while (isEmptyQueue(q1) == 0) {
        if (getFront(q1)->item == a)
            getFront(q1)->item = b;
        else if (getFront(q1)->item == b)
            getFront(q1)->item = a;
        dequeue(&q1);
    }

    // Find first wrong value from the right (stack)

//    printf("q1 size: %d\n", q1.size);

//    Stack stack_sort;
//    stack_sort.top = NULL;
//    stack_sort.size = 0;
//
//    Stack stack_sort_helper;
//    stack_sort_helper.top = NULL;
//    stack_sort_helper.size = 0;
//
//    while (isEmptyQueue(q1) == 0) { // while input queue is not empty
//        if (isEmptyStack(stack_sort) == 1) { // sorting stack is empty just push
//            push(&stack_sort, getFront(q1));
//            dequeue(&q1);
//        }
//        else if (getFront(q1)->item > peek(stack_sort)->item) {
//            push(&stack_sort, getFront(q1));
//            dequeue(&q1);
//        }
//        else {
//            while (isEmptyStack(stack_sort) == 0 && peek(stack_sort)->item > getFront(q1)->item) {
//                push(&stack_sort_helper, peek(stack_sort));
//                pop(&stack_sort);
//            }
//            push(&stack_sort, getFront(q1));
//            dequeue(&q1);
//            while (isEmptyStack(stack_sort_helper) == 0) {
//                push(&stack_sort, peek(stack_sort_helper));
//                pop(&stack_sort_helper);
//            }
//        }
//    }
//
////    printf("stack_sort size: %d\n", stack_sort.size);
//
//    Stack sorted_stack;
//    sorted_stack.top = NULL;
//    sorted_stack.size = 0;
//
//    while(isEmptyStack(stack_sort) == 0) {
//        push(&sorted_stack, peek(stack_sort));
//        pop(&stack_sort);
//    }
//
//
////    while(isEmptyStack(sorted_stack) == 0) {
////        printf("%d ", peek(sorted_stack)->item );
////        pop(&sorted_stack);
////    }
////    printf("\n");
//
//    Stack s2;
//    s2.top = NULL;
//    s2.size = 0;
//
//    BTNode *cursor1;
//    cursor1 = root;
//
//    while (isEmptyStack(s2) == 0 || cursor1 != NULL) {
//        if (cursor1 != NULL) {
//            push(&s2, cursor1);
//            cursor1 = cursor1->left;
//        }
//        else {
//            cursor1 = peek(s2);
//            pop(&s2);
//            //
////            printf("%d ", cursor1->item);
//            printf("%d ", peek(sorted_stack)->item);
////            cursor1->item = peek(sorted_stack)->item;
//            pop(&sorted_stack);
//            //
//            cursor1 = cursor1->right;
//        }
//    }
//
//    printf("\n");
    return root;

}
