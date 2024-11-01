#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 50005
#define MAXK 20005
#define LOGK 15
#define INF 100000000000LL

typedef long long ll;

// Structure for internal network edges
typedef struct Edge {
    int to;
    int c;
    int d;
    struct Edge* next;
} Edge;

// Adjacency list for internal network
Edge* adj[MAXN];

// Structure for trie
int parentK[MAXK];
int depthK[MAXK];
int up[MAXK][LOGK];

// Structure for priority queue
typedef struct {
    int node;
    int trie_node;
    ll dist;
} HeapNode;

HeapNode heapNodes[MAXN * LOGK];
int heapSize = 0;

// Swap two heap nodes
void swapHeap(int i, int j){
    HeapNode temp = heapNodes[i];
    heapNodes[i] = heapNodes[j];
    heapNodes[j] = temp;
}

// Compare function for heap
int lessThan(ll a, ll b){
    return a < b;
}

// Push a node into the heap
void pushHeap(int node, int trie_node, ll dist){
    heapSize++;
    heapNodes[heapSize].node = node;
    heapNodes[heapSize].trie_node = trie_node;
    heapNodes[heapSize].dist = dist;
    // Heapify up
    int i = heapSize;
    while(i > 1){
        int parent = i / 2;
        if(lessThan(heapNodes[i].dist, heapNodes[parent].dist)){
            swapHeap(i, parent);
            i = parent;
        }
        else break;
    }
}

// Pop the smallest node from the heap
HeapNode popHeap(){
    HeapNode top = heapNodes[1];
    heapNodes[1] = heapNodes[heapSize];
    heapSize--;
    // Heapify down
    int i = 1;
    while(1){
        int smallest = i;
        int left = 2*i;
        int right = 2*i + 1;
        if(left <= heapSize && lessThan(heapNodes[left].dist, heapNodes[smallest].dist)){
            smallest = left;
        }
        if(right <= heapSize && lessThan(heapNodes[right].dist, heapNodes[smallest].dist)){
            smallest = right;
        }
        if(smallest != i){
            swapHeap(i, smallest);
            i = smallest;
        }
        else break;
    }
    return top;
}

// Function to add edge to adjacency list
void addEdge(int from, int to, int c, int d){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->c = c;
    e->d = d;
    e->next = adj[from];
    adj[from] = e;
}

// Function to build trie and compute depth and ancestors
void buildTrie(int k, int trie_edges[][3]){
    // Initialize root
    parentK[1] = 1;
    depthK[1] = 0;
    // Initialize up table
    for(int i=1;i<=k;i++){
        for(int j=0;j<LOGK;j++) up[i][j] = 1;
    }
    // Build parent and depth
    for(int i=0;i<k-1;i++){
        int u = trie_edges[i][0];
        int v = trie_edges[i][1];
        // int w = trie_edges[i][2]; // Character not used
        parentK[v] = u;
        depthK[v] = depthK[u] + 1;
    }
    // Binary lifting
    for(int j=1;j<LOGK;j++){
        for(int i=1;i<=k;i++){
            up[i][j] = up[up[i][j-1]][j-1];
        }
    }
}

// Function to compute LCA
int LCA_func(int u, int v){
    if(depthK[u] < depthK[v]){
        int temp = u; u = v; v = temp;
    }
    // Lift u to depth of v
    for(int j=LOGK-1; j>=0; j--){
        if(depthK[u] - (1<<j) >= depthK[v]){
            u = up[u][j];
        }
    }
    if(u == v) return u;
    // Lift both u and v
    for(int j=LOGK-1; j>=0; j--){
        if(up[u][j] != up[v][j]){
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

ll dist_arr[MAXN];
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        // Initialize adjacency list
        for(int i=1;i<=n;i++) adj[i] = NULL;
        // Read m edges
        for(int i=0;i<m;i++){
            int a, b, c, d;
            scanf("%d %d %d %d", &a, &b, &c, &d);
            addEdge(a, b, c, d);
        }
        // Read k-1 trie edges
        int trie_edges[k-1][3];
        for(int i=0;i<k-1;i++){
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            trie_edges[i][0] = u;
            trie_edges[i][1] = v;
            trie_edges[i][2] = w;
        }
        // Build trie
        buildTrie(k, trie_edges);
        // Initialize distances
        for(int i=1;i<=n;i++) dist_arr[i] = INF;
        dist_arr[1] = 0;
        // Initialize heap
        heapSize = 0;
        pushHeap(1, 1, 0);
        // Dijkstra
        while(heapSize > 0){
            HeapNode current = popHeap();
            int u = current.node;
            int s = current.trie_node;
            ll d = current.dist;
            if(d > dist_arr[u]) continue;
            Edge* e = adj[u];
            while(e){
                int v = e->to;
                int t = e->d;
                int lca = LCA_func(s, t);
                int len = depthK[lca];
                ll new_dist = d + (ll)e->c + (ll)len;
                if(new_dist < dist_arr[v]){
                    dist_arr[v] = new_dist;
                    pushHeap(v, t, new_dist);
                }
                e = e->next;
            }
        }
        // Print results
        for(int i=2;i<=n;i++){
            printf("%lld\n", dist_arr[i]);
        }
    }
    return 0;
}