#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 500
#define MAX_M 500
#define MAX_SIZE 250000

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    // Initialize height grid
    int height[MAX_N][MAX_M];
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            scanf("%d", &height[i][j]);
        }
    }
    
    // Directions: up, down, left, right
    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, -1, 1};
    
    // Identify sources
    bool is_source[MAX_N][MAX_M];
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            bool source = true;
            for(int d=0; d<4; d++) {
                int ni = i + di[d];
                int nj = j + dj[d];
                if(ni >=0 && ni < N && nj >=0 && nj < M){
                    if(height[ni][nj] > height[i][j]){
                        source = false;
                        break;
                    }
                }
            }
            is_source[i][j] = source;
        }
    }
    
    // Collect sources and check if all are on first row
    bool all_sources_first_row = true;
    int reservoir_count = 0;
    // To store first row sources
    int queue_x[MAX_SIZE];
    int queue_y[MAX_SIZE];
    int head = 0, tail = 0;
    
    for(int j=0; j<M; j++) {
        if(is_source[0][j]){
            reservoir_count++;
            // Enqueue for BFS if needed
            queue_x[tail] = 0;
            queue_y[tail] = j;
            tail++;
        }
    }
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(is_source[i][j]){
                if(i !=0){
                    all_sources_first_row = false;
                }
            }
        }
    }
    
    if(all_sources_first_row){
        printf("1\n%d\n", reservoir_count);
    }
    else{
        // Perform BFS from first row sources
        bool visited[MAX_N][MAX_M];
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                visited[i][j] = false;
            }
        }
        // Initialize queue with first row sources
        head = 0;
        tail = 0;
        for(int j=0; j<M; j++) {
            if(is_source[0][j]){
                visited[0][j] = true;
                queue_x[tail] = 0;
                queue_y[tail] = j;
                tail++;
            }
        }
        
        while(head < tail){
            int x = queue_x[head];
            int y = queue_y[head];
            head++;
            for(int d=0; d<4; d++) {
                int ni = x + di[d];
                int nj = y + dj[d];
                if(ni >=0 && ni < N && nj >=0 && nj < M){
                    if(height[ni][nj] <= height[x][y] && !visited[ni][nj]){
                        visited[ni][nj] = true;
                        queue_x[tail] = ni;
                        queue_y[tail] = nj;
                        tail++;
                    }
                }
            }
        }
        
        // Count last row cells not visited
        int dead = 0;
        for(int j=0; j<M; j++) {
            if(!visited[N-1][j]){
                dead++;
            }
        }
        printf("0\n%d\n", dead);
    }
    
    return 0;
}