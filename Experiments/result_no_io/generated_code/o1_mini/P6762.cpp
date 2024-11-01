#include <stdio.h>
#include <string.h>

#define SIZE 6

char view1[6][7];
char view2[6][7];
int grid[SIZE][SIZE];
long long count_result = 0;

// Directions for 2x2 block placement
int dx[2] = {0, 1};
int dy[2] = {0, 1};

// Function to check if a block can be placed at (x, y)
int can_place(int x, int y) {
    if (x + 1 >= SIZE || y + 1 >= SIZE)
        return 0;
    for(int i=0;i<2;i++) {
        for(int j=0;j<2;j++) {
            if(grid[x+i][y+j] != 0)
                return 0;
        }
    }
    return 1;
}

// Function to place or remove a block
void place_block(int x, int y, int color) {
    for(int i=0;i<2;i++) {
        for(int j=0;j<2;j++) {
            grid[x+i][y+j] = color;
        }
    }
}

// Function to check if current grid matches view1 and view2
int matches_views() {
    // Check view1
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            char c = view1[i][j];
            if(c == '.') {
                if(grid[i][j] != 0)
                    return 0;
            }
            else {
                if(grid[i][j] != (c == 'W' ? 1 : (c == 'G' ? 2 : 3)))
                    return 0;
            }
        }
    }
    // Check view2 (rotated 90 degrees counterclockwise)
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            char c = view2[i][j];
            int gi = j;
            int gj = SIZE - 1 - i;
            if(c == '.') {
                if(grid[gi][gj] != 0)
                    return 0;
            }
            else {
                if(grid[gi][gj] != (c == 'W' ? 1 : (c == 'G' ? 2 : 3)))
                    return 0;
            }
        }
    }
    return 1;
}

void backtrack(int x, int y) {
    if(x == SIZE) {
        if(matches_views())
            count_result++;
        return;
    }
    if(y == SIZE) {
        backtrack(x + 1, 0);
        return;
    }
    if(grid[x][y] != 0) {
        backtrack(x, y + 1);
        return;
    }
    // Try placing no block
    backtrack(x, y + 1);
    // Try placing a block with different colors
    for(int color=1; color<=3; color++) {
        if(can_place(x, y)) {
            place_block(x, y, color);
            backtrack(x, y + 1);
            place_block(x, y, 0);
        }
    }
}

int main(){
    int H;
    scanf("%d", &H);
    for(int i=0;i<H;i++) {
        scanf("%s", view1[i]);
    }
    for(int i=0;i<H;i++) {
        scanf("%s", view2[i]);
    }
    backtrack(0, 0);
    printf("%lld\n", count_result);
    return 0;
}