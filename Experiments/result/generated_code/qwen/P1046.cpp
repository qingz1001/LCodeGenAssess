#include <stdio.h>

int main() {
    int heights[10];
    int max_height;
    int count = 0;

    for (int i = 0; i < 10; i++) {
        scanf("%d", &heights[i]);
    }
    scanf("%d", &max_height);

    for (int i = 0; i < 10; i++) {
        if (heights[i] <= max_height || heights[i] <= max_height + 30) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}