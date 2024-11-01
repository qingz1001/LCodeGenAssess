#include <stdio.h>
#include <stdlib.h>

#define MAX_N 101
#define MAX_P 10000

typedef struct {
    int from;
    int weight;
} Edge;

int main(){
    int n, p;
    scanf("%d %d", &n, &p);
    
    int C[MAX_N], U[MAX_N];
    for(int i=1;i<=n;i++) {
        scanf("%d %d", &C[i], &U[i]);
    }
    
    // Initialize incoming and outgoing edges
    Edge incoming[MAX_N][MAX_N];
    int in_cnt[MAX_N] = {0};
    
    Edge outgoing[MAX_N][MAX_N];
    int out_cnt[MAX_N] = {0};
    
    for(int i=0;i<p;i++){
        int from, to, w;
        scanf("%d %d %d", &from, &to, &w);
        incoming[to][in_cnt[to]].from = from;
        incoming[to][in_cnt[to]].weight = w;
        in_cnt[to]++;
        
        outgoing[from][out_cnt[from]].from = to;
        outgoing[from][out_cnt[from]].weight = w;
        out_cnt[from]++;
    }
    
    // Topological Sort using Kahn's algorithm
    int in_degree[MAX_N];
    for(int i=1;i<=n;i++) {
        in_degree[i] = in_cnt[i];
    }
    
    int queue[MAX_N];
    int front = 0, rear = 0;
    for(int i=1;i<=n;i++) {
        if(in_degree[i] == 0){
            queue[rear++] = i;
        }
    }
    
    int topo_order[MAX_N];
    int idx = 0;
    while(front < rear){
        int u = queue[front++];
        topo_order[idx++] = u;
        for(int i=0;i<out_cnt[u];i++){
            int v = outgoing[u][i].from;
            in_degree[v]--;
            if(in_degree[v] == 0){
                queue[rear++] = v;
            }
        }
    }
    
    // If not all nodes are processed, there is a cycle, but problem guarantees DAG
    // Compute C_i in topological order
    int computed[MAX_N] = {0};
    for(int i=0;i<idx;i++){
        int u = topo_order[i];
        if(in_cnt[u] > 0){
            int sum = 0;
            for(int j=0;j<in_cnt[u];j++){
                int from = incoming[u][j].from;
                int w = incoming[u][j].weight;
                sum += w * C[from];
            }
            C[u] = sum - U[u];
        }
    }
    
    // Identify output layer neurons (no outgoing edges)
    int output_nodes[MAX_N];
    int out_num = 0;
    for(int i=1;i<=n;i++){
        if(out_cnt[i] == 0){
            output_nodes[out_num++] = i;
        }
    }
    
    // Collect output neurons with C_i >0
    int result[MAX_N][2];
    int res_cnt = 0;
    for(int i=0;i<out_num;i++){
        int node = output_nodes[i];
        if(C[node] > 0){
            result[res_cnt][0] = node;
            result[res_cnt][1] = C[node];
            res_cnt++;
        }
    }
    
    if(res_cnt == 0){
        printf("NULL");
    }
    else{
        // Sort the results by node number
        for(int i=0;i<res_cnt-1;i++){
            for(int j=i+1;j<res_cnt;j++){
                if(result[i][0] > result[j][0]){
                    int temp0 = result[i][0];
                    int temp1 = result[i][1];
                    result[i][0] = result[j][0];
                    result[i][1] = result[j][1];
                    result[j][0] = temp0;
                    result[j][1] = temp1;
                }
            }
        }
        for(int i=0;i<res_cnt;i++){
            printf("%d %d\n", result[i][0], result[i][1]);
        }
    }
    
    return 0;
}