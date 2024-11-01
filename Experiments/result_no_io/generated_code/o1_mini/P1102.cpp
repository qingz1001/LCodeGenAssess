#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Comparator for qsort
int cmp(const void *a, const void *b){
    long long aa = *(long long*)a;
    long long bb = *(long long*)b;
    if(aa < bb) return -1;
    else if(aa > bb) return 1;
    else return 0;
}

// Binary search to find target in array unique[0..m-1]
int binary_search_unique(long long *unique, int m, long long target){
    int left = 0, right = m-1;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(unique[mid] == target) return mid;
        else if(unique[mid] < target) left = mid +1;
        else right = mid -1;
    }
    return -1;
}

int main(){
    int N;
    ll C;
    scanf("%d %lld", &N, &C);
    long long *a = (long long*)malloc(N * sizeof(long long));
    for(int i=0;i<N;i++) scanf("%lld", &a[i]);
    qsort(a, N, sizeof(long long), cmp);
    // Count unique and frequencies
    long long *unique = (long long*)malloc(N * sizeof(long long));
    int *freq = (int*)malloc(N * sizeof(int));
    int m =0;
    unique[m] = a[0];
    freq[m] =1;
    for(int i=1;i<N;i++){
        if(a[i] == unique[m]){
            freq[m]++;
        }
        else{
            m++;
            unique[m] = a[i];
            freq[m] =1;
        }
    }
    m++;
    ll total =0;
    for(int i=0;i<m;i++){
        ll target = unique[i] + C;
        int idx = binary_search_unique(unique, m, target);
        if(idx != -1){
            total += (ll)freq[i] * freq[idx];
        }
    }
    printf("%lld\n", total);
    free(a);
    free(unique);
    free(freq);
    return 0;
}