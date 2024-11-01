#include <stdio.h>

#define MOD 92084931
#define MAXN 200005

long long prefixSum[MAXN];
int n, M;

int main() {
    scanf("%d %d", &n, &M);
    
    long long sum = 0;
    int left = 1, right = 0;
    long long result = 0;
    
    for (int i = 1; i <= n; i++) {
        int num;
        scanf("%d", &num);
        sum += num;
        prefixSum[i] = sum;
        
        while (left <= i && sum > (long long)M * (i - left + 1)) {
            result = (result + i - right) % MOD;
            left++;
            sum -= prefixSum[left - 1] - prefixSum[left - 2];
        }
        
        if (left > right) right = left - 1;
        
        while (right < i && sum + prefixSum[right + 1] - prefixSum[right] > (long long)M * (i - right)) {
            right++;
            sum += prefixSum[right] - prefixSum[right - 1];
        }
    }
    
    printf("%lld\n", result);
    
    return 0;
}