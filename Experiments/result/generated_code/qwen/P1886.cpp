#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int minQueue[MAXN], maxQueue[MAXN];
int minFront = 0, minRear = 0;
int maxFront = 0, maxRear = 0;

void pushMin(int *queue, int *rear, int value) {
    while (*rear > 0 && queue[*rear - 1] > value) {
        (*rear)--;
    }
    queue[(*rear)++] = value;
}

void popMin(int *queue, int *front, int value) {
    if (*front == value) {
        (*front)++;
    }
}

void pushMax(int *queue, int *rear, int value) {
    while (*rear > 0 && queue[*rear - 1] < value) {
        (*rear)--;
    }
    queue[(*rear)++] = value;
}

void popMax(int *queue, int *front, int value) {
    if (*front == value) {
        (*front)++;
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int minValues[n - k + 1], maxValues[n - k + 1];
    int minIndex = 0, maxIndex = 0;

    for (int i = 1; i <= n; i++) {
        pushMin(minQueue, &minRear, a[i]);
        pushMax(maxQueue, &maxRear, a[i]);

        if (i >= k) {
            minValues[minIndex] = minQueue[minFront];
            maxValues[maxIndex] = maxQueue[maxFront];

            popMin(minQueue, &minFront, a[i - k + 1]);
            popMax(maxQueue, &maxFront, a[i - k + 1]);

            minIndex++;
            maxIndex++;
        }
    }

    for (int i = 0; i < n - k + 1; i++) {
        printf("%d ", minValues[i]);
    }
    printf("\n");

    for (int i = 0; i < n - k + 1; i++) {
        printf("%d ", maxValues[i]);
    }
    printf("\n");

    return 0;
}