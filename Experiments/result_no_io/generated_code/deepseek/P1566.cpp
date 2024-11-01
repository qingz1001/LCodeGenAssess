#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int count_add_equations(int *arr, int n) {
    int count = 0;
    qsort(arr, n, sizeof(int), compare);

    for (int i = n - 1; i >= 0; i--) {
        int left = 0, right = i - 1;
        while (left < right) {
            if (arr[left] + arr[right] == arr[i]) {
                count++;
                break;
            } else if (arr[left] + arr[right] < arr[i]) {
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
        int arr[m];
        for (int i = 0; i < m; i++) {
            scanf("%d", &arr[i]);
        }
        printf("%d\n", count_add_equations(arr, m));
    }

    return 0;
}