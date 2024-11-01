#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

int catalan_number(int n) {
    if (n == 0 || n == 1) return 1;
    int result = 0;
    for (int i = 0; i < n; i++) {
        result = (result + (long long)catalan_number(i) * catalan_number(n - i - 1)) % MOD;
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Calculate the number of m-ary trees with n nodes
    int num_trees = 0;
    for (int i = 0; i <= n; i++) {
        num_trees = (num_trees + (long long)catalan_number(i) * factorial(m) % MOD) % MOD;
    }
    
    printf("%d\n", num_trees);
    return 0;
}