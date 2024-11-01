#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int to;
    int weight;
} Edge;

int main(){
    int n, p;
    scanf("%d %d", &n, &p);
    
    long long C_init[101], U[101];
    for(int i=1;i<=n;i++){
        scanf("%lld %lld", &C_init[i], &U[i]);
    }
    
    Edge outgoing[101][100];
    int out_cnt[101];
    Edge incoming[101][100];
    int in_cnt[101];
    for(int i=1;i<=n;i++) {
        out_cnt[i]=0;
        in_cnt[i]=0;
    }
    
    for(int i=0;i<p;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        outgoing[u][out_cnt[u]].to = v;
        outgoing[u][out_cnt[u]].weight = w;
        out_cnt[u]++;
        
        incoming[v][in_cnt[v]].to = u;
        incoming[v][in_cnt[v]].weight = w;
        in_cnt[v]++;
    }
    
    // Identify output layer neurons
    int output_neurons[101];
    int out_num=0;
    for(int i=1;i<=n;i++) {
        if(out_cnt[i]==0){
            output_neurons[out_num++] = i;
        }
    }
    
    // Topological sort
    int in_degree[101];
    for(int i=1;i<=n;i++) in_degree[i] = in_cnt[i];
    
    int topo[101];
    int topo_cnt=0;
    int queue[101];
    int front=0, rear=0;
    for(int i=1;i<=n;i++) {
        if(in_degree[i]==0){
            queue[rear++] = i;
        }
    }
    
    while(front < rear){
        int u = queue[front++];
        topo[topo_cnt++] = u;
        for(int i=0;i<out_cnt[u];i++){
            int v = outgoing[u][i].to;
            in_degree[v]--;
            if(in_degree[v]==0){
                queue[rear++] = v;
            }
        }
    }
    
    // Compute C_i
    long long C[101];
    for(int i=1;i<=n;i++) C[i] = C_init[i];
    
    for(int i=0;i<topo_cnt;i++){
        int u = topo[i];
        if(in_cnt[u] >0){
            long long sum=0;
            for(int j=0;j<in_cnt[u];j++){
                int from = incoming[u][j].to;
                int w = incoming[u][j].weight;
                sum += (long long)w * C[from];
            }
            C[u] = sum - U[u];
        }
    }
    
    // Collect output neurons with C_i >0
    int result_ids[101];
    long long result_C[101];
    int res=0;
    for(int i=0;i<out_num;i++){
        int id = output_neurons[i];
        if(C[id] > 0){
            result_ids[res] = id;
            result_C[res] = C[id];
            res++;
        }
    }
    
    if(res ==0){
        printf("NULL\n");
    }
    else{
        // Sort by id ascending
        for(int i=0;i<res-1;i++){
            for(int j=i+1;j<res;j++){
                if(result_ids[i] > result_ids[j]){
                    int tmp_id = result_ids[i];
                    long long tmp_c = result_C[i];
                    result_ids[i] = result_ids[j];
                    result_C[i] = result_C[j];
                    result_ids[j] = tmp_id;
                    result_C[j] = tmp_c;
                }
            }
        }
        for(int i=0;i<res;i++) printf("%d %lld\n", result_ids[i], result_C[i]);
    }
    
    return 0;
}