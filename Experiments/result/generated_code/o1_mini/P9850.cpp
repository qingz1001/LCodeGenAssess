#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Function to calculate n choose k
ll comb(ll n, ll k){
    if(n < k) return 0;
    if(k == 0) return 1;
    if(k ==1) return n;
    if(k ==2) return n*(n-1)/2;
    if(k ==3) return n*(n-1)*(n-2)/6;
    if(k ==4) return n*(n-1)*(n-2)*(n-3)/24;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Allocate memory for adjacency list
    // To save space, use a packed array and pointers
    // Since m <= 200000, each node can have up to m neighbors
    // Use dynamic allocation
    // First, count degrees
    ll *degree = (ll*)calloc(n+1, sizeof(ll));
    int u, v;
    for(int i=0;i<m;i++){
        scanf("%d %d", &u, &v);
        degree[u]++;
        degree[v]++;
    }
    
    // Allocate adjacency lists
    ll total_edges = m;
    int **adj = (int**)malloc((n+1)*sizeof(int*));
    for(int i=1;i<=n;i++) {
        adj[i] = (int*)malloc(degree[i]*sizeof(int));
        degree[i] = 0; // Reset to use as index
    }
    // Read edges again
    fseek(stdin, 0, SEEK_SET);
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++){
        scanf("%d %d", &u, &v);
        adj[u][degree[u]++] = v;
        adj[v][degree[v]++] = u;
    }
    // Sort adjacency lists
    for(int i=1;i<=n;i++){
        // Simple insertion sort as degrees are small
        for(int j=1; j<degree[i]; j++){
            int key = adj[i][j];
            int l = j-1;
            while(l >=0 && adj[i][l] > key){
                adj[i][l+1] = adj[i][l];
                l--;
            }
            adj[i][l+1] = key;
        }
    }
    
    // Count R: number of 4-cliques
    ll R =0;
    for(int u=1; u<=n; u++){
        for(int i=0; i<degree[u]; i++){
            int v = adj[u][i];
            if(v <=u) continue;
            // Find intersection of adj[u] and adj[v], greater than v
            int pu = 0, pv_ptr =0;
            // Start from first element >v in adj[u]
            while(pu < degree[u] && adj[u][pu] <=v) pu++;
            // Start from first element >v in adj[v]
            pv_ptr =0;
            while(pv_ptr < degree[v] && adj[v][pv_ptr] <=v) pv_ptr++;
            ll count =0;
            while(pu < degree[u] && pv_ptr < degree[v]){
                if(adj[u][pu] == adj[v][pv_ptr]){
                    if(adj[u][pu] > v){
                        count++;
                    }
                    pu++;
                    pv_ptr++;
                }
                else if(adj[u][pu] < adj[v][pv_ptr]){
                    pu++;
                }
                else{
                    pv_ptr++;
                }
            }
            R += count;
        }
    }
    
    // Calculate sum of C(degree[v],2}
    ll sum_c2 =0;
    for(int i=1;i<=n;i++){
        sum_c2 += comb(degree[i], 2);
    }
    
    // Calculate C(m,2)
    ll c_m2 = comb(m,2);
    
    // Calculate C(n,4)
    ll c_n4 = comb(n,4);
    
    // Calculate m * C(n-2,2)
    ll term_m_c = m * comb(n-2,2);
    
    // Calculate B - R
    ll answer = c_n4 - term_m_c + c_m2 - sum_c2 - R;
    
    printf("%lld\n", answer);
    
    // Free memory
    for(int i=1;i<=n;i++) free(adj[i]);
    free(adj);
    free(degree);
    
    return 0;
}