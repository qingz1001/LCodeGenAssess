#include <stdio.h>
#include <stdlib.h>

#define MAX_M 30
#define MAX_X 1000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int count_equations(int *arr, int m) {
    int count = 0;
    int sum[1 << MAX_M] = {0};
    int n = 1 << m;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i & (1 << j)) {
                sum[i] += arr[j];
            }
        }
    }

    for (int i = 1; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((i & j) == 0 && sum[i | j] == sum[i] + sum[j]) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    int t, m;
    int arr[MAX_M];

    scanf("%d", &t);

    while (t--) {
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &arr[i]);
        }

        qsort(arr, m, sizeof(int), compare);

        printf("%d\n", count_equations(arr, m));
    }

    return 0;
}