#include <stdio.h>

int main() {
    long long n, p, k;
    scanf("%lld %lld %lld", &n, &p, &k);

    // 计算光经过 k 次反射后的位置
    // 每次反射相当于将光的位置加上 p，然后对 n 取模
    long long t = p;
    for (long long i = 0; i < k; i++) {
        t = (t + p) % n;
    }

    printf("%lld\n", t);
    return 0;
}