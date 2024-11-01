#include <stdio.h>
#include <string.h>

#define MAX_N 350

int main() {
    int n;
    char necklace[MAX_N + 1];

    scanf("%d %s", &n, necklace);

    int max_collected = 0;

    for (int i = 0; i < n; i++) {
        int collected = 0;
        char current_color = necklace[i];
        int start = i;

        for (int j = i; j < n + i; j++) {
            char color = necklace[j % n];
            if (color == 'w') continue; // Skip white beads
            if (color == current_color) {
                collected++;
            } else {
                break;
            }
        }

        max_collected = collected > max_collected ? collected : max_collected;
    }

    printf("%d\n", max_collected);

    return 0;
}