#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void push(Stack *sPtr, BTNode *item){
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

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}

void createExpTree(BTNode** root,char* prefix)
{
    //Write your code here
    Stack stack;
    BTNode *cursor, *temp;
    while (*prefix) {
        if (*root == NULL) { // first character (will always be operator)
            temp = (BTNode*) malloc(sizeof(BTNode));
//            printf("%c\n", *prefix);
            temp->item = -(*prefix);
            temp->left = NULL;
            temp->right = NULL;
            *root = temp; // set root to first node
            cursor = *root; // set cursor to root
            prefix++;
        }
        else if (isdigit(*prefix) != 0) { // prefix is a digit
            temp = (BTNode*) malloc(sizeof(BTNode));
//            printf("%d\n", atoi(prefix));
            temp->item = atoi(prefix);
            temp->left = NULL;
            temp->right = NULL;

            while (isdigit(*prefix) != 0) { // shift prefix to new position after number
                prefix++;
            }

            // both left and right have nodes, iterate through stack to find previous nodes with NULL value
            while (cursor->left != NULL && cursor->right != NULL) {
                cursor = peek(stack);
                pop(&stack);
            }

            if (cursor->left == NULL) {
                cursor->left = temp;
            }
            else if (cursor->right == NULL) {
                cursor->right = temp;
            }
        }
        else if (*prefix == '+' || *prefix == '-' || *prefix == '*' || *prefix == '/' || *prefix == '(' || *prefix == ')') {
            temp = (BTNode*) malloc(sizeof(BTNode));
//            printf("%c\n", *prefix);
            temp->item = -(*prefix);
            temp->left = NULL;
            temp->right = NULL;

            // both left and right have nodes, iterate through stack to find previous nodes with NULL value
            while (cursor->left != NULL && cursor->right != NULL) {
                cursor = peek(stack);
                pop(&stack);
            }

            if (cursor->left == NULL) {
                cursor->left = temp;
                push(&stack, cursor); // push current node to stack before going to new node
                cursor = cursor->left;
            }

            else if (cursor->right == NULL) {
                cursor->right = temp;
                push(&stack, cursor); // push current node to stack before going to new node
                cursor = cursor->right;
            }
            prefix++;
        }
        else { // *prefix is a whitespace character
            prefix++;
        }
    }
}

void printTree(BTNode *node){
    //Write your code here
    if (node == NULL)
        return;
    printTree(node->left);
    if (node->item < 0)
        printf("%c ", abs(node->item));
    else
        printf("%d ", node->item);
    printTree(node->right);
}


void printTreePostfix(BTNode *node){
   //Write your code here
    if (node == NULL)
        return;

    printTreePostfix(node->left);
    printTreePostfix(node->right);
    if (node->item < 0)
        printf("%c ", abs(node->item));
    else
        printf("%d ", node->item);
}

double computeTree(BTNode *node){
//Write your code here
    // base case: tree has no nodes
    if (node == NULL) {
        return 0;
    }

    // the leaves of a binary expression tree are operands
    if (node->left == NULL && node->right == NULL) {
//        printf("return: %d\n", node->item);
        return (double) (node->item);
    }

    // recursively evaluate the left and right nodes
    double x = computeTree(node->left);
//    printf("x = %lf\n", x);
    double y = computeTree(node->right);
//    printf("y = %lf\n", y);


//    printf("%c\n", (char)(abs(node->item)));
    if ((char)(abs(node->item)) == '+') {
        return (x + y);
    }
    if ((char)(abs(node->item)) == '-') {
        return (x - y);
    }
    if ((char)(abs(node->item)) == '*') {
        return (x * y);
    }
    if ((char)(abs(node->item)) == '/') {
        return (x / y);
    }
}

