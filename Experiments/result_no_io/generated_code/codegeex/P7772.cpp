#include <stdio.h>

int main() {
    int A, I;
    scanf("%d %d", &A, &I);

    // 计算最小的N，使得ceil(N/A) >= I
    // ceil(N/A) >= I 等价于 N/A >= I - 1 + (N mod A >= 1)
    // 因此 N >= A * (I - 1) + 1，如果 A * (I - 1) + 1 < A 则 N = A * I
    int N = A * I;
    if (N % A == 0) {
        N -= 1;
    }

    printf("%d\n", N);
    return 0;
}