#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_R 40
#define MAX_C 26
#define MAX_K 1000
#define INF 1000000000

typedef struct {
    int r;
    int c;
} Position;

// Queue for BFS
typedef struct {
    int r;
    int c;
} QueueNode;

void bfs(int R, int C, int start_r, int start_c, int steps[][MAX_C], int deltas[][2], int num_deltas) {
    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            steps[i][j] = INF;
        }
    }
    QueueNode queue[R*C];
    int front = 0, rear = 0;
    queue[rear].r = start_r;
    queue[rear].c = start_c;
    rear++;
    steps[start_r][start_c] = 0;
    while(front < rear){
        int current_r = queue[front].r;
        int current_c = queue[front].c;
        front++;
        for(int i=0;i<num_deltas;i++) {
            int nr = current_r + deltas[i][0];
            int nc = current_c + deltas[i][1];
            if(nr >=0 && nr < R && nc >=0 && nc < C && steps[nr][nc]==INF){
                steps[nr][nc] = steps[current_r][current_c] + 1;
                queue[rear].r = nr;
                queue[rear].c = nc;
                rear++;
            }
        }
    }
}

int main(){
    int R, C;
    scanf("%d %d", &R, &C);
    // Read the remaining lines
    char buffer[10000];
    Position king;
    Position knights[MAX_K];
    int K = 0;
    // Read all remaining input
    fgets(buffer, sizeof(buffer), stdin); // consume the newline after C
    while(fgets(buffer, sizeof(buffer), stdin)){
        char *token = strtok(buffer, " \n");
        while(token != NULL){
            int len = strlen(token);
            if(len < 2){
                token = strtok(NULL, " \n");
                continue;
            }
            char col = token[0];
            int row = atoi(&token[1]) -1;
            int c = col - 'A';
            if(K == 0){
                king.r = row;
                king.c = c;
            }
            else{
                knights[K-1].r = row;
                knights[K-1].c = c;
                K++;
            }
            token = strtok(NULL, " \n");
        }
    }
    // After first position is king, the rest are knights
    // Adjust K
    K = 0;
    // Re-read to count knights
    fseek(stdin, 0, SEEK_SET);
    scanf("%d %d", &R, &C);
    // Read positions again
    fgets(buffer, sizeof(buffer), stdin); // consume the first newline
    while(fgets(buffer, sizeof(buffer), stdin)){
        char *token = strtok(buffer, " \n");
        while(token != NULL){
            int len = strlen(token);
            if(len < 2){
                token = strtok(NULL, " \n");
                continue;
            }
            char col = token[0];
            int row = atoi(&token[1]) -1;
            int c = col - 'A';
            if(K == 0){
                king.r = row;
                king.c = c;
                K++;
            }
            else{
                knights[K-1].r = row;
                knights[K-1].c = c;
                K++;
            }
            token = strtok(NULL, " \n");
        }
    }
    K = K >0 ? K-1 : 0;
    // Define movement deltas
    int king_deltas[8][2] = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},         {0,1},
        {1,-1}, {1,0}, {1,1}
    };
    int knight_deltas[8][2] = {
        {2,1},{1,2},{-1,2},{-2,1},
        {-2,-1},{-1,-2},{1,-2},{2,-1}
    };
    // Compute king_steps
    int king_steps[MAX_R][MAX_C];
    bfs(R, C, king.r, king.c, king_steps, king_deltas, 8);
    // Compute knight_steps
    int **knight_steps = (int **)malloc(K * sizeof(int *));
    for(int k=0; k<K; k++) {
        knight_steps[k] = (int *)malloc(R * C * sizeof(int));
        int temp_steps[MAX_R][MAX_C];
        bfs(R, C, knights[k].r, knights[k].c, temp_steps, knight_deltas, 8);
        // Flatten the 2D array
        for(int r=0; r<R; r++) {
            for(int c=0; c<C; c++) {
                knight_steps[k][r*C + c] = temp_steps[r][c];
            }
        }
    }
    // Initialize min_total_steps
    int min_total_steps = INF;
    // Iterate over all target cells
    for(int tr=0; tr<R; tr++) {
        for(int tc=0; tc<C; tc++) {
            // Compute sum_steps without pairing
            int sum_steps = king_steps[tr][tc];
            for(int k=0; k<K; k++) {
                sum_steps += knight_steps[k][tr*C + tc];
            }
            if(sum_steps < min_total_steps){
                min_total_steps = sum_steps;
            }
            // Compute t_steps via knight BFS from target
            int t_steps[MAX_R][MAX_C];
            bfs(R, C, tr, tc, t_steps, knight_deltas, 8);
            // Compute sum_steps_total
            int sum_steps_total =0;
            for(int k=0; k<K; k++) {
                sum_steps_total += knight_steps[k][tr*C + tc];
            }
            // For each knight, compute the option with pairing
            for(int k=0; k<K; k++) {
                int min_option = INF;
                for(int r=0; r<R; r++) {
                    for(int c=0; c<C; c++) {
                        int tmp = king_steps[r][c] + knight_steps[k][r*C + c] + t_steps[r][c];
                        if(tmp < min_option){
                            min_option = tmp;
                        }
                    }
                }
                int total_steps_option = min_option + (sum_steps_total - knight_steps[k][tr*C + tc]);
                if(total_steps_option < min_total_steps){
                    min_total_steps = total_steps_option;
                }
            }
        }
    }
    printf("%d\n", min_total_steps);
    // Free memory
    for(int k=0; k<K; k++) {
        free(knight_steps[k]);
    }
    free(knight_steps);
    return 0;
}