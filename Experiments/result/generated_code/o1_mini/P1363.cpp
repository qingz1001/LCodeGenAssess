#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNM 2250000

typedef long long ll;

int N, M;
char *grid;
int *parent;
ll *diff_x;
ll *diff_y;
int *queue;
int front, rear;

int find_set(int x, ll *total_x, ll *total_y) {
    if (parent[x] == x) {
        *total_x = 0;
        *total_y = 0;
        return x;
    }
    ll px, py;
    int root = find_set(parent[x], &px, &py);
    *total_x = diff_x[x] + px;
    *total_y = diff_y[x] + py;
    parent[x] = root;
    diff_x[x] = *total_x;
    diff_y[x] = *total_y;
    return root;
}

int main(){
    while(scanf("%d %d", &N, &M)!=EOF){
        grid = (char*)malloc(N*M + 1);
        for(int i=0;i<N;i++){
            scanf("%s", &grid[i*M]);
        }
        
        parent = (int*)malloc(N*M * sizeof(int));
        diff_x = (ll*)calloc(N*M, sizeof(ll));
        diff_y = (ll*)calloc(N*M, sizeof(ll));
        for(int i=0;i<N*M;i++) parent[i]=i;
        
        // Find S
        int start = -1;
        for(int i=0;i<N;i++) {
            for(int j=0;j<M;j++) {
                if(grid[i*M + j] == 'S'){
                    start = i*M + j;
                    break;
                }
            }
            if(start != -1) break;
        }
        
        // BFS
        queue = (int*)malloc(N*M * sizeof(int));
        front = 0;
        rear = 0;
        queue[rear++] = start;
        int *visited = (int*)calloc(N*M, sizeof(int));
        visited[start] = 1;
        int conflict = 0;
        while(front < rear && !conflict){
            int current = queue[front++];
            int ci = current / M;
            int cj = current % M;
            // Directions: U, D, L, R
            int dirs[4][2] = { {ci-1, cj}, {ci+1, cj}, {ci, cj-1}, {ci, cj+1} };
            ll shifts[4][2] = { {0,0}, {0,0}, {0,0}, {0,0} };
            for(int d=0; d<4; d++){
                int ni = dirs[d][0];
                int nj = dirs[d][1];
                ll shift_x = 0, shift_y = 0;
                if(ni <0){
                    ni += N;
                    shift_x = -1;
                }
                if(ni >=N){
                    ni -= N;
                    shift_x = 1;
                }
                if(nj <0){
                    nj += M;
                    shift_y = -1;
                }
                if(nj >=M){
                    nj -= M;
                    shift_y = 1;
                }
                if(grid[ni*M + nj] == '#' ) continue;
                int neighbor = ni*M + nj;
                // Define the difference between current and neighbor
                ll dx, dy;
                if(d ==0){ // U
                    dx = shift_x;
                    dy = shift_y;
                }
                else if(d ==1){ // D
                    dx = shift_x;
                    dy = shift_y;
                }
                else if(d ==2){ // L
                    dx = shift_x;
                    dy = shift_y;
                }
                else { // R
                    dx = shift_x;
                    dy = shift_y;
                }
                // Union current and neighbor
                ll total_x1, total_y1, total_x2, total_y2;
                int root1 = find_set(current, &total_x1, &total_y1);
                int root2 = find_set(neighbor, &total_x2, &total_y2);
                if(root1 != root2){
                    parent[root1] = root2;
                    diff_x[root1] = total_x2 - total_x1 + dx;
                    diff_y[root1] = total_y2 - total_y1 + dy;
                }
                else{
                    if(total_x1 - total_x2 != dx || total_y1 - total_y2 != dy){
                        conflict =1;
                        break;
                    }
                }
                if(!visited[neighbor]){
                    visited[neighbor]=1;
                    queue[rear++] = neighbor;
                }
            }
        }
        if(conflict) printf("Yes\n");
        else printf("No\n");
        free(grid);
        free(parent);
        free(diff_x);
        free(diff_y);
        free(queue);
    }
}