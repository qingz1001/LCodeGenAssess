#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 501

char input[MAX_LEN];
int len;
int best_split[MAX_LEN];
int curr_split[MAX_LEN];
int best_split_count = 0;
int curr_split_count = 0;

long long str_to_num(int start, int end) {
    char temp[MAX_LEN];
    strncpy(temp, input + start, end - start + 1);
    temp[end - start + 1] = '\0';
    return atoll(temp);
}

int compare_splits() {
    if (curr_split_count < best_split_count) return 1;
    if (curr_split_count > best_split_count) return 0;
    
    for (int i = 0; i < curr_split_count; i++) {
        if (curr_split[i] > best_split[i]) return 1;
        if (curr_split[i] < best_split[i]) return 0;
    }
    return 0;
}

void update_best_split() {
    best_split_count = curr_split_count;
    for (int i = 0; i < curr_split_count; i++) {
        best_split[i] = curr_split[i];
    }
}

void solve(int start, long long prev) {
    if (start == len) {
        if (compare_splits()) {
            update_best_split();
        }
        return;
    }
    
    long long curr = 0;
    for (int end = start; end < len; end++) {
        curr = curr * 10 + (input[end] - '0');
        if (curr <= prev) continue;
        
        curr_split[curr_split_count++] = end;
        solve(end + 1, curr);
        curr_split_count--;
        
        if (input[start] == '0') break;
    }
}

int main() {
    scanf("%s", input);
    len = strlen(input);
    
    solve(0, 0);
    
    int start = 0;
    for (int i = 0; i < best_split_count; i++) {
        printf("%.*s", best_split[i] - start + 1, input + start);
        if (i < best_split_count - 1) printf(",");
        start = best_split[i] + 1;
    }
    printf("\n");
    
    return 0;
}