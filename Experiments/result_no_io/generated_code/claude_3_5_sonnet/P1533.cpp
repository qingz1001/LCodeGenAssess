#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300000
#define MAX_M 50000

typedef struct {
    int value;
    int index;
} Dog;

int cmp(const void *a, const void *b) {
    return ((Dog*)a)->value - ((Dog*)b)->value;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Dog dogs[MAX_N];
    int original[MAX_N];

    for (int i = 0; i < n; i++) {
        scanf("%d", &dogs[i].value);
        dogs[i].index = i;
        original[i] = dogs[i].value;
    }

    qsort(dogs, n, sizeof(Dog), cmp);

    int i, j, k;
    for (int q = 0; q < m; q++) {
        scanf("%d %d %d", &i, &j, &k);
        i--; j--; k--;

        int left = 0, right = n - 1, mid, count;
        while (left < right) {
            mid = left + (right - left) / 2;
            count = 0;
            for (int x = i; x <= j; x++) {
                if (original[x] <= dogs[mid].value) {
                    count++;
                }
            }
            if (count > k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        printf("%d\n", dogs[left].value);
    }

    return 0;
}