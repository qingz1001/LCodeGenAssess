#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int v;
    int t;
} Balloon;

int compare(const void *a, const void *b) {
    return ((Balloon *)b)->t - ((Balloon *)a)->t;
}

int main() {
    int n, T;
    scanf("%d %d", &n, &T);

    Balloon balloons[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &balloons[i].v, &balloons[i].t);
    }

    qsort(balloons, n, sizeof(Balloon), compare);

    int max_height = 0;
    int result = 0;

    for (int i = 0; i < n; i++) {
        if (balloons[i].t <= T) {
            int height = balloons[i].v * (T - balloons[i].t);
            if (height > max_height) {
                max_height = height;
                result = i + 1;
            }
        } else {
            break;
        }
    }

    printf("%d\n", result);

    return 0;
}