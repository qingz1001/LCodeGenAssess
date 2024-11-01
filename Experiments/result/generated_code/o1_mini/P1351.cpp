#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    int *u = (int*)malloc((n-1) * sizeof(int));
    int *v = (int*)malloc((n-1) * sizeof(int));
    int *degree = (int*)calloc(n+1, sizeof(int));
    for(int i=0;i<n-1;i++){
        scanf("%d %d", &u[i], &v[i]);
        degree[u[i]]++;
        degree[v[i]]++;
    }
    // Calculate offsets
    int *offset = (int*)malloc((n+2) * sizeof(int));
    offset[1] = 0;
    for(int i=2;i<=n;i++){
        offset[i] = offset[i-1] + degree[i-1];
    }
    // Fill adjacency list
    int *adj = (int*)malloc((2*(n-1)) * sizeof(int));
    int *temp_degree_fill = (int*)calloc(n+1, sizeof(int));
    for(int i=0;i<n-1;i++){
        int a = u[i];
        int b = v[i];
        adj[offset[a] + temp_degree_fill[a]] = b;
        temp_degree_fill[a]++;
        adj[offset[b] + temp_degree_fill[b]] = a;
        temp_degree_fill[b]++;
    }
    free(u);
    free(v);
    free(temp_degree_fill);
    // Read W
    int *W = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &W[i]);
    // Compute max and sum
    ll max_val = 0;
    int sum_total = 0;
    for(int w=1;w<=n;w++){
        if(degree[w] >=2){
            ll sum_w =0;
            ll sum_sq_w =0;
            int max1 =0, max2=0;
            for(int i=0;i<degree[w];i++){
                int neighbor = adj[offset[w] + i];
                sum_w += W[neighbor];
                sum_sq_w += (ll)W[neighbor] * W[neighbor];
                if(W[neighbor] > max1){
                    max2 = max1;
                    max1 = W[neighbor];
                }
                else if(W[neighbor] > max2){
                    max2 = W[neighbor];
                }
            }
            int sum_w_mod = sum_w % 10007;
            int sum_sq_w_mod = sum_sq_w % 10007;
            int term = (sum_w_mod * (ll)sum_w_mod - sum_sq_w_mod) % 10007;
            if(term <0) term +=10007;
            sum_total = (sum_total + term) % 10007;
            ll candidate = (ll)max1 * max2;
            if(candidate > max_val) max_val = candidate;
        }
    }
    printf("%lld %d\n", max_val, sum_total);
    // Free memory
    free(degree);
    free(offset);
    free(adj);
    free(W);
    return 0;
}