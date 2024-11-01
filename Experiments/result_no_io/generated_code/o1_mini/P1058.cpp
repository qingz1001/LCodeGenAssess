#include <stdio.h>
#include <string.h>

#define MAX_M 50
#define MAX_N 50
#define MAX_H 100
#define BLOCK_HEIGHT 6
#define BLOCK_WIDTH 5

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int grid[MAX_M][MAX_N];
    int max_h = 0;
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d", &grid[i][j]);
            if(grid[i][j] > max_h) max_h = grid[i][j];
        }
    }

    // Calculate canvas size
    // Each block adds BLOCK_HEIGHT vertically and BLOCK_WIDTH horizontally
    // The total height and width depend on m, n, and max_h
    int canvas_height = (m + n) * 3 + max_h * 3 + 6;
    int canvas_width = (m + n) * 3 + 12;
    if(canvas_height > 3000) canvas_height = 3000;
    if(canvas_width > 3000) canvas_width = 3000;

    // To handle large sizes, use dynamic allocation
    char **canvas = (char **)malloc(canvas_height * sizeof(char *));
    for(int i=0;i<canvas_height;i++) {
        canvas[i] = (char *)malloc((canvas_width +1) * sizeof(char));
        memset(canvas[i], '.', canvas_width);
        canvas[i][canvas_width] = '\0';
    }

    // Function to set a character if within bounds
    auto set_char = [&](int y, int x, char c) {
        if(y >=0 && y < canvas_height && x >=0 && x < canvas_width){
            canvas[y][x] = c;
        }
    };

    // Iterate through each cell
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            int h = grid[i][j];
            for(int k=0;k<h;k++) {
                // Calculate the base position for this block
                // The origin is at the left bottom
                int origin_y = (m + n) * 3 + max_h * 3 - ((i + j) * 3) - k * 3;
                int origin_x = (j - i) * 3 + max_h * 3;

                // Draw the block
                // Line 0:   +---+
                set_char(origin_y - 0, origin_x + 3, '+');
                set_char(origin_y - 0, origin_x + 4, '-');
                set_char(origin_y - 0, origin_x + 5, '-');
                set_char(origin_y - 0, origin_x + 6, '-');
                set_char(origin_y - 0, origin_x + 7, '+');

                // Line 1:  /   /|
                set_char(origin_y - 1, origin_x + 2, '/');
                set_char(origin_y - 1, origin_x + 3+1, ' ');
                set_char(origin_y - 1, origin_x + 4+1, ' ');
                set_char(origin_y - 1, origin_x + 5+1, ' ');
                set_char(origin_y - 1, origin_x + 6, '/');
                set_char(origin_y - 1, origin_x + 7, '|');

                // Line 2: +---+ |
                set_char(origin_y - 2, origin_x + 3, '+');
                set_char(origin_y - 2, origin_x + 4, '-');
                set_char(origin_y - 2, origin_x + 5, '-');
                set_char(origin_y - 2, origin_x + 6, '-');
                set_char(origin_y - 2, origin_x + 7, '+');
                set_char(origin_y - 2, origin_x + 8, ' ');
                set_char(origin_y - 2, origin_x + 9, '|');

                // Line 3: |   | +
                set_char(origin_y - 3, origin_x + 3, '|');
                set_char(origin_y - 3, origin_x + 4, ' ');
                set_char(origin_y - 3, origin_x + 5, ' ');
                set_char(origin_y - 3, origin_x + 6, ' ');
                set_char(origin_y - 3, origin_x + 7, '|');
                set_char(origin_y - 3, origin_x + 8, ' ');
                set_char(origin_y - 3, origin_x + 9, '+');

                // Line 4: |   |/
                set_char(origin_y - 4, origin_x + 3, '|');
                set_char(origin_y - 4, origin_x + 4, ' ');
                set_char(origin_y - 4, origin_x + 5, ' ');
                set_char(origin_y - 4, origin_x + 6, ' ');
                set_char(origin_y - 4, origin_x + 7, '|');
                set_char(origin_y - 4, origin_x + 8, '/');

                // Line 5: +---+
                set_char(origin_y - 5, origin_x + 3, '+');
                set_char(origin_y - 5, origin_x + 4, '-');
                set_char(origin_y - 5, origin_x + 5, '-');
                set_char(origin_y - 5, origin_x + 6, '-');
                set_char(origin_y - 5, origin_x + 7, '+');
            }
        }
    }

    // Find the bounds to print
    int top = canvas_height, bottom = 0, left = canvas_width, right =0;
    for(int i=0;i<canvas_height;i++) {
        for(int j=0;j<canvas_width;j++) {
            if(canvas[i][j] != '.') {
                if(i < top) top = i;
                if(i > bottom) bottom = i;
                if(j < left) left = j;
                if(j > right) right = j;
            }
        }
    }
    if(top > bottom || left > right){
        // Nothing to print
        printf(".");
        return 0;
    }

    // Print the relevant part
    for(int i=top;i<=bottom;i++) {
        for(int j=left;j<=right;j++) {
            putchar(canvas[i][j]);
        }
        putchar('\n');
    }

    // Free memory
    for(int i=0;i<canvas_height;i++) free(canvas[i]);
    free(canvas);
    return 0;
}