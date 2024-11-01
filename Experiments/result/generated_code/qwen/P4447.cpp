#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int min_group_size = 1;
    int current_group_size = 1;

    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) {
            current_group_size++;
            if (current_group_size > min_group_size) {
                min_group_size = current_group_size;
            }
        } else {
            current_group_size = 1;
        }
    }

    printf("%d\n", min_group_size);

    free(a);
    return 0;
}