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
    int food = 10;

    for (int i = 0; i < G; i++) {
        if (trash[i].time > time && height < D) {
            time = trash[i].time;
        }
        if (food <= 0) {
            printf("%d\n", time);
            return 0;
        }
        if (trash[i].time <= time) {
            height += trash[i].height;
            food -= trash[i].food;
        }
    }

    if (height >= D) {
        printf("%d\n", time);
    } else {
        printf("%d\n", time + (D - height));
    }

    return 0;
}