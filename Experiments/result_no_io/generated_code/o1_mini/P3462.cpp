#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Comparator for ascending order
int cmp_asc(const void *a, const void *b) {
    uint32_t va = *(uint32_t*)a;
    uint32_t vb = *(uint32_t*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int main(){
    int n, m;
    if(scanf("%d %d", &n, &m)!=2){
        return 1;
    }
    uint32_t *w = (uint32_t*)malloc(n * sizeof(uint32_t));
    uint32_t *s = (uint32_t*)malloc(m * sizeof(uint32_t));
    for(int i=0;i<n;i++) scanf("%u", &w[i]);
    for(int i=0;i<m;i++) scanf("%u", &s[i]);
    // Sort weights ascendingly
    qsort(s, m, sizeof(uint32_t), cmp_asc);
    // Compute prefix sums
    uint64_t *prefix = (uint64_t*)malloc((m+1) * sizeof(uint64_t));
    prefix[0] = 0;
    for(int i=0;i<m;i++) prefix[i+1] = prefix[i] + s[i];
    // Sort containers ascendingly
    qsort(w, n, sizeof(uint32_t), cmp_asc);
    int j = 0;
    for(int i=0;i<n && j<m;i++){
        uint32_t wi = w[i];
        // Binary search for maximum k
        int low = 0;
        int high = m - j;
        while(low < high){
            int mid = (low + high + 1) / 2;
            if(j + mid > m){
                high = mid -1;
                continue;
            }
            uint64_t sum = prefix[j + mid] - prefix[j];
            if(sum <= wi){
                low = mid;
            }
            else{
                high = mid -1;
            }
        }
        j += low;
    }
    printf("%d\n", j);
    free(w);
    free(s);
    free(prefix);
    return 0;
}