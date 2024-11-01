#include <stdio.h>
#include <stdlib.h>

#define MAX 2000

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    // Allocate grid
    char **grid = (char **)malloc(N * sizeof(char *));
    for(int i=0;i<N;i++) {
        grid[i] = (char *)malloc(M * sizeof(char));
        for(int j=0;j<M;j++) {
            char c;
            scanf(" %c", &c);
            if(c == '0') grid[i][j] = 0;
            else grid[i][j] = 1;
        }
    }
    // Largest square
    int max_square = 0;
    // Two dp arrays for two patterns
    int **dp0 = (int **)malloc(N * sizeof(int *));
    int **dp1 = (int **)malloc(N * sizeof(int *));
    for(int i=0;i<N;i++){
        dp0[i] = (int *)malloc(M * sizeof(int));
        dp1[i] = (int *)malloc(M * sizeof(int));
        for(int j=0;j<M;j++){
            // Pattern 0: (i+j) %2 == grid[i][j]
            int expected0 = (i + j) % 2;
            int expected1 = 1 - expected0;
            if(grid[i][j] == expected0){
                if(i==0 || j==0) dp0[i][j] = 1;
                else{
                    int min = dp0[i-1][j];
                    if(dp0[i][j-1] < min) min = dp0[i][j-1];
                    if(dp0[i-1][j-1] < min) min = dp0[i-1][j-1];
                    dp0[i][j] = min +1;
                }
            }
            else{
                dp0[i][j] = 0;
            }
            if(grid[i][j] == expected1){
                if(i==0 || j==0) dp1[i][j] = 1;
                else{
                    int min = dp1[i-1][j];
                    if(dp1[i][j-1] < min) min = dp1[i][j-1];
                    if(dp1[i-1][j-1] < min) min = dp1[i-1][j-1];
                    dp1[i][j] = min +1;
                }
            }
            else{
                dp1[i][j] = 0;
            }
            int local_max = dp0[i][j] > dp1[i][j] ? dp0[i][j] : dp1[i][j];
            if(local_max > max_square) max_square = local_max;
        }
    }
    // Largest rectangle
    int max_rect = 0;
    // Heights for two patterns
    int *height0 = (int *)calloc(M, sizeof(int));
    int *height1 = (int *)calloc(M, sizeof(int));
    // Stack for histogram
    int *stack = (int *)malloc(M * sizeof(int));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            int expected0 = (i + j) % 2;
            int expected1 = 1 - expected0;
            if(grid[i][j] == expected0){
                height0[j] +=1;
            }
            else{
                height0[j] =0;
            }
            if(grid[i][j] == expected1){
                height1[j] +=1;
            }
            else{
                height1[j] =0;
            }
        }
        // Function to calculate max area for heights
        for(int p=0;p<2;p++){
            int *h = p==0 ? height0 : height1;
            int top = -1;
            for(int j=0;j<=M;j++){
                int cur_height = (j<M)? h[j] : 0;
                while(top >=0 && cur_height < h[stack[top]]){
                    int height = h[stack[top--]];
                    int width = top==-1 ? j : j - stack[top]-1;
                    int area = height * width;
                    if(area > max_rect) max_rect = area;
                }
                stack[++top] = j;
            }
        }
    }
    printf("%d\n%d\n", max_square * max_square, max_rect);
    // Free memory
    for(int i=0;i<N;i++) {
        free(grid[i]);
        free(dp0[i]);
        free(dp1[i]);
    }
    free(grid);
    free(dp0);
    free(dp1);
    free(height0);
    free(height1);
    free(stack);
    return 0;
}