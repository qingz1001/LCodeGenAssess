#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f

int clocks[9];
int moves[9][5] = {
    {0, 1, 3, 4, -1},
    {0, 1, 2, -1},
    {1, 2, 4, 5, -1},
    {0, 3, 6, -1},
    {1, 3, 4, 5, 7},
    {2, 5, 8, -1},
    {3, 4, 6, 7, -1},
    {6, 7, 8, -1},
    {4, 5, 7, 8, -1}
};

int result[40], temp[40];
int minStep = INF;

void dfs(int move, int step) {
    if (move == 9) {
        for (int i = 0; i < 9; i++) {
            if (clocks[i] != 0) return;
        }
        if (step < minStep) {
            minStep = step;
            memcpy(result, temp, sizeof(temp));
        }
        return;
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; moves[move][j] != -1; j++) {
            clocks[moves[move][j]] = (clocks[moves[move][j]] + i) % 4;
        }
        for (int j = 0; j < i; j++) {
            temp[step + j] = move + 1;
        }
        dfs(move + 1, step + i);
        for (int j = 0; moves[move][j] != -1; j++) {
            clocks[moves[move][j]] = (clocks[moves[move][j]] - i + 4) % 4;
        }
    }
}

int main() {
    for (int i = 0; i < 9; i++) {
        scanf("%d", &clocks[i]);
        clocks[i] = (clocks[i] / 3) % 4;
    }
    
    dfs(0, 0);
    
    for (int i = 0; i < minStep; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    return 0;
}