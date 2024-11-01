#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAXN 1005

typedef struct Node {
    int id;
    int child_cnt;
    int children[MAXN];
} Node;

Node tree[MAXN];
ll dp_max[MAXN][2];
ll dp_cnt[MAXN][2];
int visited[MAXN];
int N;

ll max_ll(ll a, ll b) {
    return a > b ? a : b;
}

void dfs(int u, int parent){
    visited[u] = 1;
    dp_max[u][0] = 0;
    dp_cnt[u][0] = 1;
    dp_max[u][1] = 0;
    dp_cnt[u][1] = 1;

    for(int i=0;i<tree[u].child_cnt;i++){
        int v = tree[u].children[i];
        if(v == parent) continue;
        dfs(v, u);

        // When u is not matched
        dp_max[u][0] += max_ll(dp_max[v][0], dp_max[v][1]);
        if(dp_max[v][0] > dp_max[v][1]){
            dp_cnt[u][0] *= dp_cnt[v][0];
        }
        else if(dp_max[v][0] < dp_max[v][1]){
            dp_cnt[u][0] *= dp_cnt[v][1];
        }
        else{
            dp_cnt[u][0] *= (dp_cnt[v][0] + dp_cnt[v][1]);
        }

        // When u is matched, it must be matched with one child
        // We'll handle it later
    }

    // Now handle dp_max[u][1]
    dp_max[u][1] = 0;
    dp_cnt[u][1] = 0;
    for(int i=0;i<tree[u].child_cnt;i++){
        int v = tree[u].children[i];
        if(v == parent) continue;

        ll temp = 1;
        ll total = 1;
        // u is matched with v
        ll total_matching = 1 + dp_max[v][0];
        // add other children
        for(int j=0;j<tree[u].child_cnt;j++){
            if(j == i) continue;
            int w = tree[u].children[j];
            if(w == parent) continue;
            total_matching += max_ll(dp_max[w][0], dp_max[w][1]);
        }

        // Now find the total ways
        ll ways = dp_cnt[v][0];
        for(int j=0;j<tree[u].child_cnt;j++){
            if(j == i) continue;
            int w = tree[u].children[j];
            if(w == parent) continue;
            if(dp_max[w][0] > dp_max[w][1]){
                ways *= dp_cnt[w][0];
            }
            else if(dp_max[w][0] < dp_max[w][1]){
                ways *= dp_cnt[w][1];
            }
            else{
                ways *= (dp_cnt[w][0] + dp_cnt[w][1]);
            }
        }

        if(total_matching > dp_max[u][1]){
            dp_max[u][1] = total_matching;
            dp_cnt[u][1] = ways;
        }
        else if(total_matching == dp_max[u][1]){
            dp_cnt[u][1] += ways;
        }
    }

    // If no children are matched, set dp_max[u][1] accordingly
    if(dp_max[u][1] == 0){
        dp_max[u][1] = 0;
        dp_cnt[u][1] = 1;
    }
}

int main(){
    scanf("%d", &N);
    for(int i=0;i<N;i++){
        int u, m;
        scanf("%d %d", &u, &m);
        tree[u].child_cnt = m;
        for(int j=0;j<m;j++){
            scanf("%d", &tree[u].children[j]);
        }
    }

    // Find root (assuming 1 is root)
    dfs(1, -1);

    // The answer is max of dp_max[1][0] and dp_max[1][1]
    ll answer_max = max_ll(dp_max[1][0], dp_max[1][1]);
    ll answer_cnt = 0;
    if(dp_max[1][0] > dp_max[1][1]){
        answer_cnt = dp_cnt[1][0];
    }
    else if(dp_max[1][0] < dp_max[1][1]){
        answer_cnt = dp_cnt[1][1];
    }
    else{
        answer_cnt = dp_cnt[1][0] + dp_cnt[1][1];
    }

    printf("%lld\n%lld\n", answer_max, answer_cnt);
    return 0;
}