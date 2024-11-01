#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1001
#define MAX_K 10000
#define INF 1000000000

typedef struct {
    int neighbors[MAX_N];
    int cnt;
} AdjList;

typedef struct {
    int *data;
    int front, rear, size;
} Queue;

void enqueue(Queue *q, int val) {
    q->data[q->rear++] = val;
    q->size++;
}

int dequeue(Queue *q) {
    q->size--;
    return q->data[q->front++];
}

int is_empty(Queue *q) {
    return q->size == 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int d_min, d_max;
    scanf("%d %d", &d_min, &d_max);
    int x[n+1], y[n+1];
    for(int i=1;i<=n;i++) scanf("%d %d", &x[i], &y[i]);
    int k;
    scanf("%d", &k);
    int v[k], u[k];
    for(int i=0;i<k;i++) scanf("%d %d", &v[i], &u[i]);
    AdjList left_adj[n+1];
    AdjList right_adj[n+1];
    for(int i=1;i<=n;i++) { left_adj[i].cnt = 0; right_adj[i].cnt = 0; }
    for(int i=0;i<m;i++){
        int a, b, type;
        scanf("%d %d %d", &a, &b, &type);
        if(type == 0){
            left_adj[a].neighbors[left_adj[a].cnt++] = b;
            left_adj[b].neighbors[left_adj[b].cnt++] = a;
        }
        else{
            right_adj[a].neighbors[right_adj[a].cnt++] = b;
            right_adj[b].neighbors[right_adj[b].cnt++] = a;
        }
    }
    // Collect unique_v
    int unique_v_ids[n+1];
    int unique_v_count = 0;
    int is_unique_v_flag[n+1];
    memset(is_unique_v_flag, 0, sizeof(is_unique_v_flag));
    for(int i=0;i<k;i++) if(!is_unique_v_flag[v[i]]){
        unique_v_ids[unique_v_count++] = v[i];
        is_unique_v_flag[v[i]] = 1;
    }
    // Collect unique_u
    int unique_u_ids[n+1];
    int unique_u_count = 0;
    int is_unique_u_flag[n+1];
    memset(is_unique_u_flag, 0, sizeof(is_unique_u_flag));
    for(int i=0;i<k;i++) if(!is_unique_u_flag[u[i]]){
        unique_u_ids[unique_u_count++] = u[i];
        is_unique_u_flag[u[i]] = 1;
    }
    // Allocate distance arrays
    int **distance_left = (int **)malloc(unique_v_count * sizeof(int *));
    for(int i=0;i<unique_v_count;i++) distance_left[i] = (int *)malloc((n+1)*sizeof(int));
    int **distance_right = (int **)malloc(unique_u_count * sizeof(int *));
    for(int i=0;i<unique_u_count;i++) distance_right[i] = (int *)malloc((n+1)*sizeof(int));
    // BFS for left
    int *visited = (int *)malloc((n+1)*sizeof(int));
    Queue q_queue;
    q_queue.data = (int *)malloc((n+1)*sizeof(int));
    q_queue.front = q_queue.rear = q_queue.size = 0;
    for(int i=0;i<unique_v_count;i++){
        for(int j=1;j<=n;j++) distance_left[i][j] = INF;
        memset(visited, 0, (n+1)*sizeof(int));
        int start = unique_v_ids[i];
        distance_left[i][start] = 0;
        enqueue(&q_queue, start);
        visited[start] = 1;
        while(!is_empty(&q_queue)){
            int current = dequeue(&q_queue);
            for(int j=0; j<left_adj[current].cnt; j++){
                int neighbor = left_adj[current].neighbors[j];
                if(!visited[neighbor]){
                    distance_left[i][neighbor] = distance_left[i][current] + 1;
                    enqueue(&q_queue, neighbor);
                    visited[neighbor] = 1;
                }
            }
        }
        q_queue.front = q_queue.rear = q_queue.size = 0;
    }
    // BFS for right
    for(int i=0;i<unique_u_count;i++){
        for(int j=1;j<=n;j++) distance_right[i][j] = INF;
        memset(visited, 0, (n+1)*sizeof(int));
        int start = unique_u_ids[i];
        distance_right[i][start] = 0;
        enqueue(&q_queue, start);
        visited[start] = 1;
        while(!is_empty(&q_queue)){
            int current = dequeue(&q_queue);
            for(int j=0; j<right_adj[current].cnt; j++){
                int neighbor = right_adj[current].neighbors[j];
                if(!visited[neighbor]){
                    distance_right[i][neighbor] = distance_right[i][current] + 1;
                    enqueue(&q_queue, neighbor);
                    visited[neighbor] = 1;
                }
            }
        }
        q_queue.front = q_queue.rear = q_queue.size = 0;
    }
    free(visited);
    free(q_queue.data);
    // Map each attack to unique_v and unique_u
    int attack_unique_v[k];
    for(int i=0;i<k;i++) {
        for(int j=0;j<unique_v_count;j++) if(unique_v_ids[j]==v[i]){
            attack_unique_v[i] = j;
            break;
        }
    }
    int attack_unique_u[k];
    for(int i=0;i<k;i++) {
        for(int j=0;j<unique_u_count;j++) if(unique_u_ids[j]==u[i]){
            attack_unique_u[i] = j;
            break;
        }
    }
    // Compute results
    int *result = (int *)malloc(k * sizeof(int));
    for(int i=0;i<k;i++) result[i] = INF;
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++) {
            if(i == j) continue;
            int t1 = distance_left[attack_unique_v[i]][v[j]];
            int t2 = distance_right[attack_unique_u[i]][u[j]];
            if(t1 == INF || t2 == INF) continue;
            int t = (t1 > t2) ? t1 : t2;
            if(t < result[i]) result[i] = t;
        }
    }
    // Check distance constraints and set -1 if no valid j
    for(int i=0;i<k;i++){
        if(result[i] == INF){
            printf("-1\n");
        }
        else{
            printf("%d\n", result[i]);
        }
    }
    // Free memory
    for(int i=0;i<unique_v_count;i++) free(distance_left[i]);
    free(distance_left);
    for(int i=0;i<unique_u_count;i++) free(distance_right[i]);
    free(distance_right);
    free(result);
    return 0;
}