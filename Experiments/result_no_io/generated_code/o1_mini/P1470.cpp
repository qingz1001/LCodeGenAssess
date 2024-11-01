#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_P 200
#define MAX_WORD_LEN 10
#define MAX_S 200005

int main(){
    // Initialize arrays for words by length
    char *words[MAX_WORD_LEN +1][MAX_P];
    int word_count[MAX_WORD_LEN +1];
    for(int i=0;i<=MAX_WORD_LEN;i++) word_count[i]=0;
    
    // Read P
    char buffer[1005];
    while(fgets(buffer, sizeof(buffer), stdin)){
        // Remove trailing newline
        int len = strlen(buffer);
        if(len >0 && buffer[len-1]=='\n') buffer[len-1]=0;
        if(strcmp(buffer, ".") ==0) break;
        // Tokenize the line
        char *token = strtok(buffer, " ");
        while(token){
            int l = strlen(token);
            if(l <= MAX_WORD_LEN){
                words[l][word_count[l]++] = strdup(token);
            }
            token = strtok(NULL, " ");
        }
    }
    
    // Read s
    char s_buffer[MAX_S];
    int s_len =0;
    while(fgets(buffer, sizeof(buffer), stdin)){
        int len = strlen(buffer);
        if(len >0 && buffer[len-1]=='\n') buffer[len-1]=0;
        for(int i=0;i<len;i++){
            s_buffer[s_len++] = buffer[i];
            if(s_len >= MAX_S-1) break;
        }
    }
    s_buffer[s_len] =0;
    
    // DP array
    bool *dp = calloc(s_len +1, sizeof(bool));
    dp[0] = true;
    int max_k =0;
    for(int i=1;i<=s_len;i++){
        for(int l=1;l<=MAX_WORD_LEN && l<=i;l++){
            if(dp[i - l]){
                // Check if s[i-l to i-1] is in words[l]
                bool found = false;
                for(int w=0; w < word_count[l]; w++){
                    if(strncmp(&s_buffer[i - l], words[l][w], l) ==0){
                        dp[i] = true;
                        if(i > max_k) max_k = i;
                        found = true;
                        break;
                    }
                }
                if(found) break;
            }
        }
    }
    printf("%d\n", max_k);
    
    // Free allocated memory
    for(int l=1;l<=MAX_WORD_LEN;l++) {
        for(int w=0; w < word_count[l]; w++) {
            free(words[l][w]);
        }
    }
    free(dp);
    return 0;
}