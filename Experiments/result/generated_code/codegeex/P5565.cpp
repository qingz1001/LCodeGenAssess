#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 998244353

typedef long long ll;

ll pow2[400005];

// 计算和谐度
ll calculateHarmony(const char *expression, int length) {
    // 实现计算和谐度的逻辑
    // ...
    return 0;
}

int main() {
    int m;
    scanf("%d", &m);

    char expression[400005];
    scanf("%s", expression);

    pow2[0] = 1;
    for (int i = 1; i < 400005; i++) {
        pow2[i] = (pow2[i-1] * 2) % MOD;
    }

    for (int i = 0; i < m; i++) {
        int a;
        char b;
        scanf("%d %c", &a, &b);

        // 修改表达式
        expression[a-1] = b;

        // 计算和谐度
        ll harmony = calculateHarmony(expression, strlen(expression));
        printf("%lld\n", harmony);
    }

    return 0;
}