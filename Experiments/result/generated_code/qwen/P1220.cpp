#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int position;
    int power;
} Light;

int compare(const void *a, const void *b) {
    return ((Light *)a)->position - ((Light *)b)->position;
}

int main() {
    int n, c;
    scanf("%d %d", &n, &c);
    Light lights[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &lights[i].position, &lights[i].power);
    }

    qsort(lights, n, sizeof(Light), compare);

    int left = 0, right = n - 1;
    int total_power = 0;
    while (left <= right) {
        if (abs(c - lights[left].position) <= abs(c - lights[right].position)) {
            total_power += lights[left++].power;
        } else {
            total_power += lights[right--].power;
        }
    }

    printf("%d\n", total_power);
    return 0;
}