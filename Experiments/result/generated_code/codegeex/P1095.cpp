#include <stdio.h>

int main() {
    int M, S, T;
    scanf("%d %d %d", &M, &S, &T);

    int max_distance = 0;
    int time = 0;

    while (time < T) {
        if (M >= 10) {
            M -= 10;
            time++;
            max_distance += 60;
        } else {
            int run_time = (M / 4) + 1;
            M = 0;
            time += run_time;
            max_distance += run_time * 17;
        }

        if (max_distance >= S) {
            printf("Yes\n");
            printf("%d\n", time);
            return 0;
        }

        if (time + 1 < T) {
            M += 4;
            if (M > 10) M = 10;
            time++;
        }
    }

    printf("No\n");
    printf("%d\n", max_distance);
    return 0;
}