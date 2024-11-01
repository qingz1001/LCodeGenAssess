#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_M 801
#define MAX_N 1001

typedef struct {
    int x;
    int y;
} Tower;

double dist(Tower a, Tower b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int cmp(const void *a, const void *b) {
    Tower *x = (Tower *)a;
    Tower *y = (Tower *)b;
    return x->x - y->x;
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    Tower towers[MAX_M];
    for (int i = 0; i < M; i++) {
        scanf("%d%d", &towers[i].x, &towers[i].y);
    }

    qsort(towers, M, sizeof(Tower), cmp);

    double l = 0, r = 100000;
    while (r - l > 0.01) {
        double mid = (l + r) / 2;
        int left = 0, right = 0;
        int vis[MAX_M] = {0};

        while (right < M) {
            while (right < M && dist(towers[left], towers[right]) <= mid * 2) {
                right++;
            }
            if (right - left > 1) {
                for (int i = left + 1; i < right; i++) {
                    vis[i] = 1;
                }
            }
            left++;
        }

        int flag = 0;
        for (int i = 0; i < M; i++) {
            if (!vis[i]) {
                flag = 1;
                break;
            }
        }

        if (flag) {
            l = mid;
        } else {
            r = mid;
        }
    }

    printf("%.2lf\n", r);
    return 0;
}