#include <stdio.h>

#define MAX_N 1001

int main() {
    int n, k;
    int sieve[MAX_N] = {0};
    int count = 0;
    
    scanf("%d %d", &n, &k);
    
    for (int i = 2; i <= n; i++) {
        if (sieve[i] == 0) {
            for (int j = i; j <= n; j += i) {
                if (sieve[j] == 0) {
                    sieve[j] = 1;
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