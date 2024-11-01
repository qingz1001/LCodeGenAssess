#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    qsort(arr, n, sizeof(int), compare);
    
    int max_sum = -1;
    for (int i = 0; i < n - 2; i++) {
        if (arr[i] >= m) break;
        for (int j = i + 1; j < n - 1; j++) {
            if (arr[i] + arr[j] >= m) break;
            for (int k = j + 1; k < n; k++) {
                if (arr[i] + arr[j] + arr[k] <= m) {
                    max_sum = arr[i] + arr[j] + arr[k];
                } else {
                    break;
                }
            }
        }
    }
    
    printf("%d\n", max_sum);
    return 0;
}