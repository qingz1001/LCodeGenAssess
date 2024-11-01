#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define LOG 20

typedef long long ll;

typedef struct Line {
    ll m;
    ll c;
} Line;

typedef struct {
    Line lines[60];
    int size;
} CHT;

int n, t;
int parent_node[MAXN];
ll s_v[MAXN];
ll p_v[MAXN];
ll q_v[MAXN];
ll l_v[MAXN];
ll dist_v[MAXN];
int size_subtree[MAXN];
int heavy[MAXN];
int depth_v[MAXN];
int head_node[MAXN];
int pos_in_base[MAXN];
int current_pos = 1;
int up[LOG][MAXN];
int chain_id[MAXN];
CHT chts[MAXN];
Line temp_lines[60];
int line_ptr[MAXN];

// Adjacency list
int adj_head[MAXN];
int adj_to[2*MAXN];
int adj_next[2*MAXN];
int adj_cnt = 0;

void add_edge(int u, int v){
    adj_to[adj_cnt] = v;
    adj_next[adj_cnt] = adj_head[u];
    adj_head[u] = adj_cnt++;
}

int dfs(int v){
    size_subtree[v] = 1;
    heavy[v] = -1;
    int max_size = 0;
    for(int i = adj_head[v]; i != -1; i = adj_next[i]){
        int u = adj_to[i];
        depth_v[u] = depth_v[v] + 1;
        dist_v[u] = dist_v[v] + s_v[u];
        up[0][u] = v;
        for(int k =1; k<LOG; k++) {
            if(up[k-1][u] != -1)
                up[k][u] = up[k-1][up[k-1][u]];
            else
                up[k][u] = -1;
        }
        int sz = dfs(u);
        size_subtree[v] += sz;
        if(sz > max_size){
            max_size = sz;
            heavy[v] = u;
        }
    }
    return size_subtree[v];
}

void decompose(int v, int h, int cid){
    head_node[v] = h;
    pos_in_base[v] = current_pos++;
    chain_id[v] = cid;
    if(heavy[v] != -1){
        decompose(heavy[v], h, cid);
        for(int i = adj_head[v]; i != -1; i = adj_next[i]){
            int u = adj_to[i];
            if(u != heavy[v]){
                decompose(u, u, ++cid);
            }
        }
    }
}

int find_a_low(int v, ll lower){
    if(dist_v[v] < lower) return -1;
    for(int k = LOG-1; k >=0; k--){
        if(up[k][v] != -1 && dist_v[up[k][v]] >= lower){
            v = up[k][v];
        }
    }
    return v;
}

int cmp_lines(const void *a, const void *b){
    ll intersect = ((*(Line*)a).c - (*(Line*)a).m * 0) - ((*(Line*)b).c - (*(Line*)b).m * 0);
    return 0;
}

int main(){
    memset(adj_head, -1, sizeof(adj_head));
    scanf("%d %d", &n, &t);
    for(int v=2; v<=n; v++){
        scanf("%d %lld %lld %lld %lld", &parent_node[v], &s_v[v], &p_v[v], &q_v[v], &l_v[v]);
        add_edge(parent_node[v], v);
    }
    depth_v[1] = 0;
    dist_v[1] = 0;
    for(int k=0; k<LOG; k++) for(int v=1; v<=n; v++) if(k !=0) {
        if(up[k-1][v] != -1)
            up[k][v] = up[k-1][up[k-1][v]];
        else
            up[k][v] = -1;
    }
    dfs(1);
    decompose(1,1,0);
    // Initialize dp
    ll dp[MAXN];
    dp[1] = 0;
    // Initialize CHTs
    for(int cid=0; cid<=n; cid++) {
        chts[cid].size =0;
    }
    // Process nodes in order of increasing depth (BFS order)
    // To ensure that parents are processed before children
    int queue[MAXN];
    int front=0, back=0;
    queue[back++] =1;
    while(front < back){
        int v = queue[front++];
        // Compute dp[v] if not root
        if(v !=1){
            ll lower = dist_v[v] - l_v[v];
            if(lower <0) lower =0;
            int a_low = find_a_low(v, lower);
            // Query from a_low to root
            ll min_val = 1e18;
            if(a_low != -1){
                int u = v;
                while(head_node[u] != head_node[a_low]){
                    // Query the chain of u from head to u
                    int cid = chain_id[u];
                    CHT *cht = &chts[cid];
                    // Binary search on cht to find min at p_v[v]
                    // Lines are sorted by decreasing m
                    if(cht->size >0){
                        int l =0, r = cht->size -1;
                        ll best = 1e18;
                        while(l <= r){
                            int mid = (l + r)/2;
                            ll y1 = cht->lines[mid].m * p_v[v] + cht->lines[mid].c;
                            if(mid+1 < cht->size){
                                ll y2 = cht->lines[mid+1].m * p_v[v] + cht->lines[mid+1].c;
                                if(y2 < y1){
                                    l = mid +1;
                                }
                                else{
                                    r = mid -1;
                                    if(y1 < best) best = y1;
                                }
                            }
                            else{
                                if(y1 < best) best = y1;
                                break;
                            }
                        }
                        if(best < min_val) min_val = best;
                    }
                    u = up[0][head_node[u]];
                }
                // Now head_node[u] == head_node[a_low]
                int cid = chain_id[u];
                CHT *cht = &chts[cid];
                // Find the range within the chain from a_low to u
                // Since lines are added in order, just query the whole chain up to u
                if(cht->size >0){
                    int l =0, r = cht->size -1;
                    ll best = 1e18;
                    while(l <= r){
                        int mid = (l + r)/2;
                        ll y1 = cht->lines[mid].m * p_v[v] + cht->lines[mid].c;
                        if(mid+1 < cht->size){
                            ll y2 = cht->lines[mid+1].m * p_v[v] + cht->lines[mid+1].c;
                            if(y2 < y1){
                                l = mid +1;
                            }
                            else{
                                r = mid -1;
                                if(y1 < best) best = y1;
                            }
                        }
                        else{
                            if(y1 < best) best = y1;
                            break;
                        }
                    }
                    if(best < min_val) min_val = best;
                }
            }
            dp[v] = q_v[v] + dist_v[v] * p_v[v] + min_val;
        }
        // Insert current node's line into its chain's CHT
        if(v !=1){
            int cid = chain_id[v];
            CHT *cht = &chts[cid];
            Line new_line;
            new_line.m = -dist_v[v];
            new_line.c = dp[v];
            // Maintain lower convex hull
            while(cht->size >=2){
                Line l1 = cht->lines[cht->size-2];
                Line l2 = cht->lines[cht->size-1];
                // Check if the new line makes l2 obsolete
                // Intersection(l1, l2) >= Intersection(l2, new_line)
                // To avoid floating point, compare (l2.c - l1.c)/(l1.m - l2.m) >= (new_line.c - l2.c)/(l2.m - new_line.m)
                // Cross multiply to maintain precision
                ll lhs_num = (l2.c - l1.c) * (new_line.m - l2.m);
                ll rhs_num = (new_line.c - l2.c) * (l1.m - l2.m);
                if(lhs_num >= rhs_num){
                    cht->size--;
                }
                else{
                    break;
                }
            }
            cht->lines[cht->size++] = new_line;
        }
        // Enqueue children
        for(int i = adj_head[v]; i != -1; i = adj_next[i]){
            int u = adj_to[i];
            queue[back++] =u;
        }
    }
    // Now print dp[2..n]
    for(int v=2; v<=n; v++) printf("%lld\n", dp[v]);
    return 0;
}