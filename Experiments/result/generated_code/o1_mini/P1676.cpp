#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    long long l = *(long long *)a;
    long long r = *(long long *)b;
    if (l < r) return -1;
    if (l > r) return 1;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    long long *arr = (long long *)malloc(n * sizeof(long long));
    for(int i=0;i<n;i++) scanf("%lld", &arr[i]);
    qsort(arr, n, sizeof(long long), compare);
    long long left = 0;
    long long right = arr[n-1] - arr[0];
    long long result = 0;
    while(left <= right){
        long long mid = left + (right - left) / 2;
        int count = 1;
        long long last = arr[0];
        for(int i=1;i<n;i++){
            if(arr[i] - last >= mid){
                count++;
                last = arr[i];
                if(count >= m) break;
            }
        }
        if(count >= m){
            result = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    printf("%lld\n", result);
    free(arr);
    return 0;
}