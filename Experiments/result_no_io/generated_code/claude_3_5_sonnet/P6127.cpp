#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 6
#define MAX_STATES (1 << MAX_N)

int n;
char truth_table[MAX_STATES][MAX_N + 1];
char result[1000000];
int result_len = 0;

void generate_minterm(int state) {
    int first = 1;
    for (int i = 0; i < n; i++) {
        if (!first) {
            result[result_len++] = '&';
        }
        if (truth_table[state][i] == 'F') {
            result[result_len++] = '!';
        }
        result[result_len++] = 'a' + i;
        first = 0;
    }
}

void solve() {
    int first = 1;
    for (int state = 0; state < (1 << n); state++) {
        if (truth_table[state][n] == 'T') {
            if (!first) {
                result[result_len++] = '|';
            }
            generate_minterm(state);
            first = 0;
        }
    }
    result[result_len] = '\0';
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < (1 << n); i++) {
        scanf("%s", truth_table[i]);
    }
    
    solve();
    printf("%s\n", result);
    
    return 0;
}