#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_SIZE 30

int main() {
    int n;
    while (scanf("%d", &n) != EOF && n != 0) {
        int sizes[MAX_N];
        for (int i = 0; i < n; ++i) {
            scanf("%d", &sizes[i]);
        }

        // Sort the squares by their size in ascending order
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - 1 - i; ++j) {
                if (sizes[j] > sizes[j + 1]) {
                    int temp = sizes[j];
                    sizes[j] = sizes[j + 1];
                    sizes[j + 1] = temp;
                }
            }
        }

        // Determine which squares can be seen
        int visible[MAX_N];
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (i == 0 || sizes[i] > sizes[i - 1]) {
                visible[count++] = i + 1;
            }
        }

        // Output the result
        for (int i = 0; i < count; ++i) {
            printf("%d%s", visible[i], i == count - 1 ? "\n" : " ");
        }
    }
    return 0;
}