#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500005
#define LL long long

int n, k;
LL m[MAX_N];

int check(LL p) {
    int shots = 0;
    LL damage[MAX_N];
    memset(damage, 0, sizeof(damage));
    
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            damage[i] += damage[i-1];
        }
        if (damage[i] >= m[i]) continue;
        
        LL remain = m[i] - damage[i];
        int need = (remain + p - 1) / p;
        shots += need;
        if (shots > k) return 0;
        
        damage[i] += (LL)need * p;
        for (int j = i + 1; j < n && j - i <= p; j++) {
            damage[j] += (LL)need * (p - (j - i) * (j - i));
        }
    }
    return 1;
}

LL binary_search() {
    LL left = 1, right = 1e10;
    while (left < right) {
        LL mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &m[i]);
    }
    
    printf("%lld\n", binary_search());
    return 0;
}