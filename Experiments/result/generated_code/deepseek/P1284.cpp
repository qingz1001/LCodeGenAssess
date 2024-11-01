#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

    // Sort the lengths in descending order
    qsort(lengths, n, sizeof(int), compare);

    // Try to form the largest triangle using the first three lengths
    int a = lengths[0], b = lengths[1], c = lengths[2];
    if (a + b > c && a + c > b && b + c > a) {
        // Heron's formula to calculate the area of the triangle
        double s = (a + b + c) / 2.0;
        double area = sqrt(s * (s - a) * (s - b) * (s - c));
        int result = (int)(area * 100);
        printf("%d\n", result);
    } else {
        printf("-1\n");
    }

    return 0;
}