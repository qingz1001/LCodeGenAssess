#include <stdio.h>

int main() {
    int M, S, T;
    scanf("%d %d %d", &M, &S, &T);

    int time = 0;
    int distance = 0;
    int magic = M;

    while (time < T) {
        if (magic >= 10) {
            distance += 60;
            magic -= 10;
        } else if (magic + 4 >= 10) {
            magic += 4;
            time++;
            if (time == T) break;
            distance += 60;
            magic -= 10;
        } else {
            int run_time = (10 - magic + 3) / 4;
            if (time + run_time >= T) {
                distance += 17 * (T - time);
                time = T;
                break;
            }
            distance += 17 * run_time;
            time += run_time;
            magic += 4 * run_time;
        }
        time++;
        if (distance >= S) break;
    }

    if (distance >= S) {
        printf("Yes\n%d\n", time);
    } else {
        while (time < T) {
            distance += 17;
            time++;
        }
        printf("No\n%d\n", distance);
    }

    return 0;
}