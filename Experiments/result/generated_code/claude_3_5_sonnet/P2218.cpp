#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 20000
#define INF 1000000001

typedef long long ll;

struct Point {
    int x, y;
} points[MAX_N];

int N;

int check(int L) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                int minX = INF, maxX = -INF, minY = INF, maxY = -INF;
                for (int t = 0; t < N; t++) {
                    if (t == i || t == j || t == k) continue;
                    minX = (points[t].x < minX) ? points[t].x : minX;
                    maxX = (points[t].x > maxX) ? points[t].x : maxX;
                    minY = (points[t].y < minY) ? points[t].y : minY;
                    maxY = (points[t].y > maxY) ? points[t].y : maxY;
                }
                if (maxX - minX <= L && maxY - minY <= L) return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int left = 0, right = 2000000000, mid;
    while (left < right) {
        mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    return 0;
}