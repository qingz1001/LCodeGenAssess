#include <stdio.h>
#include <stdlib.h>

int count_thair(int n, int a[]) {
    int count = 0;
    for (int j = 1; j < n - 1; j++) {
        int left_count = 0;
        for (int i = 0; i < j; i++) {
            if (a[i] < a[j]) {
                left_count++;
            }
        }
        int right_count = 0;
        for (int k = j + 1; k < n; k++) {
            if (a[j] < a[k]) {
                right_count++;
            }
        }
        count += left_count * right_count;
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int result = count_thair(n, a);
    printf("%d\n", result);
    free(a);
    return 0;
}