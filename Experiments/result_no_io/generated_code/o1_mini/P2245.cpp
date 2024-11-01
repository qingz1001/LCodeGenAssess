#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 300005
#define LOGN 20
#define MAX_EDGES 600010
#define MAX_QUEUE 100005
#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef struct {
    int a;
    int b;
    int l;
} EdgeStruct;

typedef struct {
    int to;
    int weight;
    int next;
} EdgeList;

EdgeStruct edges[MAXM];
EdgeList adjList[MAX_EDGES];
int headAdj[MAXN];
int edge_cnt = 0;

int parentUF[MAXN];
int find_set(int u) {
    if(parentUF[u] != u){
        parentUF[u] = find_set(parentUF[u]);
    }
    return parentUF[u];
}

void union_set_func(int u, int v){
    int pu = find_set(u);
    int pv = find_set(v);
    if(pu != pv){
        parentUF[pu] = pv;
    }
}

int cmp(const void* a, const void* b){
    EdgeStruct *ea = (EdgeStruct*)a;
    EdgeStruct *eb = (EdgeStruct*)b;
    if(ea->l != eb->l)
        return ea->l - eb->l;
    return 0;
}

int depth_arr[MAXN];
int parent_arr[LOGN][MAXN];
int max_edge_arr[LOGN][MAXN];

int queue_arr[MAX_QUEUE];
int front_q, rear_q;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=0;i<M;i++){
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].l);
    }
    qsort(edges, M, sizeof(EdgeStruct), cmp);
    for(int i=1;i<=N;i++) {
        parentUF[i] = i;
        headAdj[i] = -1;
    }
    for(int i=0;i<M;i++){
        int a = edges[i].a;
        int b = edges[i].b;
        int l = edges[i].l;
        if(find_set(a) != find_set(b)){
            union_set_func(a, b);
            // Add edge a -> b
            adjList[edge_cnt].to = b;
            adjList[edge_cnt].weight = l;
            adjList[edge_cnt].next = headAdj[a];
            headAdj[a] = edge_cnt++;
            // Add edge b -> a
            adjList[edge_cnt].to = a;
            adjList[edge_cnt].weight = l;
            adjList[edge_cnt].next = headAdj[b];
            headAdj[b] = edge_cnt++;
        }
    }
    memset(depth_arr, -1, sizeof(depth_arr));
    // BFS to set depth, parent[0], max_edge[0]
    for(int u=1; u<=N; u++){
        if(depth_arr[u] == -1){
            depth_arr[u] = 0;
            front_q = 0;
            rear_q = 0;
            queue_arr[rear_q++] = u;
            while(front_q < rear_q){
                int current = queue_arr[front_q++];
                for(int e = headAdj[current]; e != -1; e = adjList[e].next){
                    int v = adjList[e].to;
                    int w = adjList[e].weight;
                    if(depth_arr[v] == -1){
                        depth_arr[v] = depth_arr[current] + 1;
                        parent_arr[0][v] = current;
                        max_edge_arr[0][v] = w;
                        queue_arr[rear_q++] = v;
                    }
                }
            }
        }
    }
    // Binary Lifting Preprocessing
    for(int k=1; k<LOGN; k++){
        for(int u=1; u<=N; u++){
            if(parent_arr[k-1][u] != 0){
                parent_arr[k][u] = parent_arr[k-1][parent_arr[k-1][u]];
                max_edge_arr[k][u] = MAX(max_edge_arr[k-1][u], max_edge_arr[k-1][parent_arr[k-1][u]]);
            }
        }
    }
    int Q;
    scanf("%d", &Q);
    for(int i=0;i<Q;i++){
        int A, B;
        scanf("%d %d", &A, &B);
        if(find_set(A) != find_set(B)){
            printf("impossible\n");
            continue;
        }
        if(A == B){
            printf("0\n");
            continue;
        }
        int u = A;
        int v = B;
        int max_val = 0;
        if(depth_arr[u] < depth_arr[v]){
            // Swap u and v
            int temp = u;
            u = v;
            v = temp;
        }
        // Lift u up to depth of v
        for(int k=LOGN-1; k>=0; k--){
            if(depth_arr[u] - (1<<k) >= depth_arr[v]){
                max_val = MAX(max_val, max_edge_arr[k][u]);
                u = parent_arr[k][u];
            }
        }
        if(u != v){
            for(int k=LOGN-1; k>=0; k--){
                if(parent_arr[k][u] != 0 && parent_arr[k][u] != parent_arr[k][v]){
                    max_val = MAX(max_val, max_edge_arr[k][u]);
                    max_val = MAX(max_val, max_edge_arr[k][v]);
                    u = parent_arr[k][u];
                    v = parent_arr[k][v];
                }
            }
            // Final step to the LCA
            max_val = MAX(max_val, max_edge_arr[0][u]);
            max_val = MAX(max_val, max_edge_arr[0][v]);
        }
        printf("%d\n", max_val);
    }
    return 0;
}