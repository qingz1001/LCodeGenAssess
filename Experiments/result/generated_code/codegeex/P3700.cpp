#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>

using namespace std;

#define MOD 1000000007
#define MAXN 4000001

long long f[MAXN];
int prime[MAXN];
bool is_prime[MAXN];

// 预处理函数，计算前n个数的最大公约数
void gcd_precompute(int n) {
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!is_prime[i]) {
            prime[++prime[0]] = i;
            f[i] = (long long)i * i % MOD;
        }
        for (int j = 1; j <= prime[0] && i * prime[j] <= n; j++) {
            is_prime[i * prime[j]] = true;
            f[i * prime[j]] = f[i] * f[prime[j]] % MOD;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    gcd_precompute(n);
    
    for (int i = 0; i < m; i++) {
        long long a, b, x, k;
        scanf("%lld %lld %lld %lld", &a, &b, &x, &k);
        
        // 计算修改后的前k行前k列的和
        long long result = 0;
        for (long long j = 1; j <= k; j++) {
            long long g = __gcd(j, a + b - 1);
            long long p = a * b / g;
            long long q = a + b - 1;
            result = (result + f[g] * x % MOD * (p / g) % MOD * (q / g) % MOD) % MOD;
        }
        
        printf("%lld\n", result);
    }
    
    return 0;
}