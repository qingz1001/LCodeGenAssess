#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Shift;

int compare(const void *a, const void *b) {
    Shift *shiftA = (Shift *)a;
    Shift *shiftB = (Shift *)b;
    return shiftA->start - shiftB->start;
}

int main() {
    int N, T;
    scanf("%d %d", &N, &T);

    Shift shifts[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &shifts[i].start, &shifts[i].end);
    }

    qsort(shifts, N, sizeof(Shift), compare);

    int current_end = 0;
    int next_end = 0;
    int cows_used = 0;
    int i = 0;

    while (current_end < T) {
        while (i < N && shifts[i].start <= current_end + 1) {
            if (shifts[i].end > next_end) {
                next_end = shifts[i].end;
            }
            i++;
        }

        if (next_end == current_end) {
            printf("-1\n");
            return 0;
        }

        current_end = next_end;
        cows_used++;
    }

    printf("%d\n", cows_used);
    return 0;
}