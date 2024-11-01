#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int height;
    int food;
} Trash;

int compare(const void *a, const void *b) {
    return ((Trash *)a)->time - ((Trash *)b)->time;
}

int main() {
    int D, G;
    scanf("%d %d", &D, &G);
    Trash trash[G];
    for (int i = 0; i < G; i++) {
        scanf("%d %d %d", &trash[i].time, &trash[i].food, &trash[i].height);
    }

    qsort(trash, G, sizeof(Trash), compare);

    int time = 10;
    int height = 0;
    int index = 0;

    while (index < G) {
        if (time >= trash[index].time) {
            if (time + trash[index].food >= D) {
                printf("%d\n", trash[index].time);
                return 0;
            }
            time += trash[index].food;
            height += trash[index].height;
            index++;
        } else {
            if (height == 0) {
                printf("10\n");
                return 0;
            }
            height--;
        }
    }

    printf("%d\n", time);
    return 0;
}