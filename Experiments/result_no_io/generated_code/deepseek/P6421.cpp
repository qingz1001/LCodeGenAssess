#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    int is_prime[n + 1];
    for (int i = 2; i <= n; i++) {
        is_prime[i] = 1;
    }
    
    int count = 0;
    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) {
            for (int j = p; j <= n; j += p) {
                if (is_prime[j]) {
                    is_prime[j] = 0;
                    count++;
                    if (count == k) {
                        printf("%d\n", j);
                        return 0;
                    }
                }
            }
        }
    }
    
    return 0;
}