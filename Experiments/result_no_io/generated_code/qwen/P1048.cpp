#include <stdio.h>
#include <stdlib.h>

#define MAX_T 1000
#define MAX_M 100

typedef struct {
    int time;
    int value;
} Plant;

int compare(const void *a, const void *b) {
    return ((Plant *)b)->value - ((Plant *)a)->value;
}

int main() {
    int T, M;
    scanf("%d %d", &T, &M);

    Plant plants[MAX_M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &plants[i].time, &plants[i].value);
    }

    qsort(plants, M, sizeof(Plant), compare);

    int max_value = 0;
    for (int i = 0; i < M && T > 0; i++) {
        if (plants[i].time <= T) {
            max_value += plants[i].value;
            T -= plants[i].time;
        }
    }

    printf("%d\n", max_value);

    return 0;
}