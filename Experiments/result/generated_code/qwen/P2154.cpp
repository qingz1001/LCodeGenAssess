#include <stdio.h>
#define MOD 2147483648

int main() {
    int N, M, W, k;
    scanf("%d %d", &N, &M);
    scanf("%d", &W);
    int trees[W][2];
    for (int i = 0; i < W; i++) {
        scanf("%d %d", &trees[i][0], &trees[i][1]);
    }
    scanf("%d", &k);

    long long total_holiness = 0;

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            int count = 0;
            for (int l = 0; l < W; l++) {
                if (abs(trees[l][0] - i) + abs(trees[l][1] - j) == 2 * k + 1) {
                    count++;
                }
            }
            total_holiness += count;
            total_holiness %= MOD;
        }
    }

    printf("%lld\n", total_holiness);
    return 0;
}