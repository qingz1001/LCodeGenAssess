#include <stdio.h>
#include <string.h>

#define MAXN 201
#define MAXM 4000
#define INF 100000000000LL

typedef long long ll;

typedef struct {
    int to;
    int rev;
    ll cap;
} Edge;

Edge graph[MAXN][MAXM];
int graph_size[MAXN];

int level_arr[MAXN];
int iter_arr[MAXN];

int queue_arr[MAXN];
int front, rear;

void add_edge(int a, int b, ll c){
    graph[a][graph_size[a]].to = b;
    graph[a][graph_size[a]].cap = c;
    graph[a][graph_size[a]].rev = graph_size[b];
    graph_size[a]++;
    
    graph[b][graph_size[b]].to = a;
    graph[b][graph_size[b]].cap = 0;
    graph[b][graph_size[b]].rev = graph_size[a]-1;
    graph_size[b]++;
}

int bfs(int s, int t){
    memset(level_arr, -1, sizeof(level_arr));
    front = rear =0;
    queue_arr[rear++] = s;
    level_arr[s] =0;
    while(front < rear){
        int u = queue_arr[front++];
        for(int i=0;i<graph_size[u];i++){
            Edge *e = &graph[u][i];
            if(e->cap >0 && level_arr[e->to]==-1){
                level_arr[e->to] = level_arr[u]+1;
                queue_arr[rear++] = e->to;
                if(e->to == t) break;
            }
        }
    }
    return level_arr[t]!=-1;
}

ll min_ll(ll a, ll b){
    return a < b ? a : b;
}

ll dfs(int u, int t, ll upTo){
    if(u == t) return upTo;
    for(int *p=&iter_arr[u]; *p < graph_size[u]; (*p)++){
        Edge *e = &graph[u][*p];
        if(e->cap >0 && level_arr[u] < level_arr[e->to]){
            ll d = dfs(e->to, t, min_ll(upTo, e->cap));
            if(d >0){
                e->cap -=d;
                graph[e->to][e->rev].cap +=d;
                return d;
            }
        }
    }
    return 0;
}

ll dinic(int s, int t){
    ll flow =0;
    while(bfs(s, t)){
        memset(iter_arr, 0, sizeof(iter_arr));
        ll f;
        while( (f = dfs(s, t, INF)) >0 ){
            flow +=f;
        }
    }
    return flow;
}

int main(){
    int n, m;
    ll x;
    scanf("%d %d %lld", &n, &m, &x);
    for(int i=0;i<m;i++){
        int a, b;
        ll c;
        scanf("%d %d %lld", &a, &b, &c);
        add_edge(a, b, c);
    }
    ll max_flow = dinic(1, n);
    if(max_flow >0){
        ll batches = (x + max_flow -1)/max_flow;
        printf("%lld %lld\n", max_flow, batches);
    }
    else{
        printf("Orz Ni Jinan Saint Cow!\n");
    }
    return 0;
}