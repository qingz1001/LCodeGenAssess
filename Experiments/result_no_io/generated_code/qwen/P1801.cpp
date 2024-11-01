#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMANDS 200000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int a[MAX_COMMANDS];
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }

    int u[MAX_COMMANDS];
    for (int i = 0; i < n; i++) {
        scanf("%d", &u[i]);
    }

    int result[n];
    int add_index = 0;
    int get_count = 0;

    for (int i = 0; i < n; i++) {
        while (add_index < u[i]) {
            if (add_index == 0 || a[add_index] > a[add_index - 1]) {
                qsort(a, add_index + 1, sizeof(int), compare);
            }
            add_index++;
        }
        result[i] = a[get_count++];
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}