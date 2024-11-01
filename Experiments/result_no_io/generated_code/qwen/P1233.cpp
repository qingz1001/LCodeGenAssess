#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int length;
    int width;
} Stick;

int compare(const void *a, const void *b) {
    Stick *stickA = (Stick *)a;
    Stick *stickB = (Stick *)b;
    if (stickA->length != stickB->length) {
        return stickB->length - stickA->length;
    }
    return stickB->width - stickA->width;
}

int main() {
    int n;
    scanf("%d", &n);
    Stick sticks[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &sticks[i].length, &sticks[i].width);
    }

    qsort(sticks, n, sizeof(Stick), compare);

    int totalTime = 1;
    for (int i = 1; i < n; i++) {
        if (sticks[i].length < sticks[i - 1].length || sticks[i].width < sticks[i - 1].width) {
            totalTime++;
        }
    }

    printf("%d\n", totalTime);
    return 0;
}