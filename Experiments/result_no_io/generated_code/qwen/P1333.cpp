#include <stdio.h>
#include <string.h>

#define MAX_COLORS 26
#define MAX_RODS 250000

int main() {
    char rods[MAX_RODS][3];
    int color_count[MAX_COLORS] = {0};
    int n;

    // Read input
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s %s", rods[i], rods[i] + 2);
        color_count[rods[i][0] - 'a']++;
        color_count[rods[i][2] - 'a']--;
    }

    // Check if the arrangement is possible
    int odd_count = 0;
    for (int i = 0; i < MAX_COLORS; i++) {
        if (color_count[i] != 0) {
            odd_count++;
        }
    }

    if (odd_count == 0 || (odd_count == 2 && n % 2 == 1)) {
        printf("Possible\n");
    } else {
        printf("Impossible\n");
    }

    return 0;
}