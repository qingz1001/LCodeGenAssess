#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

int head_arr[MAXN];
int edge_arr[MAXM];
int next_arr[MAXM];
int in_degree[MAXN];
int dp_arr[MAXN];
int queue_arr[MAXN];

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    for(int i=1;i<=N;i++) head_arr[i] = -1;
    for(int i=0;i<M;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        edge_arr[i] = y;
        next_arr[i] = head_arr[x];
        head_arr[x] = i;
        in_degree[y]++;
    }
    
    for(int i=1;i<=N;i++) dp_arr[i] = 1;
    
    int front=0, back=0;
    for(int i=1;i<=N;i++) {
        if(in_degree[i]==0){
            queue_arr[back++] = i;
        }
    }
    
    while(front < back){
        int x = queue_arr[front++];
        for(int i = head_arr[x]; i != -1; i = next_arr[i]){
            int y = edge_arr[i];
            if(dp_arr[y] < dp_arr[x] + 1){
                dp_arr[y] = dp_arr[x] + 1;
            }
            in_degree[y]--;
            if(in_degree[y] == 0){
                queue_arr[back++] = y;
            }
        }
    }
    
    for(int i=1;i<=N;i++) printf("%d\n", dp_arr[i]);
    
    return 0;
}