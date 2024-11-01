#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M, J;
    scanf("%d %d", &N, &M);
    scanf("%d", &J);

    int apples[J];
    for (int i = 0; i < J; i++) {
        scanf("%d", &apples[i]);
    }

    int current_position = 1; // 初始位置在最左边
    int total_distance = 0;

    for (int i = 0; i < J; i++) {
        int apple_position = apples[i];
        if (apple_position < current_position) {
            total_distance += current_position - apple_position;
            current_position = apple_position;
        } else if (apple_position > current_position + M - 1) {
            total_distance += apple_position - (current_position + M - 1);
            current_position = apple_position - M + 1;
        }
    }

    printf("%d\n", total_distance);

    return 0;
}