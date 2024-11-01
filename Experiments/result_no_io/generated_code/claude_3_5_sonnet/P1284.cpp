#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 40

int n;
int lengths[MAX_N];

double calculateArea(int a, int b, int c) {
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    qsort(lengths, n, sizeof(int), compare);

    double maxArea = 0;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (lengths[i] < lengths[j] + lengths[k]) {
                    double area = calculateArea(lengths[i], lengths[j], lengths[k]);
                    if (area > maxArea) {
                        maxArea = area;
                    }
                    break;
                }
            }
        }
    }

    if (maxArea > 0) {
        printf("%d\n", (int)(maxArea * 100));
    } else {
        printf("-1\n");
    }

    return 0;
}