#include <stdio.h>

int main() {
    int heights[10];
    int reach;
    int count = 0;

    for (int i = 0; i < 10; i++) {
        scanf("%d", &heights[i]);
    }
    scanf("%d", &reach);

    for (int i = 0; i < 10; i++) {
        if (heights[i] <= reach + 30) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}