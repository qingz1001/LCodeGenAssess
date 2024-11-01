#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int minQueue[MAXN], maxQueue[MAXN];
int minFront = 0, minRear = -1;
int maxFront = 0, maxRear = -1;

void pushMin(int *queue, int *rear, int value) {
    while (*rear >= minFront && queue[*rear] > value) {
        (*rear)--;
    }
    queue[++(*rear)] = value;
}

void popMin(int *queue, int *front) {
    if (minFront <= *front) {
        minFront++;
    }
}

int getMin(int *queue, int front) {
    return queue[front];
}

void pushMax(int *queue, int *rear, int value) {
    while (*rear >= maxFront && queue[*rear] < value) {
        (*rear)--;
    }
    queue[++(*rear)] = value;
}

void popMax(int *queue, int *front) {
    if (maxFront <= *front) {
        maxFront++;
    }
}

int getMax(int *queue, int front) {
    return queue[front];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int minResult[n - k + 1], maxResult[n - k + 1];
    int minIndex = 0, maxIndex = 0;

    for (int i = 0; i < n; i++) {
        pushMin(minQueue, &minRear, a[i]);
        pushMax(maxQueue, &maxRear, a[i]);

        if (i >= k) {
            popMin(minQueue, &minFront);
            popMax(maxQueue, &maxFront);
        }

        if (i >= k - 1) {
            minResult[minIndex++] = getMin(minQueue, minFront);
            maxResult[maxIndex++] = getMax(maxQueue, maxFront);
        }
    }

    for (int i = 0; i < n - k + 1; i++) {
        printf("%d ", minResult[i]);
    }
    printf("\n");

    for (int i = 0; i < n - k + 1; i++) {
        printf("%d ", maxResult[i]);
    }
    printf("\n");

    return 0;
}