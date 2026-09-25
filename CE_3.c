//Class Exercise 3
//The program calculates the height, in terms of number of edges, of a complete binary tree using the number 
//of nodes.
// You are using GCC
#include <stdio.h>
int main() {
    int n;-
    scanf("%d", &n);
    int x;
    for (int i = 0; i < n; i++)
        scanf("%d", &x);
    int height = 0;
    int nodes = 1;
    while (nodes * 2 <= n) {
        nodes *= 2;
        height++;
    }
    printf("Height of the binary tree: %d", height);
    return 0;
}