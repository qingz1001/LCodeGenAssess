#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 计算在字典序排列中，第k个数的位置
long long q(long long k, long long n) {
    char s[20];
    sprintf(s, "%lld", k);
    int len = strlen(s);
    long long ans = 0;
    for (int i = 0; i < len; i++) {
        ans = ans * 10 + s[i] - '0';
        if (ans > n) return 0;
    }
    return ans;
}

// 递归查找最小的n，使得q(n, k) = m
long long findN(long long k, long long m, long long l, long long r) {
    if (l > r) return 0;
    long long mid = (l + r) / 2;
    long long val = q(mid, k);
    if (val == m) return mid;
    else if (val < m) return findN(k, m, mid + 1, r);
    else return findN(k, m, l, mid - 1);
}

int main() {
    long long k, m;
    scanf("%lld%lld", &k, &m);
    long long ans = findN(k, m, k, 1e18);
    printf("%lld\n", ans);
    return 0;
}