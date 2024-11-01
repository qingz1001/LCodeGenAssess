#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int a[MAX_N];
int stack[MAX_N];
int top = -1;

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int operations = 0;

    for (int i = 0; i < n; i++) {
        while (top >= 0 && stack[top] > a[i]) {
            top--;
        }
        
        if (top < 0 || stack[top] < a[i]) {
            top++;
            stack[top] = a[i];
            operations++;
        }
    }

    printf("%d\n", operations);

    return 0;
}