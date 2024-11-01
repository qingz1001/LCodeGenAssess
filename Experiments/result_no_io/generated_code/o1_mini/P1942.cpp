#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1002
#define MAX_WORDS 2001
#define MAX_LINE 2005

typedef struct {
    char word[MAX_N + 2];
} Word;

int main(){
    int n;
    char line[MAX_LINE];
    Word words[MAX_WORDS];
    int count = 0;

    // Read n
    while(fgets(line, sizeof(line), stdin)){
        if(sscanf(line, "%d", &n) == 1){
            break;
        }
    }

    // Read words
    while(fgets(line, sizeof(line), stdin)){
        int len = strlen(line);
        // Remove newline and spaces
        int j = 0;
        for(int i=0;i<len;i++){
            if(line[i] != ' ' && line[i] != '\n' && line[i] != '\r'){
                words[count].word[j++] = line[i];
            }
        }
        if(j > 0){
            words[count].word[j] = '\0';
            count++;
            if(count >= MAX_WORDS) break;
        }
    }

    // Function to calculate sum
    auto calc_sum = [&](char *w) -> long long {
        long long sum = 0;
        for(int i=0; w[i]; i++){
            if(w[i] == '1') sum += (i+1);
        }
        return sum;
    };

    // Process each word
    for(int w=0; w<count; w++){
        char *trans = words[w].word;
        int len = strlen(trans);
        char original[MAX_N +2];
        int found = 0;

        // Operation 4: No change
        if(len == n){
            long long s = calc_sum(trans);
            if(s % (n+1) ==0){
                printf("%s\n", trans);
                continue;
            }
        }

        // Operation 1: Replace one 1 with 0
        if(len == n){
            for(int i=0; i<len; i++){
                if(trans[i] == '1'){
                    strcpy(original, trans);
                    original[i] = '0';
                    long long s = calc_sum(original);
                    if(s % (n+1) ==0){
                        printf("%s\n", original);
                        found = 1;
                        break;
                    }
                }
            }
            if(found) continue;
        }

        // Operation 2: Delete one symbol (original had n, transformed has n-1)
        if(len == n-1 && n >=4 && n <=1000){
            for(int i=0; i<=len; i++){
                for(char c='0'; c<='1'; c++){
                    strcpy(original, "");
                    for(int j=0; j<=len; j++){
                        if(j == i){
                            original[j] = c;
                            original[j+1] = '\0';
                        }
                        if(j < len){
                            int idx = strlen(original);
                            original[idx] = trans[j];
                            original[idx+1] = '\0';
                        }
                    }
                    long long s = calc_sum(original);
                    if(s % (n+1) ==0){
                        printf("%s\n", original);
                        found =1;
                        break;
                    }
                }
                if(found) break;
            }
            if(found) continue;
        }

        // Operation 3: Insert one symbol (original had n, transformed has n+1)
        if(len == n+1 && n >=4 && n <=1000){
            for(int i=0; i<len; i++){
                strcpy(original, "");
                for(int j=0; j<len; j++){
                    if(j != i){
                        int idx = strlen(original);
                        original[idx] = trans[j];
                        original[idx+1] = '\0';
                    }
                }
                original[len-1] = '\0';
                long long s = calc_sum(original);
                if(s % (n+1) ==0){
                    printf("%s\n", original);
                    found =1;
                    break;
                }
            }
            if(found) continue;
        }

        // If not found
        printf("-1\n");
    }

    return 0;
}