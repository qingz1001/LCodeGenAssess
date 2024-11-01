#include <stdio.h>

int main() {
    int M, i, sum, start, end;
    scanf("%d", &M);

    // 外层循环从1开始，到M/2+1结束
    for (start = 1; start <= M / 2 + 1; start++) {
        sum = 0;
        // 内层循环从start开始，到M/2+1结束
        for (i = start; i <= M / 2 + 1; i++) {
            sum += i;
            if (sum == M) {
                end = i;
                break;
            } else if (sum > M) {
                break;
            }
        }
        if (sum == M) {
            printf("%d %d\n", start, end);
        }
    }

    return 0;
}