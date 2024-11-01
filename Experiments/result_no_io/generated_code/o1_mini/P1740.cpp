#include <stdio.h>
#include <string.h>

#define MAX_N 888
#define MAX_LINE 2000

int main(){
    int n;
    scanf("%d", &n);
    getchar(); // consume the newline after n
    char input[2*MAX_N][2*MAX_N+2];
    for(int i=0;i<2*n;i++){
        fgets(input[i], 2*n+2, stdin);
        // Remove newline if present
        size_t len = strlen(input[i]);
        if(input[i][len-1] == '\n') input[i][len-1] = '\0';
    }
    // Initialize output grid with '0's
    char output[2*MAX_N+1][2*MAX_N+2];
    for(int i=0;i<2*n+1;i++){
        for(int j=0;j<2*n+1;j++){
            output[i][j] = '0';
        }
        output[i][2*n] = '\0';
    }
    // Map input to output
    for(int i=0;i<2*n;i++){
        for(int j=0;j<2*n;j++){
            if(input[i][j] == '/' || input[i][j] == '\\'){
                output[i][j] = '1';
            }
        }
    }
    // Print output
    printf("%d\n", n);
    for(int i=0;i<2*n+1;i++){
        for(int j=0;j<2*n+1;j++){
            printf("%c", output[i][j]);
        }
        printf("\n");
    }
    return 0;
}