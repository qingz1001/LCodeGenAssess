#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MOD 786433

// Fast exponentiation: computes a^b mod mod
ll power_mod_func(ll a, ll b, ll mod_val) {
    if(a == 0 && b == 0) return 0;
    ll res = 1;
    a %= mod_val;
    while(b > 0){
        if(b & 1){
            res = (res * a) % mod_val;
        }
        a = (a * a) % mod_val;
        b >>= 1;
    }
    return res;
}

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[200005];
ll a[200005];
ll sum_total = 0;

// Preallocate memory for edges
Edge edges_storage[400010];
int edge_ptr = 0;

// Function to add edge to the adjacency list
void add_edge(int u, int v){
    edges_storage[edge_ptr].to = v;
    edges_storage[edge_ptr].next = adj[u];
    adj[u] = &edges_storage[edge_ptr++];
}

// Maximum number of different AND values per node
#define MAX_LIST 30

// Arrays to store all possible (val, cnt) pairs
ll all_vals[3000000];
ll all_cnts[3000000];
int ptr_all = 0;

// DFS function
void dfs(int node, int parent, ll *prev_vals, int prev_len){
    // Temporary arrays for current node
    ll curr_vals[MAX_LIST];
    ll curr_cnts[MAX_LIST];
    int curr_len = 0;

    // Process previous list
    for(int i=0;i<prev_len;i++){
        ll new_val = prev_vals[i] & a[node];
        // Merge into curr_vals
        int j;
        for(j=0; j<curr_len; j++) if(curr_vals[j] == new_val) break;
        if(j < curr_len){
            curr_cnts[j] += 1;
        }
        else{
            curr_vals[curr_len] = new_val;
            curr_cnts[curr_len++] = 1;
        }
    }

    // Add the current node itself
    ll own_val = a[node];
    int j;
    for(j=0; j<curr_len; j++) if(curr_vals[j] == own_val) break;
    if(j < curr_len){
        curr_cnts[j] +=1;
    }
    else{
        curr_vals[curr_len] = own_val;
        curr_cnts[curr_len++] =1;
    }

    // For each unique val, compute x^x and add to sum
    for(int i=0;i<curr_len;i++){
        if(curr_vals[i] ==0){
            // 0^0 =0, do nothing
            continue;
        }
        ll px = power_mod_func(curr_vals[i], curr_vals[i], MOD);
        sum_total = (sum_total + px * curr_cnts[i]) % MOD;
    }

    // Recurse to children
    for(Edge* e = adj[node]; e != NULL; e = e->next){
        if(e->to != parent){
            dfs(e->to, node, curr_vals, curr_len);
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    for(int i=1;i<n;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, -1, NULL, 0);
    printf("%lld\n", sum_total);
    return 0;
}