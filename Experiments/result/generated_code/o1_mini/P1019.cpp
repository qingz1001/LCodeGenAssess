#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_LEN 21

int n;
char words[MAX_N][MAX_LEN];
int len_word[MAX_N];
int can_connect[MAX_N][MAX_N];
int overlap[MAX_N][MAX_N];
char start_char;
int max_length = 0;

// Function to check if a is a substring of b
int is_substring(char *a, char *b) {
    return strstr(b, a) != NULL;
}

// Function to compute maximum overlap between a's suffix and b's prefix
int compute_overlap(char *a, char *b, int len_a, int len_b) {
    int max_k = 0;
    int k;
    for(k = 1; k <= len_a && k <= len_b; k++) {
        if(strncmp(a + len_a - k, b, k) == 0) {
            max_k = k;
        }
    }
    return max_k;
}

// DFS function
void dfs(int last, unsigned long long used, int total) {
    if(total > max_length) {
        max_length = total;
    }
    for(int j = 0; j < n; j++) {
        if(can_connect[last][j]) {
            int cnt = (used >> (2 * j)) & 3;
            if(cnt < 2) {
                // Update used
                unsigned long long new_used = used + (1ULL << (2 * j));
                // Update total length
                int new_total = total + (len_word[j] - overlap[last][j]);
                // Recurse
                dfs(j, new_used, new_total);
            }
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i =0;i<n;i++) {
        scanf("%s", words[i]);
        len_word[i] = strlen(words[i]);
    }
    scanf(" %c", &start_char);
    
    // Precompute can_connect and overlap
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(i == j){
                // Can connect to itself
                can_connect[i][j] = 1;
                overlap[i][j] = compute_overlap(words[i], words[j], len_word[i], len_word[j]);
            }
            else{
                // Check if neither is a substring of the other
                if(!is_substring(words[i], words[j]) && !is_substring(words[j], words[i])) {
                    can_connect[i][j] = 1;
                    overlap[i][j] = compute_overlap(words[i], words[j], len_word[i], len_word[j]);
                }
                else{
                    can_connect[i][j] = 0;
                    overlap[i][j] = 0;
                }
            }
        }
    }
    
    // Iterate through all starting words
    for(int i=0;i<n;i++) {
        if(words[i][0] == start_char) {
            unsigned long long used = 0;
            used += (1ULL << (2 * i));
            dfs(i, used, len_word[i]);
        }
    }
    
    printf("%d\n", max_length);
    return 0;
}