#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_N 100005
#define INF 1e18

typedef struct Node {
    double critical_T;
    long long C;
    long long S;
} Node;

#include <string.h>

Node nodes[MAX_N];
long long prefix_sum_C[MAX_N];
long long prefix_sum_S_arr[MAX_N];
long long total_S = 0;

// For BFS
typedef struct Queue {
    int front, rear, size;
    int data[MAX_N];
} Queue;

void enqueue(Queue* q, int x){
    if(q->rear == MAX_N-1) return;
    q->data[++q->rear] = x;
    q->size++;
}

int dequeue(Queue* q){
    if(q->size ==0) return -1;
    int x = q->data[q->front++];
    q->size--;
    return x;
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    
    // Initialize
    memset(nodes, 0, sizeof(nodes));
    
    // Build tree
    // To store children
    int *children_counts = (int*)calloc(N+1, sizeof(int));
    int **children = (int**)malloc((N+1) * sizeof(int*));
    for(int i=1;i<=N;i++) children[i] = NULL;
    
    // Temporary storage for children
    int *temp = (int*)calloc(N+1, sizeof(int));
    
    // Read input
    // Nodes 2 to N
    for(int i=2;i<=N;i++){
        int P;
        long long C, M;
        scanf("%d %lld %lld", &P, &C, &M);
        nodes[i].C = C;
        // S will be set later
        // Build children list
        children_counts[P]++;
    }
    
    // Allocate memory for children
    for(int i=1;i<=N;i++){
        if(children_counts[i] >0){
            children[i] = (int*)malloc(children_counts[i] * sizeof(int));
            memset(children[i], 0, children_counts[i] * sizeof(int));
        }
    }
    
    // Reset and read again to fill children
    rewind(stdin);
    // Read N and K again
    scanf("%d %d", &N, &K);
    // Read nodes 2 to N
    int P;
    long long C, M;
    for(int i=2;i<=N;i++){
        scanf("%d %lld %lld", &P, &C, &M);
        // Assign to children
        children[P][temp[P]++] = i;
        nodes[i].C = C;
        // M will be used to compute S later
        nodes[i].S = M;
    }
    
    // BFS to compute S_i
    Queue q;
    q.front = 1;
    q.rear = 0;
    q.size = 0;
    enqueue(&q, 1);
    nodes[1].S = (long long)INF;
    
    while(q.size >0){
        int u = dequeue(&q);
        for(int i=0;i<children_counts[u];i++){
            int v = children[u][i];
            if(nodes[u].S < nodes[v].S){
                nodes[v].S = nodes[u].S;
            }
            else{
                // nodes[v].S already has M_v, take min
                // which is already done by assigning min(S_parent, M_v)
                nodes[v].S = nodes[v].S < nodes[u].S ? nodes[v].S : nodes[u].S;
            }
            enqueue(&q, v);
        }
    }
    
    // Prepare nodes list excluding node1
    int total_nodes = 0;
    Node sorted_nodes[MAX_N];
    for(int i=2;i<=N;i++){
        if(nodes[i].S ==0){
            sorted_nodes[total_nodes].critical_T = 1e20;
        }
        else{
            sorted_nodes[total_nodes].critical_T = (double)nodes[i].C / (double)nodes[i].S;
        }
        sorted_nodes[total_nodes].C = nodes[i].C;
        sorted_nodes[total_nodes].S = nodes[i].S;
        total_nodes++;
    }
    
    // Sort sorted_nodes by critical_T ascending
    int cmp(const void *a, const void *b){
        double ta = ((Node*)a)->critical_T;
        double tb = ((Node*)b)->critical_T;
        if(ta < tb) return -1;
        if(ta > tb) return 1;
        return 0;
    }
    qsort(sorted_nodes, total_nodes, sizeof(Node), cmp);
    
    // Compute prefix sums
    prefix_sum_C[0] = sorted_nodes[0].C;
    prefix_sum_S_arr[0] = sorted_nodes[0].S;
    for(int i=1;i<total_nodes;i++){
        prefix_sum_C[i] = prefix_sum_C[i-1] + sorted_nodes[i].C;
        prefix_sum_S_arr[i] = prefix_sum_S_arr[i-1] + sorted_nodes[i].S;
    }
    
    // Compute total_S
    total_S = prefix_sum_S_arr[total_nodes-1];
    
    // Process queries
    for(int q_idx=0; q_idx<K; q_idx++){
        long long T;
        scanf("%lld", &T);
        // Binary search for the last index where critical_T <= T
        int left =0, right = total_nodes-1, pos = -1;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(sorted_nodes[mid].critical_T <= (double)T){
                pos = mid;
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        long long sum_C =0, sum_S =0;
        if(pos >=0){
            sum_C = prefix_sum_C[pos];
            sum_S = prefix_sum_S_arr[pos];
        }
        long long cows = sum_C + (T * (total_S - sum_S));
        printf("%lld\n", cows);
    }
    
    // Free memory
    for(int i=1;i<=N;i++) {
        if(children[i] != NULL){
            free(children[i]);
        }
    }
    free(children);
    free(children_counts);
    free(temp);
    
    return 0;
}