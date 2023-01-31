#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int  item;
	struct _dbllistnode *next;
	struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist{
   int size;
   CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i,cases;
    int numP;
    scanf("%d",&cases);
    for(i=0; i<cases; i++)
    {
        while(scanf("%d",&item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n",numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value){
      //create a new node
      CDblListNode* newNode;
      newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
      newNode->item = value;

      if(ptrCDLL->size==0) //first node
      {
          newNode->next = newNode;
          newNode->pre = newNode;
          ptrCDLL->head = newNode;
      }
      else{
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
      }
      ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL){

    if(CDLL.head==NULL) return;

    CDblListNode* temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head){
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n",temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL){
    if(ptrCDLL->head==NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next!= ptrCDLL->head) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }

    free(cur);
    ptrCDLL->head =NULL;
    ptrCDLL->size =0;

}



int numMountainPairs(CDblLinkedList CDLL)
{
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
// Write your code here

    CDblListNode *count;
    int length = 0;

    count = CDLL.head;
    do { // count number of adjacent pairs
        length++;
        count = count->next;
    } while (count != CDLL.head);


    if (length == 3)
        return 3;
    if (length == 2)
        return 1;
    if (length == 1)
        return 0;

    CDblListNode *A, *B, *cursor; // cursor is to clear other nodes to positive after iterating clockwise and anti clockwise
    A = CDLL.head;
    B = A->next;

    int pairs = 0, AmaxB;

    do {
        // 1. COUNT CLOCKWISE
        AmaxB = -1;
        while (B != A) {
//            printf("CW = A:%d, B:%d, AmaxB: %d\n", A->item, B->item, AmaxB);
            if (B == A->next) { // adjacent pairs
                if (abs(B->item) > A->item) { // absolute(B) is bigger than A, no need continue
                    if (B->item >= 0) { // B is not negative can add pair
//                        printf("ClockwisePair:%d,%d\n", A->item, B->item);
                        pairs++;
                        B->item = -(B->item);
                    }
                    break;
                }
                else if (abs(B->item) <= A->item) { // absolute(B) is smaller or equal than A, can continue

                    if (abs(B->item) > AmaxB) {
                        AmaxB = abs(B->item);
                    }

                    if (B->item >= 0) { // B is not negative, can add pair
//                        printf("ClockwisePair:%d,%d\n", A->item, B->item);
                        pairs++;
//                        AmaxB = B->item;
                        B->item = -(B->item);
                    }
                }
            }
            else { // non adjacent pairs
                if (abs(B->item) > A->item) { // absolute(B) is larger than A,
                    if (B->item >= 0) { // if positive add pair and break loop
//                        printf("ClockwisePair:%d,%d\n", A->item, B->item);
                        pairs++;
                        B->item = -(B->item); // add negative sign, pair is alr added
                    }
                    break; // if negative no need add pair, just break loop
                }
                else if (abs(B->item) <= A->item) { // absolute(B) is smaller than or equal than A, can continue
                    if (abs(B->item) > AmaxB) {
                        AmaxB = abs(B->item);
                    }
                    if (abs(B->item) >= AmaxB && B->item >= 0) { // absolute(B) is larger/equal to AmaxB, can add pair and continue
                        // B is positive, never seen before, add pair make it negative
//                        printf("ClockwisePair:%d,%d\n", A->item, B->item);
                        pairs++;
//                        AmaxB = B->item;
                        B->item = -(B->item);
                    }
                }
            }
            B = B->next;
        }

        // 2. COUNT ANTI-CLOCKWISE
        AmaxB = -1;
        B = A->pre;
        while (B != A) { //
//            printf("ACW = A:%d, B:%d, AmaxB: %d\n", A->item, B->item, AmaxB);
            if (B == A->pre) { // adjacent pairs
                if (abs(B->item) > A->item) { // absolute(B) is bigger than A, no need continue
                    if (B->item >= 0) { // B is postive can add pair
//                        printf("AntiClockwisePair:%d,%d\n", A->item, B->item);
                        pairs++;
                        B->item = -(B->item);
                    }
                    break;
                }
                else if (abs(B->item) <= A->item) { // absolute(B) is smaller or equal than A, can continue
                    if (abs(B->item) > AmaxB) {
                        AmaxB = abs(B->item);
                    }
                    if (B->item >= 0) { // B is positive, can add pair
//                        printf("AntiClockwisePair:%d,%d\n", A->item, B->item);
                        pairs++;
                        B->item = -(B->item);
                    }
                }
            }
            else { // non adjacent pairs
                if (abs(B->item) > A->item) { // absolute(B) is larger than A,
                    if (B->item >= 0) { // if positive add pair and break loop
//                        printf("AntiClockwisePair:%d,%d\n", A->item, B->item);
                        pairs++;
                        B->item = -(B->item); // add negative sign, pair is alr added
                    }
                    break; // if negative no need add pair, just break loop
                }
                else if (abs(B->item) <= A->item) { // absolute(B) is smaller than or equal than A, can continue
                    if (abs(B->item) > AmaxB) {
                        AmaxB = abs(B->item);
                    }
                    if (abs(B->item) >= AmaxB && B->item >= 0) { // absolute(B) is larger/equal to AmaxB, can add pair and continue
                        // B is positive, never seen before, add pair make it negative
//                        printf("AntiClockwisePair:%d,%d\n", A->item, B->item);
                        pairs++;
//                        AmaxB = B->item;
                        B->item = -(B->item);
                    }
                }
            }
            B = B->pre;
        }

        // 3. CLEAR ALL EXCEPT A AND PREVIOUS As TO POSITIVE

        cursor = A->next;
        do {
            if (cursor->item < 0) { // item is negative
                cursor->item = abs(cursor->item);
            }
            cursor = cursor->next;
        } while (cursor != CDLL.head);

        A->item = -(A->item); // set start to negative
        A = A->next;
        B = A->next;

    } while (A != CDLL.head);

    CDLL.head->pre->item = abs(CDLL.head->pre->item); // clear last to positive

    return pairs;
}
