#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define INF 0x3f3f3f3f

int R, C, M;
int P[MAXN][MAXN];
int prefix_sum[MAXN][MAXN];

void preprocess() {
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            prefix_sum[i][j] = prefix_sum[i-1][j] + prefix_sum[i][j-1] - prefix_sum[i-1][j-1] + P[i][j];
        }
    }
}

int query(int x1, int y1, int x2, int y2) {
    return prefix_sum[x2][y2] - prefix_sum[x1-1][y2] - prefix_sum[x2][y1-1] + prefix_sum[x1-1][y1-1];
}

int main() {
    scanf("%d %d %d", &R, &C, &M);
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            scanf("%d", &P[i][j]);
        }
    }
    preprocess();
    for (int i = 0; i < M; ++i) {
        int x1, y1, x2, y2, H;
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &H);
        int sum = query(x1, y1, x2, y2);
        if (sum >= H) {
            printf("%d\n", (x2-x1+1)*(y2-y1+1));
        } else {
            printf("Poor QLW\n");
        }
    }
    return 0;
}