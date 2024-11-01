#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int count_equations(int *arr, int n) {
    int count = 0;
    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n; i++) {
        int left = 0, right = n - 1;
        while (left < right) {
            if (left == i) left++;
            if (right == i) right--;
            if (left >= right) break;

            int sum = arr[left] + arr[right];
            if (sum == arr[i]) {
                count++;
                break;
            } else if (sum < arr[i]) {
                left++;
            } else {
                right--;
            }
        }
    }

    return count;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int m;
        scanf("%d", &m);
        int *arr = (int *)malloc(m * sizeof(int));

        for (int i = 0; i < m; i++) {
            scanf("%d", &arr[i]);
        }

        int result = count_equations(arr, m);
        printf("%d\n", result);

        free(arr);
    }

    return 0;
}