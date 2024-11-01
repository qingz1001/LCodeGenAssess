#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct {
    char grid[MAX][MAX + 1];
} Grid;

// Function to copy grid src to dest
void copyGrid(Grid src, Grid *dest, int n){
    for(int i=0;i<n;i++){
        strcpy(dest->grid[i], src.grid[i]);
    }
}

// Function to rotate grid 90 degrees clockwise
Grid rotate90(Grid g, int n){
    Grid res;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res.grid[i][j] = g.grid[n-j-1][i];
        }
        res.grid[i][n] = '\0';
    }
    return res;
}

// Function to reflect grid horizontally
Grid reflect(Grid g, int n){
    Grid res;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res.grid[i][j] = g.grid[i][n-j-1];
        }
        res.grid[i][n] = '\0';
    }
    return res;
}

// Function to compare two grids
int compare(Grid a, Grid b, int n){
    for(int i=0;i<n;i++){
        if(strcmp(a.grid[i], b.grid[i]) != 0){
            return 0;
        }
    }
    return 1;
}

int main(){
    int n;
    scanf("%d", &n);
    Grid original, target, temp;
    // Read original grid
    for(int i=0;i<n;i++){
        scanf("%s", original.grid[i]);
    }
    // Read target grid
    for(int i=0;i<n;i++){
        scanf("%s", target.grid[i]);
    }
    // Step 1: Rotate 90
    temp = rotate90(original, n);
    if(compare(temp, target, n)){
        printf("1\n");
        return 0;
    }
    // Step 2: Rotate 180
    temp = rotate90(temp, n);
    if(compare(temp, target, n)){
        printf("2\n");
        return 0;
    }
    // Step 3: Rotate 270
    temp = rotate90(temp, n);
    if(compare(temp, target, n)){
        printf("3\n");
        return 0;
    }
    // Step 4: Reflect
    Grid reflected = reflect(original, n);
    if(compare(reflected, target, n)){
        printf("4\n");
        return 0;
    }
    // Step 5: Reflect and Rotate 90, 180, 270
    // Rotate 90
    temp = rotate90(reflected, n);
    if(compare(temp, target, n)){
        printf("5\n");
        return 0;
    }
    // Rotate 180
    temp = rotate90(temp, n);
    if(compare(temp, target, n)){
        printf("6\n");
        return 0;
    }
    // Rotate 270
    temp = rotate90(temp, n);
    if(compare(temp, target, n)){
        printf("7\n");
        return 0;
    }
    // Step 6: No Change
    if(compare(original, target, n)){
        printf("7\n");
        return 0;
    }
    // Step 7: Invalid Transformation
    printf("7\n");
    return 0;
}