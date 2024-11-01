#include <stdio.h>
#include <string.h>

#define MAX_COLORS 100
#define MAX_RODS 250000

typedef struct {
    char color1[MAX_COLORS];
    char color2[MAX_COLORS];
} Rod;

int main() {
    int n;
    scanf("%d", &n);
    Rod rods[MAX_RODS];

    for (int i = 0; i < n; ++i) {
        scanf("%s %s", rods[i].color1, rods[i].color2);
    }

    int count[MAX_COLORS] = {0};
    for (int i = 0; i < n; ++i) {
        if (strcmp(rods[i].color1, rods[i].color2) == 0) {
            continue;
        }
        count[rods[i].color1[0]]++;
        count[rods[i].color2[0]]--;
    }

    int odd_count = 0;
    for (int i = 0; i < MAX_COLORS; ++i) {
        if (count[i] != 0 && count[i] % 2 != 0) {
            odd_count++;
        }
    }

    if (odd_count == 0 || (odd_count == 2 && n % 2 == 0)) {
        printf("Possible\n");
    } else {
        printf("Impossible\n");
    }

    return 0;
}