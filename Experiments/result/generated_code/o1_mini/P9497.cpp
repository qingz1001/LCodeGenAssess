#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    long long aa = *(long long*)a;
    long long bb = *(long long*)b;
    if(aa < bb) return -1;
    if(aa > bb) return 1;
    return 0;
}

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    long long *arr = (long long*)malloc((long long)n * n * sizeof(long long));
    for(int i=0;i<n*n;i++) scanf("%lld", &arr[i]);
    qsort(arr, n*n, sizeof(long long), cmp);
    while(q--){
        long long v;
        scanf("%lld", &v);
        int left=0, right=n*n;
        while(left < right){
            int mid = left + (right - left)/2;
            if(arr[mid] >= v) right = mid;
            else left = mid +1;
        }
        long long count = n*n - left;
        if(count > n) count = n;
        printf("%lld\n", count);
    }
    free(arr);
    return 0;
}