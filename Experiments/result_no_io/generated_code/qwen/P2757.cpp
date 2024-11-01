#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50001
#define MAX_T 5

int find_arithmetic_subsequence(int *arr, int n) {
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int d = arr[i + 1] - arr[i];
            for (int j = i + 2; j + len - 1 < n; ++j) {
                if (arr[j] - arr[j - 1] == d) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    int T, N;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        int arr[MAX_N];
        for (int i = 0; i < N; ++i) {
            scanf("%d", &arr[i]);
        }
        if (find_arithmetic_subsequence(arr, N)) {
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }
    return 0;
}