#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_A 10005
#define MAX_N 4

typedef struct {
    int count;
    int positions[MAX_A];
    int length;
} Substring;

char A[MAX_A];
Substring substrings[MAX_N];
int N;
unsigned char coverage[MAX_A];
int min_ans, max_ans;

void copy_coverage(unsigned char *dest, unsigned char *src) {
    memcpy(dest, src, MAX_A);
}

int count_coverage(unsigned char *cov) {
    int cnt = 0;
    for(int i = 0; i < strlen(A); i++) {
        if(cov[i]) cnt++;
    }
    return cnt;
}

void backtrack(int idx, unsigned char *cov, int *current_min, int *current_max) {
    if(idx == N){
        int cnt = count_coverage(cov);
        if(cnt < *current_min) *current_min = cnt;
        if(cnt > *current_max) *current_max = cnt;
        return;
    }
    for(int i = 0; i < substrings[idx].count; i++){
        unsigned char new_cov[MAX_A];
        copy_coverage(new_cov, cov);
        int pos = substrings[idx].positions[i];
        for(int j = 0; j < substrings[idx].length; j++){
            if(A[pos + j] != '\0'){
                new_cov[pos + j] = 1;
            }
        }
        backtrack(idx + 1, new_cov, current_min, current_max);
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%s", A);
        scanf("%d", &N);
        for(int i = 0; i < N; i++){
            char B[MAX_A];
            scanf("%s", B);
            substrings[i].count = 0;
            substrings[i].length = strlen(B);
            int lenA = strlen(A);
            int lenB = substrings[i].length;
            for(int j = 0; j <= lenA - lenB; j++){
                if(strncmp(&A[j], B, lenB) == 0){
                    substrings[i].positions[substrings[i].count++] = j;
                }
            }
        }
        min_ans = strlen(A);
        max_ans = 0;
        unsigned char initial_cov[MAX_A];
        memset(initial_cov, 0, sizeof(initial_cov));
        backtrack(0, initial_cov, &min_ans, &max_ans);
        printf("%d %d\n", min_ans, max_ans);
    }
    return 0;
}