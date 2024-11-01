#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *lengths = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    // Sort the lengths in non-decreasing order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (lengths[i] > lengths[j]) {
                int temp = lengths[i];
                lengths[i] = lengths[j];
                lengths[j] = temp;
            }
        }
    }

    int max_area = -1;
    // Try all combinations of three lengths to form a triangle
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (lengths[i] + lengths[j] > lengths[k]) {
                    int s = (lengths[i] + lengths[j] + lengths[k]) / 2;
                    int area_squared = s * (s - lengths[i]) * (s - lengths[j]) * (s - lengths[k]);
                    if (area_squared > 0) {
                        int area = (int)sqrt(area_squared);
                        if (area * area == area_squared) {
                            max_area = area * 100;
                            break;
                        }
                    }
                }
            }
            if (max_area != -1) break;
        }
        if (max_area != -1) break;
    }

    printf("%d\n", max_area);

    free(lengths);
    return 0;
}