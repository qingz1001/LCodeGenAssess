#include <stdio.h>

#define MAX_N 2000000000
#define MAX_PRIME 11

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
int max_exp[] = {30, 19, 13, 11, 8, 8, 7, 7, 6, 6, 5};

long long ans = 1;
int max_div = 1;

void dfs(int depth, long long num, int div, int last_exp) {
    if (div > max_div || (div == max_div && num < ans)) {
        if (num <= MAX_N) {
            ans = num;
            max_div = div;
        }
    }
    
    if (depth >= MAX_PRIME) return;
    
    long long p = primes[depth];
    for (int i = 1; i <= max_exp[depth] && i <= last_exp; i++) {
        if (num * p > MAX_N) break;
        dfs(depth + 1, num * p, div * (i + 1), i);
        p *= primes[depth];
    }
}

int main() {
    int N;
    scanf("%d", &N);
    
    dfs(0, 1, 1, 30);
    
    printf("%lld\n", ans);
    
    return 0;
}