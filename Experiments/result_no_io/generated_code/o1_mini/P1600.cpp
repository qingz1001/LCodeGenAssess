pp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 300005;
int n, m;
vector<vector<int>> adj(MAXN);
int wj[MAXN];
int in_time[MAXN], out_time[MAXN], timer_val = 1;
int depth_node[MAXN];
int parent_node[19][MAXN];
vector<int> nodes_at_depth[MAXN];
vector<vector<int>> t_sorted(MAXN, vector<int>());
int LOG = 19;
int counts_result[MAXN];

struct Player {
    int s;
    int t;
} player_data[MAXN];

void dfs(int u, int p){
    parent_node[0][u] = p;
    in_time[u] = timer_val;
    nodes_at_depth[depth_node[u]].push_back(u);
    timer_val++;
    for(auto &v: adj[u]){
        if(v != p){
            depth_node[v] = depth_node[u] + 1;
            dfs(v, u);
        }
    }
    out_time[u] = timer_val;
    timer_val++;
}

int get_kth_ancestor(int u, int k){
    for(int i=0;i<LOG;i++){
        if(u == -1) break;
        if(k & (1<<i)){
            u = parent_node[i][u];
            if(u == -1) break;
        }
    }
    return u;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i=0;i<n-1;i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // Initialize parent_node with -1
    for(int k=0; k<19; k++) {
        for(int u=1; u<=n; u++) {
            parent_node[k][u] = -1;
        }
    }
    // Root the tree at 1
    depth_node[1] = 0;
    dfs(1, -1);
    // Binary Lifting
    for(int k=1; k<19; k++){
        for(int u=1; u<=n; u++){
            if(parent_node[k-1][u] != -1){
                parent_node[k][u] = parent_node[k-1][parent_node[k-1][u]];
            }
        }
    }
    // Read wj
    for(int j=1; j<=n; j++) cin >> wj[j];
    // Read players and organize t_sorted
    for(int i=0; i<m; i++){
        cin >> player_data[i].s >> player_data[i].t;
        t_sorted[player_data[i].s].push_back(in_time[player_data[i].t]);
    }
    // Sort t_sorted for each s
    for(int u=1; u<=n; u++) {
        if(!t_sorted[u].empty()) sort(t_sorted[u].begin(), t_sorted[u].end());
    }
    // Precompute list of nodes at each depth sorted by in_time
    for(int d=0; d<=n; d++) {
        if(!nodes_at_depth[d].empty()){
            sort(nodes_at_depth[d].begin(), nodes_at_depth[d].end(), [&](const int &a, const int &b) -> bool{
                return in_time[a] < in_time[b];
            });
        }
    }
    // Precompute prefix sums of players with s_i == u for each depth
    vector<vector<int>> prefix_s(n+1, vector<int>());
    for(int d=0; d<=n; d++){
        int size_d = nodes_at_depth[d].size();
        prefix_s[d].resize(size_d +1, 0);
        for(int i=0; i<size_d; i++) {
            prefix_s[d][i+1] = prefix_s[d][i] + (int)t_sorted[nodes_at_depth[d][i]].size();
        }
    }
    // Process each j
    for(int j=1; j<=n; j++){
        // Category 1
        int anc = -1;
        if(wj[j] <= depth_node[j]){
            anc = get_kth_ancestor(j, wj[j]);
        }
        if(anc != -1 && anc != 0){
            // Number of t_i in [in[j], out[j]] for s_i == anc
            if(!t_sorted[anc].empty()){
                int l = lower_bound(t_sorted[anc].begin(), t_sorted[anc].end(), in_time[j]) - t_sorted[anc].begin();
                int r = upper_bound(t_sorted[anc].begin(), t_sorted[anc].end(), out_time[j]) - t_sorted[anc].begin();
                counts_result[j] += (r - l);
            }
        }
        // Category 2
        int d = depth_node[j] + wj[j];
        if(d <= n && !nodes_at_depth[d].empty()){
            // Binary search to find nodes u in [in[j], out[j]] at depth d
            auto &list_d = nodes_at_depth[d];
            int sz = list_d.size();
            int left = lower_bound(list_d.begin(), list_d.end(), [&](const int &u) -> bool{
                return in_time[u] >= in_time[j];
            }) - list_d.begin();
            int right_idx = upper_bound(list_d.begin(), list_d.end(), [&](const int &u) -> bool{
                return in_time[u] > out_time[j];
            }, [&](const int &a, const int &b) -> bool{
                return a < b;
            }) - list_d.begin() -1;
            if(left <= right_idx){
                // Total players with s_i == u in [left, right_idx]
                // Here we approximate by summing t_sorted size
                // which represents number of players with s_i == u
                ll sum_s = 0;
                for(int i=left; i<=right_idx; i++) sum_s += t_sorted[list_d[i]].size();
                // Now calculate sum_t_in_j
                ll sum_t = 0;
                for(int i=left; i<=right_idx; i++){
                    int u = list_d[i];
                    if(!t_sorted[u].empty()){
                        sum_t += upper_bound(t_sorted[u].begin(), t_sorted[u].end(), out_time[j]) - lower_bound(t_sorted[u].begin(), t_sorted[u].end(), in_time[j]);
                    }
                }
                counts_result[j] += (sum_s - sum_t);
            }
        }
    }
    // Output the results
    for(int j=1; j<=n; j++) {
        cout << counts_result[j] << (j==n? '\n' : ' ');
    }
}