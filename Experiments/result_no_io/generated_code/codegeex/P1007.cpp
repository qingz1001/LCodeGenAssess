#include <stdio.h>
#include <stdlib.h>

int main() {
    int L, N;
    scanf("%d %d", &L, &N);

    int *soldiers = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &soldiers[i]);
    }

    int max_time = 0;
    int min_time = L;

    for (int i = 0; i < N; i++) {
        int time_to_left = soldiers[i];
        int time_to_right = L - soldiers[i] + 1;

        max_time = (max_time > time_to_left || max_time > time_to_right) ? max_time : (time_to_left > time_to_right ? time_to_left : time_to_right);
        min_time = (min_time < time_to_left && min_time < time_to_right) ? min_time : (time_to_left < time_to_right ? time_to_left : time_to_right);
    }

    printf("%d %d\n", min_time, max_time);

    free(soldiers);
    return 0;
}