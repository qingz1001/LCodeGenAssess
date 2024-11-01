#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    // Initialize adjacency list
    // Maximum edges: 2*(n-1)
    int max_edges = 2 * (n -1);
    int *edge_to = (int*)malloc(sizeof(int)*max_edges);
    int *edge_next = (int*)malloc(sizeof(int)*max_edges);
    int *head = (int*)calloc(n+1, sizeof(int));
    for(int i=0;i<max_edges;i++) head[i] = -1;
    int edge_cnt =0;
    // Read edges
    for(int i=0;i<n-1;i++){
        int u, v;
        scanf("%d%d", &u, &v);
        edge_to[edge_cnt] = v;
        edge_next[edge_cnt] = head[u];
        head[u] = edge_cnt++;
        edge_to[edge_cnt] = u;
        edge_next[edge_cnt] = head[v];
        head[v] = edge_cnt++;
    }
    // Read weights
    int *W = (int*)malloc(sizeof(int)*(n+1));
    for(int i=1;i<=n;i++) scanf("%d", &W[i]);
    ll sum_total =0;
    ll max_total =0;
    for(int w=1; w<=n; w++){
        // Traverse neighbors and collect sum, sum of squares, and top two
        ll S_w =0;
        ll S2_w =0;
        int max1=0, max2=0;
        int e = head[w];
        int degree =0;
        while(e != -1){
            int u = edge_to[e];
            S_w += W[u];
            S2_w += (ll)W[u] * W[u];
            if(W[u] > max1){
                max2 = max1;
                max1 = W[u];
            }
            else if(W[u] > max2){
                max2 = W[u];
            }
            degree++;
            e = edge_next[e];
        }
        if(degree >=2){
            ll S_w_mod = S_w % 10007;
            ll S_w_sq_mod = (S_w_mod * S_w_mod) % 10007;
            ll S2_w_mod = S2_w % 10007;
            ll contrib = (S_w_sq_mod - S2_w_mod + 10007) % 10007;
            sum_total = (sum_total + contrib) % 10007;
            ll product = (ll)max1 * max2;
            if(product > max_total) max_total = product;
        }
    }
    printf("%lld %lld\n", max_total, sum_total);
    // Free memory
    free(edge_to);
    free(edge_next);
    free(head);
    free(W);
    return 0;
}