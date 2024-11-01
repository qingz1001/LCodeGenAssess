#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAX_R 40
#define MAX_C 26
#define MAX_POS 1040
#define MAX_KNIGHTS 100
#define INF 1000000

typedef struct {
    int r, c;
} Position;

typedef struct {
    int r, c;
} QueueNode;

int R, C;
char buffer[10000];
Position king;
Position knights[MAX_KNIGHTS];
int num_knights = 0;

// Directions for king
int drk[8] = {-1,-1,-1,0,0,1,1,1};
int dck[8] = {-1,0,1,-1,1,-1,0,1};

// Directions for knight
int drn[8] = {-2,-1,1,2,2,1,-1,-2};
int dcn[8] = {1,2,2,1,-1,-2,-2,-1};

// Distance matrices
int king_dist[MAX_R][MAX_C][MAX_R][MAX_C];
int knight_dist[MAX_R][MAX_C][MAX_R][MAX_C];

// BFS for king
void bfs_king(int sr, int sc, int dist[MAX_R][MAX_C]){
    int visited[MAX_R][MAX_C];
    memset(visited, 0, sizeof(visited));
    for(int i=0;i<R;i++) for(int j=0;j<C;j++) dist[i][j] = INF;
    QueueNode queue[MAX_R*MAX_C];
    int front=0, rear=0;
    queue[rear++] = (QueueNode){sr, sc};
    dist[sr][sc] = 0;
    visited[sr][sc] = 1;
    while(front < rear){
        QueueNode current = queue[front++];
        for(int d=0; d<8; d++){
            int nr = current.r + drk[d];
            int nc = current.c + dck[d];
            if(nr >=0 && nr < R && nc >=0 && nc < C && !visited[nr][nc]){
                dist[nr][nc] = dist[current.r][current.c] + 1;
                queue[rear++] = (QueueNode){nr, nc};
                visited[nr][nc] = 1;
            }
        }
    }
}

// BFS for knight
void bfs_knight(int sr, int sc, int dist[MAX_R][MAX_C]){
    int visited[MAX_R][MAX_C];
    memset(visited, 0, sizeof(visited));
    for(int i=0;i<R;i++) for(int j=0;j<C;j++) dist[i][j] = INF;
    QueueNode queue[MAX_R*MAX_C];
    int front=0, rear=0;
    queue[rear++] = (QueueNode){sr, sc};
    dist[sr][sc] = 0;
    visited[sr][sc] = 1;
    while(front < rear){
        QueueNode current = queue[front++];
        for(int d=0; d<8; d++){
            int nr = current.r + drn[d];
            int nc = current.c + dcn[d];
            if(nr >=0 && nr < R && nc >=0 && nc < C && !visited[nr][nc]){
                dist[nr][nc] = dist[current.r][current.c] + 1;
                queue[rear++] = (QueueNode){nr, nc};
                visited[nr][nc] = 1;
            }
        }
    }
}

int main(){
    // Read R and C
    if(scanf("%d %d", &R, &C)!=2) return 0;
    // Read the rest as tokens
    int token_r = 0, token_c = 0;
    char col;
    int row;
    while(scanf(" %c %d", &col, &row) == 2){
        int c = col - 'A';
        int r = row -1;
        if(token_r ==0 && token_c ==0){
            king.r = r;
            king.c = c;
            token_r = token_c =1;
        }
        else{
            knights[num_knights].r = r;
            knights[num_knights].c = c;
            num_knights++;
        }
    }
    // Precompute distances
    // For king
    for(int i=0;i<R;i++) for(int j=0;j<C;j++) {
        bfs_king(i, j, king_dist[i][j]);
    }
    // For knights
    for(int i=0;i<R;i++) for(int j=0;j<C;j++) {
        bfs_knight(i, j, knight_dist[i][j]);
    }
    int min_total = INF;
    // Iterate over all target cells
    for(int tr=0; tr<R; tr++) {
        for(int tc=0; tc<C; tc++) {
            // Case 1: No merge
            int total = king_dist[king.r][king.c][tr][tc];
            for(int k=0; k<num_knights; k++) {
                total += knight_dist[knights[k].r][knights[k].c][tr][tc];
            }
            if(total < min_total){
                min_total = total;
            }
            // Case 2: Merge king with one knight
            for(int k=0; k<num_knights; k++) {
                // Iterate over all possible meeting points
                for(int mr=0; mr<R; mr++) {
                    for(int mc=0; mc<C; mc++) {
                        int dk = king_dist[king.r][king.c][mr][mc];
                        int dk_n = knight_dist[knights[k].r][knights[k].c][mr][mc];
                        int d_kn_to_t = knight_dist[mr][mc][tr][tc];
                        if(dk < INF && dk_n < INF && d_kn_to_t < INF){
                            int current = dk + dk_n + d_kn_to_t;
                            // Add other knights
                            for(int kk=0; kk<num_knights; kk++) {
                                if(kk !=k){
                                    current += knight_dist[knights[kk].r][knights[kk].c][tr][tc];
                                }
                            }
                            if(current < min_total){
                                min_total = current;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", min_total);
    return 0;
}