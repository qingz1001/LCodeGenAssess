#include <stdio.h>

int main() {
    int apples[10];
    int max_height, count = 0;

    for (int i = 0; i < 10; i++) {
        scanf("%d", &apples[i]);
    }

    scanf("%d", &max_height);

    max_height += 30; // 加上板凳的高度

    for (int i = 0; i < 10; i++) {
        if (apples[i] <= max_height) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}