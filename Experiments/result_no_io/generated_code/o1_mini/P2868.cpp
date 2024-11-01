#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1001
#define MAXM 5001
#define INF 1e18

typedef struct {
    int to;
    int T;
} Edge;

Edge adj[MAXN][MAXM];
int head[MAXN];
int adj_size[MAXN];

int main(){
    int L, P;
    scanf("%d %d", &L, &P);
    int F[MAXN];
    for(int i=1;i<=L;i++) scanf("%d", &F[i]);
    // Initialize adjacency lists
    for(int i=1;i<=L;i++) adj_size[i]=0;
    for(int i=0;i<P;i++){
        int u, v, T;
        scanf("%d %d %d", &u, &v, &T);
        adj[u][adj_size[u]].to = v;
        adj[u][adj_size[u]].T = T;
        adj_size[u]++;
    }
    double low = 0.0, high = 1000000.0;
    double eps = 1e-7;
    for(int iter=0; iter<50; iter++){
        double mid = (low + high) / 2.0;
        // Compute w' = C*T_e - F_v
        // Run Bellman-Ford to detect if any cycle has sum(w') <0
        // Initialize distances
        double dist_arr[MAXN];
        for(int i=1;i<=L;i++) dist_arr[i]=0.0;
        // Initialize queue with all nodes
        int queue[MAXN];
        int front=0, rear=0;
        int inq[MAXN] = {0};
        int cnt[MAXN] = {0};
        for(int i=1;i<=L;i++){
            queue[rear++] = i;
            inq[i] = 1;
            cnt[i]++;
        }
        int found = 0;
        while(front < rear && !found){
            int u = queue[front++];
            inq[u] = 0;
            for(int i=0;i<adj_size[u] && !found;i++){
                int v = adj[u][i].to;
                double w = mid * adj[u][i].T - F[v];
                if(dist_arr[v] > dist_arr[u] + w + 1e-12){
                    dist_arr[v] = dist_arr[u] + w;
                    if(!inq[v]){
                        queue[rear++] = v;
                        inq[v] = 1;
                        cnt[v]++;
                        if(cnt[v] > L){
                            found = 1;
                            break;
                        }
                    }
                }
            }
        }
        if(found){
            high = mid;
        }
        else{
            low = mid;
        }
    }
    // After binary search, check if any cycle exists
    // To handle the case where no cycle exists, perform one more check
    double final_C = low;
    // Compute w' = C*T_e - F_v
    // Run Bellman-Ford to detect if any cycle has sum(w') <0
    double dist_arr[MAXN];
    for(int i=1;i<=L;i++) dist_arr[i]=0.0;
    // Initialize queue with all nodes
    int queue[MAXN];
    int front=0, rear=0;
    int inq[MAXN] = {0};
    int cnt_final[MAXN] = {0};
    for(int i=1;i<=L;i++){
        queue[rear++] = i;
        inq[i] = 1;
        cnt_final[i]++;
    }
    int found_final = 0;
    while(front < rear && !found_final){
        int u = queue[front++];
        inq[u] = 0;
        for(int i=0;i<adj_size[u] && !found_final;i++){
            int v = adj[u][i].to;
            double w = final_C * adj[u][i].T - F[v];
            if(dist_arr[v] > dist_arr[u] + w + 1e-12){
                dist_arr[v] = dist_arr[u] + w;
                if(!inq[v]){
                    queue[rear++] = v;
                    inq[v] = 1;
                    cnt_final[v]++;
                    if(cnt_final[v] > L){
                        found_final = 1;
                        break;
                    }
                }
            }
        }
    }
    if(!found_final){
        printf("0.00\n");
        return 0;
    }
    // Compute floor(low * 100) / 100
    long long x = (long long)(low * 100.0);
    printf("%.2lf\n", (double)x / 100.0);
    return 0;
}