#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to trim leading and trailing spaces
void trim(char *s) {
    int start = 0, end = strlen(s) - 1;
    while(s[start] == ' ' || s[start] == '\t') start++;
    while(end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')) end--;
    if(start > 0 || end < (int)(strlen(s) -1)) {
        int i, j=0;
        for(i = start; i <= end; i++) s[j++] = s[i];
        s[j] = '\0';
    }
}

// Function to check if the sum of positions of '1's is multiple of (n+1) or zero
int is_valid(char *s, int n) {
    long long sum = 0;
    for(int i=0;i<strlen(s);i++) {
        if(s[i] == '1') sum += (i+1);
    }
    return (sum ==0) || (sum % (n+1) ==0);
}

int main(){
    int n;
    if(scanf("%d", &n)!=1) return 0;
    getchar(); // consume newline after number
    char line[2005];
    while(fgets(line, sizeof(line), stdin)){
        trim(line);
        if(strlen(line)==0) continue;
        int len = strlen(line);
        char original[1005];
        int found = 0;
        if(len == n){
            if(is_valid(line, n)){
                printf("%s\n", line);
                continue;
            }
            // Try operation1: change one '1' to '0'
            for(int i=0;i<len;i++){
                if(line[i] == '1'){
                    strcpy(original, line);
                    original[i] = '0';
                    if(is_valid(original, n)){
                        printf("%s\n", original);
                        found =1;
                        break;
                    }
                }
            }
            if(found) continue;
            printf("-1\n");
        }
        else if(len == n+1){
            // Try operation3: delete one symbol, prefer '0's first
            // First delete '0's
            int success =0;
            for(int i=0;i<len;i++){
                if(line[i] == '0'){
                    int k=0;
                    for(int j=0; j<len; j++) if(j !=i) original[k++] = line[j];
                    original[k] = '\0';
                    if(is_valid(original, n)){
                        printf("%s\n", original);
                        success =1;
                        break;
                    }
                }
            }
            if(success){
                continue;
            }
            // Then delete '1's
            for(int i=0;i<len;i++){
                if(line[i] == '1'){
                    int k=0;
                    for(int j=0; j<len; j++) if(j !=i) original[k++] = line[j];
                    original[k] = '\0';
                    if(is_valid(original, n)){
                        printf("%s\n", original);
                        success =1;
                        break;
                    }
                }
            }
            if(success){
                continue;
            }
            printf("-1\n");
        }
        else if(len == n-1){
            // Try operation2: insert one symbol, prefer '0's first
            int success =0;
            for(int i=0;i<=len;i++){
                // Insert '0'
                int k=0;
                for(int j=0; j<i; j++) original[k++] = line[j];
                original[k++] = '0';
                for(int j=i; j<len; j++) original[k++] = line[j];
                original[k] = '\0';
                if(is_valid(original, n)){
                    printf("%s\n", original);
                    success =1;
                    break;
                }
            }
            if(success){
                continue;
            }
            for(int i=0;i<=len;i++){
                // Insert '1'
                int k=0;
                for(int j=0; j<i; j++) original[k++] = line[j];
                original[k++] = '1';
                for(int j=i; j<len; j++) original[k++] = line[j];
                original[k] = '\0';
                if(is_valid(original, n)){
                    printf("%s\n", original);
                    success =1;
                    break;
                }
            }
            if(success){
                continue;
            }
            printf("-1\n");
        }
        else{
            printf("-1\n");
        }
    }
    return 0;
}