#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

int dist[MAX][2];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int x1, y1, x2, y2, N;
    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &N);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        dist[i][0] = (x - x1) * (x - x1) + (y - y1) * (y - y1);
        dist[i][1] = (x - x2) * (x - x2) + (y - y2) * (y - y2);
    }

    qsort(dist, N, sizeof(dist[0]), compare);

    int ans = 0x7fffffff;
    for (int i = 0; i < N; i++) {
        int r1 = dist[i][0], r2 = dist[i][1];
        int r = r1 + r2;
        if (r < ans) {
            ans = r;
        }
        for (int j = i + 1; j < N; j++) {
            r1 = dist[j][0];
            if (r1 > r2) {
                r = r1 + r2;
                if (r < ans) {
                    ans = r;
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}