#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode{
    BTNode* node;
    struct _queuenode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space,int left);
//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * node);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2);

int main()
{
    BTNode* root = (BTNode*) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode* node;
    enqueue(&q,root);

    int nodeV;
    char opL, opR;

    while(!isEmptyQueue(q)){
            scanf("%d %c %c",&nodeV,&opL,&opR);
            node = getFront(q);dequeue(&q);
            node->nodeV = nodeV;

            if(opL != '@'){
                node->left = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->left);
            }
            else node->left =NULL;
            if(opR != '@'){
                node->right = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->right);
            }
            else
                node->right = NULL;
    }

    int v1,v2;
    scanf("%d %d",&v1,&v2);
    int cost = twoNodesCost(root,v1,v2);

    printBTNode(root,0,0);

    printf("Distance is %d\n",cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
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
    return q.head->node;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
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

          printf("%d\n", root->nodeV);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2)
{

    // Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
    // Write your code here

    // 1. Use a stack (2 queues) to store path to nodeV1)

    if (nodeV1 == nodeV2) // start and end on the same node
        return nodeV1;

    Queue v1Path, v1Path_helper;
    v1Path.head = NULL;
    v1Path.tail = NULL;
    v1Path.size = 0;
    v1Path_helper.head = NULL;
    v1Path_helper.tail = NULL;
    v1Path_helper.size = 0;

    BTNode *cursorV1;
    enqueue(&v1Path, node); // enqueue the root into stack
    cursorV1 = node;

    while (isEmptyQueue(v1Path) != 1) { // if empty stack end the loop (all nodes visited)

//        printf("%d\n", cursor->nodeV);
        if (cursorV1->nodeV == nodeV1) { // node has been found, path is in "stack" v1Path
            break;
        }

        if (cursorV1->left != NULL && cursorV1->left->nodeV >= 0) {
            cursorV1 = cursorV1->left;

            if (isEmptyQueue(v1Path) == 0) { // add node to the stack - start
                while (isEmptyQueue(v1Path) == 0) {
                    enqueue(&v1Path_helper, getFront(v1Path));
                    dequeue(&v1Path);
                }
                enqueue(&v1Path, cursorV1); // enqueue node into the stack
                while (isEmptyQueue(v1Path_helper) == 0) {
                    enqueue(&v1Path, getFront(v1Path_helper));
                    dequeue(&v1Path_helper);
                }
            } // add node to the stack - end
        }
        else if (cursorV1->right != NULL && cursorV1->right->nodeV >= 0) {
            cursorV1 = cursorV1->right;
            if (isEmptyQueue(v1Path) == 0) { // add node to the stack - start
                while (isEmptyQueue(v1Path) == 0) {
                    enqueue(&v1Path_helper, getFront(v1Path));
                    dequeue(&v1Path);
                }
                enqueue(&v1Path, cursorV1); // enqueue node into the stack
                while (isEmptyQueue(v1Path_helper) == 0) {
                    enqueue(&v1Path, getFront(v1Path_helper));
                    dequeue(&v1Path_helper);
                }
            } // add node to the stack - end
        }
        else { // both left and right are null/negative, time to go back
            cursorV1->nodeV = -(cursorV1->nodeV);
//            printf("Removing: %d\n", getFront(v1Path)->nodeV);
            dequeue(&v1Path); // dequeue the current node from "stack"
            cursorV1 = getFront(v1Path);
        }
    }

    // Print Path to nodeV1
//    QueueNode *curV1;
//    curV1 = v1Path.head;
//
//    printf("Path to nodeV1: ");
//    while (curV1 != NULL) {
//        printf("%d ", curV1->node->nodeV);
//        curV1 = curV1->next;
//    }
//    printf("\n");

    // Reset node values back to positive
    Queue clear, clear_helper;
    BTNode *tempClear;
    clear.head = NULL;
    clear.tail = NULL;
    clear.size = 0;
    clear_helper.head = NULL;
    clear_helper.tail = NULL;
    clear_helper.size = 0;

    enqueue(&clear, node);
//    tempClear = node;

    while (isEmptyQueue(clear) == 0) {
//        printf("root: %d\n", (getFront(clear))->nodeV);
        tempClear = getFront(clear);
        // operation here:
        tempClear->nodeV = abs(tempClear->nodeV);
//        printf("set positive: %d\n", tempClear->nodeV);
        dequeue(&clear);

        if (tempClear->right != NULL) {
            if (isEmptyQueue(clear) == 0) { // add node to the stack - start
                while (isEmptyQueue(clear) == 0) {
                    enqueue(&clear_helper, getFront(clear));
                    dequeue(&clear);
                }
                enqueue(&clear, tempClear->right); // enqueue node into the stack
                while (isEmptyQueue(clear_helper) == 0) {
                    enqueue(&clear, getFront(clear_helper));
                    dequeue(&clear_helper);
                }
            } // add node to the stack - end
            else {
                enqueue(&clear, tempClear->right);
            }
        }
        if (tempClear->left != NULL) {
            if (isEmptyQueue(clear) == 0) { // add node to the stack - start
                while (isEmptyQueue(clear) == 0) {
                    enqueue(&clear_helper, getFront(clear));
                    dequeue(&clear);
                }
                enqueue(&clear, tempClear->left); // enqueue node into the stack
                while (isEmptyQueue(clear_helper) == 0) {
                    enqueue(&clear, getFront(clear_helper));
                    dequeue(&clear_helper);
                }
            } // add node to the stack - end
            else {
                enqueue(&clear, tempClear->left);
            }
        }
//        printf("clear queue empty?: %d\n", isEmptyQueue(clear));
    }

    // 3. Use a stack (2 queues) to store path to nodeV2)
    Queue v2Path, v2Path_helper;
    v2Path.head = NULL;
    v2Path.tail = NULL;
    v2Path.size = 0;
    v2Path_helper.head = NULL;
    v2Path_helper.tail = NULL;
    v2Path_helper.size = 0;

    BTNode *cursorV2;
    enqueue(&v2Path, node); // enqueue the root into stack
    cursorV2 = node;

    while (isEmptyQueue(v2Path) != 1) { // if empty stack end the loop (all nodes visited)

//        printf("%d\n", cursor->nodeV);
        if (cursorV2->nodeV == nodeV2) { // node has been found, path is in "stack" v2Path
            break;
        }

        if (cursorV2->left != NULL && cursorV2->left->nodeV >= 0) {
            cursorV2 = cursorV2->left;

            if (isEmptyQueue(v2Path) == 0) { // add node to the stack - start
                while (isEmptyQueue(v2Path) == 0) {
                    enqueue(&v2Path_helper, getFront(v2Path));
                    dequeue(&v2Path);
                }
                enqueue(&v2Path, cursorV2); // enqueue node into the stack
                while (isEmptyQueue(v2Path_helper) == 0) {
                    enqueue(&v2Path, getFront(v2Path_helper));
                    dequeue(&v2Path_helper);
                }
            } // add node to the stack - end
        }
        else if (cursorV2->right != NULL && cursorV2->right->nodeV >= 0) {
            cursorV2 = cursorV2->right;
            if (isEmptyQueue(v2Path) == 0) { // add node to the stack - start
                while (isEmptyQueue(v2Path) == 0) {
                    enqueue(&v2Path_helper, getFront(v2Path));
                    dequeue(&v2Path);
                }
                enqueue(&v2Path, cursorV2); // enqueue node into the stack
                while (isEmptyQueue(v2Path_helper) == 0) {
                    enqueue(&v2Path, getFront(v2Path_helper));
                    dequeue(&v2Path_helper);
                }
            } // add node to the stack - end
        }
        else { // both left and right are null/negative, time to go back
            cursorV2->nodeV = -(cursorV2->nodeV);
//            printf("Removing: %d\n", getFront(v2Path)->nodeV);
            dequeue(&v2Path); // dequeue the current node from "stack"
            cursorV2 = getFront(v2Path);
        }
    }

    // Print Path to nodeV2
//    QueueNode *curV2;
//    curV2 = v2Path.head;
//
//    printf("Path to nodeV2: ");
//    while (curV2 != NULL) {
//        printf("%d ", curV2->node->nodeV);
//        curV2 = curV2->next;
//    }
//    printf("\n");

    // Reset node values back to positive
    clear.head = NULL;
    clear.tail = NULL;
    clear.size = 0;
    clear_helper.head = NULL;
    clear_helper.tail = NULL;
    clear_helper.size = 0;

    enqueue(&clear, node);
//    tempClear = node;

    while (isEmptyQueue(clear) == 0) {
//        printf("root: %d\n", (getFront(clear))->nodeV);
        tempClear = getFront(clear);
        // operation here:
        tempClear->nodeV = abs(tempClear->nodeV);
//        printf("set positive: %d\n", tempClear->nodeV);
        dequeue(&clear);

        if (tempClear->right != NULL) {
            if (isEmptyQueue(clear) == 0) { // add node to the stack - start
                while (isEmptyQueue(clear) == 0) {
                    enqueue(&clear_helper, getFront(clear));
                    dequeue(&clear);
                }
                enqueue(&clear, tempClear->right); // enqueue node into the stack
                while (isEmptyQueue(clear_helper) == 0) {
                    enqueue(&clear, getFront(clear_helper));
                    dequeue(&clear_helper);
                }
            } // add node to the stack - end
            else {
                enqueue(&clear, tempClear->right);
            }
        }
        if (tempClear->left != NULL) {
            if (isEmptyQueue(clear) == 0) { // add node to the stack - start
                while (isEmptyQueue(clear) == 0) {
                    enqueue(&clear_helper, getFront(clear));
                    dequeue(&clear);
                }
                enqueue(&clear, tempClear->left); // enqueue node into the stack
                while (isEmptyQueue(clear_helper) == 0) {
                    enqueue(&clear, getFront(clear_helper));
                    dequeue(&clear_helper);
                }
            } // add node to the stack - end
            else {
                enqueue(&clear, tempClear->left);
            }
        }
//        printf("clear queue empty?: %d\n", isEmptyQueue(clear));
    }

    // Find Lowest Common Ancestor
    QueueNode *curV1;
    QueueNode *curV2;
    curV1 = v1Path.head;
    int LCA, sum = 0;

    while (curV1 != NULL) {
        curV2 = v2Path.head;
        while (curV2 != NULL) {
            if (curV1->node->nodeV == curV2->node->nodeV) {
//                printf("LCA: %d\n", curV1->node->nodeV);
                LCA = curV1->node->nodeV;
                curV1 = v1Path.head;
                curV2 = v2Path.head;

                if (curV1->node->nodeV == LCA) {
                    sum += curV2->node->nodeV;
                    while (curV2->next->node->nodeV != LCA) {
                        curV2 = curV2->next;
                        sum += curV2->node->nodeV;
                    }
                    return sum + LCA;
                }

                if (curV2->node->nodeV == LCA) {
                    sum += curV1->node->nodeV;
                    while (curV1->next->node->nodeV != LCA) {
                        curV1 = curV1->next;
                        sum += curV1->node->nodeV;
                    }
                    return sum + LCA;
                }

                sum += curV1->node->nodeV;
                while (curV1->next->node->nodeV != LCA) {
                    curV1 = curV1->next;
                    sum += curV1->node->nodeV;
                }

                sum += curV2->node->nodeV;
                while (curV2->next->node->nodeV != LCA) {
                    curV2 = curV2->next;
                    sum += curV2->node->nodeV;
                }

                return sum + LCA;
            }
            curV2 = curV2->next;
        }
        curV1 = curV1->next;
    }

}
