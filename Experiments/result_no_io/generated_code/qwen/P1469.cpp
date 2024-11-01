#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *sticks = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
    }

    // 使用异或运算来找出唯一的那根筷子
    int unique = 0;
    for (int i = 0; i < n; i++) {
        unique ^= sticks[i];
    }

    printf("%d\n", unique);

    free(sticks);
    return 0;
}