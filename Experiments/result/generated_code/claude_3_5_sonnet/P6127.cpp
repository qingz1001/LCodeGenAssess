#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 6
#define MAX_TERMS (1 << MAX_N)

int n;
bool truth_table[MAX_TERMS];
char result[1000];
int result_len;

void generate_term(int term, char* buf) {
    int len = 0;
    for (int i = 0; i < n; i++) {
        if (term & (1 << i)) {
            buf[len++] = 'a' + i;
        } else {
            buf[len++] = '!';
            buf[len++] = 'a' + i;
        }
        if (i < n - 1) buf[len++] = '&';
    }
    buf[len] = '\0';
}

void add_to_result(const char* term) {
    if (result_len > 0) {
        result[result_len++] = '|';
    }
    strcpy(result + result_len, term);
    result_len += strlen(term);
}

void simplify() {
    char terms[MAX_TERMS][MAX_N * 2 + 1];
    int term_count = 0;
    
    for (int i = 0; i < (1 << n); i++) {
        if (truth_table[i]) {
            generate_term(i, terms[term_count]);
            term_count++;
        }
    }
    
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < term_count; i++) {
            for (int j = i + 1; j < term_count; j++) {
                int diff_count = 0;
                int diff_pos = -1;
                for (int k = 0; k < n; k++) {
                    if (terms[i][k * 2] != terms[j][k * 2]) {
                        diff_count++;
                        diff_pos = k;
                    }
                }
                if (diff_count == 1) {
                    memmove(terms[i] + diff_pos * 2, terms[i] + diff_pos * 2 + 2, strlen(terms[i]) - diff_pos * 2 - 1);
                    memmove(terms[j], terms[j + 1], (term_count - j - 1) * sizeof(terms[0]));
                    term_count--;
                    j--;
                    changed = true;
                }
            }
        }
    } while (changed);
    
    for (int i = 0; i < term_count; i++) {
        add_to_result(terms[i]);
    }
}

int main() {
    scanf("%d", &n);
    
    char input[MAX_N + 2];
    for (int i = 0; i < (1 << n); i++) {
        scanf("%s", input);
        truth_table[i] = (input[n] == 'T');
    }
    
    simplify();
    
    printf("%s\n", result);
    
    return 0;
}