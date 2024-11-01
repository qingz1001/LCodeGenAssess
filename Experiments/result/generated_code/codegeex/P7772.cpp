#include <stdio.h>

int main() {
    int A, I, N;
    scanf("%d %d", &A, &I);

    // 循环查找最小的N，使得ceil(N/A) >= I
    for (N = 1; ; N++) {
        if ((N + A - 1) / A >= I) { // 使用整数除法，并加上A-1来确保向上取整
            break;
        }
    }

    printf("%d\n", N);
    return 0;
}