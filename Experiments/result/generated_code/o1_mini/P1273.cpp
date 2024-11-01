#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    int cost;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
} Node;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    Node* graph = (Node*)calloc(N+1, sizeof(Node));
    
    for(int i=1;i<=N-M;i++){
        int K;
        scanf("%d", &K);
        for(int j=0;j<K;j++){
            int A, C;
            scanf("%d %d", &A, &C);
            Edge* newEdge = (Edge*)malloc(sizeof(Edge));
            newEdge->to = A;
            newEdge->cost = C;
            newEdge->next = graph[i].head;
            graph[i].head = newEdge;
        }
    }
    
    int* pay = (int*)malloc((M+1)*sizeof(int));
    for(int i=1;i<=M;i++) scanf("%d", &pay[i]);
    
    // BFS to compute costs
    int* cost = (int*)malloc((N+1)*sizeof(int));
    for(int i=1;i<=N;i++) cost[i] = -1;
    int queue[N+1];
    int front=0, rear=0;
    queue[rear++] = 1;
    cost[1] = 0;
    while(front < rear){
        int u = queue[front++];
        Edge* e = graph[u].head;
        while(e){
            if(cost[e->to]==-1){
                cost[e->to] = cost[u] + e->cost;
                queue[rear++] = e->to;
            }
            e = e->next;
        }
    }
    
    // Collect di
    int totalM = M;
    int* di = (int*)malloc(M*sizeof(int));
    for(int i=0;i<M;i++) {
        int user = N-M+1 + i;
        di[i] = pay[i+1] - cost[user];
    }
    
    // Sort di descending
    int cmp(const void* a, const void* b){
        int da = *((int*)a);
        int db = *((int*)b);
        if(da < db) return 1;
        else if(da > db) return -1;
        else return 0;
    }
    qsort(di, M, sizeof(int), cmp);
    
    // Find maximum k
    long long sum = 0;
    int result = 0;
    for(int k=1;k<=M;k++){
        sum += di[k-1];
        if(sum >=0) result = k;
    }
    printf("%d", result);
    
    // Free memory
    for(int i=1;i<=N;i++){
        Edge* e = graph[i].head;
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(graph);
    free(pay);
    free(cost);
    free(di);
    return 0;
}