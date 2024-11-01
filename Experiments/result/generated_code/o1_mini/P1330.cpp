#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10005
#define MAXM 100005

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} Queue;

Queue* createQueue(int size){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(size * sizeof(int));
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

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *u = (int*)malloc(m * sizeof(int));
    int *v = (int*)malloc(m * sizeof(int));
    int *deg = (int*)calloc(n+1, sizeof(int));
    
    for(int i=0;i<m;i++){
        scanf("%d %d", &u[i], &v[i]);
        deg[u[i]]++;
        deg[v[i]]++;
    }
    
    int *start = (int*)malloc((n+1) * sizeof(int));
    start[1] = 0;
    for(int i=2;i<=n;i++) start[i] = start[i-1] + deg[i-1];
    
    int total_adj = start[n] + deg[n];
    int *adj = (int*)malloc((2*m) * sizeof(int));
    memcpy(adj, malloc(2*m * sizeof(int)), 2*m * sizeof(int)); // Initialize if needed
    
    int *pos = (int*)malloc((n+1) * sizeof(int));
    memcpy(pos, start, (n+1) * sizeof(int));
    
    for(int i=0;i<m;i++){
        adj[pos[u[i]]++] = v[i];
        adj[pos[v[i]]++] = u[i];
    }
    
    free(u);
    free(v);
    free(deg);
    free(pos);
    
    int *color = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) color[i] = -1;
    
    Queue* q = createQueue(n);
    long long total = 0;
    int impossible = 0;
    
    for(int i=1;i<=n && !impossible;i++){
        if(color[i]==-1){
            enqueue(q, i);
            color[i] = 0;
            int cnt0 = 1, cnt1 = 0;
            while(!isEmpty(q) && !impossible){
                int current = dequeue(q);
                for(int j=start[current]; j<start[current]+deg[current]; j++){
                    int neighbor = adj[j];
                    if(color[neighbor]==-1){
                        color[neighbor] = 1 - color[current];
                        if(color[neighbor]==0) cnt0++;
                        else cnt1++;
                        enqueue(q, neighbor);
                    }
                    else{
                        if(color[neighbor] == color[current]){
                            impossible = 1;
                            break;
                        }
                    }
                }
            }
            if(!impossible){
                if(cnt0 < cnt1) total += cnt0;
                else total += cnt1;
            }
        }
    }
    
    if(impossible){
        printf("Impossible\n");
    }
    else{
        printf("%lld\n", total);
    }
    
    // Free allocated memory
    free(start);
    free(adj);
    free(color);
    free(q->data);
    free(q);
    
    return 0;
}