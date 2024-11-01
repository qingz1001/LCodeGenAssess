#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long val;
    long long count;
} Pair;

// Comparator for qsort
int compare(const void *a, const void *b){
    long long va = (*(long long*)a);
    long long vb = (*(long long*)b);
    if(va < vb) return -1;
    if(va > vb) return 1;
    return 0;
}

// Binary search to find val in array sorted_vals with size n
long long binary_search_val(Pair sorted_vals[], long long n, long long val){
    long long left = 0, right = n-1;
    while(left <= right){
        long long mid = left + (right - left)/2;
        if(sorted_vals[mid].val == val){
            return sorted_vals[mid].count;
        }
        else if(sorted_vals[mid].val < val){
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    return 0;
}

int main(){
    long long N, C;
    scanf("%lld %lld", &N, &C);
    long long *arr = (long long*)malloc(N * sizeof(long long));
    for(long long i=0;i<N;i++) scanf("%lld", &arr[i]);
    qsort(arr, N, sizeof(long long), compare);
    // Count unique values
    long long unique =0;
    Pair *sorted_vals = (Pair*)malloc(N * sizeof(Pair));
    long long current = arr[0];
    long long cnt =1;
    for(long long i=1;i<N;i++){
        if(arr[i] == current){
            cnt++;
        }
        else{
            sorted_vals[unique].val = current;
            sorted_vals[unique].count = cnt;
            unique++;
            current = arr[i];
            cnt =1;
        }
    }
    sorted_vals[unique].val = current;
    sorted_vals[unique].count = cnt;
    unique++;
    long long result =0;
    for(long long i=0;i<unique;i++){
        long long target = sorted_vals[i].val + C;
        long long freq = binary_search_val(sorted_vals, unique, target);
        result += sorted_vals[i].count * freq;
    }
    printf("%lld\n", result);
    free(arr);
    free(sorted_vals);
    return 0;
}