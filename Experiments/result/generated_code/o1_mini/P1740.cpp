#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    getchar(); // consume newline after n
    int size = 2 * n;
    char **grid = (char **)malloc(size * sizeof(char *));
    for(int i=0;i<size;i++){
        grid[i] = (char *)malloc((size+1) * sizeof(char));
        fgets(grid[i], size+1, stdin);
        getchar(); // consume newline
    }
    // Initialize the rectangle edges
    int rect_rows = 2 * n +1;
    int rect_cols = 2 * n +1;
    char **rect = (char **)malloc(rect_rows * sizeof(char *));
    for(int i=0;i<rect_rows;i++){
        rect[i] = (char *)malloc((rect_cols +1) * sizeof(char));
        for(int j=0;j<rect_cols;j++) rect[i][j] = '0';
        rect[i][rect_cols] = '\0';
    }
    // Map the diamond edges to rectangle
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            char c = grid[i][j];
            int rect_i = i +1;
            int rect_j = j +1;
            if(c == '/'){
                if(rect_i >0 && rect_j < rect_cols-1){
                    rect[rect_i-1][rect_j+1] = '1';
                }
                if(rect_i < rect_rows-1 && rect_j >0){
                    rect[rect_i+1][rect_j-1] = '1';
                }
            }
            else if(c == '\\'){
                if(rect_i >0 && rect_j >0){
                    rect[rect_i-1][rect_j-1] = '1';
                }
                if(rect_i < rect_rows-1 && rect_j < rect_cols-1){
                    rect[rect_i+1][rect_j+1] = '1';
                }
            }
        }
    }
    // Print output
    printf("%d\n", n);
    for(int i=0;i<rect_rows;i++){
        printf("%s\n", rect[i]);
    }
    // Free memory
    for(int i=0;i<size;i++) free(grid[i]);
    free(grid);
    for(int i=0;i<rect_rows;i++) free(rect[i]);
    free(rect);
    return 0;
}