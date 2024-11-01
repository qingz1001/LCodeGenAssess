#include <stdio.h>

int main() {
    int M, S, T;
    scanf("%d %d %d", &M, &S, &T);

    int dist = 0;
    int time = 0;

    while (time < T) {
        if (M >= 10) {
            dist += 60;
            M -= 10;
        } else {
            int rest_time = (10 - M + 3) / 4;
            if (time + rest_time < T) {
                time += rest_time;
                M += 4 * rest_time;
                continue;
            } else {
                dist += 17 * (T - time);
                break;
            }
        }
        time++;
        if (dist >= S) {
            printf("Yes\n%d\n", time);
            return 0;
        }
    }

    printf("No\n%d\n", dist);
    return 0;
}