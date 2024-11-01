#include <stdio.h>

#define MAX_FACTORS 10
#define MAX_PRIMES 10

long long n;
int primes[MAX_PRIMES] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int max_factors[MAX_FACTORS];
int current_factors[MAX_FACTORS];
long long max_num = 1;
int max_divisors = 1;

void dfs(int depth, long long current_num, int current_divisors, int last_factor) {
    if (current_num > n) return;
    
    if (current_divisors > max_divisors || (current_divisors == max_divisors && current_num < max_num)) {
        max_divisors = current_divisors;
        max_num = current_num;
        for (int i = 0; i < depth; i++) {
            max_factors[i] = current_factors[i];
        }
    }
    
    if (depth == MAX_FACTORS) return;
    
    for (int i = 1; i <= last_factor; i++) {
        if (current_num * primes[depth] > n) break;
        current_factors[depth] = i;
        dfs(depth + 1, current_num * primes[depth], current_divisors * (i + 1), i);
    }
}

int main() {
    scanf("%lld", &n);
    dfs(0, 1, 1, 30);
    printf("%lld\n", max_num);
    return 0;
}