#include <stdio.h>

#define MOD 92084931

int main() {
    int n;
    long long M;
    scanf("%d %lld", &n, &M);
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    long long count = 0;
    long long sum = 0;
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        sum += arr[right];
        
        while (sum > M * (right - left + 1)) {
            count = (count + (right - left + 1)) % MOD;
            sum -= arr[left];
            left++;
        }
    }
    
    while (left < n) {
        count = (count + (n - left)) % MOD;
        left++;
    }
    
    printf("%lld\n", count);
    
    return 0;
}