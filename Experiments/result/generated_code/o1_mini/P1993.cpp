#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005
#define MAXM 50000
#define INF 2147483647

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

int parent[MAXN];
int rank_set[MAXN];
int group_id[MAXN];
int gid = 0;

Edge* adj[MAXN];
int dist_arr[MAXN];
int in_queue[MAXN];
int count_relax[MAXN];
int queue_arr[MAXN * 2];
int head = 0, tail = 0;

void uf_init(int n){
    for(int i=0;i<=n;i++){
        parent[i] = i;
        rank_set[i] = 0;
    }
}

int uf_find_set(int x){
    if(parent[x] != x){
        parent[x] = uf_find_set(parent[x]);
    }
    return parent[x];
}

void uf_union_set(int x, int y){
    int fx = uf_find_set(x);
    int fy = uf_find_set(y);
    if(fx == fy) return;
    if(rank_set[fx] < rank_set[fy]){
        parent[fx] = fy;
    }
    else{
        parent[fy] = fx;
        if(rank_set[fx] == rank_set[fy]){
            rank_set[fx]++;
        }
    }
}

void add_edge(int from, int to, int weight){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->weight = weight;
    e->next = adj[from];
    adj[from] = e;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    uf_init(n);
    int type, a, b, c;
    // First pass to handle type 3
    for(int i=0;i<m;i++){
        scanf("%d", &type);
        if(type == 3){
            scanf("%d %d", &a, &b);
            uf_union_set(a, b);
        }
        else{
            if(type ==1 || type ==2){
                if(type ==1){
                    scanf("%d %d %d", &a, &b, &c);
                }
                else{
                    scanf("%d %d %d", &a, &b, &c);
                }
            }
        }
    }
    // Assign group ids
    for(int i=1;i<=n;i++){
        int f = uf_find_set(i);
        if(group_id[f]==0){
            gid++;
            group_id[f] = gid;
        }
    }
    int ng = gid;
    // Reinitialize to read constraints again
    rewind(stdin);
    scanf("%d %d", &n, &m);
    // Skip first m lines to process type 3 and store others
    // To store constraints, use arrays
    typedef struct Constraint {
        int type;
        int a;
        int b;
        int c;
    } Constraint;
    Constraint* constraints = (Constraint*)malloc(sizeof(Constraint)*m);
    int cm=0;
    for(int i=0;i<m;i++){
        scanf("%d", &type);
        if(type ==3){
            scanf("%d %d", &a, &b);
            // Already processed
        }
        else{
            if(type ==1 || type ==2){
                scanf("%d %d %d", &a, &b, &c);
                constraints[cm].type = type;
                constraints[cm].a = a;
                constraints[cm].b = b;
                constraints[cm].c = c;
                cm++;
            }
        }
    }
    // Build graph
    for(int i=0;i<cm;i++){
        type = constraints[i].type;
        a = constraints[i].a;
        b = constraints[i].b;
        c = constraints[i].c;
        int ga = group_id[uf_find_set(a)];
        int gb = group_id[uf_find_set(b)];
        if(type ==1){
            // x[a] >= x[b] + c => x[b] - x[a] <= -c
            add_edge(ga, gb, -c);
        }
        else{
            // type ==2
            // x[a] <= x[b] + c => x[a] - x[b] <= c
            add_edge(gb, ga, c);
        }
    }
    // Add a super source 0, connect to all nodes with 0 weight
    for(int i=1;i<=ng;i++){
        add_edge(0, i, 0);
    }
    // Initialize SPFA
    for(int i=0;i<=ng;i++) dist_arr[i] = 0;
    memset(in_queue, 0, sizeof(int)*(ng+1));
    memset(count_relax, 0, sizeof(int)*(ng+1));
    head = 0;
    tail = 0;
    queue_arr[tail++] = 0;
    in_queue[0] =1;
    while(head < tail){
        int u = queue_arr[head++];
        if(head >= ng*2) head = 0;
        in_queue[u] =0;
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            int v = e->to;
            if(dist_arr[v] > dist_arr[u] + e->weight){
                dist_arr[v] = dist_arr[u] + e->weight;
                if(!in_queue[v]){
                    queue_arr[tail++] = v;
                    if(tail >= ng*2) tail =0;
                    in_queue[v] =1;
                    count_relax[v]++;
                    if(count_relax[v] > ng){
                        printf("No\n");
                        return 0;
                    }
                }
            }
        }
    }
    printf("Yes\n");
    // Free memory
    for(int i=0;i<=ng;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(constraints);
    return 0;
}