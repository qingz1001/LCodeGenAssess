#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long max_long(long long a, long long b) {
    return a > b ? a : b;
}

int main(){
    int n;
    scanf("%d", &n);
    int *a = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    // Duplicate the array to handle circularity
    int *arr = (int*)malloc(sizeof(int)*2*n);
    for(int i=0;i<2*n;i++) arr[i] = a[i%n];
    free(a);
    // Compute prefix max subarray sums
    long long *prefix = (long long*)malloc(sizeof(long long)*(2*n));
    long long current = arr[0];
    prefix[0] = current;
    for(int i=1;i<2*n;i++){
        if(current < 0) current = arr[i];
        else current += arr[i];
        prefix[i] = max_long(prefix[i-1], current);
    }
    // Compute suffix max subarray sums
    long long *suffix = (long long*)malloc(sizeof(long long)*(2*n));
    current = arr[2*n-1];
    suffix[2*n-1] = current;
    for(int i=2*n-2;i>=0;i--){
        if(current < 0) current = arr[i];
        else current += arr[i];
        suffix[i] = max_long(suffix[i+1], current);
    }
    // Find the maximum sum of two non-overlapping subarrays
    long long result = LLONG_MIN;
    for(int i=0;i<n;i++){
        long long first = prefix[i];
        long long second = suffix[i+1];
        if(i +1 < 2*n)
            result = max_long(result, first + second);
    }
    // Also consider splitting the array differently
    for(int i=n;i<2*n;i++){
        long long first = prefix[i];
        long long second = suffix[i+1];
        if(i +1 < 2*n)
            result = max_long(result, first + second);
    }
    printf("%lld\n", result);
    free(arr);
    free(prefix);
    free(suffix);
    return 0;
}