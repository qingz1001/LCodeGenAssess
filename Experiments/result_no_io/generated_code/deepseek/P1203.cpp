#include <stdio.h>
#include <string.h>

#define MAXN 350

int max(int a, int b) {
    return a > b ? a : b;
}

int count_beads(char necklace[], int n, int start) {
    int left = start;
    int right = (start + 1) % n;
    char left_color = necklace[left];
    char right_color = necklace[right];
    int left_count = 0;
    int right_count = 0;

    // Count beads to the left
    while (left != right) {
        if (left_color == 'w') {
            left_color = necklace[left];
        }
        if (necklace[left] == left_color || necklace[left] == 'w') {
            left_count++;
            left = (left - 1 + n) % n;
        } else {
            break;
        }
    }

    // Count beads to the right
    while (right != left) {
        if (right_color == 'w') {
            right_color = necklace[right];
        }
        if (necklace[right] == right_color || necklace[right] == 'w') {
            right_count++;
            right = (right + 1) % n;
        } else {
            break;
        }
    }

    return left_count + right_count;
}

int main() {
    int n;
    char necklace[MAXN];
    scanf("%d", &n);
    scanf("%s", necklace);

    int max_beads = 0;
    for (int i = 0; i < n; i++) {
        max_beads = max(max_beads, count_beads(necklace, n, i));
    }

    printf("%d\n", max_beads);
    return 0;
}