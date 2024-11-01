#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 30
#define MAX_M 30
#define MAX_Q 500
#define MAX_QUEUE (900*900)
#define DIRS 4

typedef struct {
    int blank;
    int piece;
} State;

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    int board[MAX_N][MAX_M];
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d", &board[i][j]);
        }
    }
    // Read all queries
    int queries[q][6];
    for(int i=0;i<q;i++) {
        scanf("%d %d %d %d %d %d", &queries[i][0], &queries[i][1],
              &queries[i][2], &queries[i][3],
              &queries[i][4], &queries[i][5]);
    }
    // Directions: up, down, left, right
    int dx[DIRS] = {-1, 1, 0, 0};
    int dy[DIRS] = {0, 0, -1, 1};
    // Visited array with query id
    int visited_size = n*m;
    int *visited = (int*)malloc(sizeof(int)*n*m*n*m);
    memset(visited, 0, sizeof(int)*n*m*n*m);
    // Queue
    State *queue = (State*)malloc(sizeof(State)*MAX_QUEUE);
    int front, rear;
    for(int qid=1; qid<=q; qid++){
        int EX = queries[qid-1][0]-1;
        int EY = queries[qid-1][1]-1;
        int SX = queries[qid-1][2]-1;
        int SY = queries[qid-1][3]-1;
        int TX = queries[qid-1][4]-1;
        int TY = queries[qid-1][5]-1;
        int initial_blank = EX * m + EY;
        int initial_piece = SX * m + SY;
        int target_piece = TX * m + TY;
        // Check if initial and target positions are movable
        if(board[EX][EY]==0 || board[SX][SY]==0 || board[TX][TY]==0){
            printf("-1\n");
            continue;
        }
        // Initialize BFS
        front = 0;
        rear = 0;
        queue[rear].blank = initial_blank;
        queue[rear].piece = initial_piece;
        rear++;
        int found = -1;
        // Mark visited
        visited[initial_blank * (n*m) + initial_piece] = qid;
        // BFS
        int steps = 0;
        while(front < rear){
            int current_size = rear - front;
            for(int i=0;i<current_size;i++){
                State current = queue[front++];
                if(current.piece == target_piece){
                    found = steps;
                    front = rear; // break all
                    break;
                }
                int bx = current.blank / m;
                int by = current.blank % m;
                int px = current.piece / m;
                int py = current.piece % m;
                for(int d=0; d<DIRS; d++){
                    int nbx = bx + dx[d];
                    int nby = by + dy[d];
                    if(nbx <0 || nbx >=n || nby <0 || nby >=m) continue;
                    if(board[nbx][nby]==0) continue;
                    int new_blank = nbx * m + nby;
                    if(new_blank == current.piece){
                        // Push the piece
                        int npx = px + dx[d];
                        int npy = py + dy[d];
                        if(npx <0 || npx >=n || npy <0 || npy >=m) continue;
                        if(board[npx][npy]==0) continue;
                        int new_piece = npx * m + npy;
                        if(visited[new_blank * (n*m) + new_piece] != qid){
                            visited[new_blank * (n*m) + new_piece] = qid;
                            queue[rear].blank = new_blank;
                            queue[rear].piece = new_piece;
                            rear++;
                            if(rear >= MAX_QUEUE){
                                // Queue overflow, should not happen
                                break;
                            }
                        }
                    }
                    else{
                        // Just move the blank
                        if(visited[new_blank * (n*m) + current.piece] != qid){
                            visited[new_blank * (n*m) + current.piece] = qid;
                            queue[rear].blank = new_blank;
                            queue[rear].piece = current.piece;
                            rear++;
                            if(rear >= MAX_QUEUE){
                                // Queue overflow, should not happen
                                break;
                            }
                        }
                    }
                }
            }
            steps++;
            if(found != -1) break;
            if(steps > n*m*2) break; // Prevent infinite loop
        }
        printf("%d\n", found);
    }
    free(queue);
    free(visited);
    return 0;
}