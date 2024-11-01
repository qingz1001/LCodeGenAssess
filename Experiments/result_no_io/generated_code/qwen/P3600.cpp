#include <stdio.h>
#include <stdlib.h>

#define MOD 666623333

typedef struct {
    int value;
    int index;
} Element;

int compare(const void *a, const void *b) {
    return ((Element *)a)->value - ((Element *)b)->value;
}

int main() {
    int n, x, q;
    scanf("%d %d %d", &n, &x, &q);

    Element elements[n];
    for (int i = 0; i < n; i++) {
        elements[i].value = rand() % x + 1;
        elements[i].index = i + 1;
    }

    qsort(elements, n, sizeof(Element), compare);

    int result = 0;
    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--;
        r--;

        int min_value = INT_MAX;
        for (int j = l; j <= r; j++) {
            if (elements[j].index >= l && elements[j].index <= r) {
                min_value = elements[j].value;
                break;
            }
        }

        if (min_value > result) {
            result = min_value;
        }
    }

    printf("%d\n", result);

    return 0;
}