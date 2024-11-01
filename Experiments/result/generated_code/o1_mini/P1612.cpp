#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define LOG 20

typedef long long ll;

int n;
int p[MAXN];
ll w[MAXN];
ll c_val[MAXN];
int up[LOG][MAXN];
ll sum_up[LOG][MAXN];

int main(){
    // Read n
    scanf("%d", &n);
    // Read p[2..n]
    for(int i=2;i<=n;i++) {
        scanf("%d", &p[i]);
    }
    // Read w[1..n]
    for(int i=1;i<=n;i++) {
        scanf("%lld", &w[i]);
    }
    // Read c[1..n]
    for(int i=1;i<=n;i++) {
        scanf("%lld", &c_val[i]);
    }
    // Initialize up[0][u] and sum_up[0][u]
    for(int u=1; u<=n; u++) {
        up[0][u] = p[u];
        if(p[u] != 0){
            sum_up[0][u] = w[p[u]];
        }
        else{
            sum_up[0][u] = 0;
        }
    }
    // Build binary lifting tables
    for(int k=1; k<LOG; k++){
        for(int u=1; u<=n; u++){
            if(up[k-1][u] != 0){
                up[k][u] = up[k-1][ up[k-1][u] ];
                sum_up[k][u] = sum_up[k-1][u] + sum_up[k-1][ up[k-1][u] ];
            }
            else{
                up[k][u] = 0;
                sum_up[k][u] = sum_up[k-1][u];
            }
        }
    }
    // For each node, find the maximum chain length
    ll result[MAXN];
    for(int u=1; u<=n; u++){
        ll total = w[u];
        int length = 1;
        int current = u;
        for(int k=LOG-1; k>=0; k--){
            if(up[k][current] != 0 && total + sum_up[k][current] <= c_val[u]){
                total += sum_up[k][current];
                length += (1 << k);
                current = up[k][current];
            }
        }
        result[u] = length;
    }
    // Print the results
    for(int u=1; u<=n; u++){
        printf("%lld%c", result[u], u<n?' ':'\n');
    }
    return 0;
}