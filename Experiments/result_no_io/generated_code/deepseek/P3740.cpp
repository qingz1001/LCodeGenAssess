#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000000
#define MAXM 1000

int wall[MAXN + 1];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int A, B;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &A, &B);
        for (int j = A; j <= B; j++) {
            wall[j] = i + 1; // 用海报的编号来标记墙上的位置
        }
    }

    int seen[MAXM + 1] = {0};
    int count = 0;

    for (int i = 1; i <= N; i++) {
        if (wall[i] != 0 && !seen[wall[i]]) {
            seen[wall[i]] = 1;
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}