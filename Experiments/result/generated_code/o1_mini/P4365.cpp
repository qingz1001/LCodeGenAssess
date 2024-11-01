#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXK 105
#define MOD 64123

typedef struct {
    int parent;
    int size;
    long long freq[MAXK];
} DSU_Node;

int n, k, W;
int d[MAXN];
int edges[MAXN][2];
DSU_Node dsu[MAXN];
int order[MAXN];
long long ans = 0;
int active[MAXN];
int cmp(const void* a, const void* b) {
    int idx1 = *((int*)a);
    int idx2 = *((int*)b);
    if(d[idx1] != d[idx2]) return d[idx2] - d[idx1];
    return idx1 - idx2;
}

int find_set(int x){
    if(dsu[x].parent != x){
        dsu[x].parent = find_set(dsu[x].parent);
    }
    return dsu[x].parent;
}

int main(){
    scanf("%d %d %d", &n, &k, &W);
    for(int i=1;i<=n;i++) scanf("%d", &d[i]);
    for(int i=0;i<n-1;i++) scanf("%d %d", &edges[i][0], &edges[i][1]);
    for(int i=1;i<=n;i++) { order[i-1]=i; }
    qsort(order, n, sizeof(int), cmp);
    for(int i=1;i<=n;i++){
        dsu[i].parent = i;
        dsu[i].size = 1;
        memset(dsu[i].freq, 0, sizeof(dsu[i].freq));
    }
    for(int i=0;i<n;i++){
        int u = order[i];
        active[u]=1;
        dsu[u].freq[0] = 1;
        // Check all neighbors
        for(int j=0; j<n-1; j++){
            if(edges[j][0]==u || edges[j][1]==u){
                int v = (edges[j][0]==u)? edges[j][1] : edges[j][0];
                if(active[v]){
                    int pu = find_set(u);
                    int pv = find_set(v);
                    if(pu != pv){
                        // Merge smaller set into larger
                        if(dsu[pu].size < dsu[pv].size){
                            int temp = pu; pu = pv; pv = temp;
                        }
                        // Combine frequencies
                        long long new_freq[MAXK];
                        memset(new_freq, 0, sizeof(new_freq));
                        for(int a=0; a<k; a++) {
                            if(dsu[pu].freq[a]==0) continue;
                            for(int b=0; b<k; b++) {
                                if(dsu[pv].freq[b]==0) continue;
                                if(a + b < k){
                                    new_freq[a + b] = (new_freq[a + b] + dsu[pu].freq[a] * dsu[pv].freq[b]) % MOD;
                                }
                            }
                        }
                        for(int a=0; a<k; a++) {
                            dsu[pu].freq[a] = (dsu[pu].freq[a] + dsu[pv].freq[a]) % MOD;
                        }
                        for(int a=0; a<k; a++) {
                            if(a < k) dsu[pu].freq[a] = (dsu[pu].freq[a] + new_freq[a]) % MOD;
                        }
                        dsu[pu].size += dsu[pv].size;
                        dsu[pv].parent = pu;
                    }
                }
            }
        }
        int pu = find_set(u);
        if(i+1 >= k){
            ans = (ans + (dsu[pu].freq[k-1] * (long long)d[u]) % MOD) % MOD;
        }
    }
    printf("%lld\n", ans % MOD);
    return 0;
}