#include <stdio.h>
#include <stdlib.h>

#define N_MAX 1001
#define P_MAX 20000
#define INF 1000000000

typedef struct {
    int to;
    int len;
} Edge;

typedef struct {
    int node;
    int cnt;
} QueueNode;

Edge adj[N_MAX][10000];
int adj_size_arr[N_MAX];

int check(int m, int N, int K) {
    int dist[N_MAX];
    for(int i = 1; i <= N; i++) dist[i] = K + 1;
    dist[1] = 0;
    
    // Initialize queue
    QueueNode queue_[100000];
    int front = 0, rear = 0;
    
    queue_[rear].node = 1;
    queue_[rear].cnt = 0;
    rear++;
    
    while(front < rear){
        QueueNode qn = queue_[front++];
        int u = qn.node;
        int cnt_u = qn.cnt;
        
        for(int i = 0; i < adj_size_arr[u]; i++) {
            int v = adj[u][i].to;
            int len = adj[u][i].len;
            int new_cnt = cnt_u + (len > m ? 1 : 0);
            if(new_cnt < dist[v] && new_cnt <= K){
                dist[v] = new_cnt;
                queue_[rear].node = v;
                queue_[rear].cnt = new_cnt;
                rear++;
                if(rear >= 100000) break;
            }
        }
    }
    
    return dist[N] <= K;
}

int main(){
    int N, P, K;
    scanf("%d %d %d", &N, &P, &K);
    
    int a, b, l;
    int max_L = 0;
    for(int i = 0; i < P; i++){
        scanf("%d %d %d", &a, &b, &l);
        adj[a][adj_size_arr[a]++] = (Edge){b, l};
        adj[b][adj_size_arr[b]++] = (Edge){a, l};
        if(l > max_L) max_L = l;
    }
    
    // Binary search
    int left = 0, right = max_L, ans = -1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(check(mid, N, K)){
            ans = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    
    // Check if N is 1
    if(N == 1){
        printf("0\n");
        return 0;
    }
    
    // Check if ans was found
    if(ans != -1){
        printf("%d\n", ans);
    }
    else{
        printf("-1\n");
    }
    
    return 0;
}