#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 50005
#define MAX_M 50005
#define MAX_K 20005

typedef long long ll;

struct Edge {
    int to, next;
    int cost, dic;
};

struct TreeNode {
    int ch[26], fa;
    int len;
};

struct HeapNode {
    int v;
    ll d;
};

int n, m, k;
int head[MAX_N], ecnt;
Edge e[MAX_M * 2];
TreeNode tr[MAX_K];
int fail[MAX_K];

ll dist[MAX_N];
int vis[MAX_N];

HeapNode heap[MAX_N];
int heap_size;

void add_edge(int u, int v, int c, int d) {
    e[++ecnt] = (Edge){v, head[u], c, d};
    head[u] = ecnt;
}

void insert_trie(int u, int v, int w) {
    if (!tr[u].ch[w - 1]) {
        tr[u].ch[w - 1] = v;
        tr[v].fa = u;
        tr[v].len = tr[u].len + 1;
    }
}

void build_ac() {
    int q[MAX_K], l = 0, r = 0;
    q[r++] = 1;
    while (l < r) {
        int u = q[l++];
        for (int i = 0; i < 26; i++) {
            if (tr[u].ch[i]) {
                int v = tr[u].ch[i];
                q[r++] = v;
                if (u == 1) fail[v] = 1;
                else {
                    int j = fail[tr[v].fa];
                    while (j > 1 && !tr[j].ch[i]) j = fail[j];
                    if (tr[j].ch[i]) j = tr[j].ch[i];
                    fail[v] = j;
                }
            }
        }
    }
}

void heap_push(int v, ll d) {
    int i = ++heap_size;
    while (i > 1 && heap[i / 2].d > d) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = (HeapNode){v, d};
}

HeapNode heap_pop() {
    HeapNode res = heap[1];
    HeapNode x = heap[heap_size--];
    int i = 1, j = 2;
    while (j <= heap_size) {
        if (j < heap_size && heap[j + 1].d < heap[j].d) j++;
        if (x.d <= heap[j].d) break;
        heap[i] = heap[j];
        i = j;
        j *= 2;
    }
    heap[i] = x;
    return res;
}

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    heap_push(1, 0);
    
    while (heap_size) {
        HeapNode node = heap_pop();
        int u = node.v;
        if (vis[u]) continue;
        vis[u] = 1;
        
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to;
            ll w = e[i].cost;
            int x = e[i].dic, y = 1;
            while (x > 1 && y < tr[x].len) {
                x = fail[x];
                y = tr[x].len;
            }
            w += y;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                heap_push(v, dist[v]);
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        
        memset(head, 0, sizeof(head));
        ecnt = 0;
        memset(tr, 0, sizeof(tr));
        tr[1].len = 0;
        
        for (int i = 1; i <= m; i++) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            add_edge(a, b, c, d);
        }
        
        for (int i = 1; i < k; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            insert_trie(u, v, w);
        }
        
        build_ac();
        
        memset(vis, 0, sizeof(vis));
        heap_size = 0;
        dijkstra();
        
        for (int i = 2; i <= n; i++) {
            printf("%lld\n", dist[i]);
        }
    }
    
    return 0;
}