#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int main() {
    int N;
    scanf("%d", &N);

    // 计算最大基值
    int max_base = 0;
    for (int i = 1; i <= N; i++) {
        max_base += i;
        max_base %= MOD;
    }

    printf("%d\n", max_base);
    return 0;
}