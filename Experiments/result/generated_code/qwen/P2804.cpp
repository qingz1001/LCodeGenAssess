#include <stdio.h>

#define MOD 92084931

int main() {
    int n, M;
    scanf("%d %d", &n, &M);
    
    long long arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
    }
    
    long long count = 0;
    for (int start = 0; start < n; ++start) {
        long long sum = 0;
        for (int end = start; end < n; ++end) {
            sum += arr[end];
            if ((sum * (end - start + 1)) > (long long)M * (end - start + 1)) {
                count++;
                count %= MOD;
            }
        }
    }
    
    printf("%lld\n", count);
    
    return 0;
}