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

    int left_index = c - 1;
    int right_index = c;
    int total_power = 0;

    while (left_index >= 0 || right_index < n) {
        if (left_index >= 0 && (right_index == n || lights[left_index].position > lights[right_index].position)) {
            total_power += lights[left_index].power;
            left_index--;
        } else {
            total_power += lights[right_index].power;
            right_index++;
        }
    }

    printf("%d\n", total_power);
    return 0;
}