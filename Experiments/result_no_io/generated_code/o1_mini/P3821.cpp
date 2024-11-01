#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 51
#define MAXM 1251
#define MAXA 31
#define MAXT 5
#define INF INT32_MAX

typedef struct Edge {
    int to;
    int w;
} Edge;

typedef struct Node {
    Edge edges[MAXM];
    int cnt;
} Node;

typedef struct Monster {
    int T;
    int path[MAXT];
} Monster;

int n, m, s, t, k;
Node graph[MAXN];
int a;
Monster monsters[MAXA];
int forbidden[300][MAXN]; // period up to 60
int period = 1;

typedef long long ll;

int max(int a, int b) { return a > b ? a : b; }

int gcd(int a, int b){
    while(b){
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int lcm(int a, int b){
    return a / gcd(a, b) * b;
}

// BFS State
int visited[MAXN][60];
int queue_curr[300*50];
int queue_next[300*50];
int front, rear;

int check(int B){
    // Reset forbidden
    for(int i=0;i<period;i++) {
        for(int j=1;j<=n;j++) {
            forbidden[i][j] = 0;
        }
    }
    // Mark forbidden rooms
    for(int i=0;i<a;i++){
        Monster m = monsters[i];
        for(int t_step=0;t_step<period;t_step++){
            int pos = m.path[t_step % m.T];
            forbidden[t_step][pos] = 1;
        }
    }
    // If start is forbidden at time 0
    if(forbidden[0][s]) return 0;
    // Initialize BFS
    memset(visited, 0, sizeof(visited));
    front = rear = 0;
    queue_curr[rear++] = s;
    visited[0][s] = 1;
    // Iterate k steps
    int current_time = 0;
    while(current_time < k){
        // Prepare next queue
        int next_size = 0;
        for(int i=0;i<rear;i++){
            int u = queue_curr[i];
            for(int j=0;j<graph[u].cnt;j++){
                Edge e = graph[u].edges[j];
                if(e.w > B) continue;
                int v = e.to;
                int next_time = (current_time +1) % period;
                if(forbidden[next_time][v]) continue;
                if(!visited[next_time][v]){
                    visited[next_time][v] = 1;
                    queue_next[next_size++] = v;
                }
            }
        }
        if(next_size == 0) break;
        // Swap queues
        memcpy(queue_curr, queue_next, sizeof(int)*next_size);
        rear = next_size;
        memset(queue_next, 0, sizeof(queue_next));
        current_time++;
    }
    // Check if t is reachable at time k
    return visited[k % period][t];
}

int main(){
    // Read n, m, s, t, k
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);
    // Read edges, keep last w for multiple edges
    int last_w[MAXN][MAXN];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) last_w[i][j] = -1;
    }
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        last_w[u][v] = w;
        last_w[v][u] = w;
    }
    // Build graph
    for(int i=1;i<=n;i++) {
        graph[i].cnt =0;
        for(int j=1;j<=n;j++) {
            if(last_w[i][j] != -1){
                graph[i].edges[graph[i].cnt].to = j;
                graph[i].edges[graph[i].cnt].w = last_w[i][j];
                graph[i].cnt++;
            }
        }
    }
    // Read monsters
    scanf("%d", &a);
    for(int i=0;i<a;i++){
        scanf("%d", &monsters[i].T);
        for(int j=0;j<monsters[i].T;j++) scanf("%d", &monsters[i].path[j]);
        period = lcm(period, monsters[i].T);
    }
    // Read k
    // Binary search over B
    int left = 1, right = 1000000000, ans = -1;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(check(mid)){
            ans = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    if(ans != -1) printf("%d\n", ans);
    else printf("IMP0SSBLE!!\n");
    return 0;
}