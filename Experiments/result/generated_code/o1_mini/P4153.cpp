#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void *a, const void *b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int n, m, s, t;
    ll k;
    scanf("%d %d %d %d %lld", &n, &m, &s, &t, &k);
    
    // Initialize arrays
    ll *s_to_u = (ll*)malloc((n+1) * sizeof(ll));
    ll *u_to_t = (ll*)malloc((n+1) * sizeof(ll));
    for(int i=1;i<=n;i++){
        s_to_u[i] = -1;
        u_to_t[i] = -1;
    }
    
    // Read edges
    for(int i=0;i<m;i++){
        int x, y;
        ll z;
        scanf("%d %d %lld", &x, &y, &z);
        if(x == s && y != t){
            if(s_to_u[y] == -1 || z < s_to_u[y]){
                s_to_u[y] = z;
            }
        }
        if(y == t && x != s){
            if(u_to_t[x] == -1 || z < u_to_t[x]){
                u_to_t[x] = z;
            }
        }
    }
    
    // Collect deltas
    ll sum_a = 0;
    ll *deltas = (ll*)malloc((n+1) * sizeof(ll));
    int count = 0;
    for(int i=1;i<=n;i++){
        if(i == s || i == t) continue;
        if(s_to_u[i] == -1 && u_to_t[i] == -1){
            // No way to disconnect
            continue;
        }
        if(s_to_u[i] == -1){
            sum_a += u_to_t[i];
            continue;
        }
        if(u_to_t[i] == -1){
            sum_a += s_to_u[i];
            continue;
        }
        if(s_to_u[i] < u_to_t[i]){
            sum_a += s_to_u[i];
            deltas[count++] = u_to_t[i] - s_to_u[i];
        }
        else{
            sum_a += u_to_t[i];
            deltas[count++] = s_to_u[i] - u_to_t[i];
        }
    }
    
    qsort(deltas, count, sizeof(ll), cmp);
    
    ll *results = (ll*)malloc((k+1) * sizeof(ll));
    int output_count = 0;
    for(int i=0;i<count && output_count < k;i++){
        results[output_count++] = sum_a + deltas[i];
    }
    
    // Always include sum_a as the first result if possible
    if(k > 0){
        printf("%lld\n", sum_a);
        for(int i=0;i<output_count && i < k-1;i++){
            printf("%lld\n", results[i]);
        }
    }
    
    if(output_count < k){
        printf("-1\n");
    }
    
    free(s_to_u);
    free(u_to_t);
    free(deltas);
    free(results);
    return 0;
}