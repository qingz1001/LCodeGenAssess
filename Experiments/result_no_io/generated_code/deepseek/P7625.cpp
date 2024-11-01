#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M, J;
    scanf("%d %d", &N, &M);
    scanf("%d", &J);

    int position = 1; // 初始位置，船在最左边
    int distance = 0;

    for (int i = 0; i < J; i++) {
        int apple_column;
        scanf("%d", &apple_column);

        // 计算船需要移动的距离
        if (apple_column < position) {
            distance += position - apple_column;
            position = apple_column;
        } else if (apple_column > position + M - 1) {
            distance += apple_column - (position + M - 1);
            position = apple_column - M + 1;
        }
    }

    printf("%d\n", distance);

    return 0;
}