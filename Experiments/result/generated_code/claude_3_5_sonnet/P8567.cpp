#include <stdio.h>
#include <stdint.h>

int64_t f(int64_t x) {
    return __builtin_ctzll(x);
}

int64_t solve(int64_t l, int64_t r) {
    int64_t count = 0;
    int64_t last_one = f(l);
    int64_t next_power = (l | (l - 1)) + 1;
    
    while (next_power <= r) {
        count += next_power - l - 1;
        l = next_power;
        last_one = f(l);
        next_power = (l | (l - 1)) + 1;
    }
    
    for (int64_t i = l; i < r; i++) {
        if (f(i) < f(i + 1)) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int64_t l, r;
        scanf("%lld %lld", &l, &r);
        printf("%lld\n", solve(l, r));
    }
    
    return 0;
}