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

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * data);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode* createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

BTNode* findLargestBST (BTNode* root);

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
    printf("The input binary tree:\n");
    printBTNode(root,0,0);
    printf("\n");
    BTNode* BSTnode = findLargestBST (root);
    printf("The largest binary search subtree:\n");
    if(BSTnode)
        printBTNode(BSTnode,0,0);
    else
        printf("No BST\n");
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


BTNode* findLargestBST (BTNode* root)
{
    // Write your code here

    if (root->left == NULL && root->right == NULL){
        return root;
    }

    Queue s1, q1, s2, q2; // s1 and s2 will act as "stack" and q1 and q2 will be the helper queues
    // s1 and q1 will be the "stack" for the outer loop and s2, q2 will be the stack for the inner loop
    s1.head = NULL;
    s1.tail = NULL;
    s1.size = 0;
    q1.head = NULL;
    q1.tail = NULL;
    q1.size = 0;

    BTNode *cursor1, *cursor2, *rootBiSubTree;
    int count, largest = 0, BST;
    enqueue(&s1, root); // enqueue root into the "stack"
//    printf("s1 isEmpty: %d\n", isEmptyQueue(s1));

    while (isEmptyQueue(s1) == 0) {// while "stack" is not empty
        cursor1 = getFront(s1);
//        printf("%d ", getFront(s1)->item);
        dequeue(&s1); // remove first item in the stack

        count = 0;
        // NESTED LOOP START
        s2.head = NULL;
        s2.tail = NULL;
        s2.size = 0;
        q2.head = NULL;
        q2.tail = NULL;
        q2.size = 0;

        BST = 1;

        enqueue(&s2, cursor1);
        while (isEmptyQueue(s2) == 0) { // while "stack2" is not empty
            cursor2 = getFront(s2);
//            printf("%d ", cursor2->item);
            count++;
            dequeue(&s2);

            if (cursor2->right != NULL) {
                if (cursor2->right->item < cursor2->item || (cursor2->right->item > cursor1->item && cursor2->item < cursor1->item)) { // item on right does not fulfill BST requirement
//                    printf("not bst ");
                    BST = 0;
                    break;
                }
                if (isEmptyQueue(s2) == 0) { // s1 is not empty
                    while (isEmptyQueue(s2) == 0) {
                        enqueue(&q2, getFront(s2));
                        dequeue(&s2);
                    }
                    enqueue(&s2, cursor2->right); // enqueue right node to the "stack"
                    while (isEmptyQueue(q2) == 0) {
                        enqueue(&s2, getFront(q2));
                        dequeue(&q2);
                    }
                }
                else { // s1 is empty, just add to "stack"
                    enqueue(&s2, cursor2->right);
                }

            }

            if (cursor2->left != NULL) {
                if (cursor2->left->item > cursor2->item || (cursor2->left->item < cursor1->item && cursor2->item > cursor1->item)) { // item on left does not fulfill BST requirement
//                    printf("not bst ");
                    BST = 0;
                    break;
                }
                if (isEmptyQueue(s2) == 0) { // s1 is not empty
                    while (isEmptyQueue(s2) == 0) {
                        enqueue(&q2, getFront(s2));
                        dequeue(&s2);
                    }
                    enqueue(&s2, cursor2->left); // enqueue left node to the "stack"
                    while (isEmptyQueue(q2) == 0) {
                        enqueue(&s2, getFront(q2));
                        dequeue(&q2);
                    }
                }
                else { // s1 is empty, just add to "stack"
                    enqueue(&s2, cursor2->left);
                }

            }
        }
        if (BST == 1) {
            if (count > largest) {
                largest = count;
                rootBiSubTree = cursor1;
            }
        }
        // NESTED LOOP END

//        printf("\n");

//        if (rootBiSubTree == root) { // largest binary search subtree is the entire tree
//            return rootBiSubTree;
//        }

        // push item to "stack" - START
        if (cursor1->right != NULL) { // if the current cursor -> right has a child
            if (isEmptyQueue(s1) == 0) { // s1 is not empty
                while (isEmptyQueue(s1) == 0) {
                    enqueue(&q1, getFront(s1));
                    dequeue(&s1);
                }
                enqueue(&s1, cursor1->right); // enqueue right node to the "stack"
                while (isEmptyQueue(q1) == 0) {
                    enqueue(&s1, getFront(q1));
                    dequeue(&q1);
                }
            }
            else { // s1 is empty, just add to "stack"
                enqueue(&s1, cursor1->right);
            }
            // push item to "stack" - END
        }
        // push item to "stack" - START
        if (cursor1->left != NULL) { // if the current cursor -> left has a child
            if (isEmptyQueue(s1) == 0) { // s1 is not empty
                while (isEmptyQueue(s1) == 0) {
                    enqueue(&q1, getFront(s1));
                    dequeue(&s1);
                }
                enqueue(&s1, cursor1->left); // enqueue left node to the "stack"
                while (isEmptyQueue(q1) == 0) {
                    enqueue(&s1, getFront(q1));
                    dequeue(&q1);
                }
            }
            else { // s1 is empty, just add to "stack"
                enqueue(&s1, cursor1->left);
            }
        }
        // push item to "stack" - END
    }

    if (largest == 1 && rootBiSubTree != root) {
        return NULL;
    }
    return rootBiSubTree;

}
