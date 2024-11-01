#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAXM 1000
#define MAXQ 1000
#define MAX_QUEUE (MAXN * MAXM)

int main(){
    int N, M, Q;
    scanf("%d %d %d", &N, &M, &Q);
    char grid[MAXN][MAXM];
    for(int i=0;i<N;i++) {
        scanf("%s", grid[i]);
    }
    // Use a single array for visited with query id
    int *visited = (int *)calloc(N*M, sizeof(int));
    // Queue for BFS
    int *queue = (int *)malloc(sizeof(int) * MAX_QUEUE);
    for(int q=1; q<=Q; q++){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1--; y1--; x2--; y2--;
        int count = 0;
        int head = 0, tail = 0;
        for(int i=x1;i<=x2;i++) {
            for(int j=y1;j<=y2;j++) {
                int idx = i*M + j;
                if(visited[idx] != q){
                    // Start BFS
                    count++;
                    queue[tail++] = idx;
                    visited[idx] = q;
                    char color = grid[i][j];
                    while(head < tail){
                        int current = queue[head++];
                        int ci = current / M;
                        int cj = current % M;
                        // Check neighbors
                        // Up
                        if(ci > x1){
                            int ni = ci-1, nj = cj;
                            if(nj >= y1 && nj <= y2 && grid[ni][nj]==color){
                                int nidx = ni*M + nj;
                                if(visited[nidx] != q){
                                    visited[nidx] = q;
                                    queue[tail++] = nidx;
                                }
                            }
                        }
                        // Down
                        if(ci < x2){
                            int ni = ci+1, nj = cj;
                            if(nj >= y1 && nj <= y2 && grid[ni][nj]==color){
                                int nidx = ni*M + nj;
                                if(visited[nidx] != q){
                                    visited[nidx] = q;
                                    queue[tail++] = nidx;
                                }
                            }
                        }
                        // Left
                        if(cj > y1){
                            int ni = ci, nj = cj-1;
                            if(ni >= x1 && ni <= x2 && grid[ni][nj]==color){
                                int nidx = ni*M + nj;
                                if(visited[nidx] != q){
                                    visited[nidx] = q;
                                    queue[tail++] = nidx;
                                }
                            }
                        }
                        // Right
                        if(cj < y2){
                            int ni = ci, nj = cj+1;
                            if(ni >= x1 && ni <= x2 && grid[ni][nj]==color){
                                int nidx = ni*M + nj;
                                if(visited[nidx] != q){
                                    visited[nidx] = q;
                                    queue[tail++] = nidx;
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%d\n", count);
    }
    free(visited);
    free(queue);
    return 0;
}