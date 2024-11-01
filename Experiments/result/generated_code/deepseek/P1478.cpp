#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int effort;
} Apple;

int compare(const void *a, const void *b) {
    Apple *appleA = (Apple *)a;
    Apple *appleB = (Apple *)b;
    return appleA->effort - appleB->effort;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    int a, b;
    scanf("%d %d", &a, &b);

    Apple apples[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &apples[i].height, &apples[i].effort);
    }

    // Sort apples by effort required to pick them
    qsort(apples, n, sizeof(Apple), compare);

    int max_apples = 0;
    int total_effort = 0;

    for (int i = 0; i < n; i++) {
        if (apples[i].height <= a + b) {
            if (total_effort + apples[i].effort <= s) {
                total_effort += apples[i].effort;
                max_apples++;
            } else {
                break;
            }
        }
    }

    printf("%d\n", max_apples);

    return 0;
}