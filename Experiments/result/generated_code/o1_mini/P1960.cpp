#include <stdio.h>
#include <stdlib.h>

#define MAXN 5001
#define MAXM 100001

int adj_head[MAXN];
int edge_to[MAXM];
int edge_next_arr[MAXM];
int in_degree[MAXN];
int queue_array[MAXN];
int ranking[MAXN];

int main(){
    int N, M;
    scanf("%d", &N);
    scanf("%d", &M);
    for(int i=1; i<=N; i++) adj_head[i] = 0;
    for(int i=1; i<=M; i++){
        int X, Y;
        scanf("%d %d", &X, &Y);
        edge_to[i] = Y;
        edge_next_arr[i] = adj_head[X];
        adj_head[X] = i;
        in_degree[Y]++;
    }
    int front =0, rear=0;
    for(int i=1; i<=N; i++) if(in_degree[i]==0) queue_array[rear++] = i;
    int multiple =0;
    for(int t=0; t<N; t++){
        if(rear - front >1) multiple =1;
        if(rear - front ==0){
            break;
        }
        int current = queue_array[front++];
        ranking[t] = current;
        for(int e = adj_head[current]; e !=0; e = edge_next_arr[e]){
            int neighbor = edge_to[e];
            in_degree[neighbor]--;
            if(in_degree[neighbor]==0){
                queue_array[rear++] = neighbor;
            }
        }
    }
    for(int t=0; t<N; t++) printf("%d\n", ranking[t]);
    printf("%d\n", multiple?1:0);
    return 0;
}