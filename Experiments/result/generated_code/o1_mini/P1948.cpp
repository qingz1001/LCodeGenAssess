#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001
#define MAXE 20010
#define INF 1000000000

typedef struct {
    int to;
    int length;
    int next;
} Edge;

Edge edges[MAXE];
int headList[MAXN];
int edgeCount = 0;

// Function to add edge to adjacency list
void addEdge(int from, int to, int length) {
    edges[edgeCount].to = to;
    edges[edgeCount].length = length;
    edges[edgeCount].next = headList[from];
    headList[from] = edgeCount++;
}

// Function to perform 0-1 BFS and return minimum number of cables > L
int bfs(int n, int L, int K) {
    int min_cost[MAXN];
    for(int i=1;i<=n;i++) min_cost[i] = INF;
    min_cost[1] = 0;
    
    // Deque implementation
    int deque[MAXE];
    int front = 0, back = 0;
    deque[back++] = 1;
    
    while(front < back){
        int u = deque[front++];
        for(int e = headList[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            int w = edges[e].length;
            int new_cost = min_cost[u] + (w > L ? 1 : 0);
            if(new_cost < min_cost[v]){
                min_cost[v] = new_cost;
                if(w > L){
                    deque[back++] = v;
                }
                else{
                    front--;
                    if(front < 0) front = 0;
                    // Shift elements right to insert at front
                    for(int i = back; i > front; i--){
                        deque[i] = deque[i-1];
                    }
                    deque[front++] = v;
                    back++;
                }
            }
        }
    }
    return min_cost[n];
}

int main(){
    int n, p, k;
    scanf("%d %d %d", &n, &p, &k);
    
    // Initialize adjacency list
    for(int i=1;i<=n;i++) headList[i] = -1;
    
    // Read edges
    for(int i=0;i<p;i++){
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        addEdge(a, b, l);
        addEdge(b, a, l);
    }
    
    int low = 0, high = 1000000, answer = -1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        int res = bfs(n, mid, k);
        if(res <= k){
            answer = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    
    // Check if answer was found
    if(answer != -1){
        printf("%d\n", answer);
    }
    else{
        printf("-1\n");
    }
    
    return 0;
}