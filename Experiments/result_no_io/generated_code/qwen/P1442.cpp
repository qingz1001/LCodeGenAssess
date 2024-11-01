#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int h;
    int l;
    int r;
} Platform;

int main() {
    int n, h;
    scanf("%d %d", &n, &h);
    int x, y;
    scanf("%d %d", &x, &y);

    Platform platforms[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &platforms[i].h, &platforms[i].l, &platforms[i].r);
    }

    int min_time = 1e9;
    for (int i = 0; i < n; i++) {
        if (y > platforms[i].h) continue;
        int fall_time = platforms[i].h - y;
        if (fall_time > h) continue;

        int left_time = abs(x - platforms[i].l);
        int right_time = abs(x - platforms[i].r);
        int total_time = fall_time + (left_time < right_time ? left_time : right_time);

        if (total_time < min_time) {
            min_time = total_time;
        }
    }

    printf("%d\n", min_time);
    return 0;
}