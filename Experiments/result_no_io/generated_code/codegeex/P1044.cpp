#include <stdio.h>
#include <stdlib.h>

long long int count(int n, int *stack, int top) {
    if (n == 0) {
        return 1;
    }
    long long int result = 0;
    for (int i = 1; i <= n; i++) {
        if (!top || stack[top - 1] != i) {
            stack[top++] = i;
            result += count(n - 1, stack, top);
            top--;
        }
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    int *stack = (int *)malloc(n * sizeof(int));
    printf("%lld\n", count(n, stack, 0));
    free(stack);
    return 0;
}