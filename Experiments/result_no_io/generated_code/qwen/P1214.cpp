#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25
#define MAX_M 250

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Generate the set of double square numbers
    int double_squares[MAX_M * MAX_M];
    int count = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            double_squares[count++] = i * i + j * j;
        }
    }

    // Sort the double square numbers
    qsort(double_squares, count, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // Find all arithmetic progressions of length n
    int found = 0;
    for (int i = 0; i < count - n + 1; i++) {
        for (int j = i + 1; j < count - n + 2; j++) {
            int diff = double_squares[j] - double_squares[i];
            int valid = 1;
            for (int k = 2; k < n; k++) {
                if (double_squares[i + k] != double_squares[i] + k * diff) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                printf("%d %d\n", double_squares[i], diff);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("NONE\n");
    }

    return 0;
}