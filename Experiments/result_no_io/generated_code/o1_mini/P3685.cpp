#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HINTS 10
#define MAX_HINT_LEN 9
#define MAX_SEQUENCE 15

typedef struct {
    int digits[MAX_HINT_LEN];
    int length;
} Hint;

int n;
Hint hints[MAX_HINTS];

// Function to check if a single hint is satisfied by the sequence
int is_hint_satisfied(char *S, int len, Hint *h) {
    for(int i=0;i<len;i++) {
        // Try going right from position i
        int seen[10] = {0};
        int temp[MAX_HINT_LEN];
        int k = 0;
        for(int j=i; j<len && k < h->length; j++) {
            int d = S[j] - '0';
            if(!seen[d]) {
                temp[k++] = d;
                seen[d] = 1;
            }
        }
        if(k == h->length) {
            int match = 1;
            for(int m=0; m<h->length; m++) {
                if(temp[m] != h->digits[m]) {
                    match = 0;
                    break;
                }
            }
            if(match) return 1;
        }
        // Try going left from position i
        memset(seen, 0, sizeof(seen));
        k = 0;
        for(int j=i; j>=0 && k < h->length; j--) {
            int d = S[j] - '0';
            if(!seen[d]) {
                temp[k++] = d;
                seen[d] = 1;
            }
        }
        if(k == h->length) {
            int match = 1;
            for(int m=0; m<h->length; m++) {
                if(temp[m] != h->digits[m]) {
                    match = 0;
                    break;
                }
            }
            if(match) return 1;
        }
    }
    return 0;
}

// Function to check if all hints are satisfied
int all_hints_satisfied(char *S, int len) {
    for(int i=0;i<n;i++) {
        if(!is_hint_satisfied(S, len, &hints[i])) return 0;
    }
    return 1;
}

// Recursive backtracking function
int backtrack(char *S, int len, int target_len) {
    if(len == target_len) {
        if(all_hints_satisfied(S, len)) return 1;
        return 0;
    }
    for(char d='1'; d<='9'; d++) {
        S[len] = d;
        if(backtrack(S, len+1, target_len)) return 1;
    }
    return 0;
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        hints[i].length = 0;
        while(1){
            int x;
            scanf("%d", &x);
            if(x == 0) break;
            hints[i].digits[hints[i].length++] = x;
        }
    }
    char S[MAX_SEQUENCE+1];
    S[MAX_SEQUENCE] = '\0';
    int found = 0;
    for(int l=1; l<=MAX_SEQUENCE && !found; l++) {
        if(backtrack(S, 0, l)) {
            printf("%d\n", l);
            found = 1;
            break;
        }
    }
    if(!found) printf("-1\n");
    return 0;
}