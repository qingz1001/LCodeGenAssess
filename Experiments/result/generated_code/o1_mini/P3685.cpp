#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HINTS 10
#define MAX_HINT_LEN 9
#define MAX_SEQUENCE_LEN 12
#define DIGIT_RANGE 9

int n;
int hints[MAX_HINTS][MAX_HINT_LEN];
int hint_lens[MAX_HINTS];

// Function to read input
void read_input() {
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        int num;
        hint_lens[i]=0;
        while(1){
            scanf("%d", &num);
            if(num ==0) break;
            hints[i][hint_lens[i]++] = num;
        }
    }
}

// Function to check if a sequence satisfies a single hint
int check_hint(int *seq, int len, int *hint, int hlen){
    for(int p=0;p<len;p++) {
        for(int dir=0; dir<2; dir++) { // 0: left, 1: right
            int record[10] = {0};
            int idx = 0;
            for(int i=0; i<len; i++) {
                int pos = dir ? p + i : p - i;
                if(pos <0 || pos >= len) break;
                int d = seq[pos];
                if(!record[d]){
                    record[d] = 1;
                    if(idx >= hlen || d != hint[idx]) break;
                    idx++;
                    if(idx == hlen) return 1;
                }
            }
            if(idx == hlen) return 1;
        }
    }
    return 0;
}

// Function to check if a sequence satisfies all hints
int is_valid(int *seq, int len){
    for(int i=0;i<n;i++) {
        if(!check_hint(seq, len, hints[i], hint_lens[i])) return 0;
    }
    return 1;
}

// Recursive function to generate sequences
int result = -1;
int current_sequence[20];

void backtrack(int pos, int len){
    if(result != -1) return;
    if(pos == len){
        if(is_valid(current_sequence, len)){
            result = len;
        }
        return;
    }
    for(int d=1; d<=DIGIT_RANGE; d++){
        current_sequence[pos] = d;
        backtrack(pos+1, len);
        if(result != -1) return;
    }
}

int main(){
    read_input();
    for(int len=1; len<=MAX_SEQUENCE_LEN; len++){
        backtrack(0, len);
        if(result != -1){
            printf("%d\n", result);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}