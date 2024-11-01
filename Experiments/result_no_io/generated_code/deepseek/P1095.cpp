#include <stdio.h>

int main() {
    int M, S, T;
    scanf("%d %d %d", &M, &S, &T);

    int distance = 0;
    int time = 0;

    while (time < T) {
        if (M >= 10) {
            M -= 10;
            distance += 60;
        } else {
            int rest_time = (10 - M + 3) / 4; // 计算需要休息的时间
            if (time + rest_time < T) {
                time += rest_time;
                M += rest_time * 4;
            } else {
                break;
            }
        }
        time++;
        if (distance >= S) {
            printf("Yes\n%d\n", time);
            return 0;
        }
    }

    while (time < T) {
        distance += 17;
        time++;
        if (distance >= S) {
            printf("Yes\n%d\n", time);
            return 0;
        }
    }

    printf("No\n%d\n", distance);
    return 0;
}