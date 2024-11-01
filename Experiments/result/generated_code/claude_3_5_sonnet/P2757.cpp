#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_N 500005

int A[MAX_N];
int pos[MAX_N];

bool check_arithmetic_subsequence(int n) {
    for (int i = 1; i <= n; i++) {
        pos[A[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int diff = A[j] - A[i];
            int next = A[j] + diff;
            int count = 2;

            while (next <= n && pos[next] > j) {
                j = pos[next];
                next += diff;
                count++;
            }

            if (count >= 3) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int T, N;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) {
            scanf("%d", &A[i]);
        }

        if (check_arithmetic_subsequence(N)) {
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }

    return 0;
}