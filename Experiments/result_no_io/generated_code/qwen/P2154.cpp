#include <stdio.h>
#include <stdlib.h>

#define MOD 2147483648

int main() {
    int N, M, W, k;
    scanf("%d %d", &N, &M);
    scanf("%d", &W);
    int *trees = (int *)malloc(W * sizeof(int));
    for (int i = 0; i < W; i++) {
        scanf("%d %d", &trees[i], &trees[i + W]);
    }
    scanf("%d", &k);

    long long result = 0;

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            int count = 0;
            for (int t = 0; t < W; t += 2) {
                if (abs(trees[t] - i) == k && trees[t + 1] == j) count++;
                if (trees[t] == i && abs(trees[t + 1] - j) == k) count++;
            }
            result = (result + count) % MOD;
        }
    }

    printf("%lld\n", result);

    free(trees);
    return 0;
}