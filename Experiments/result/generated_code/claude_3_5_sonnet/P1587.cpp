#include <stdio.h>
#include <string.h>

#define MAX_N 1000000000
#define MAX_K 2000

int n, m, k;
int phi[MAX_K + 1];
int cnt[MAX_K + 1];

void init_phi() {
    for (int i = 1; i <= k; i++) {
        phi[i] = i;
    }
    for (int i = 2; i <= k; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= k; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int get_cycle_length(int x, int y) {
    int g = gcd(x, y);
    y /= g;
    int res = 1;
    while (y % k == 0) {
        y /= k;
    }
    for (int i = 2; i * i <= y; i++) {
        if (y % i == 0) {
            int cnt = 0;
            while (y % i == 0) {
                y /= i;
                cnt++;
            }
            int len = 1;
            while (cnt--) {
                len *= i;
            }
            res = res / gcd(res, phi[i]) * phi[i];
        }
    }
    if (y > 1) {
        res = res / gcd(res, phi[y]) * phi[y];
    }
    return res;
}

long long solve() {
    init_phi();
    memset(cnt, 0, sizeof(cnt));
    
    long long ans = 0;
    for (int y = 1; y <= m; y++) {
        for (int x = 1; x <= n && x <= y; x++) {
            if (gcd(x, y) == 1) {
                int len = get_cycle_length(x, y);
                if (len <= k) {
                    cnt[len]++;
                }
            }
        }
    }
    
    for (int i = 1; i <= k; i++) {
        ans += cnt[i];
    }
    
    return ans;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    printf("%lld\n", solve());
    return 0;
}