#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Comparator function for qsort
int cmp(const void *a, const void *b) {
    uint64_t ua = *(uint64_t*)a;
    uint64_t ub = *(uint64_t*)b;
    if (ua < ub) return -1;
    if (ua > ub) return 1;
    return 0;
}

// Custom binary search to handle __int128 key
int binary_search_custom(uint64_t *a, int n, __int128 key) {
    int left = 0, right = n - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if ((__int128)a[mid] == key)
            return mid;
        else if ((__int128)a[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main(){
    int n;
    int k;
    if (scanf("%d %d", &n, &k) != 2){
        return 1;
    }

    uint64_t *a = (uint64_t*)malloc(n * sizeof(uint64_t));
    if (a == NULL){
        return 1;
    }

    for(int i=0;i<n;i++){
        if (scanf("%llu", &a[i]) !=1){
            free(a);
            return 1;
        }
    }

    qsort(a, n, sizeof(uint64_t), cmp);

    bool *excluded = (bool*)calloc(n, sizeof(bool));
    if (excluded == NULL){
        free(a);
        return 1;
    }

    int count = 0;
    for(int i=0;i<n;i++){
        if (!excluded[i]){
            count++;
            __int128 y = (__int128)k * ( (__int128)a[i]);
            // If y exceeds uint64_t, it won't be in the array
            if (y <= UINT64_MAX){
                int pos = binary_search_custom(a, n, y);
                if (pos != -1){
                    excluded[pos] = true;
                }
            }
        }
    }

    printf("%d\n", count);

    free(a);
    free(excluded);
    return 0;
}