#include <stdio.h>
#define MOD 1000000007

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    long long ans = 0;
    long long power = 1;
    
    // Calculate the number of possible strings of length n
    for (int i = 0; i < n; i++) {
        power = (power * m) % MOD;
    }
    
    // Calculate the expected value of the number of distinct substrings
    for (int i = 1; i <= n; i++) {
        long long ways = power / m;
        long long substrings = power;
        
        // Subtract the number of substrings that are not distinct
        for (int j = 1; j <= i / 2; j++) {
            substrings -= ways / (m - j + 1);
        }
        
        // Add the contribution of substrings of length i
        ans = (ans + substrings % MOD) % MOD;
    }
    
    // Output the result
    printf("%lld\n", ans);
    
    return 0;
}