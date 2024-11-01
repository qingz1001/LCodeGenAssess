#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

// Structure to hold each mineral's weight and value
typedef struct {
    int w;
    int v;
} Mineral;

// Comparator for sorting in descending order of weight
int compare(const void *a, const void *b) {
    Mineral *ma = (Mineral *)a;
    Mineral *mb = (Mineral *)b;
    if (mb->w != ma->w)
        return mb->w - ma->w;
    return 0;
}

int main(){
    int n, m;
    ll s;
    scanf("%d %d %lld", &n, &m, &s);
    
    Mineral *minerals = (Mineral *)malloc(n * sizeof(Mineral));
    for(int i=0;i<n;i++) {
        scanf("%d %d", &minerals[i].w, &minerals[i].v);
    }
    
    // Initialize difference array
    ll *delta = (ll *)calloc(n+2, sizeof(ll));
    for(int i=0;i<m;i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        delta[l] +=1;
        if(r+1 <= n)
            delta[r+1] -=1;
    }
    
    // Compute count_j using prefix sums
    ll *count = (ll *)malloc((n+1) * sizeof(ll));
    count[0] = 0;
    for(int i=1;i<=n;i++) {
        count[i] = count[i-1] + delta[i];
    }
    
    free(delta);
    
    // Sort minerals in descending order of weight
    qsort(minerals, n, sizeof(Mineral), compare);
    
    ll y = 0;
    ll min_diff = llabs(s - y);
    int i = 0;
    while(i < n){
        int current_w = minerals[i].w;
        // Process all minerals with current_w
        while(i < n && minerals[i].w == current_w){
            y += (minerals[i].v) * count[i+1];
            i++;
        }
        ll diff = llabs(s - y);
        if(diff < min_diff){
            min_diff = diff;
        }
    }
    
    // After all, y includes all possible, compare with last y
    printf("%lld\n", min_diff);
    
    free(minerals);
    free(count);
    return 0;
}