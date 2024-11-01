#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char line[300000];
    if(!fgets(line, sizeof(line), stdin)){
        return 0;
    }
    // Tokenize the input line
    char *token = strtok(line, " \n");
    if(token == NULL){
        return 0;
    }
    int N = atoi(token);
    static int counts[40010];
    int count_len = 0;
    while((token = strtok(NULL, " \n")) != NULL){
        counts[count_len++] = atoi(token);
    }
    // Initialize grid
    static char grid[40000];
    int total = 0;
    char current = '0';
    for(int i = 0; i < count_len; i++){
        for(int j = 0; j < counts[i]; j++){
            if(total < N*N){
                grid[total++] = current;
            }
        }
        current = (current == '0') ? '1' : '0';
    }
    // Print the grid
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            putchar(grid[i*N + j]);
        }
        putchar('\n');
    }
    return 0;
}