#include <stdio.h>

int main() {
    int N, B;
    scanf("%d %d", &N, &B);

    int heights[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    // 对奶牛的身高进行从高到低排序
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (heights[i] < heights[j]) {
                int temp = heights[i];
                heights[i] = heights[j];
                heights[j] = temp;
            }
        }
    }

    int sum = 0;
    int count = 0;
    for (int i = 0; i < N; i++) {
        sum += heights[i];
        count++;
        if (sum >= B) {
            break;
        }
    }

    printf("%d\n", count);
    return 0;
}