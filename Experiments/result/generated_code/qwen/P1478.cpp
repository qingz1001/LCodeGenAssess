#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int cost;
} Apple;

int compare(const void *a, const void *b) {
    return ((Apple *)b)->cost - ((Apple *)a)->cost;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    int a, b;
    scanf("%d %d", &a, &b);
    Apple apples[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &apples[i].height, &apples[i].cost);
    }

    qsort(apples, n, sizeof(Apple), compare);

    int count = 0;
    for (int i = 0; i < n && s >= 0; i++) {
        int reach = a + b;
        if (apples[i].height <= reach) {
            s -= apples[i].cost;
            if (s >= 0) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}