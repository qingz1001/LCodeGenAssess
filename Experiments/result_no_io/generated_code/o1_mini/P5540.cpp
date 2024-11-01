#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int u, v, a, b;
} Edge;

int cmp(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if (ea->a != eb->a)
        return ea->a - eb->a;
    return ea->b - eb->b;
}

int parent[200];

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Edge edges[m];
    for(int i=0;i<m;i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
    }
    qsort(edges, m, sizeof(Edge), cmp);
    // Initialize DP
    int MAX_A = 200 * 255;
    int dp[MAX_A+1];
    for(int i=0;i<=MAX_A;i++) dp[i] = 1e9;
    dp[0] = 0;
    // Iterate edges
    for(int i=0;i<m;i++) {
        for(int a = MAX_A - edges[i].a; a >=0; a--){
            if(dp[a] != 1e9 && dp[a + edges[i].a] > dp[a] + edges[i].b){
                dp[a + edges[i].a] = dp[a] + edges[i].b;
            }
        }
    }
    // Find minimum A*B
    ll min_product = (ll)1e18;
    int best_a = 0, best_b = 0;
    for(int a=0;a<=MAX_A;a++) {
        if(dp[a] != 1e9){
            ll product = (ll)a * dp[a];
            if(product < min_product || (product == min_product && a < best_a)){
                min_product = product;
                best_a = a;
                best_b = dp[a];
            }
        }
    }
    printf("%d %d\n", best_a, best_b);
}