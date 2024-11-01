#include <stdio.h>
#include <string.h>

#define MAX 1800

int main(){
    int n;
    scanf("%d", &n);
    char line[MAX];
    // Allocate enough space for 2n rows and 2n columns
    int size = 2 * n + 2;
    // Initialize slash and backslash arrays
    int **slash = malloc(size * sizeof(int*));
    int **backslash_arr = malloc(size * sizeof(int*));
    for(int i=0;i<size;i++){
        slash[i] = calloc(size, sizeof(int));
        backslash_arr[i] = calloc(size, sizeof(int));
    }
    // Read upper half
    for(int y=0; y<n; y++){
        scanf(" %[^\n]", line);
        int len = strlen(line);
        int start_x = n - y -1;
        for(int k=0; k < 2*(y+1) && k < len; k++){
            char c = line[k];
            if(k%2 ==0){
                if(c == '/' || c == '1') slash[y][start_x + k/2] =1;
            }
            else{
                if(c == '\\' || c == '1') backslash_arr[y][start_x + k/2] =1;
            }
        }
    }
    // Read lower half
    for(int y=n; y<2*n; y++){
        scanf(" %[^\n]", line);
        int line_num = y - n;
        int num_chars = 2*(n - line_num);
        int start_x = line_num;
        for(int k=0; k < num_chars && k < (int)strlen(line); k++){
            char c = line[k];
            if(k%2 ==0){
                if(c == '/' || c == '1') slash[y][start_x + k/2] =1;
            }
            else{
                if(c == '\\' || c == '1') backslash_arr[y][start_x + k/2] =1;
            }
        }
    }
    // Count parallelograms
    int count =0;
    for(int y=0; y<2*n-1; y++){
        for(int x=0; x<2*n-1; x++){
            if(slash[y][x] && backslash_arr[y][x] && slash[y+1][x+1] && backslash_arr[y][x+1]){
                count++;
            }
        }
    }
    printf("%d\n", count);
    // Free memory
    for(int i=0;i<size;i++){
        free(slash[i]);
        free(backslash_arr[i]);
    }
    free(slash);
    free(backslash_arr);
    return 0;
}