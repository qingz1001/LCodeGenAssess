#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 501

typedef struct {
    char path[1001];
} DPState;

// Function to extract the last number from the path
void get_last_number(const char *path, char *number) {
    int len = strlen(path);
    int i = len - 1;
    while (i >= 0 && path[i] != ',') i--;
    strcpy(number, path + i + 1);
}

// Function to compare two numbers represented as strings
// Returns 1 if num1 > num2, 0 otherwise
int is_greater(const char *s, int start, int end, const char *num2) {
    int len1 = end - start;
    int len2 = strlen(num2);
    if (len1 != len2) return len1 > len2;
    return strncmp(s + start, num2, len1) > 0;
}

// Function to compare two paths
// Returns 1 if pathA is better, -1 if pathB is better, 0 if equal
int compare_paths(const char *pathA, const char *pathB) {
    int i = 0, j = 0;
    int lenA = strlen(pathA);
    int lenB = strlen(pathB);
    while (i < lenA && j < lenB) {
        // Extract next number from pathA
        int startA = i;
        while (i < lenA && pathA[i] != ',') i++;
        int current_lenA = i - startA;
        // Extract next number from pathB
        int startB = j;
        while (j < lenB && pathB[j] != ',') j++;
        int current_lenB = j - startB;
        // Compare lengths
        if (current_lenA != current_lenB) {
            return (current_lenA > current_lenB) ? 1 : -1;
        }
        // Compare lex order
        int cmp = strncmp(pathA + startA, pathB + startB, current_lenA);
        if (cmp != 0) {
            return (cmp > 0) ? 1 : -1;
        }
        // Move past comma
        if (i < lenA && pathA[i] == ',') i++;
        if (j < lenB && pathB[j] == ',') j++;
    }
    if (lenA == lenB) return 0;
    return (lenA > lenB) ? 1 : -1;
}

int main(){
    char s[MAX_LEN];
    scanf("%s", s);
    int l = strlen(s);
    DPState dp[MAX_LEN];
    for(int i=0;i<=l;i++) {
        dp[i].path[0] = '\0';
    }
    dp[0].path[0] = '\0';
    for(int i=1;i<=l;i++){
        for(int j=0;j<i;j++){
            char candidate[1001];
            if(j == 0){
                strncpy(candidate, s, i);
                candidate[i] = '\0';
            }
            else{
                if(dp[j].path[0] == '\0') continue;
                char last_num[MAX_LEN];
                get_last_number(dp[j].path, last_num);
                if(!is_greater(s, j, i, last_num)) continue;
                if(strlen(dp[j].path) + 1 + (i - j) >= 1001) continue;
                strcpy(candidate, dp[j].path);
                strcat(candidate, ",");
                strncat(candidate, s + j, i - j);
                candidate[i - j + strlen(dp[j].path) + 1] = '\0';
            }
            if(dp[i].path[0] == '\0'){
                strcpy(dp[i].path, candidate);
            }
            else{
                // Compare last numbers
                char last1[MAX_LEN], last2[MAX_LEN];
                // Last number of candidate
                get_last_number(candidate, last1);
                // Last number of dp[i].path
                get_last_number(dp[i].path, last2);
                int len1 = strlen(last1);
                int len2 = strlen(last2);
                if(len1 < len2 || (len1 == len2 && strcmp(last1, last2) < 0)){
                    strcpy(dp[i].path, candidate);
                }
                else if(len1 == len2 && strcmp(last1, last2) == 0){
                    // Compare paths
                    int cmp = compare_paths(candidate, dp[i].path);
                    if(cmp == 1){
                        strcpy(dp[i].path, candidate);
                    }
                }
            }
        }
    }
    printf("%s\n", dp[l].path);
    return 0;
}