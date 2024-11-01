#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct {
    int n;
    char grid[MAX][MAX+1];
} Grid;

void rotate90(char src[][MAX+1], char dest[][MAX+1], int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dest[j][n-1-i] = src[i][j];
    for(int i=0;i<n;i++) dest[i][n] = '\0';
}

void reflect(char src[][MAX+1], char dest[][MAX+1], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            dest[i][j] = src[i][n-1-j];
        dest[i][n] = '\0';
    }
}

int grids_equal(char a[][MAX+1], char b[][MAX+1], int n){
    for(int i=0;i<n;i++)
        if(strcmp(a[i], b[i]) != 0)
            return 0;
    return 1;
}

int main(){
    int n;
    Grid initial, final_g;
    scanf("%d", &n);
    for(int i=0;i<n;i++) scanf("%s", initial.grid[i]);
    for(int i=0;i<n;i++) scanf("%s", final_g.grid[i]);

    char temp1[MAX][MAX+1], temp2[MAX][MAX+1];
    // 1. Rotate 90
    rotate90(initial.grid, temp1, n);
    if(grids_equal(temp1, final_g.grid, n)){
        printf("1\n");
        return 0;
    }
    // 2. Rotate 180
    rotate90(temp1, temp2, n);
    if(grids_equal(temp2, final_g.grid, n)){
        printf("2\n");
        return 0;
    }
    // 3. Rotate 270
    rotate90(temp2, temp1, n);
    if(grids_equal(temp1, final_g.grid, n)){
        printf("3\n");
        return 0;
    }
    // 4. Reflect
    reflect(initial.grid, temp1, n);
    if(grids_equal(temp1, final_g.grid, n)){
        printf("4\n");
        return 0;
    }
    // 5. Reflect + rotate
    // Rotate 90 after reflect
    rotate90(temp1, temp2, n);
    if(grids_equal(temp2, final_g.grid, n)){
        printf("5\n");
        return 0;
    }
    // Rotate 180 after reflect
    rotate90(temp2, temp1, n);
    if(grids_equal(temp1, final_g.grid, n)){
        printf("5\n");
        return 0;
    }
    // Rotate 270 after reflect
    rotate90(temp1, temp2, n);
    if(grids_equal(temp2, final_g.grid, n)){
        printf("5\n");
        return 0;
    }
    // 6. No change
    if(grids_equal(initial.grid, final_g.grid, n)){
        printf("6\n");
        return 0;
    }
    // 7. Invalid
    printf("7\n");
    return 0;
}