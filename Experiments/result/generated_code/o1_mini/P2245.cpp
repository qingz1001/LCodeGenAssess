#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 300005
#define LOG 20

typedef struct {
    int u, v, L;
} Edge;

int cmp(const void *a, const void *b){
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if(ea->L != eb->L) return ea->L - eb->L;
    if(ea->u != eb->u) return ea->u - eb->u;
    return ea->v - eb->v;
}

typedef struct {
    int to;
    int weight;
    int next;
} AdjNode;

AdjNode adjNodes[600010];
int head[MAXN];
int adj_cnt = 0;

void addEdge(int u, int v, int w){
    adjNodes[adj_cnt].to = v;
    adjNodes[adj_cnt].weight = w;
    adjNodes[adj_cnt].next = head[u];
    head[u] = adj_cnt++;
}

int parentUF[MAXN];
int rankUF[MAXN];

int find_set(int x){
    if(parentUF[x] != x){
        parentUF[x] = find_set(parentUF[x]);
    }
    return parentUF[x];
}

void union_set_func(int x, int y){
    int fx = find_set(x);
    int fy = find_set(y);
    if(fx == fy) return;
    if(rankUF[fx] < rankUF[fy]){
        parentUF[fx] = fy;
    }
    else{
        parentUF[fy] = fx;
        if(rankUF[fx] == rankUF[fy]){
            rankUF[fx]++;
        }
    }
}

int depth_node[MAXN];
int parentk[LOG][MAXN];
int maxEdgek[LOG][MAXN];

void dfs(int u, int f){
    parentk[0][u] = f;
    AdjNode *ptr;
    for(int i = head[u]; i != -1; i = adjNodes[i].next){
        int v = adjNodes[i].to;
        int w = adjNodes[i].weight;
        if(v != f){
            depth_node[v] = depth_node[u] + 1;
            maxEdgek[0][v] = w;
            dfs(v, u);
        }
    }
}

int get_max(int u, int v){
    if(u == v) return 0;
    int max_w = 0;
    if(depth_node[u] < depth_node[v]){
        int temp = u;
        u = v;
        v = temp;
    }
    for(int k = LOG-1; k >=0; k--){
        if(depth_node[u] - (1<<k) >= depth_node[v]){
            if(maxEdgek[k][u] > max_w){
                max_w = maxEdgek[k][u];
            }
            u = parentk[k][u];
        }
    }
    if(u == v) return max_w;
    for(int k = LOG-1; k >=0; k--){
        if(parentk[k][u] != -1 && parentk[k][u] != parentk[k][v]){
            if(maxEdgek[k][u] > max_w){
                max_w = maxEdgek[k][u];
            }
            if(maxEdgek[k][v] > max_w){
                max_w = maxEdgek[k][v];
            }
            u = parentk[k][u];
            v = parentk[k][v];
        }
    }
    if(parentk[0][u] != -1){
        if(maxEdgek[0][u] > max_w){
            max_w = maxEdgek[0][u];
        }
        if(maxEdgek[0][v] > max_w){
            max_w = maxEdgek[0][v];
        }
    }
    return max_w;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Edge *edges = (Edge*)malloc(sizeof(Edge)*M);
    for(int i =0;i<M;i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].L);
    }
    qsort(edges, M, sizeof(Edge), cmp);
    for(int i=1;i<=N;i++){
        parentUF[i] = i;
        rankUF[i] = 0;
        head[i] = -1;
    }
    for(int i=0;i<M;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int L = edges[i].L;
        if(find_set(u) != find_set(v)){
            union_set_func(u, v);
            addEdge(u, v, L);
            addEdge(v, u, L);
        }
    }
    free(edges);
    memset(parentk, -1, sizeof(parentk));
    memset(maxEdgek, 0, sizeof(maxEdgek));
    for(int i=1;i<=N;i++){
        if(parentk[0][i] == -1){
            depth_node[i] = 0;
            dfs(i, -1);
        }
    }
    for(int k=1;k<LOG;k++){
        for(int v=1;v<=N;v++){
            if(parentk[k-1][v] != -1){
                parentk[k][v] = parentk[k-1][parentk[k-1][v]];
                if(maxEdgek[k-1][v] > maxEdgek[k-1][parentk[k-1][v]]){
                    maxEdgek[k][v] = maxEdgek[k-1][v];
                }
                else{
                    maxEdgek[k][v] = maxEdgek[k-1][parentk[k-1][v]];
                }
            }
            else{
                parentk[k][v] = -1;
                maxEdgek[k][v] = maxEdgek[k-1][v];
            }
        }
    }
    int Q;
    scanf("%d", &Q);
    while(Q--){
        int A, B;
        scanf("%d %d", &A, &B);
        if(find_set(A) != find_set(B)){
            printf("impossible\n");
        }
        else{
            int res = get_max(A, B);
            printf("%d\n", res);
        }
    }
    return 0;
}