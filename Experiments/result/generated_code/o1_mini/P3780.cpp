#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20005
#define MAXK 500005

typedef long long ll;

int Q;
int n, k;
int parent[MAXN];
ll a[MAXN];
ll v_val[MAXN];
int depth_node[MAXN];
int max_depth;
ll dp_current[MAXK];
ll dp_next[MAXK];

int main(){
    scanf("%d", &Q);
    while(Q--){
        scanf("%d %d", &n, &k);
        for(int i=1;i<=n;i++){
            scanf("%d %lld %lld", &parent[i], &a[i], &v_val[i]);
        }
        // Compute depth
        depth_node[1]=1;
        max_depth=1;
        for(int i=2;i<=n;i++){
            depth_node[i]=depth_node[parent[i]]+1;
            if(depth_node[i]>max_depth) max_depth = depth_node[i];
        }
        // Initialize DP
        memset(dp_current, -1, sizeof(ll)*(k+2));
        dp_current[0]=0;
        for(int i=1;i<=n;i++){
            // Iterate t from k down to 0
            for(int t=0;t<=k;t++){
                if(dp_current[t]==-1) continue;
                // Take 0 from this node
                if(dp_current[t] > dp_next[t]){
                    dp_next[t] = dp_current[t];
                }
                // Take at least 1
                ll max_take = a[i];
                ll gain = v_val[i];
                for(ll take=1; take<=max_take && t + take <=k; take++){
                    if(t + take >k) break;
                    if(dp_current[t] + take * gain > dp_next[t + take]){
                        dp_next[t + take] = dp_current[t] + take * gain;
                    }
                }
            }
            // Swap dp_current and dp_next
            memcpy(dp_current, dp_next, sizeof(ll)*(k+2));
            memset(dp_next, -1, sizeof(ll)*(k+2));
        }
        // Find maximum happiness
        ll res=0;
        for(int t=0;t<=k;t++) {
            if(dp_current[t] > res) res = dp_current[t];
        }
        printf("%lld\n", res);
    }
    return 0;
}