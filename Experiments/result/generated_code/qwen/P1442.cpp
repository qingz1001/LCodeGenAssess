#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int hi, li, ri;
} Platform;

int main() {
    int n, h, x, y;
    scanf("%d %d", &n, &h);
    scanf("%d %d", &x, &y);

    Platform platforms[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &platforms[i].hi, &platforms[i].li, &platforms[i].ri);
    }

    int min_time = INT_MAX;

    // Check if the ball can fall directly to the ground without hitting any platform
    if (y - h >= 0) {
        min_time = y - h;
    }

    // Check each platform
    for (int i = 0; i < n; ++i) {
        int hi = platforms[i].hi;
        int li = platforms[i].li;
        int ri = platforms[i].ri;

        if (y > hi && y <= hi + h) {
            // Calculate the time to reach the platform
            int time_to_platform = y - hi;
            // Calculate the time to roll off the platform
            int time_off_platform = abs(x - li);
            // Total time is the sum of both times
            int total_time = time_to_platform + time_off_platform;
            // Update the minimum time if this is smaller
            if (total_time < min_time) {
                min_time = total_time;
            }
        }
    }

    printf("%d\n", min_time);

    return 0;
}