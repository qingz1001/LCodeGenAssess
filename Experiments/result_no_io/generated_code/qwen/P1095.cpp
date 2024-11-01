#include <stdio.h>
#include <math.h>

int main() {
    int M, S, T;
    scanf("%d %d %d", &M, &S, &T);

    int max_distance = M * 4; // 最大移动距离
    if (max_distance >= S) {
        printf("Yes\n%d\n", ceil((double)S / 17.0));
        return 0;
    }

    int time_to_sink = T - ceil((double)(S - max_distance) / 60.0);
    if (time_to_sink <= 0) {
        printf("No\n%d\n", max_distance);
        return 0;
    }

    int remaining_time = time_to_sink;
    while (remaining_time > 0) {
        int flash_time = min(remaining_time, 10);
        remaining_time -= flash_time;
        M += flash_time * 4;

        if (M * 4 >= S) {
            printf("Yes\n%d\n", ceil((double)S / 17.0) + ceil((double)(S - max_distance) / 60.0));
            return 0;
        }
    }

    int distance_left = M * 4;
    printf("No\n%d\n", distance_left);
    return 0;
}

int min(int a, int b) {
    return a < b ? a : b;
}