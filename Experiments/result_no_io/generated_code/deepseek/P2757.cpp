#include <stdio.h>
#include <stdbool.h>

#define MAXN 10000

bool check_arithmetic_sequence(int arr[], int n) {
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            int diff = arr[j] - arr[i];
            int next = arr[j] + diff;
            for (int k = j + 1; k < n; k++) {
                if (arr[k] == next) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        int A[MAXN];
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
        if (check_arithmetic_sequence(A, N)) {
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }
    return 0;
}