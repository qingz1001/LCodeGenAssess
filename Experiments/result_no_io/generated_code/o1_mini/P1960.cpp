#include <stdio.h>

#define MAX_N 5001
#define MAX_M 100000

int adj_list[MAX_N];
int edge_to_arr[MAX_M];
int edge_next_arr[MAX_M];
int in_degree_arr[MAX_N];
int queue_arr[MAX_N];
int result_arr[MAX_N];

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++) adj_list[i] = -1;
    for(int i = 1; i <= N; i++) in_degree_arr[i] = 0;
    int edge_cnt = 0;
    for(int i = 0; i < M; i++){
        int X, Y;
        scanf("%d %d", &X, &Y);
        edge_to_arr[edge_cnt] = Y;
        edge_next_arr[edge_cnt] = adj_list[X];
        adj_list[X] = edge_cnt;
        edge_cnt++;
        in_degree_arr[Y]++;
    }
    int front = 0, rear = 0;
    for(int i = 1; i <= N; i++) {
        if(in_degree_arr[i] == 0){
            queue_arr[rear++] = i;
        }
    }
    int unique = 1;
    int index = 0;
    while(front < rear){
        if(rear - front > 1){
            unique = 0;
        }
        int x = queue_arr[front++];
        result_arr[index++] = x;
        int k = adj_list[x];
        while(k != -1){
            int y = edge_to_arr[k];
            in_degree_arr[y]--;
            if(in_degree_arr[y] == 0){
                queue_arr[rear++] = y;
            }
            k = edge_next_arr[k];
        }
    }
    for(int i = 0; i < N; i++) printf("%d\n", result_arr[i]);
    printf("%d\n", unique ? 0 : 1);
    return 0;
}