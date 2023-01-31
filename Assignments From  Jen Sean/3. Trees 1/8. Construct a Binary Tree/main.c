#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}

void buildTree(BTNode** node, char* preO, char* postO)
{
    // Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
    // Write your code here

    // 1. Root of the tree is the first element of preO/the last element of postO
    // Creating the root node
    *node = (BTNode*) malloc(sizeof(BTNode));
    (*node)->id = *preO;
    (*node)->left = NULL;
    (*node)->right = NULL;

    preO++; // set the character pointer to the next character after root

    char *preO_start = preO, *postO_start = postO, *cur_postO; // store the start address (after root) of preO and the start address of postO
    BTNode *roots[MAX_N]; // creating an array of BTNode pointers
    BTNode *cur_tree, *temp;
    int roots_index = 0, outer_break = 0;

    roots[roots_index] = *node; // add the root of the tree into the array
    roots_index++;

    while (*preO) {
//        printf("%c\n", *preO);
        while (*postO) {
//            printf("%c\n", *postO);
            if (*postO == *preO) { // found preO character in postO
//                printf("preO: %c\npostO: %c\n", *preO, *postO);
                // find nearest root in roots array
                cur_postO = postO; // set cur_postO to the same position as postO
                cur_postO++; // go to next character in postO
                while (*cur_postO) { // iterate from postO character to end of postO
                    for (int i=0; i<roots_index; i++) { // iterate through roots array to find match of root
//                        printf("cur_postO: %c\nroots array: %c\n", *cur_postO, (roots[i])->id);
                        if (*cur_postO == (roots[i])->id) { // character found in roots array
                            cur_tree = roots[i]; // set a cursor to that root and add node of id postO
                            temp = (BTNode*) malloc(sizeof(BTNode));
                            temp->id = *postO;
                            temp->left = NULL;
                            temp->right = NULL;
                            if (cur_tree->left == NULL) { // if left node is NULL, add as left node, else add as right node
                                cur_tree->left = temp;
                                roots[roots_index] = cur_tree->left;
                                roots_index++;
                            }
                            else if (cur_tree->right == NULL) {
                                cur_tree->right = temp;
                                roots[roots_index] = cur_tree->right;
                                roots_index++;
                            }
                            outer_break = 1;
                            break;
                        }
                    }
                    if (outer_break == 1) {
                        outer_break = 0;
                        break;
                    }
                    cur_postO++;
                }
            }
            postO++;
        }
        postO = postO_start; // reset postO pointer to start of the string
        preO++;
    }
}
