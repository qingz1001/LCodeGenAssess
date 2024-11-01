#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_LINE 201

int main(){
    char matrix[MAX_N][MAX_LINE];
    int N = 0;
    char buffer[MAX_LINE];
    
    while(N < MAX_N && fgets(buffer, sizeof(buffer), stdin)){
        int len = strlen(buffer);
        if(buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
            len--;
        }
        if(N == 0){
            N = len;
            if(N < 3 || N > 200){
                return 0;
            }
        }
        if(len != N){
            return 0;
        }
        strcpy(matrix[N], buffer);
        N++;
    }
    
    // Flatten the matrix
    char flat[MAX_N * MAX_N];
    int idx = 0;
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            flat[idx++] = matrix[i][j];
        }
    }
    
    // Run-length encoding
    int counts[2 * MAX_N * MAX_N +1];
    int count_idx = 0;
    int total = N * N;
    
    // Start with counting '0's
    int expected = '0';
    int cnt = 0;
    for(int i=0;i<idx;i++){
        if(flat[i] == expected){
            cnt++;
        }
        else{
            counts[count_idx++] = cnt;
            cnt = 1;
            expected = (expected == '0') ? '1' : '0';
        }
    }
    counts[count_idx++] = cnt;
    
    // If counts are not alternating starting with '0', pad with 0
    if(flat[0] != '0'){
        // Insert 0 at the beginning
        for(int i=count_idx;i>0;i--){
            counts[i] = counts[i-1];
        }
        counts[0] = 0;
        count_idx++;
    }
    
    // Print N
    printf("%d", N);
    for(int i=0;i<count_idx;i++){
        printf(" %d", counts[i]);
    }
    printf("\n");
    return 0;
}