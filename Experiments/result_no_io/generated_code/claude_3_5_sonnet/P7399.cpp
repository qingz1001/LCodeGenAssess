#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int n;
int a[MAX_N];
int stack[MAX_N];
int top = -1;

int main() {
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
            stack[++top] = a[i];
            operations++;
        }
    }
    
    printf("%d\n", operations);
    
    return 0;
}