#include <stdio.h>

int main() {
    int M, S, T;
    scanf("%d %d %d", &M, &S, &T);

    int running_time = S / 17;
    if (running_time <= T) {
        printf("Yes\n%d\n", running_time);
    } else {
        int max_distance = 0;
        for (int i = 0; i <= T; i++) {
            int remaining_time = T - i;
            int distance_covered = i * 60 + (remaining_time * M / 4);
            if (distance_covered > max_distance) {
                max_distance = distance_covered;
            }
        }
        printf("No\n%d\n", max_distance);
    }

    return 0;
}