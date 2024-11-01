#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    int* a = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &a[i]);

    // Duplicate the array to handle circularity
    int* double_a = (int*)malloc(2*n * sizeof(int));
    for(int i=0;i<2*n;i++) double_a[i] = a[i % n];

    // Compute prefix sums
    ll* prefix = (ll*)malloc((2*n+1) * sizeof(ll));
    prefix[0] = 0;
    for(int i=0;i<2*n;i++) prefix[i+1] = prefix[i] + double_a[i];

    // For each possible window of length <=n, find max subarray ending at each position
    ll max_left[2*n];
    ll current_max = double_a[0];
    max_left[0] = current_max;
    for(int i=1;i<2*n;i++){
        if (current_max < 0) current_max = double_a[i];
        else current_max += double_a[i];
        if (current_max > max_left[i-1]) max_left[i] = current_max;
        else max_left[i] = max_left[i-1];
    }

    // Similarly, find max subarray starting at each position
    ll max_right[2*n];
    current_max = double_a[2*n-1];
    max_right[2*n-1] = current_max;
    for(int i=2*n-2;i>=0;i--){
        if (current_max < 0) current_max = double_a[i];
        else current_max += double_a[i];
        if (current_max > max_right[i+1]) max_right[i] = current_max;
        else max_right[i] = max_right[i+1];
    }

    // Now, find the maximum sum of two non-overlapping subarrays within n window
    ll result = -__LONG_LONG_MAX__;
    for(int i=0;i<n;i++){
        // First subarray ends at i, second starts at i+1 to i+n-1
        if(i < 2*n-1){
            ll first = max_left[i];
            ll second = max_right[i+1];
            result = first + second > result ? first + second : result;
        }
    }

    printf("%lld\n", result);

    free(a);
    free(double_a);
    free(prefix);
    return 0;
}