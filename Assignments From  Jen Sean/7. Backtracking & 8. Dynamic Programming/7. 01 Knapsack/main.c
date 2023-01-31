#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int bottom_up_dp(int n, int *s, int *v, int C) // s is sizes of items, v is value of items
{
    //write your code here
    // n is number of items, C is capacity of knapsack
    // s is sizes of items, v is value of items

    int matrix[n+1][C+1];
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=C; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int j=s[1]; j<=C; j++) {
        matrix[1][j] = v[1];
    }

    for (int i=2; i<=n; i++) {
        if (v[i] > matrix[i-1][1] && s[i] == 1) {
            matrix[i][1] = v[i];
        }
        else {
            matrix[i][1] = matrix[i-1][1];
        }
    }

    for (int i=2; i<=n; i++) {
        for (int j=2; j<=C; j++) {
            if (j-s[i] > 0 && matrix[i-1][j-s[i]] + v[i] >= matrix[i-1][j]){
                matrix[i][j] = matrix[i-1][j-s[i]] + v[i];
            }
            else {
                matrix[i][j] = matrix[i-1][j];
            }
        }
    }

//    printf("\n");
//    for (int i=1; i<=n; i++) {
//        for (int j=1; j<=C; j++) {
//            printf("%d ", matrix[i][j]);
//        }
//        printf("\n");
//    }

    return matrix[n][C];
}


int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));

    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);

    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);

    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));

}
