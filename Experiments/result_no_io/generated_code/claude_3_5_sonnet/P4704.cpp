#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200001

typedef struct {
    int start;
    int end;
} Rope;

int compare(const void *a, const void *b) {
    Rope *ropeA = (Rope *)a;
    Rope *ropeB = (Rope *)b;
    if (ropeA->start != ropeB->start)
        return ropeA->start - ropeB->start;
    return ropeA->end - ropeB->end;
}

int main() {
    int n;
    scanf("%d", &n);

    Rope ropes[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ropes[i].start, &ropes[i].end);
        if (ropes[i].start > ropes[i].end) {
            int temp = ropes[i].start;
            ropes[i].start = ropes[i].end;
            ropes[i].end = temp;
        }
    }

    qsort(ropes, n, sizeof(Rope), compare);

    int cuts = 1;
    int max_end = ropes[0].end;

    for (int i = 1; i < n; i++) {
        if (ropes[i].start > max_end) {
            cuts++;
            max_end = ropes[i].end;
        } else if (ropes[i].end > max_end) {
            max_end = ropes[i].end;
        }
    }

    printf("%d\n", cuts);

    return 0;
}