#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10005
#define MAXM 50005
#define LOGN 15

typedef struct {
    int x, y, z;
} Edge;

typedef struct {
    int to;
    int weight;
    int next;
} Adj;

int parent_set[MAXN];
int find_set(int x) {
    if (parent_set[x] != x)
        parent_set[x] = find_set(parent_set[x]);
    return parent_set[x];
}

int cmp_desc(const void *a, const void *b){
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if (eb->z != ea->z)
        return eb->z - ea->z;
    else
        return 0;
}

Adj adj_list[MAXM * 2];
int head_list[MAXN];
int adj_cnt = 0;

void add_edge(int u, int v, int w){
    adj_list[adj_cnt].to = v;
    adj_list[adj_cnt].weight = w;
    adj_list[adj_cnt].next = head_list[u];
    head_list[u] = adj_cnt++;
}

int parent[LOGN][MAXN];
int min_edge_val[LOGN][MAXN];
int depth_arrn[MAXN];

void dfs(int u, int pre, int w){
    parent[0][u] = pre;
    min_edge_val[0][u] = w;
    for(int i = head_list[u]; i != -1; i = adj_list[i].next){
        int v = adj_list[i].to;
        int cost = adj_list[i].weight;
        if(v != pre){
            depth_arrn[v] = depth_arrn[u] + 1;
            dfs(v, u, cost);
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Edge edges[m];
    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].z);
    }
    qsort(edges, m, sizeof(Edge), cmp_desc);
    for(int i = 1; i <= n; i++) parent_set[i] = i;
    memset(head_list, -1, sizeof(head_list));
    for(int i = 0; i < m; i++){
        int fx = find_set(edges[i].x);
        int fy = find_set(edges[i].y);
        if(fx != fy){
            parent_set[fx] = fy;
            add_edge(edges[i].x, edges[i].y, edges[i].z);
            add_edge(edges[i].y, edges[i].x, edges[i].z);
        }
    }
    // Initialize LCA
    depth_arrn[1] = 0;
    dfs(1, -1, 0);
    for(int k = 1; k < LOGN; k++){
        for(int u = 1; u <= n; u++){
            if(parent[k-1][u] != -1){
                parent[k][u] = parent[k-1][parent[k-1][u]];
                if(parent[k][u] != -1)
                    min_edge_val[k][u] = min_edge_val[k-1][u] < min_edge_val[k-1][parent[k-1][u]] ? min_edge_val[k-1][u] : min_edge_val[k-1][parent[k-1][u]];
                else
                    min_edge_val[k][u] = min_edge_val[k-1][u];
            }
            else{
                parent[k][u] = -1;
                min_edge_val[k][u] = min_edge_val[k-1][u];
            }
        }
    }
    int q;
    scanf("%d", &q);
    while(q--){
        int x, y;
        scanf("%d %d", &x, &y);
        if(find_set(x) != find_set(y)){
            printf("-1\n");
            continue;
        }
        if(x == y){
            printf("0\n");
            continue;
        }
        int min_ans = 100000;
        if(depth_arrn[x] < depth_arrn[y]){
            int temp = x; x = y; y = temp;
        }
        // Lift x up to depth of y
        for(int k = LOGN-1; k >=0; k--){
            if(depth_arrn[x] - (1<<k) >= depth_arrn[y]){
                if(min_edge_val[k][x] < min_ans)
                    min_ans = min_edge_val[k][x];
                x = parent[k][x];
            }
        }
        if(x != y){
            for(int k = LOGN-1; k >=0; k--){
                if(parent[k][x] != -1 && parent[k][x] != parent[k][y]){
                    if(min_edge_val[k][x] < min_ans)
                        min_ans = min_edge_val[k][x];
                    if(min_edge_val[k][y] < min_ans)
                        min_ans = min_edge_val[k][y];
                    x = parent[k][x];
                    y = parent[k][y];
                }
            }
            if(parent[0][x] != -1 && parent[0][y] != -1){
                if(min_edge_val[0][x] < min_ans)
                    min_ans = min_edge_val[0][x];
                if(min_edge_val[0][y] < min_ans)
                    min_ans = min_edge_val[0][y];
            }
        }
        printf("%d\n", min_ans);
    }
    return 0;
}