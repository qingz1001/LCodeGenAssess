#include <stdio.h>
#include <stdlib.h>

#define MAX_R 200
#define MAX_C 200
#define MAX_M 200000

int book[MAX_R][MAX_C];
int prefix_sum[MAX_R + 1][MAX_C + 1];

int query(int x1, int y1, int x2, int y2) {
    return prefix_sum[x2 + 1][y2 + 1] - prefix_sum[x1][y2 + 1] - prefix_sum[x2 + 1][y1] + prefix_sum[x1][y1];
}

int main() {
    int R, C, M;
    scanf("%d %d %d", &R, &C, &M);

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &book[i][j]);
            prefix_sum[i][j] = book[i][j] + prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1];
        }
    }

    while (M--) {
        int x1, y1, x2, y2, H;
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &H);
        int total_pages = query(x1, y1, x2, y2);
        if (total_pages >= H) {
            printf("%d\n", (total_pages + H - 1) / H);
        } else {
            printf("Poor QLW\n");
        }
    }

    return 0;
}