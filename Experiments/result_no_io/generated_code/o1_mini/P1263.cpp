#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 200
#define MAX_N 200
#define MAX_H 400
#define MAX_V 400
#define MAX_EDGES 80000

typedef struct {
    int v;
    int x;
    int y;
} Edge;

Edge adj[MAX_H + 1][MAX_EDGES];
int adj_size[MAX_H + 1];

int h_id[MAX_M + 1][MAX_N + 1];
int v_id[MAX_M + 1][MAX_N + 1];
int h_cnt = 0, v_cnt = 0;

int matchV[MAX_V + 1];
int guardX[MAX_V + 1];
int guardY[MAX_V + 1];
int visitedV[MAX_V + 1];

int m, n;
int grid[MAX_M +1][MAX_N +1];

int DFS(int u){
    for(int i=0;i < adj_size[u];i++){
        int v = adj[u][i].v;
        if(!visitedV[v]){
            visitedV[v] = 1;
            if(matchV[v] == -1 || DFS(matchV[v])){
                matchV[v] = u;
                guardX[v] = adj[u][i].x;
                guardY[v] = adj[u][i].y;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    scanf("%d %d", &m, &n);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            scanf("%d", &grid[i][j]);
        }
    }
    // Assign horizontal IDs
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(grid[i][j] != 2){
                if(j == 1 || grid[i][j-1]==2){
                    h_cnt++;
                }
                h_id[i][j] = h_cnt;
            }
            else{
                h_id[i][j] = 0;
            }
        }
    }
    // Assign vertical IDs
    for(int j=1;j<=n;j++){
        for(int i=1;i<=m;i++){
            if(grid[i][j] != 2){
                if(i == 1 || grid[i-1][j]==2){
                    v_cnt++;
                }
                v_id[i][j] = v_cnt;
            }
            else{
                v_id[i][j] = 0;
            }
        }
    }
    // Build adjacency list
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(grid[i][j] == 0){
                int h = h_id[i][j];
                int v = v_id[i][j];
                if(h !=0 && v !=0){
                    adj[h][adj_size[h]].v = v;
                    adj[h][adj_size[h]].x = i;
                    adj[h][adj_size[h]].y = j;
                    adj_size[h]++;
                }
            }
        }
    }
    // Initialize matches
    for(int i=1;i<=v_cnt;i++) matchV[i] = -1;
    int result = 0;
    // Perform matching
    for(int u=1;u<=h_cnt;u++){
        memset(visitedV, 0, sizeof(visitedV));
        if(DFS(u)) result++;
    }
    // Collect matched positions
    printf("%d\n", result);
    for(int v=1;v<=v_cnt;v++){
        if(matchV[v] != -1){
            printf("%d %d\n", guardX[v], guardY[v]);
        }
    }
    return 0;
}