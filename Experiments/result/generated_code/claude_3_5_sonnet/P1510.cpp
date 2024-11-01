#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

typedef struct {
    int volume;
    int effort;
} Stone;

int compare(const void *a, const void *b) {
    Stone *sa = (Stone *)a;
    Stone *sb = (Stone *)b;
    return sa->effort - sb->effort;
}

int main() {
    int v, n, c;
    scanf("%d %d %d", &v, &n, &c);

    Stone stones[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &stones[i].volume, &stones[i].effort);
    }

    qsort(stones, n, sizeof(Stone), compare);

    int total_volume = 0;
    int remaining_effort = c;

    for (int i = 0; i < n && total_volume < v; i++) {
        if (remaining_effort >= stones[i].effort) {
            total_volume += stones[i].volume;
            remaining_effort -= stones[i].effort;
        } else {
            break;
        }
    }

    if (total_volume >= v) {
        printf("%d\n", remaining_effort);
    } else {
        printf("Impossible\n");
    }

    return 0;
}