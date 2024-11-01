#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_P 200
#define MAX_L 10
#define MAX_S 200005

typedef struct {
    char str[MAX_L + 1];
} String;

int cmp_str(const void *a, const void *b) {
    return strcmp(((String*)a)->str, ((String*)b)->str);
}

int main(){
    String plen[MAX_L+1][MAX_P];
    int plen_count[MAX_L+1];
    memset(plen_count, 0, sizeof(plen_count));
    
    char line[1000];
    // Read P
    while(fgets(line, sizeof(line), stdin)){
        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;
        if(strcmp(line, ".") == 0) break;
        int len = strlen(line);
        int start =0;
        while(start < len){
            // Skip leading spaces
            while(start < len && line[start] == ' ') start++;
            if(start >= len) break;
            // Find end of word
            int end = start;
            while(end < len && line[end] != ' ') end++;
            int slen = end - start;
            if(slen >0){
                char word[MAX_L+1];
                strncpy(word, line + start, slen);
                word[slen] = '\0';
                int l = slen;
                strcpy(plen[l][plen_count[l]].str, word);
                plen_count[l]++;
            }
            start = end;
        }
    }
    // Sort each plen[l]
    for(int l=1;l<=MAX_L;l++) {
        if(plen_count[l]>0){
            qsort(plen[l], plen_count[l], sizeof(String), cmp_str);
        }
    }
    // Read s
    char s[MAX_S];
    int s_len =0;
    while(fgets(line, sizeof(line), stdin)){
        int len = strlen(line);
        if(line[len-1] == '\n') line[len-1] = 0;
        int l = strlen(line);
        for(int i=0;i<l;i++) s[s_len++] = line[i];
    }
    s[s_len] = '\0';
    // DP
    char dp[MAX_S];
    memset(dp, 0, sizeof(dp));
    dp[0] =1;
    int max_k =0;
    for(int i=1;i<=s_len;i++){
        for(int l=1;l<=MAX_L;l++){
            if(i >= l && dp[i - l]){
                char temp[MAX_L+1];
                memcpy(temp, s + i - l, l);
                temp[l] = '\0';
                // Binary search in plen[l]
                int left =0, right = plen_count[l]-1, found =0;
                while(left <= right){
                    int mid = left + (right - left)/2;
                    int cmp = strcmp(temp, plen[l][mid].str);
                    if(cmp ==0){
                        found =1;
                        break;
                    }
                    else if(cmp <0){
                        right = mid -1;
                    }
                    else{
                        left = mid +1;
                    }
                }
                if(found){
                    dp[i] =1;
                    if(i > max_k) max_k =i;
                    break;
                }
            }
        }
    }
    printf("%d\n", max_k);
}