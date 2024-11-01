#include <stdio.h>

#define MAXN 2000001

long long sum[MAXN];
int phi[MAXN];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        phi[i] = i;
    }
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            sum[j] += (long long)i * phi[j / i];
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    init(n);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += sum[i] - i;
    }
    ans /= 2;
    printf("%lld\n", ans);
    return 0;
}