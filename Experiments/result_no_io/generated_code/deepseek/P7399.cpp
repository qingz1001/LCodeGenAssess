#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int operations = 0;
    int i = 0;

    while (i < n) {
        if (a[i] == 0) {
            i++;
            continue;
        }

        int start = i;
        while (i < n && a[i] != 0) {
            i++;
        }

        operations++;
    }

    printf("%d\n", operations);
    free(a);
    return 0;
}