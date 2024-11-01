#include <stdio.h>
#include <stdlib.h>

int minOperations(int n, int a[]) {
    int operations = 0;
    int i = 0;

    while (i < n) {
        int start = i;
        int value = a[i];

        while (i < n && a[i] == value) {
            i++;
        }

        operations++;
    }

    return operations;
}

int main() {
    int n;
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int result = minOperations(n, a);
    printf("%d\n", result);

    free(a);
    return 0;
}