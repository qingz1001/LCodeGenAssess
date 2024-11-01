#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int n;
    scanf("%d", &n);
    int lengths[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    qsort(lengths, n, sizeof(int), compare);

    int max_area = -1;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                int a = lengths[i];
                int b = lengths[j];
                int c = lengths[k];
                if (a + b > c && a + c > b && b + c > a) {
                    double p = (a + b + c) / 2.0;
                    double area = sqrt(p * (p - a) * (p - b) * (p - c));
                    int rounded_area = (int)(area * 100);
                    if (rounded_area > max_area) {
                        max_area = rounded_area;
                    }
                }
            }
        }
    }

    printf("%d\n", max_area);
    return 0;
}