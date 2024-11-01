#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    char necklace[n + 1];
    scanf("%s", necklace);

    int max_count = 0;

    for (int i = 0; i < n; i++) {
        int count = 1;
        int color = necklace[i];

        // Collect beads of the same color on one side
        for (int j = i + 1; j < n; j++) {
            if (necklace[j] == color || necklace[j] == 'w') {
                count++;
            } else {
                break;
            }
        }

        // Collect beads of the same color on the other side
        for (int j = i - 1; j >= 0; j--) {
            if (necklace[j] == color || necklace[j] == 'w') {
                count++;
            } else {
                break;
            }
        }

        max_count = max(max_count, count);
    }

    printf("%d\n", max_count);
    return 0;
}