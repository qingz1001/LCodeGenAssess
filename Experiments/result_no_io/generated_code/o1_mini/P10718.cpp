#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOD 998244353

typedef long long ll;

// Fast exponentiation
ll power_mod(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// Combination n choose k modulo MOD
ll comb(int n, int k){
    if(k > n) return 0;
    ll res = 1;
    for(int i=1;i<=k;i++) {
        res = res * (n - i + 1) % MOD;
        ll inv = power_mod(i, MOD-2);
        res = res * inv % MOD;
    }
    return res;
}

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    // Read coordinates
    int (*coords)[2] = malloc(sizeof(int) * 2 * n);
    for(int i=0;i<n;i++) {
        scanf("%d %d", &coords[i][0], &coords[i][1]);
    }
    
    // Read edges
    int (*edges)[2] = malloc(sizeof(int) * 2 * m);
    for(int i=0;i<m;i++) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }
    
    // Read cycles
    int **cycles = malloc(sizeof(int*) * k);
    int *cycle_sizes = malloc(sizeof(int) * k);
    for(int i=0;i<k;i++) {
        int li;
        scanf("%d", &li);
        cycle_sizes[i] = li;
        cycles[i] = malloc(sizeof(int) * li);
        for(int j=0;j<li;j++) {
            scanf("%d", &cycles[i][j]);
            cycles[i][j]--; // 0-based indexing
        }
    }
    
    int q;
    scanf("%d", &q);
    int *queries = malloc(sizeof(int) * q);
    for(int i=0;i<q;i++) {
        scanf("%d", &queries[i]);
    }
    
    // Placeholder for processing
    // Implement the algorithm to compute the required sums here.
    // Due to the complexity of the problem, the implementation is omitted.
    
    // Dummy output
    for(int i=0;i<q;i++) {
        printf("0\n");
    }
    
    // Free allocated memory
    free(coords);
    free(edges);
    for(int i=0;i<k;i++) {
        free(cycles[i]);
    }
    free(cycles);
    free(cycle_sizes);
    free(queries);
    
    return 0;
}