#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_TOTAL 40000

int main(){
    char buffer[MAX_N + 2]; // +1 for possible '\n', +1 for '\0'
    char s[MAX_TOTAL +1];
    s[0] = '\0';
    int N = 0;
    int line_count = 0;
    
    // Read first line
    if(fgets(buffer, sizeof(buffer), stdin)){
        int len = strlen(buffer);
        if(buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
            len--;
        }
        N = len;
        strcat(s, buffer);
        line_count++;
    }

    // Read next N-1 lines
    while(line_count < N && fgets(buffer, sizeof(buffer), stdin)){
        int len = strlen(buffer);
        if(buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
            len--;
        }
        // Ensure the line has exactly N characters
        if(len != N){
            // Handle invalid input if necessary
        }
        strcat(s, buffer);
        line_count++;
    }

    // Now s has N*N characters
    // Begin run-length encoding
    // Prepare counts, maximum possible runs is 2*N*N (alternating every character)
    int counts[2*MAX_TOTAL];
    int count_size = 0;
    char expected = '0';
    int count = 0;
    for(int i=0; i < N*N; i++){
        if(s[i] == expected){
            count++;
        }
        else{
            counts[count_size++] = count;
            count = 1;
            expected = (expected == '0') ? '1' : '0';
        }
    }
    counts[count_size++] = count;
    
    // Now print N and the counts
    printf("%d", N);
    for(int i=0; i < count_size; i++){
        printf(" %d", counts[i]);
    }
    printf("\n");
    
    return 0;
}