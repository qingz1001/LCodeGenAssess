#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 30
#define MAX_M 30
#define MAX_POS 900
#define MAX_QUEUE (MAX_POS * MAX_POS)

typedef struct {
    int block;
    int blank;
    int steps;
} State;

int n, m, q;
int grid[MAX_N][MAX_M];
unsigned char visited_bits[MAX_POS][113]; // 900 / 8 = 112.5, use 113
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(){
    scanf("%d %d %d", &n, &m, &q);
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    // Prepare queue
    State queue[MAX_QUEUE];
    int head, tail;
    while(q--){
        int EX, EY, SX, SY, TX, TY;
        scanf("%d %d %d %d %d %d", &EX, &EY, &SX, &SY, &TX, &TY);
        // Convert to 0-based
        EX--; EY--; SX--; SY--; TX--; TY--;
        int start_block = SX * m + SY;
        int start_blank = EX * m + EY;
        int target = TX * m + TY;
        // Initialize visited
        memset(visited_bits, 0, sizeof(visited_bits));
        // Initialize queue
        head = 0;
        tail = 0;
        queue[tail].block = start_block;
        queue[tail].blank = start_blank;
        queue[tail].steps = 0;
        tail++;
        // Mark visited
        int byte = start_blank / 8;
        int bit = start_blank % 8;
        visited_bits[start_block][byte] |= (1 << bit);
        int found = -1;
        while(head < tail){
            State current = queue[head++];
            if(current.block == target){
                found = current.steps;
                break;
            }
            int bx = current.block / m;
            int by = current.block % m;
            int zx = current.blank / m;
            int zy = current.blank % m;
            for(int d=0; d<4; d++){
                int nzx = zx + dx[d];
                int nzy = zy + dy[d];
                if(nzx <0 || nzx >=n || nzy <0 || nzy >=m) continue;
                if(grid[nzx][nzy] == 0) continue;
                int new_blank = nzx * m + nzy;
                if(new_blank == current.block){
                    // Push the block
                    int nbx = bx + dx[d];
                    int nby = by + dy[d];
                    if(nbx <0 || nbx >=n || nby <0 || nby >=m) continue;
                    if(grid[nbx][nby] == 0) continue;
                    int new_block = nbx * m + nby;
                    // Check visited
                    int byte_idx = new_blank / 8;
                    int bit_idx = new_blank % 8;
                    if(!(visited_bits[new_block][new_blank / 8] & (1 << (new_blank % 8)))){
                        visited_bits[new_block][byte_idx] |= (1 << bit_idx);
                        if(tail < MAX_QUEUE){
                            queue[tail].block = new_block;
                            queue[tail].blank = current.block;
                            queue[tail].steps = current.steps +1;
                            tail++;
                        }
                    }
                }
                else{
                    // Move blank without moving block
                    // Ensure blank does not move onto the block
                    if(new_blank == current.block) continue;
                    int byte_idx = new_blank / 8;
                    int bit_idx = new_blank % 8;
                    if(!(visited_bits[current.block][byte_idx] & (1 << bit_idx))){
                        visited_bits[current.block][byte_idx] |= (1 << bit_idx);
                        if(tail < MAX_QUEUE){
                            queue[tail].block = current.block;
                            queue[tail].blank = new_blank;
                            queue[tail].steps = current.steps +1;
                            tail++;
                        }
                    }
                }
            }
        }
        printf("%d\n", found);
    }
    return 0;
}