#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Queue implementation for BFS
typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} Queue;

Queue* createQueue(int size){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(sizeof(int)*size);
    q->front = 0;
    q->rear = 0;
    q->size = size;
    return q;
}

int isEmpty(Queue* q){
    return q->front == q->rear;
}

void enqueue(Queue* q, int val){
    q->data[q->rear++] = val;
}

int dequeue(Queue* q){
    return q->data[q->front++];
}

void freeQueue(Queue* q){
    free(q->data);
    free(q);
}

// BFS to compute distances
void bfs(int n, int **graph, int src, int *dist){
    for(int i=0;i<n;i++) dist[i] = INT32_MAX;
    Queue* q = createQueue(n*n);
    dist[src] = 0;
    enqueue(q, src);
    while(!isEmpty(q)){
        int u = dequeue(q);
        for(int i=0; i<graph[u][0]; i++){
            int v = graph[u][i+1];
            if(dist[v] == INT32_MAX){
                dist[v] = dist[u] + 1;
                enqueue(q, v);
            }
        }
    }
    freeQueue(q);
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int d_min, d_max;
    scanf("%d %d", &d_min, &d_max);
    int *x = (int*)malloc(sizeof(int)*n);
    int *y = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d %d", &x[i], &y[i]);
    int k;
    scanf("%d", &k);
    int *v_list = (int*)malloc(sizeof(int)*k);
    int *u_list = (int*)malloc(sizeof(int)*k);
    for(int i=0;i<k;i++){
        scanf("%d %d", &v_list[i], &u_list[i]);
        v_list[i]--;
        u_list[i]--;
    }
    // Initialize graphs
    int **left_graph = (int**)malloc(sizeof(int*)*n);
    int **right_graph = (int**)malloc(sizeof(int*)*n);
    int *left_size = (int*)calloc(n, sizeof(int));
    int *right_size = (int*)calloc(n, sizeof(int));
    for(int i=0;i<n;i++){
        left_graph[i] = (int*)malloc(sizeof(int)*(m*2+1));
        right_graph[i] = (int*)malloc(sizeof(int)*(m*2+1));
        left_graph[i][0] = 0;
        right_graph[i][0] = 0;
    }
    for(int i=0;i<m;i++){
        int a, b, type;
        scanf("%d %d %d", &a, &b, &type);
        a--; b--;
        if(type == 0){
            left_graph[a][ ++left_graph[a][0] ] = b;
            left_graph[b][ ++left_graph[b][0] ] = a;
        }
        else{
            right_graph[a][ ++right_graph[a][0] ] = b;
            right_graph[b][ ++right_graph[b][0] ] = a;
        }
    }
    // Compute all distances for left and right
    int **d_left = (int**)malloc(sizeof(int*)*n);
    int **d_right = (int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++){
        d_left[i] = (int*)malloc(sizeof(int)*n);
        d_right[i] = (int*)malloc(sizeof(int)*n);
    }
    for(int i=0;i<n;i++) bfs(n, left_graph, i, d_left[i]);
    for(int i=0;i<n;i++) bfs(n, right_graph, i, d_right[i]);
    // Read attacks are already read
    // For each attack, find min t
    for(int i=0;i<k;i++){
        int vi = v_list[i];
        int ui = u_list[i];
        int min_t = INT32_MAX;
        for(int j=0;j<k;j++){
            if(j == i) continue;
            int vj = v_list[j];
            int uj = u_list[j];
            int dl = d_left[vi][vj];
            int dr = d_right[ui][uj];
            if(dl == INT32_MAX || dr == INT32_MAX) continue;
            int t = dl > dr ? dl : dr;
            if(t < min_t){
                min_t = t;
            }
        }
        if(min_t != INT32_MAX){
            printf("%d\n", min_t);
        }
        else{
            printf("-1\n");
        }
    }
    // Free memory
    for(int i=0;i<n;i++){
        free(left_graph[i]);
        free(right_graph[i]);
        free(d_left[i]);
        free(d_right[i]);
    }
    free(left_graph);
    free(right_graph);
    free(d_left);
    free(d_right);
    free(left_size);
    free(right_size);
    free(x);
    free(y);
    free(v_list);
    free(u_list);
    return 0;
}