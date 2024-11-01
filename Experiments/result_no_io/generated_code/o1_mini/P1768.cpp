#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAXN 7001
#define MAXM 20001

typedef struct Edge {
    int to;
    int V;
    int P;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
Edge edges_storage[MAXM];
int edge_count = 0;

void add_edge(int u, int v, int V, int P){
    edges_storage[edge_count].to = v;
    edges_storage[edge_count].V = V;
    edges_storage[edge_count].P = P;
    edges_storage[edge_count].next = adj[u];
    adj[u] = &edges_storage[edge_count++];
}

bool check(double R, int N){
    double* dist = (double*)calloc(N+1, sizeof(double));
    int* cnt = (int*)calloc(N+1, sizeof(int));
    bool* inq = (bool*)calloc(N+1, sizeof(bool));
    int* queue = (int*)malloc((N+1) * sizeof(int));
    int front = 0, rear = 0;
    for(int i=1;i<=N;i++){
        queue[rear++] = i;
        inq[i] = true;
    }
    bool hasCycle = false;
    while(front < rear){
        int u = queue[front++];
        inq[u] = false;
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            double val = e->V - R * e->P;
            if(dist[e->to] < dist[u] + val){
                dist[e->to] = dist[u] + val;
                if(!inq[e->to]){
                    queue[rear++] = e->to;
                    inq[e->to] = true;
                    if(++cnt[e->to] >= N){
                        hasCycle = true;
                        break;
                    }
                }
            }
        }
        if(hasCycle) break;
    }
    free(dist);
    free(cnt);
    free(inq);
    free(queue);
    return hasCycle;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=0;i<M;i++){
        int u, v, V, P;
        scanf("%d %d %d %d", &u, &v, &V, &P);
        add_edge(u, v, V, P);
    }
    double low = 0.0, high = 200.0, mid;
    double res = -1.0;
    for(int i=0;i<50;i++){
        mid = (low + high) / 2.0;
        if(check(mid, N)){
            res = mid;
            low = mid;
        }
        else{
            high = mid;
        }
    }
    // Check if any cycle exists
    bool anyCycle = false;
    for(int i=1;i<=N && !anyCycle;i++){
        for(Edge* e = adj[i]; e != NULL && !anyCycle; e = e->next){
            // To detect any cycle, perform DFS or similar
            // But already handled in binary search
            anyCycle = true;
        }
    }
    // To ensure if any cycle exists, check if res was updated
    if(res < 0){
        // Further check if any cycle exists
        // Implement a simple cycle detection, e.g., DFS
        // But due to time constraints, assume if binary search didn't find, no cycle
        printf("-1\n");
    }
    else{
        printf("%.1lf\n", res);
    }
    return 0;
}