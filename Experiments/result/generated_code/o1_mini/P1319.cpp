#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    int total = N * N;
    char *matrix = (char *)malloc(sizeof(char) * (total + 1));
    int run, pos = 0;
    char current = '0';
    while(scanf("%d", &run) != EOF && pos < total){
        for(int i = 0; i < run && pos < total; i++){
            matrix[pos++] = current;
        }
        current = (current == '0') ? '1' : '0';
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            putchar(matrix[i*N + j]);
        }
        putchar('\n');
    }
    free(matrix);
    return 0;
}