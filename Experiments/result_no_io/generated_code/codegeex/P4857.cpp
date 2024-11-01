#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll a[k];
    for (ll i = 0; i < k; i++) {
        scanf("%lld", &a[i]);
    }

    // 按照检票员一次检验的长度进行排序
    for (ll i = 0; i < k - 1; i++) {
        for (ll j = i + 1; j < k; j++) {
            if (a[i] > a[j]) {
                ll temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    ll current_position = 0;
    ll command_count = 0;
    ll result[k];

    // 遍历每个检票员，计算他们的最后一步是第几次命令
    for (ll i = 0; i < k; i++) {
        while (current_position < a[i]) {
            current_position += a[0];
            command_count++;
        }
        result[i] = command_count;
        current_position = a[i];
        command_count++;
    }

    // 输出结果
    for (ll i = 0; i < k; i++) {
        printf("%lld ", result[i]);
    }
    printf("\n");

    return 0;
}