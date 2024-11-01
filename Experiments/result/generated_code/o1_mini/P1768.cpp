#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 7001
#define MAXM 20001

int head_arr[MAXN];
int to_arr[MAXM];
int V_arr[MAXM];
int P_arr[MAXM];
int next_arr[MAXM];

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++) head_arr[i]=-1;
    int edge_cnt=0;
    int u, v, Vi, Pi;
    for(int i=0;i<M;i++){
        scanf("%d %d %d %d", &u, &v, &Vi, &Pi);
        to_arr[edge_cnt] = v;
        V_arr[edge_cnt] = Vi;
        P_arr[edge_cnt] = Pi;
        next_arr[edge_cnt] = head_arr[u];
        head_arr[u] = edge_cnt;
        edge_cnt++;
    }
    // Check for cycle using iterative DFS
    bool has_cycle = false;
    bool *visited = (bool*)calloc(N+1, sizeof(bool));
    bool *onStack = (bool*)calloc(N+1, sizeof(bool));
    int *stack = (int*)malloc((N+1)*sizeof(int));
    int top = 0;
    for(int i=1;i<=N && !has_cycle;i++){
        if(!visited[i]){
            stack[top++] = i;
            visited[i] = true;
            onStack[i] = true;
            while(top >0 && !has_cycle){
                int current = stack[top-1];
                bool finished = true;
                for(int k=head_arr[current]; k!=-1 && !has_cycle; k=next_arr[k]){
                    int neighbor = to_arr[k];
                    if(!visited[neighbor]){
                        stack[top++] = neighbor;
                        visited[neighbor] = true;
                        onStack[neighbor] = true;
                        finished = false;
                        break;
                    }
                    else if(onStack[neighbor]){
                        has_cycle = true;
                        break;
                    }
                }
                if(finished){
                    onStack[current] = false;
                    top--;
                }
            }
        }
    }
    free(visited);
    free(onStack);
    free(stack);
    if(!has_cycle){
        printf("-1\n");
        return 0;
    }
    // Binary search for maximum ratio
    double low=0.0, high=200.0, mid, ans=-1.0;
    for(int it=0; it<50; it++){
        mid = (low + high) / 2.0;
        // SPFA to detect if any cycle has sum V - mid * P >=0
        double *d = (double*)calloc(N+1, sizeof(double));
        bool *inqueue = (bool*)calloc(N+1, sizeof(bool));
        int *cnt = (int*)calloc(N+1, sizeof(int));
        int *queue = (int*)malloc((N+1)*sizeof(int));
        int front=0, rear=0;
        for(int i=1;i<=N;i++){
            queue[rear++] = i;
            inqueue[i] = true;
        }
        bool flag = false;
        while(front < rear && !flag){
            int u = queue[front++];
            inqueue[u] = false;
            for(int k=head_arr[u]; k!=-1 && !flag; k=next_arr[k]){
                int v = to_arr[k];
                double w = (double)V_arr[k] - mid * (double)P_arr[k];
                if(d[v] < d[u] + w){
                    d[v] = d[u] + w;
                    if(!inqueue[v]){
                        queue[rear++] = v;
                        inqueue[v] = true;
                        cnt[v]++;
                        if(cnt[v] > N){
                            flag = true;
                            break;
                        }
                    }
                }
            }
        }
        free(d);
        free(inqueue);
        free(cnt);
        free(queue);
        if(flag){
            ans = mid;
            low = mid;
        }
        else{
            high = mid;
        }
    }
    // Print the answer with one decimal
    printf("%.1lf\n", ans);
    return 0;
}