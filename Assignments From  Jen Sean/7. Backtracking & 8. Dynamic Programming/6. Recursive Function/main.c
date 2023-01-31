#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *data;

int top_down_dp(int n)
{
    //write your code here
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    if (n == 2)
        return 2;

    if (data[n-1] == -1) // not stored in data array
        data[n-1] = top_down_dp(n-1);

    if (data[n-2] == -1) // not stored in data array
        data[n-2] = top_down_dp(n-2);

    if (data[n-3] == -1) // not stored in data array
        data[n-3] = top_down_dp(n-3);

    data[n] = data[n-1] + (2 * data[n-2]) - (3 * data[n-3]);
    return data[n];
}



int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);

    // allocate memory to data array
    data = malloc(sizeof(int) * (n+1));
    for (i=0; i<=n; i++)
        data[i] = -1;

    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));

}
