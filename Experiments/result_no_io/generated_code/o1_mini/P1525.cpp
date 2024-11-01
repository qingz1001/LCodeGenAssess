#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20001
#define MAXM 200000

typedef struct {
    int a;
    int b;
    int c;
} Edge;

Edge edges[100000];
int N, M;
int head_arr[MAXN];
int to_arr[MAXM];
int next_arr[MAXM];
int edge_cnt;
int color_arr[MAXN];
int queue_arr[MAXN];

int check_bipartite(int C) {
    // Initialize adjacency list
    memset(head_arr, -1, sizeof(int) * (N + 1));
    edge_cnt = 0;
    for(int i = 0; i < M; i++) {
        if(edges[i].c > C){
            to_arr[edge_cnt] = edges[i].b;
            next_arr[edge_cnt] = head_arr[edges[i].a];
            head_arr[edges[i].a] = edge_cnt++;
            
            to_arr[edge_cnt] = edges[i].a;
            next_arr[edge_cnt] = head_arr[edges[i].b];
            head_arr[edges[i].b] = edge_cnt++;
        }
    }
    
    // Initialize colors
    memset(color_arr, -1, sizeof(int) * (N + 1));
    
    // BFS to check bipartite
    for(int i = 1; i <= N; i++) {
        if(color_arr[i] == -1){
            color_arr[i] = 0;
            int front = 0, rear = 0;
            queue_arr[rear++] = i;
            while(front < rear){
                int current = queue_arr[front++];
                for(int e = head_arr[current]; e != -1; e = next_arr[e]){
                    int neighbor = to_arr[e];
                    if(color_arr[neighbor] == -1){
                        color_arr[neighbor] = 1 - color_arr[current];
                        queue_arr[rear++] = neighbor;
                    }
                    else if(color_arr[neighbor] != 1 - color_arr[current]){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c);
    }
    int l = 0, r = 1000000000, ans = 0;
    while(l < r){
        int mid = l + (r - l) / 2;
        if(check_bipartite(mid)){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    // After binary search, check if any conflicts exist
    // If l > 1e9, set to 0
    if(l > 1000000000){
        printf("0\n");
    }
    else{
        // Check if there are any edges with c > l
        int has_conflict = 0;
        for(int i = 0; i < M; i++) {
            if(edges[i].c > l){
                has_conflict = 1;
                break;
            }
        }
        if(has_conflict){
            printf("%d\n", l);
        }
        else{
            printf("0\n");
        }
    }
    return 0;
}