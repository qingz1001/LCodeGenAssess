#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int x, y;
    int v;
} Edge;

int cmp_edges(const void *a, const void *b){
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    if(ea->v != eb->v) return ea->v - eb->v;
    return 0;
}

typedef struct Node {
    int to;
    int weight;
    struct Node* next;
} Node;

Node* adj[300005];
ll res = LLONG_MIN;

ll max1[300005];
ll max2[300005];

void add_edge(int from, int to, int w){
    Node* node = (Node*)malloc(sizeof(Node));
    node->to = to;
    node->weight = w;
    node->next = adj[from];
    adj[from] = node;
}

void dfs(int u, int parent_u){
    max1[u] = 0;
    max2[u] = 0;
    Node* ptr = adj[u];
    while(ptr){
        int v = ptr->to;
        int w = ptr->weight;
        if(v == parent_u){
            ptr = ptr->next;
            continue;
        }
        dfs(v, u);
        ll temp = max1[v] + w;
        if(temp > max1[u]){
            max2[u] = max1[u];
            max1[u] = temp;
        }
        else if(temp > max2[u]){
            max2[u] = temp;
        }
        if(res < max1[u] + max2[u]){
            res = max1[u] + max2[u];
        }
        ptr = ptr->next;
    }
    if(res < max1[u]){
        res = max1[u];
    }
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    Edge* edges = (Edge*)malloc((N-1)*sizeof(Edge));
    for(int i=0;i<N-1;i++) scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].v);
    qsort(edges, N-1, sizeof(Edge), cmp_edges);
    int count = 0;
    for(int i=0;i<N-1 && count<K;i++) {
        if(edges[i].v < 0){
            edges[i].v = 0;
            count++;
        }
    }
    for(int i=0;i<N-1;i++){
        add_edge(edges[i].x, edges[i].y, edges[i].v);
        add_edge(edges[i].y, edges[i].x, edges[i].v);
    }
    dfs(1, -1);
    printf("%lld\n", res);
    free(edges);
    return 0;
}