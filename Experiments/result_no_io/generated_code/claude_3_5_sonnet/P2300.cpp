#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

int p[MAX_N];
int stack[MAX_N];
int top = -1;

int main() {
    int n, i, merges = 0;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    for (i = 0; i < n; i++) {
        while (top >= 0 && p[i] < stack[top]) {
            top--;
            merges++;
        }
        if (top >= 0 && p[i] == stack[top]) {
            top--;
            merges++;
        }
        stack[++top] = p[i];
    }

    merges += top;

    printf("%d\n", merges);

    return 0;
}