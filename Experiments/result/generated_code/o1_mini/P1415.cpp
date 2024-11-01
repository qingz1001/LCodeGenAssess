#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_L 500
#define MAX_SEQ 1000

typedef struct {
    char sequence[MAX_SEQ];
    char last_number[MAX_L + 1];
    int valid;
} DPCell;

int compare_numbers(const char *a, int len_a, const char *b, int len_b) {
    if (len_a != len_b)
        return (len_a > len_b) ? 1 : -1;
    return strncmp(a, b, len_a);
}

int main(){
    char s[MAX_L +1];
    scanf("%s", s);
    int l = strlen(s);
    DPCell dp[MAX_L +1];
    for(int i=0;i<=l;i++){
        dp[i].valid = 0;
        dp[i].sequence[0] = '\0';
        dp[i].last_number[0] = '\0';
    }
    dp[0].valid = 1;
    dp[0].sequence[0] = '\0';
    dp[0].last_number[0] = '\0';
    
    for(int i=1;i<=l;i++){
        for(int j=0;j<i;j++){
            if(!dp[j].valid) continue;
            int len = i - j;
            char num[MAX_L +1];
            strncpy(num, s + j, len);
            num[len] = '\0';
            // Compare with last number
            if(j ==0 || compare_numbers(num, len, dp[j].last_number, strlen(dp[j].last_number)) >0){
                // Build candidate sequence
                char candidate_seq[MAX_SEQ];
                if(j ==0){
                    strcpy(candidate_seq, num);
                }
                else{
                    strcpy(candidate_seq, dp[j].sequence);
                    strcat(candidate_seq, ",");
                    strcat(candidate_seq, num);
                }
                // Compare with existing dp[i]
                if(!dp[i].valid){
                    strcpy(dp[i].sequence, candidate_seq);
                    strcpy(dp[i].last_number, num);
                    dp[i].valid =1;
                }
                else{
                    // Compare last numbers
                    int cmp_last = compare_numbers(num, len, dp[i].last_number, strlen(dp[i].last_number));
                    if(cmp_last <0){
                        strcpy(dp[i].sequence, candidate_seq);
                        strcpy(dp[i].last_number, num);
                    }
                    else if(cmp_last ==0){
                        if(strcmp(candidate_seq, dp[i].sequence) >0){
                            strcpy(dp[i].sequence, candidate_seq);
                            strcpy(dp[i].last_number, num);
                        }
                    }
                }
            }
        }
    }
    if(dp[l].valid){
        printf("%s\n", dp[l].sequence);
    }
    return 0;
}