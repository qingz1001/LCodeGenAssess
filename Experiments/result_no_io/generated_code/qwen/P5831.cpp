#include <stdio.h>
#include <stdlib.h>

#define MAX_K 10
#define MAX_N 20

int main() {
    int K, N;
    scanf("%d %d", &K, &N);

    int rankings[MAX_K][MAX_N];
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &rankings[i][j]);
        }
    }

    int consistent_pairs = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            int is_consistent = 1;
            for (int k = 0; k < K; ++k) {
                if ((rankings[k][i] > rankings[k][j]) != (i > j)) {
                    is_consistent = 0;
                    break;
                }
            }
            if (is_consistent) {
                ++consistent_pairs;
            }
        }
    }

    printf("%d\n", consistent_pairs);

    return 0;
}