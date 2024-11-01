#include <stdio.h>
#include <string.h>

typedef long long ll;

ll n;
char num[100001];

int main() {
    // 读取输入的数字
    scanf("%s", num);
    n = strlen(num);

    // 计算可能的摆放大阵的种数
    ll result = 1;
    for (int i = 0; i < n; i++) {
        result *= 5;
    }

    // 输出结果
    printf("%lld\n", result);

    return 0;
}