#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int N, B;
    scanf("%d %d", &N, &B);
    int heights[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    // 将奶牛的身高从高到低排序
    qsort(heights, N, sizeof(int), compare);

    int sum = 0;
    int count = 0;
    for (int i = 0; i < N; i++) {
        sum += heights[i];
        count++;
        if (sum >= B) {
            printf("%d\n", count);
            break;
        }
    }

    return 0;
}